#pragma once
#include "CPlayer.h"
#include "Networking.h"

class CConnectionHandler {
public:
	virtual void onDisconnect(CPlayer* connection) = 0;
	virtual void onConnectionError(CPlayer* connection, SocketResult result) = 0;

};
