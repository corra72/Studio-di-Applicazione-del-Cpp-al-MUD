#include "CMudHandler.hpp"

int main()
{
	CMudHandler handler=CMudHandler("Nebbie.ini");
	handler.run();
	CSocket* conn = new CSocket();
	CPlayer player(conn, &handler);
	try {
		player.save();
		player.load("Data.bin");
		cout << "Everything went allright!\n";
	}
	catch (const char* exMsg) {
		cout << "I've got an exception!\n";
		cerr << exMsg;
		return -1;
	}
	catch (...) {
		cout << "I've got an untrapped exception!\n";
	}
	return 0;
}

