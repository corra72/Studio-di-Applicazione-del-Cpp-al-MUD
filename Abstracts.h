#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "structs.h"
#include "Enumerators.h"

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
* semplice classe che [dovrebbe] fa[re] una sola cosa: verificare se l'oggetto è il target
* di un'azione, ovvero se le sue keywords sono compatibili con quelle richieste
*
* Devo ancora pensare come sviluppare bene il concetto, quindi non odiarmi :p
*/

extern class CEquipment;
extern class CCharacter;
extern class CRoom;

class CTargettable {
protected:
    string Keywords;
public:
    CTargettable(string keywords);

    // Meglio averle già spezzettate, visto che l'operazione di spezzettamento costicchia
    bool isTarget(std::vector<string> &keywords);

    // Ricordati sempre di distruggere tutti i puntatori nel distruttore
    ~CTargettable();
};

class CInventoryObject {
protected:
    /*
    * Per prima cosa, questa è una variabile, non un puntatore.
    * Sta nella sezione protected, vuol dire che è vista da tutte le classi figlie, ma non
    * da altre classi; accederemo ai suoi dati in altro modo;
    *
    */
    list<CEquipment*> Inventory = list<CEquipment*>();

public:

    list<CEquipment*>::iterator find(std::vector<string>& keywords);

    CEquipment* moveFromList(CInventoryObject& source, list<CEquipment*>::iterator &itemIter);
    CEquipment* moveToList(CInventoryObject& destination, list<CEquipment*>::iterator &itemIter);

    ~CInventoryObject();
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
