#include <fstream>
#include "CPlayer.hpp"


CPlayer::CPlayer(CSocket *clientSocket, IConnectionHandler *owner) :
	Connection{clientSocket},
	Owner(owner)
{
	State = ConnectionState::CONN_CONNECTING;
	currentCharacter = NULL;
}

CPlayer::~CPlayer()
{
	if (Connection != NULL)
		delete Connection;
}

ConnectionState CPlayer::getState()
{
	return State;
}

SocketResult CPlayer::sendMessage(string &message)
{
	return Connection->send(message);
}

string CPlayer::receive()
{
	try {
		return Connection->receive();
	} catch(SocketResult sr) {
		// Normalmente il catch cattura una eccezione, ma qui sembra che sia più flessibile
		// Se arrivo qui vuol dire che, per qualche motivo c'è stato un problema di connessione
		// quindi, disconnetto!
		bool handled = false;
		// Qui mi aspetto che la connessione (quindi la classe CPlayer) venga rimossa dalla lista
		Owner->onConnectionError(this, sr, handled);
		// Come dicevo gli oggetti devono gestirsi da soli, quindi è compito di CPlayer quello di
		// chiudere la connessione ed eventualmente inviare un messaggio di errore.
		Connection->disconnect();
		return "";
	}
	// TODO: inserire l'istruzione return qui
}

SocketResult CPlayer::disconnect()
{
	Connection->disconnect();
	bool handled = false;
	Owner->onDisconnect(this, handled);
	return SocketResult::R_DISCONNECTED;
}

IOOperationResult CPlayer::save()
{
	if (currentCharacter != NULL) {
		// chiede a currentCharacter di popolare e ritornare la struttura tempData
		// NOTA MOLTO IMPORANTE: tempData è una struttura interna a currentCharacter, quindi
		// alla fine delle operazioni non hai bisogno di chiamare il delete! Anzi, se lo chiami
		// rischi il crash, perché tempData non è creata al volo ma è sempre attiva dentro
		// a currentCharacter
		struct char_file_u* tempData = currentCharacter->prepareForSave();
		if (tempData == NULL)
			throw "unexpected invalid save request! Are you trying to save a MOB as if it were a player?";
		// currentCharacter->ShortDesc contiene il nome del file
		ofstream myFile("Data.bin", ios::out | ios::binary);
		myFile.write((char*)&PC_HEADER, sizeof(PC_HEADER));
		myFile.write((char*)&PC_VER, sizeof(PC_VER));
		// Qui ci metti il codice per salvare effettivamente i dati
		myFile.write((char *)tempData, sizeof(char_file_u));
		myFile.close();
	}
	return IOOperationResult::SUCCEEDED;
}

IOOperationResult CPlayer::load(const char *fileName)
{
	uint32_t tempInt=-1;

	ifstream is(fileName, ios::in | ios::out | ios::binary);
	is.read((char*)&tempInt, sizeof(tempInt));
	if (tempInt == PC_HEADER) {
		// se siamo qui sappiamo che è un file del tipo corretto
		struct char_file_u* tempData = new char_file_u;
		is.read((char*)&tempInt, sizeof(tempInt));
		switch (tempInt) {
		case PC_VER:
			is.read((char*)tempData, sizeof(char_file_u));
			if (is)
				std::cout << "all characters read successfully.";
			else {
				cerr << "error: i could read only " << is.gcount() << " of " << sizeof(char_file_u) << " required";
				return IOOperationResult::F_CORRUPTEDFILE;
			}
			break;
		default:
			delete tempData;
			return IOOperationResult::F_UNKNOWVERSION;
		}

		/* OKKIO! Qui ho messo la procedura semplificata! Nella realtà l'ownership di
		* CCharacter dovrebbe essere del CMUDHandler non di CPlayer, quindi dovrebbe essere
		* responsabilità di CMUDHandler chiamare il delete
		*/
		if (currentCharacter != NULL)
			delete currentCharacter;

		/*
		* Di nuovo, quando crei CCharacter, devi prima consultare CMUDHandler (nel caso il character sia già in gioco) e, 
		* la procedura di allocazione dovrebbe essere delegata a CMUDHandler che si occupa anche di mettere il character
		* in gioco;
		* 
		* Qui semplifico perché non ho tutta la struttura di gestione del gioco, invece mi interessa vedere come si può
		* fare per far funzionare il versioning
		*/
		currentCharacter = new CCharacter(tempData);

	}
	else 
	{
		return IOOperationResult::F_ILLEGALFILETYPE;
	}

	return IOOperationResult::SUCCEEDED;
}

