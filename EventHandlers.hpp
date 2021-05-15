#pragma once
#include "structs.h"
#include "Enumerators.hpp"
#include "Networking.hpp"
#include "Abstracts.hpp"

/*
* nota tecnica: le classi puramente virtuali in altri linguaggi sono chiamate "interfacce"; in 
* c++ non hai le interfacce, ne' hai la necessità di avverle. Tuttavia, per maggiore chiarezza,
* inizierò a chiamare le classi puramente virtuali (senza metodi definiti e senza proprieta) interfacce
* ed i loro nomi inizieranno per I
* 
*/

/*
* Nota tecnica: per gestire gli eventi ci sono vari modelli: io qui userò un modello che è 
* quello di Java semplificato; perché Java? Perché tornerà molto utile nella definizione
* delle procedure speciali!
*/


/*
* I metodi che iniziano per onXXX sono metodi che vengono chiamati quando un certo evento accade.
* I campi vengono definiti in base all'oggetto che viene chiamato, ma ogni metodo ha obbligatoriamente
* due campi: 
*  - caller, è l'oggetto che ha inviato l'evento
*  - handled un booleano che diventa vero se una chiamata della catena ha gestito definitivamente l'evento; 
*    questo interrompe la catena (non credo che lo userai, ma è sempre meglio avercelo).
*/
class IDestroyableHandler {
	virtual void onReceiveDamage(CDestroyable* caller, CMUDObject* source, bool& handled) = 0;
	virtual void onDestroyed(CDestroyable* caller, bool& handled) = 0;
};

class IConnectionHandler {
public:
	virtual void onDisconnect(CPlayer* connection, bool& handled) = 0;
	virtual void onConnectionError(CPlayer* connection, SocketResult result, bool& handled) = 0;
};