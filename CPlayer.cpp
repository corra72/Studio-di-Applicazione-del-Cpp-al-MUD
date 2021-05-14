#include "CPlayer.h"


CPlayer::CPlayer(CSocket *clientSocket, IConnectionHandler* owner) :
	Connection{clientSocket},
	Owner(owner)
{
	State = ConnectionState::CONN_CONNECTING;
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

