#pragma once

// Flag per il danno
const unsigned IS_WEAPON = 0x0001;
const unsigned IS_SPELL = 0x0002;
const unsigned HAS_KI = 0x0004; // per i monaci e barbari

const __int32_t PC_HEADER = 'N' + ('A' << 8) + ('P' << 16) + ('C' << 24);
const __int32_t PC_VER = 0;

const __int32_t EQ_HEADER = 'N' + ('A' << 8) + ('E' << 16) + ('Q' << 24);
const __int32_t EQ_VER = 0;
