#pragma once
#include <string>
#include <list>

using namespace std;

enum class ESearchType {
	// valore di default; counter viene considerato un semplice indice
	hasCounter,
	// indica che si vogliono molti oggetti; ogni volta che si trova un 
	// oggetto idoneo ritorna true (vale solo per target di tipo CEquipment)
	getMultiple,
	// indica che si vogliono tutti gli oggetti che rispondono alla richiesta 
	// (vale solo per target di tipo CEquipment)
	getAll
};

/*
* CTarget è una classe concreta usata nella dichiarazione di molte classi astratte. Potevo
* mettela in Abstract.h, ma, alla fine, ritengo sia più utile averla qui.
* 
* Ricorda, una delle cose più importanti della programmazione orientata agli oggetti è che ti
* costringe a tenere le cose in ordine.
*/

class CQuery {
public:

	/*
	* indica come comportarsi con il contatore
	*/
	ESearchType type = ESearchType::hasCounter;
   
	/*
	* con getMultiple = true, indica il numero degli oggetti su cui applicare la richiesta
	* con getMultiple = false, è l'indice dell'oggetto da recuperare;
	* 
	* NOTA: volento si potrebbe passare un valore fisso, tipo 0 o MAX_INT invece di avere 
	* un flag getAll, è una scelta come un'altra, ma, per evitare confusione, in questo momento
	* preferisco andare con il flag; poi lo implementi come vuoi
	*/
	int counter=1;

	/*
	* lista di keywords da leggere; uso una lista perché ha un iteratore che, in teoria, è
	* molto più veloce di una ricerca per indice in una array; lo so che ci sono trucchi, ma,
	* con i compilatori moderni che ottimizzano il codice da soli, i trucchi non solo sono
	* inutili, ma possono diventare anche pericolosi. Conoscerli va bene, ma è meglio usare
	* gli strumenti appropriati per evitare bug difficili da individuare ed i relativi crash
	*/
	list<string> keywords();

	/*
	* quello che fa l'inzializzatore è semplicemente prendere una stringa, parsarla, e compilare
	* i campi. Per default counter = 1 se un altro valore non viene specificato; 
	*/
	CQuery(string targetString) {
		// TO DO: qui ci va il codice per parsare la stringa del target

	};

	/*
	* in realtà la logica di questa funzione può essere delegata alla funzione find() di CInventoryItem,
	* ma avere la logica di questa funzione in un unico posto è sempre meglio!
	* 
	* keywords è una stringa che contiene la porola chiave dell'oggetto che si sta esaminando,
	* strict indica se le keywords devono essere identiche o basta l'inizio;
	* 
	* se c'è un match, ci sono 3 possibili comportamenti:
	* se è getAll, allora ritorna true;
	* se è getMultiple allora ritorna true finché il counter è > 0, inoltre decrementa il counter
	* se è hasCounter allora decrementa il counter finché è > 1 ma ritorna true solo quando il counter è 1
	*/
	bool test(string targetKeywords, bool strict) {
		// TO DO: qui ci va la stringa per verificare se le keyword di questo oggetto sono
		// incluse in targetKeywords
		return false;
	};

};
