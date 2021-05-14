#pragma once
#include <string>
#include "Abstracts.h"
#include "Enumerators.h"
#include "Networking.h"
#include "EventHandlers.h"
#include "CCharacter.h"

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
    IConnectionHandler* Owner = NULL;

    CSocket* Connection = NULL;
    ConnectionState State = ConnectionState::CONN_CONNECTING;

public:


    string userID; // nome di login
    CCharacter* currentCharacter;

    CPlayer(CSocket* clientSocket, IConnectionHandler* owner);

    // Letteralmente ti dice in quale stato di gioco ti trovi in questo momento
    ConnectionState getState();

    // Invia un messaggio sul socket; questo messaggio dovrebbe arrivare al player
    SocketResult sendMessage(string &message);

    string receive();

    SocketResult disconnect()
    {
        Connection->disconnect();
        bool handled = false;
        Owner->onDisconnect(this, handled);
        return SocketResult::R_DISCONNECTED;
    }
};

