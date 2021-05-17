#pragma once
#include "structs.h"
#include "Abstracts.hpp"

class CCharacter : public CDestroyable {
private:
    struct char_file_u *saveData = NULL;

public:

    CCharacter(int vNum, string desc, string keywords, int hp);

    CCharacter(char_file_u *PCdata);

    virtual int save(ostream& out);;

    virtual int load(istream& in);;

    struct char_file_u* prepareForSave();

    virtual MudDestroyableState receiveDamage(CDestroyable& source, Damage& dam);

    virtual MudDestroyableState repairDamage(CDestroyable& source, Damage& dam);

    ~CCharacter();

};


