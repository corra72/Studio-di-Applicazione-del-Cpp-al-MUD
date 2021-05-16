#pragma once
#include <string>
#include "const.h"
#include "Abstracts.hpp"
#include "Enumerators.hpp"
#include "Networking.hpp"
#include "EventHandlers.hpp"
#include "CCharacter.hpp"

/*
* La classe CPlayer è l'interfaccia fra il giocatore ed il MUD. Tutta la parte che riguarda
* il metagioco viene gestita qui!
* 
* Il menu iniziale è gestito da CPlayer
* 
*/



using namespace std;

class CPlayer {
private: 
    IConnectionHandler *Owner;

    CSocket *Connection;
    ConnectionState State = ConnectionState::CONN_CONNECTING;

public:


    string userID; // nome di login
    CCharacter* currentCharacter;

    CPlayer(CSocket *clientSocket, IConnectionHandler *owner);
    virtual ~CPlayer();

    // Letteralmente ti dice in quale stato di gioco ti trovi in questo momento
    virtual ConnectionState getState();

    // Invia un messaggio sul socket; questo messaggio dovrebbe arrivare al player
    virtual SocketResult sendMessage(string &message);

    virtual string receive();

    virtual int save();
    virtual int load(const char *fileName);

    SocketResult disconnect();

};

