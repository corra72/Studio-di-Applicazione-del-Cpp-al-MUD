#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "structs.h"
#include "Enumerators.hpp"
#include "CQuery.hpp"

using namespace std;

class CMUDObject {

public:
    int VNUM;
    string ShortDesc;
    MudObjectType Type;

    CMUDObject(int vNum, MudObjectType type, string desc) :
        VNUM{ vNum },
        Type{ type },
        ShortDesc{ desc }
    {}

    /*
    *
    * save salva i dati su disco; cosa fa dipende dal tipo di oggetto con cui stai
    * lavorando e probabilmente l'ambito
    */

    virtual int save(ostream& out) = 0;

    /*
    *
    * load carica i dati dal disco; cosa fa dipende dal tipo di oggetto con cui stai
    * lavorando e probabilmente l'ambito
    */

    virtual int load(istream& in) = 0;

    virtual ~CMUDObject() {
    }

};


/*

* Forward declaration di un po' di classi; Purtroppo in questo momento è necessario averle
* perché le classi fanno riferimento le une alle altre; dopo vedo se esistono soluzioni più
* eleganti
*/
class IConnectionHandler;
class CEquipment;
class CCharacter;
class CRoom;
class CPlayer;


/*
* semplice classe che [dovrebbe] fa[re] una sola cosa: verificare se l'oggetto è il target
* di un'azione, ovvero se le sue keywords sono compatibili con quelle richieste
*
* CQuery è l'oggetto che contiene le informazioni con cui devi confrontarti. Visto che
* CQuery ha già una funzione per il test, isTarget in teoria è inutile, e puoi bypassarla (
* la sostituisci con CQuery.test(Keywords); e ti risparmi una chiamata a funzione; a meno che
* tu non voglia implementare per alcune classi figlie una logica speciale su isTarget, ovviamente!
* 
* Puoi anche fare il contrario, ovvero spostare la logica di CQuery::test() in isTarget, ma visto che
* test() si occupa di modificare i valori interni di CQuery, probabilmente è meglio mantenere il
* confronto in questa classe
* 
* Nota che entrambe le classi verranno usate in CInventoryObject per trovare gli oggetti che
* rispondono alla query
*/
class CTargettable {
public:
    string Keywords;

    CTargettable(string keywords);

    // Meglio averle già spezzettate, visto che l'operazione di spezzettamento costicchia
    bool isTarget(CQuery &reqKeywords);

    // Ricordati sempre di distruggere tutti i puntatori nel distruttore
    ~CTargettable();
};


/*
* CInventory Object si occupa di mantenere a medio livello una lista di oggetti e di farci 
* delle semplici query sopra. CQuery è un oggetto che contiene una lista di keywords da
* confrontare con le keyword degli oggetti di CTargettable
* 
* find e findNext trovano oggetti che rispondono alla richiesta di CQuery
* 
* get estrae un oggetto trovato da una delle funzion find dalla lista e lo ritorna per altri usi
* 
* put mette un oggetto dentro la lista
* 
* A parte find, c'è bisogno delle altre funzioni? In teoria no, ma ti fanno da interfaccia con le
* funzione di basso livello del compilatore. Se preferisci usare direttamente le funzion di
* std::list<>, accomodati, personalmente preferisco rendere più chiare le operazioni usando
* questa interfaccia, anche se si aggiunge un po' di overhead; ma almeno sei sicuro che, 
* quando chiami la funzione, sai cosa sta succedendo e che l'utilizzo è uguale in ogni
* situazione.
* 
* Questa è una implementazione molto diretta. Se sei coraggioso puoi provare ad implementare indici 
* (aka tabelle hash o tree) per velocizzare gli accessi, ma, probabilmente non hai un reale vantaggio 
* in questa classe; gli indici è meglio implementarli in contenitori globali come CMudHandler
* per comandi come portal o send, o anche una teleport che usa la shortDesc della room, se hai voglia
* di provarci
*/
class CInventoryObject {
// protected vuol dire che le classi figlie possono avere accesso diretto a questa variabile
// useremo questa capacità in CRoom
protected:
    // list è una variabile, non un puntatore; preferisci evitare i puntatori quando possibile;
    // ti risparmierai un sacco di mali di testa!
    list<CTargettable*> Inventory=list<CTargettable*>();
public:
    /*
    * trova l'iteratore che punta all'elemento che risponde alla richeista
    */
    virtual list<CTargettable*>::iterator find(CQuery& keywords);
    /*
    * usato per richieste multiple, cerca in prossimo elemento che soddisfra la richiesta
    */
    virtual list<CTargettable*>::iterator findNext(list<CTargettable*>::iterator iter, CQuery& keywords);
    /*
    * !!RIMUOVE!! l'elemento specificato dall'inventario; devi metterlo da qualche altra parte o 
    * distruggerlo, altrimenti ti trovi con un puntatore fluttuante
    */
    virtual CTargettable* get(list<CTargettable*>::iterator &itemIter);
    /*
    * mette un elemento nell'inventario
    */
    virtual void put(CTargettable* item);

    virtual ~CInventoryObject();
};


/*
* questa classe è virtuale; ti serve solo come punto di raccordo fra
* Mobile e Equipment
*
* Incidentalmente CDestroyable è anche targettable
*/
class CDestroyable : public CMUDObject, public CTargettable {
protected:
    int HP;
    int CurrHP;
    MudDestroyableState State;
public:
    CDestroyable(int vNum, MudObjectType type, string desc, string keywords, int HP);

    virtual MudDestroyableState getState();
    virtual int getHP();

    virtual MudDestroyableState receiveDamage(CDestroyable &source, Damage &dam) = 0;
    virtual MudDestroyableState repairDamage(CDestroyable &source, Damage &dam) = 0;
};
