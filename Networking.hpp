#pragma once

#ifdef __unix__
	#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>
	#define socket SOCKET
#endif


#include<string>

using namespace std;



/*
* Ok, visto che OGNI CAVOLO DI SISTEMA OPERTIVO ha delle diverse classi per la gestione
* del networking, ed a noi non interessa scrivere 10 versioni di codice che possano essere
* compilate su 10 diversi sistemi, creo due classi fantoccio che hanno le funzioni che
* ci servono e che si occupano loro di gestire la connessione a basso livello!
*/

enum class SocketResult {
	R_OK,
	R_FAIL,
	R_DISCONNECTED
};

class CSocket {
protected:

public:
	CSocket() {
	}

	~CSocket() {
	}

	// Riceve una stringa dal socket
	string &receive() {
		// Normalmente qui avresti la funzione che ti ritorna una stringa letta dal socket
		// ma visto che non c'è socket, lancia un'eccezione che ti farà crashare il MUD
		// se non la gestisci correttamente.
		throw SocketResult::R_DISCONNECTED;
	}

	// Invia un messaggio al socket
	SocketResult send(string &message) {
		return SocketResult::R_DISCONNECTED;
	
	}

	// chuide la connessione al socket
	SocketResult disconnect() {
		return SocketResult::R_DISCONNECTED;

	}

};


class CListener {
public:
	
	// Il porto di connessione TCP
	int Port;

	// Qui inizializzi lo
	CListener(int port) : 
		Port{ port } 
	{
	}

	CSocket *listen() {
		return new CSocket();
	}

	// Chiude il listener
	SocketResult close() {
		return SocketResult::R_OK;
	}

};