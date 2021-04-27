#include "CPlayer.h"


CPlayer::CPlayer(CSocket *clientSocket, CConnectionHandler *owner) :
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
		Owner->onDisconnect(this);
		Connection->disconnect();
		return "";
	}
	// TODO: inserire l'istruzione return qui
}

