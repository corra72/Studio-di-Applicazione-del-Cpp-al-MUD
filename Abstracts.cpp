#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "Abstracts.hpp"
#include "CEquipment.hpp"


using namespace std;

CTargettable::CTargettable(string keywords) {
    if (keywords[0] != ' ')
        Keywords = " " + keywords;
    else
        Keywords = keywords;
}

bool CTargettable::isTarget(CQuery& reqKeywords) {
    return reqKeywords.test(Keywords, false);
}


CTargettable::~CTargettable() {
}


list<CTargettable*>::iterator CInventoryObject::find(CQuery& keywords) {
    
    for (list<CTargettable*>::iterator iter = this->Inventory.begin(); iter != Inventory.end(); ++iter) {
        if ((*iter)->isTarget(keywords)) {
            return iter;
        }
    }
    return Inventory.end();
}

list<CTargettable*>::iterator CInventoryObject::findNext(list<CTargettable*>::iterator iter, CQuery& keywords)
{
    for (; iter != Inventory.end(); ++iter) {
        if ((*iter)->isTarget(keywords)) {
            return iter;
        }
    }
    return Inventory.end();
}

CTargettable* CInventoryObject::get(list<CTargettable*>::iterator &itemIter) {
    if (itemIter != Inventory.end()) {
        // DA TESTARE; in teoria sposta l'iteratore al prossimo elemento della lista
        // prima di rimuovere l'elemento corrente; in teoria l'iteraotre all'esterno
        // dovrebbe essere ancora valido e puntare al nuovo elemento, invece che puntare
        // ad un elemento fantasma; da verificare se erase ha chiamato il distruttore
        // di curr!
        list<CTargettable*>::iterator curr = itemIter;
        itemIter++;
        CTargettable* result = *curr;
        Inventory.erase(curr);
        return result;
    }
    return NULL;
}

void CInventoryObject::put(CTargettable* item)
{
    if(item!=NULL)
        Inventory.push_back(item);
}

CInventoryObject::~CInventoryObject() 
{
    // Vuotiamo la lista nel distruttore.
    while (!Inventory.empty()) {
        CTargettable *item = Inventory.front();
        Inventory.pop_front();
        delete item;
    }
}

CDestroyable::CDestroyable(int vNum, MudObjectType type, string desc, string keywords, int HP) :
    CMUDObject{ vNum, type , desc }, CTargettable{ keywords }
{
    this->HP = HP;
    this->CurrHP = HP;
}


MudDestroyableState CDestroyable::getState()
{
    return State;
}

int CDestroyable::getHP() {
    return HP;
};