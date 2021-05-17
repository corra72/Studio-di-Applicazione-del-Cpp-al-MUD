#pragma once
#include <cstdint>
#include "const.hpp"
#include "Enumerators.hpp"

/*
* Se non hai bisogno di classi, puoi comunque continuare ad usare le stutture
*/

struct Damage {
    int Damage;
    MudDamageType Type;
    unsigned flags;
    int MagicPower; // 0 per oggetti non magici, +1 per armi +1 e così via;
                    // In teoria dovresti categorizzare anche le spell in questo 
                    // di solito un MOB che è immune ad armi +3 è anche immune
                    // a spell di 3^ circolo tipo 'Lightning Bolt' e 'Fireball'
};


/* Used in CHAR_FILE_U *DO*NOT*CHANGE* */
struct char_skill_data {
	uint8_t learned;           /* % chance for success 0 = not learned   */

	/* change to int or long */
	uint8_t flags;             /* SKILL KNOWN? bit settings               */
	uint8_t special;           /* spell/skill specializations             */
	uint8_t nummem;            /* number of times this spell is memorized */
};



/* Used in CHAR_FILE_U *DO*NOT*CHANGE* */
struct affected_type {
	short type;           /* The type of spell that caused this      */
	int16_t duration;      /* For how long its effects will last      */
	int modifier;       /* This is added to apropriate ability     */
	int location;        /* Tells which ability to change(APPLY_XXX)*/
	int bitvector;       /* Tells which bits to set (AFF_XXX)       */
	struct affected_type* next;
};

struct affected_type_u { // To be only used in file definition,
	short type;           /* The type of spell that caused this      */
	int16_t duration;      /* For how long its effects will last      */
	int modifier;       /* This is added to apropriate ability     */
	int location;        /* Tells which ability to change(APPLY_XXX)*/
	int bitvector;       /* Tells which bits to set (AFF_XXX)       */
	int next;
};

struct char_ability_data {
	int8_t str;
	int8_t str_add;      /* 000 - 100 if strength 18             */
	int8_t intel;
	int8_t wis;
	int8_t dex;
	int8_t con;
	int8_t chr;
	int8_t extra;
	int8_t extra2;
};


/* Used in CHAR_FILE_U *DO*NOT*CHANGE* */
struct char_point_data {
	int16_t mana;
	int16_t max_mana;
	uint8_t  mana_gain;

	int16_t hit;
	int16_t max_hit;      /* Max hit for NPC                         */
	uint8_t  hit_gain;

	int16_t move;
	int16_t max_move;     /* Max move for NPC                        */
	uint8_t move_gain;
	uint16_t pRuneDei;  /* SALVO extra1 lo uso per le rune da 0 a 65535*/

	int16_t extra1;  /* extra stuff */
	int16_t extra2;
	uint8_t extra3;

	int16_t armor;        /* Internal -100..100, external -10..10 AC */
	int gold;            /* Money carried                           */
	int bankgold;        /* gold in the bank.                       */
	int exp;             /* The experience of the player            */
	int true_exp;        /* gonna be used for dual class            */
	int extra_dual;      /* case I need an extra duall class bit    */


	int8_t hitroll;       /* Any bonus or penalty to the hit roll    */
	int8_t damroll;       /* Any bonus or penalty to the damage roll */

	int8_t libero;       /* SALVO ex pQuest torna libero*/
};

struct char_file_u {
	int iClass;
	int8_t sex;
	int8_t level[ABS_MAX_CLASS];
	unsigned int birth;  /* Time of birth of character     */
	int played;    /* Number of secs played in total */
	int   race;
	unsigned int weight;
	unsigned int height;
	char title[80];
	char extra_str[255];
	int16_t hometown;
	char description[240];
	bool talks[MAX_TOUNGE];
	int extra_flags;
	int16_t load_room;            /* Which room to place char in  */
	struct char_ability_data abilities; // No pointers inside, same size on 32 and 64 bit
	struct char_point_data points; // No pointers inside, same size on 32 and 64 bit
	struct char_skill_data skills[MAX_SKILLS]; // No pointers inside, same size on 32 and 64 bit
	struct affected_type_u affected[MAX_AFFECT];
	/* specials */
	uint8_t spells_to_learn;
	int alignment;
	unsigned int affected_by;
	unsigned int affected_by2;
	unsigned int last_logon;  /* Time (in secs) of last logon */
	unsigned int    act;        /* ACT Flags                    */

	/* char data */
	char name[20];
	char authcode[7];  /* codice di autorizzazione */
	char WimpyLevel[4]; /* Wimpy level */
	char dummy[19];      /* per usi futuri */
	char pwd[11];
	int16_t apply_saving_throw[MAX_SAVES];
	int conditions[MAX_CONDITIONS];
	int startroom;  /* which room the player should start in */
	int user_flags;        /* no-delete,use ansi,etc... */
	int speaks;                /* language currently speakin in */
	int agemod;
};
