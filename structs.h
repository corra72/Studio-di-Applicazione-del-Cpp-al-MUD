#pragma once
#include "Enumerators.hpp"

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
