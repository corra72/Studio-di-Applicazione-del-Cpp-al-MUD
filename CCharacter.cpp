#include "CCharacter.hpp"

CCharacter::CCharacter(int vNum, string desc, string keywords, int hp) :
	CDestroyable{ vNum, MudObjectType::MOBILE, desc, keywords, hp }
{}

CCharacter::CCharacter(char_file_u* PCdata) : 
	CDestroyable{ -1, MudObjectType::MOBILE, "", "", 0 },
	saveData{ PCdata }
{
	if(PCdata==NULL)
		throw "Invalid null pointer in CCharacter creation!";

}

CCharacter::~CCharacter()
{
	if(saveData != NULL)
		delete saveData;
}

inline int CCharacter::save(ostream& out) {
	return -1;
}

inline int CCharacter::load(istream& in) {
	return -1;
}

struct char_file_u* CCharacter::prepareForSave() {
	/*
	* no, non è così semplice, altrimenti non avrei reso la variabile privata e non avrei creato questa funzione; per prima
	* cosa devi preparare saveData con tutti i dati che ti servono per salvarla su disco (ad esempio gli apply); io non lo faccio
	* perché non ho una versione che va live, ma mi serve per poter testare i salvataggi.
	* 
	* in realtà, quando la struttura ad oggetti sarà prevalente, probabilmente non avrai bisogno di fare queste cose, perché, 
	* al contrario delle strutture, saveData conterrà già i dati live, mentre ora viene popolata solo quando devi salvare
	*/
	return saveData;
}

MudDestroyableState CCharacter::receiveDamage(CDestroyable& source, Damage& dam) {
	// do something
	State = MudDestroyableState::FINE;
	return State;
}

MudDestroyableState CCharacter::repairDamage(CDestroyable& source, Damage& dam) {
	// do something

	State = MudDestroyableState::FINE;
	return State;
}

