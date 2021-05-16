#pragma once
#include <iostream>
#include <string>
#include "Abstracts.hpp"

using namespace std;

class CEquipment : public CDestroyable {
public:

    CEquipment(int vNum, string desc, string keywords, int HP) :
        CDestroyable{ vNum, MudObjectType::OBJECT, desc, keywords, HP}
    {

    }

    virtual int save(ostream& out);

    virtual int load(istream& in);

    virtual MudDestroyableState receiveDamage(CDestroyable &source, Damage &dam);
    virtual MudDestroyableState repairDamage(CDestroyable &source, Damage &dam);

};
