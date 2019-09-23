#include "images/sprites/sprites.h"
#include "images/images.h"
#include "gba.h"

extern volatile OamEntry shadow[];
extern const int MC_SWING[];
extern const int MC_SHOOT[];
extern const int MC_DIE[];
extern const int SPRITE_ALL[];

#define MC_SWING_LENGTH 4
#define MC_SHOOT_LENGTH 4
#define MC_DIE_LENGTH 5
#define SPRITE_ALL_LENGTH 16
#define MC_RIGHT 5
#define MC_STAND 4
#define ARROW 13
#define GOD 14
#define WASP 12
#define FIREBALL 15
#define BOSS1 11
#define BOSS2 10
#define MC_HIT 8
#define MC_JUMP 6
#define FRAME_DELAY 2
#define ANIMATION_DELAY 5
#define GRAVITY 2

#define MC_STARTX 26
#define MC_STARTY 30
#define GOD_STARTX 104
#define GOD_STARTY 3
#define RINGX 0
#define RINGY 50
#define ENTERX 206
#define ENTERY 125
#define CLEARX 206
#define CLEARY 92
#define S0X 50
#define S0Y 45
#define S1X 50
#define S1Y 85
#define S2X 50
#define S2Y 125
#define S3X 205
#define S3Y 127
#define RIDDLEX 16
#define RIDDLEY 12
#define BOSS_STARTX 104
#define BOSS_STARTY 40

#define ARROW_HW 16
#define BOSS_HW 32

#define ISINSIDE(x1, w1, x2, w2) (((x2) + (w2) > (x1) && (x2) + (w2) < (x1) + (w1)) || ((x1) + (w1) > (x2) && (x1) + (w1) < (x2) + (w2)) || ((x1) >= (x2) && (x1) + (w1) <= (x2) + (w2)) || ((x2) >= (x1) && (x2) + (w2) <= (x1) + (w1)))
#define ISCOLLIDE(x1, y1, w1, h1, x2, y2, w2, h2) (ISINSIDE(x1, w1, x2, w2) && ISINSIDE(y1, h1, y2, h2))
