#include "CEquipment.hpp"

int CEquipment::save(ostream& out)
{
    return 0;
}

int CEquipment::load(istream& in)
{
    return 0;
}

MudDestroyableState CEquipment::receiveDamage(CDestroyable &source, Damage &dam) {
    // do something
    HP -= dam.Damage;

    State = MudDestroyableState::FINE;
    return State;
}

MudDestroyableState CEquipment::repairDamage(CDestroyable &source, Damage &dam) {
    // do something
    HP += dam.Damage;

    State = MudDestroyableState::FINE;
    return State;
}
