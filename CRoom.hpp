#pragma once
#include "Abstracts.hpp"

/*
* L'oggetto CRoom è il primo definito; contiene tutti i dati che ti servono per gestire
* una stanza
*/

class CRoom : public CMUDObject {
public:
    CRoom(int vNum, string desc) :
        CMUDObject{ vNum, MudObjectType::ROOM , desc }
    {

    }

    ~CRoom() {
    }

};

