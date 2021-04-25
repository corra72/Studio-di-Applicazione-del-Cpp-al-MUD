#include <iostream>
#include <string>
#include <thread> 
#include <list>
#include <vector>
using namespace std;

/*
* 
* Questo enumeratore ti serve per categorizzare gli oggetti, di modo da poter sapere
* controllando il valore di Type se stai lavorando con una stanza, un mob on 
* oggetto. Ho levato le procedure get e set per ID, visto che è più veloce agire
* direttamente sulle variabili; ma, se lavori con le strutture, forse vorrai quelle
* procedure
* 
*/

enum class MudObjectType {
    ROOM,
    MOBILE,
    OBJECT
};

/*
* Questo enumeratore ti serve per tenere traccia dello stato di un oggetto
* che può essere danneggiato; per i mobile ci sarebbero anche gli stati
* RIDING, SITTING, STANDING, SLEEPING, UNCONSCIOUS, DIEING;
*/

enum class MudDestroyableState {
    FINE,
    DAMAGED,
    HEAVILY_DAMAGED,
    DESTROYED
};

class CMUDObject {

public:
    int VNUM;
    string ShortDesc;
    MudObjectType Type;

    CMUDObject(int vNum, MudObjectType type, string desc) :
        VNUM { vNum },
        Type{ type },
        ShortDesc{ desc }
    {}

    /* 
    * 
    * save salva i dati su disco; cosa fa dipende dal tipo di oggetto con cui stai
    * lavorando e probabilmente l'ambito
    */

    virtual int save(ostream out) = 0;

    /*
    *
    * load carica i dati dal disco; cosa fa dipende dal tipo di oggetto con cui stai
    * lavorando e probabilmente l'ambito
    */

    virtual int load(istream in) = 0;

    virtual ~CMUDObject() {
    }

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

    CEquipment* find(string keywords[]) {
        for (list<CEquipment*>::iterator iter = Inventory.begin(); iter != Inventory.end(); ++iter) {
            if ((*iter)->isTarget(keywords)) {
                return *iter;
            }
        }
        return NULL;

    }

    CEquipment* moveFromList(CInventoryObject source, CEquipment* item) {

        for (list<CEquipment*>::iterator iter = source.Inventory.begin(); iter != source.Inventory.end(); ++iter) {
            if (*iter == item) {
                Inventory.splice(Inventory.begin(), source.Inventory, iter);
                return item;
            }
        }

        return NULL;
    }

    CEquipment* moveToList() {
        return NULL;
    }

    ~CInventoryObject() {
        // Vuotiamo la lista nel distruttore.
        while (!Inventory.empty()) {
            CEquipment* item = Inventory.front();
            Inventory.pop_front();
            delete item;
        }
    }

};

/*
* L'oggetto CRoom è il primo definito; contiene tutti i dati che ti servono per gestire 
* una stanza
*/

class CRoom : public CMUDObject {
public:
    CRoom(int vNum, string desc) : 
        CMUDObject{vNum, MudObjectType::ROOM , desc}
    {
    
    }

    ~CRoom() {
    }

};


enum class MudDamageType {
    // Physical
    BLUNT,
    SLASH,
    PIERCE,

    // Non physical
    FIRE,
    COLD,
    ELECTRICITY,
    SOUND,
    RADIATION,  // attacchi basati sulla luce
    FORCE,
    MAGIC,      // magia pura
    GRAVITY,    // attacchi basati sulla gravità, o, se preferisci, attacchi basati sullo spazio
    TIME,       // attacchi basati sul tempo, tipo HASTE, SLOW e PARALYZE, l'attuale HOLD per capirci

    POISON,

    CHARM,      // tecnicamente charm contiene pure sleep e confuse, perché sono attacchi mentali

    PSYCHIC,

    HOLY,       // non so perché lo vuoi chiamare radiant
    UNHOLY,     // non capisco perché necrotic; cmq questo contiene anche lo spell CURSE
};

const unsigned IS_WEAPON = 0x0001;
const unsigned IS_SPELL  = 0x0002;
const unsigned HAS_KI    = 0x0004; // per i monaci e barbari


/*
* Se non hai bisogno di classi, puoi comunque continuare ad usare le stutture
*/

struct Damage {
    int Damage;
    MudDamageType Type;
    unsigned flags;
    int MagicPower; // 0 per oggetti non magici, +1 per armi +1 e così via;
                    // In teoria dovresti categorizzare anche le spell in questo 
                    // di solito un MOB che è immune ad armi +3 è anche immune
                    // a spell di 3^ circolo tipo 'Lightning Bolt' e 'Fireball'
};

/*
* semplice classe che [dovrebbe] fa[re] una sola cosa: verificare se l'oggetto è il target
* di un'azione, ovvero se le sue keywords sono compatibili con quelle richieste
* 
* Devo ancora pensare come sviluppare bene il concetto, quindi non odiarmi :p
*/

class CTargettable {
protected:
    string* Keywords;
public:
    CTargettable(string keywords) {
        stringstream ss(keywords);
        list<string> words;
        for (string w; ss >> w; ) words.push_back(w);
        Keywords = new string[words.size()];
        int k = 0;
        for (string w : words) {
            Keywords[k++] = w;
        }
    }

    // Meglio averle già spezzettate, visto che l'operazione di spezzettamento costicchia
    bool isTarget(string Keywords[]) {
        return false;
    }

    // Ricordati sempre di distruggere tutti i puntatori nel distruttore
    ~CTargettable() {
        delete Keywords;
    }
};


/*
* questa classe è virtuale; ti serve solo come punto di raccordo fra
* Mobile e Equipment
* 
* Incidentalmente CDestroyable è anche CTargettable; in teoria potevo inserire
* il codice di CTargettable in questa classe, ma in questo modo posso riusare
* quella parte anche per quelle classi che non sono oggetti del MUD (ad esempio
* le extra description)
*/
class CDestroyable : public CMUDObject, public CTargettable {
protected:
    int HP;
    MudDestroyableState State;
public:
    CDestroyable(int vNum, MudObjectType type, string desc, string keywords) :
        CMUDObject{ vNum, type , desc }, CTargettable{ keywords }
    {
    }
        
    virtual MudDestroyableState getState() { return State; }

    virtual MudDestroyableState receiveDamage(CDestroyable source, Damage dam) = 0;
    virtual MudDestroyableState repairDamage(CDestroyable source, Damage dam) = 0;
};


class CCharacter : public CDestroyable {

public:

    CCharacter(int vNum, string desc, string keywords) :
        CDestroyable{ vNum, MudObjectType::MOBILE, desc, keywords }
    {

    }

    virtual int save(ostream out) {
        return -1;
    };

    virtual int load(istream in) {
        return -1;
    };

    virtual MudDestroyableState receiveDamage(CDestroyable source, Damage dam) {
        // do something
        State = MudDestroyableState::FINE;
        return State;
    }

    virtual MudDestroyableState repairDamage(CDestroyable source, Damage dam) {
        // do something

        State = MudDestroyableState::FINE;
        return State;
    }

};

class CEquipment : public CDestroyable {
public:

    CEquipment(int vNum, string desc, string keywords) :
        CDestroyable{ vNum, MudObjectType::OBJECT, desc, keywords }
    {

    }

    virtual int save(ostream out) {
        return -1;
    };

    virtual int load(istream in) {
        return -1;
    };

    virtual MudDestroyableState receiveDamage(CDestroyable source, Damage dam) {
        // do something
        HP -= dam.Damage;

        State = MudDestroyableState::FINE;
        return State;
    }

    virtual MudDestroyableState repairDamage(CDestroyable source, Damage dam) {
        // do something
        HP += dam.Damage;

        State = MudDestroyableState::FINE;
        return State;
    }

};

class CPlayer : public thread {
public:
    string userID; // nome di login
    CCharacter currentCharacter;

};

int main()
{
}
