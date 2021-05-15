#pragma once
#include <thread>
#include <string>
#include "Abstracts.hpp"
#include "Networking.hpp"
#include "EventHandlers.hpp"
#include "CRoom.hpp"
#include "CEquipment.hpp"
#include "CCharacter.hpp"
#include "CPlayer.hpp"

using namespace std;


/*
* Ok, abbiamo le classi base, ora dobbiamo metterle all'opera, non credi?
* Quindi ci serve una classe che gestisca l'applicazione vera e porpria.
* 
* Ho chiamato la class MudHandler, Mud perché è il MUD vero e proprio, Handler
* perché si occuperà della gestione degli eventi.
* 
* Ora, vediamo di capire COSA gestisce esattamente.
* 
* La prima cosa che ci metterò dentro sono delle liste degli oggetti reali
* 
* Allora, non ho idea di come il MUD gestisca la cosa, ma da come la vedo io,
* da una parte hai i prototipi (quelli che leggi dal file delle aree) e dall'altra
* hai gli oggetti reali che vengono caricati da quei prototipi.
* 
*/


/*
* public CConnectionHandler
* Uno dei modi in cui si possono gestire gli eventi è creare classi puramente virtuali con i metodi
* da chiamare (handlers o listeners) ed far ereditare queste classi agli attuali oggetti che
* gestiranno gli eventi (in questo caso CMudHandler gestisce gli eventi di connessione)
*/

class CMudHandler : public IConnectionHandler {
protected:
	list<CPlayer*> ConnectedPlayers;
public:
	CMudHandler(string configFile);
	~CMudHandler();
	

	int run();

	// Ereditato tramite IConnectionHandler
	virtual void onDisconnect(CPlayer* connection, bool& handled) override;
	virtual void onConnectionError(CPlayer* connection, SocketResult result, bool& handled) override;
};
