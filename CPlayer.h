#pragma once
#include <string>
#include <thread>
#include "CCharacter.h"
#include "Abstracts.h"
#include "Enumerators.h"
#include "Networking.h"
#include "EventHandlers.h"
#include "CMudHandler.h"

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
    CSocket *Connection;
    ConnectionState State;


public:

    CConnectionHandler *Owner;

    string userID; // nome di login
    CCharacter* currentCharacter;

    CPlayer(CSocket *clientSocket, CConnectionHandler *owner);

    // Letteralmente ti dice in quale stato di gioco ti trovi in questo momento
    ConnectionState getState();

    // Invia un messaggio sul socket; questo messaggio dovrebbe arrivare al player
    SocketResult sendMessage(string &message);

    string receive();

    SocketResult disconnect()
    {
        return SocketResult::R_DISCONNECTED;
    }

};

