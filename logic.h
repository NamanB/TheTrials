#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"
#include "myLib.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    NORM,
    SWING,
    SHOOT,
    DEAD,
} Action;

typedef enum {
    // Location enum
    HOME,
    RIDDLE_ROOM,
    OUTDOORS
} Location;

typedef struct {
    int x;
    int y;
    int dy;
    int health;
    volatile OamEntry *oam;
    Action a;
    bool facingRight;
    int animateC;
    int svBlankCounter;
    bool hasRing;
    u16 *ring;
    int ringCount;
} MC;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int health;
    bool facingRight;
    bool isActive;
    volatile OamEntry *oam;
} Entity;

typedef struct {
    bool isActive;
    u16 *image;
} Select;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;

    Location location;
    Location lastLocation;
    int locEventCount;
    bool stateUpdate;
    bool showQuestion;
    MC mc;
    Entity god;
    Entity boss;
    Entity wasp;
    Entity arrow;
    Select s0;
    Select s1;
    Select s2;
    Select s3;
    Select clear;
    Select enter;
    int ansIndex;
    char ans[5];
    bool help;
    // Use union to make individual struct designs for the different entities
    // Entity *entities[];
    // int numEntities;
} AppState;


// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
