#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "Abstracts.h"
#include "CEquipment.h"

using namespace std;

CTargettable::CTargettable(string keywords) {
    if (keywords[0] != ' ')
        Keywords = " " + keywords;
    else
        Keywords = keywords;
}

bool CTargettable::isTarget(std::vector<string> &keywords) {
    for (string s : keywords) {
        // No, non è chiaro, ma, praticamente, questo si può tradurre
        // nell'equivalente unsigned di Keywords.find(s) == -1;
        // -1 unsigned è il massimo possibile valore per la variabile
        if (Keywords.find(s) == std::string::npos)
            return false;
    }
    return true;
}


CTargettable::~CTargettable() {
}


list<CEquipment*>::iterator CInventoryObject::find(std::vector<string>& keywords) {
    for (list<CEquipment*>::iterator iter = Inventory.begin(); iter != Inventory.end(); ++iter) {
        if ((*iter)->isTarget(keywords)) {
            return iter;
        }
    }
    return Inventory.end();
}

CEquipment* CInventoryObject::moveFromList(CInventoryObject &source, list<CEquipment*>::iterator &itemIter) {
    Inventory.splice(Inventory.begin(), source.Inventory, itemIter);
    return *itemIter;
}

CEquipment* CInventoryObject::moveToList(CInventoryObject& destination, list<CEquipment*>::iterator &itemIter)
{
    Inventory.splice(destination.Inventory.begin(), Inventory, itemIter);
    return *itemIter;
}

CInventoryObject::~CInventoryObject()
{
    // Vuotiamo la lista nel distruttore.
    while (!Inventory.empty()) {
        CEquipment* item = Inventory.front();
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