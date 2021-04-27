
#include <string>
#include "CMudHandler.h"

CMudHandler::CMudHandler(string configFile)
{
	ConnectedPlayers = list<CPlayer *>();
}

CMudHandler::~CMudHandler() {
	while (!ConnectedPlayers.empty()) {
		CPlayer* item = ConnectedPlayers.front();
		item->disconnect();
		ConnectedPlayers.pop_front();
		delete item;
	}
}


int CMudHandler::run() {
	/* to do... gestisce il thread principale dell'applicazione. In questo caso si 
	* limita ad uscire subito, ma in realtà dovrebbe esserci un ciclo while(true) da cui
	esci solo al reboot
	*/
	CListener listener = CListener(8080);

	try {
		while (true) {
			listener.listen();
			break;
		}
	}
	catch (exception) {
		return 1;
	}
	return 0;
}

void CMudHandler::onConnectionError(CPlayer* connection, SocketResult result)
{
}

/*
* Quando ricevi l'evento Disconnect, rimuovi la connessione dalla lista delle connessioni attive
*
*/

void CMudHandler::onDisconnect(CPlayer* connection) 
{
	ConnectedPlayers.remove(connection);
	// Non sono sicuro che questo delete sia necessario, sarebbe da fare qualche test
	delete connection;
}




