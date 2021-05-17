#pragma once


/* Differenza fra #define e const:
* #define viene sostituito prima di iniziare la compilazione con il valore indicato; non è una variabile o una funzione, ma semplicemente
* un testo che viene cercato e sostituito
* 
* const definisce una costante, una locazione di memoria su cui non puoi scrivere, ma che puoi leggere ed usare in altre funzioni
* 
* il valore di un #define non può essere cambiato dall'applicazione ma solo ricompilando
* lo stesso è per il valore di una const, ma una const può sempre essere cambiata in un tipo variabile se vuoi poter
* configurare alcuni parametri durante l'esecuzione; ovviamente, quando hai a che fare con strutture fisse, come quelle
* di salvataggio, teoricamente è più prudente usare il #define
* 
*/
#define	ABS_MAX_CLASS                                20
#define	MAX_TOUNGE                                   3
#define	MAX_SKILLS                                   350
#define	MAX_AFFECT                                   40
#define	MAX_SAVES                                    8
#define	MAX_CONDITIONS                               5

// Flag per il danno
// potrebbero essere cambiati in #define
const unsigned IS_WEAPON = 0x0001;
const unsigned IS_SPELL = 0x0002;
const unsigned HAS_KI = 0x0004; // per i monaci e barbari


/* perché gli header non possono essere cambiati in #define?
* innanzitutto gli header ed i ver li scrivi nel file, e per farlo ti serve poter accedere ad un puntatore a questi
* dati; in secondo luogo li header sono delle funzioni; in pratica, se fossero dei #define, ogni vola che li usi dovresti
* ricalclarti il valore, sprecando preziosi cicli di macchina (anche se relativamente pochi, ma devi comunque moltiplicarlo 
* per il  numero di file che salvi); essendo costanti, la funzione viene eseguita una sola volta alla dichirazione
* 
* se devi usare un valore costante che è il risulato di una funzione (purché ovviamente non cambi nel tempo), allora usa
* sempre le costant per risparmiare cicli di macchina!
* anche #define 1 << 12, per quanto sia una delle operazioni più veloci che si possono fare, è comunque una operazione in più
* che ti fa sprecare cicli di macchina che potresti impiegare per altro!
*/
const int32_t PC_HEADER = 'N' + ('A' << 8) + ('P' << 16) + ('C' << 24);
const int32_t PC_VER = 0;

const int32_t EQ_HEADER = 'N' + ('A' << 8) + ('E' << 16) + ('Q' << 24);
const int32_t EQ_VER = 0;
