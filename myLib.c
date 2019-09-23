#include "myLib.h"

volatile OamEntry shadow[128];
const int MC_SWING[4] = {0, 1, 1, 5};
const int MC_SHOOT[4] = {7, 7, 2, 2};
const int MC_DIE[5] = {8, 8, 9, 9, 3};
const int SPRITE_ALL[16] = {MC4_ID, MC5_ID, MC7_ID, MC10_ID, MC1_ID, MC2_ID, MC3_ID, MC6_ID, MC8_ID, MC9_ID, BOSS2_ID, BOSS1_ID, WASP_ID, ARROW_ID, GOD_ID, FIREBALL_ID};
