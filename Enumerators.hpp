#pragma once


enum class ConnectionState {
    CONN_CONNECTING,       // primo stato, quando invia la schermata iniziale e chiede lo UserID
    CONN_VERIFY,        // secondo stato, quando richiede la password

    DISCONNECTING,      // Quando si sta disconnettendo
    
    MNU_MAIN,           // Menu principale, quello con la scelta di entrare in gioco, cambiare PG e così via
    
    MNU_CREATION_XXX    // Vari stati di creazione del PG, scegli tu cosa metterci

};

/*
*
* Questo enumeratore ti serve per categorizzare gli oggetti, di modo da poter sapere
* controllando il valore di Type se stai lavorando con una stanza, un mob on
* oggetto. Ho levato le procedure get e set per ID, visto che è più veloce agire
* direttamente sulle variabili; ma, se lavori con le strutture, forse vorrai quelle
* procedure
*
*/

enum class MudObjectType {
    ROOM,
    MOBILE,
    OBJECT
};

/*
* Questo enumeratore ti serve per tenere traccia dello stato di un oggetto
* che può essere danneggiato; per i mobile ci sarebbero anche gli stati
* RIDING, SITTING, STANDING, SLEEPING, UNCONSCIOUS, DIEING;
*/

enum class MudDestroyableState {
    FINE,
    DAMAGED,
    HEAVILY_DAMAGED,
    DESTROYED
};


enum class MudDamageType {
    // Physical
    BLUNT,
    SLASH,
    PIERCE,

    // Non physical
    FIRE,
    COLD,
    ELECTRICITY,
    SOUND,
    RADIATION,  // attacchi basati sulla luce
    FORCE,
    MAGIC,      // magia pura
    GRAVITY,    // attacchi basati sulla gravità, o, se preferisci, attacchi basati sullo spazio
    TIME,       // attacchi basati sul tempo, tipo HASTE, SLOW e PARALYZE, l'attuale HOLD per capirci

    POISON,

    CHARM,      // tecnicamente charm contiene pure sleep e confuse, perché sono attacchi mentali

    PSYCHIC,

    HOLY,       // non so perché lo vuoi chiamare radiant
    UNHOLY,     // non capisco perché necrotic; cmq questo contiene anche lo spell CURSE
};
