#pragma once
#include <thread>

using namespace std;

class CPlayer : public thread {
public:
    string userID; // nome di login
    CCharacter* currentCharacter;

};

