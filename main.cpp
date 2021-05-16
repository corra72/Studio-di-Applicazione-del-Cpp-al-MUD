#include "CMudHandler.hpp"

int main()
{
	CMudHandler handler=CMudHandler("Nebbie.ini");
	handler.run();
	CSocket* conn = new CSocket();
	CPlayer player(conn, &handler);

	player.save();
	player.load("Data.bin");
}

