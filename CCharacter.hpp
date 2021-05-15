#pragma once
#include "Abstracts.hpp"

class CCharacter : public CDestroyable {

public:

    CCharacter(int vNum, string desc, string keywords, int hp) :
        CDestroyable{ vNum, MudObjectType::MOBILE, desc, keywords, hp }
    {

    }

    virtual int save(ostream& out) {
        return -1;
    };

    virtual int load(istream& in) {
        return -1;
    };

    virtual MudDestroyableState receiveDamage(CDestroyable& source, Damage& dam) {
        // do something
        State = MudDestroyableState::FINE;
        return State;
    }

    virtual MudDestroyableState repairDamage(CDestroyable& source, Damage& dam) {
        // do something

        State = MudDestroyableState::FINE;
        return State;
    }

};


