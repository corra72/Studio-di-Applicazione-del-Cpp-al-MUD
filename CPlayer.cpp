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

int CPlayer::save()
{
	//if (currentCharacter != NULL) {
		// currentCharacter->ShortDesc contiene il nome del file
		fstream myFile("Data.bin", ios::out | ios::binary);
		myFile.write((char*)&PC_HEADER, sizeof(PC_HEADER));
		myFile.write((char*)&PC_VER, sizeof(PC_VER));
		// Qui ci metti il codice per salvare effettivamente i dati
		myFile.close();
	//}
	return 0;
}

int CPlayer::load(const char *fileName)
{
	UINT32 tempInt=-1;

	fstream myFile(fileName, ios::in | ios::out | ios::binary);
	myFile.read((char*)&tempInt, sizeof(tempInt));
	if (tempInt == PC_HEADER) {
		// se siamo qui sappiamo che è un file del tipo corretto
		myFile.read((char*)&tempInt, sizeof(tempInt));
		switch (tempInt) {
		case PC_VER:
			// qui metti la procedura per leggere la versione corrente del file
			break;
		default:
			cout << "Unknown file version: " << tempInt;
		}

	
	}
	else 
	{
		cout << "Illegal file type";
	}

	return 0;
}

