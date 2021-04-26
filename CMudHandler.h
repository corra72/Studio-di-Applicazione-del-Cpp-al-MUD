#pragma once
#include <thread>
#include "Abstracts.h"
#include "CRoom.h"
#include "CEquipment.h"
#include "CCharacter.h"

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

class CMudHandler : public thread {
	
	CMudHandler();
	~CMudHandler();

};