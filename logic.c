#include "logic.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->gameOver = 0;
    appState->location = HOME;
    appState->lastLocation = HOME;
    appState->locEventCount = 0;
    appState->stateUpdate = true;
    appState->showQuestion = false;
    appState->god = (Entity) {GOD_STARTX, GOD_STARTY, 0, 0, 100, false, true, &shadow[1]};
    appState->boss = (Entity) {0, 0, 0, 0, 10, false, false, &shadow[2]};
    appState->wasp = (Entity) {0, 0, 0, 0, 4, false, false, &shadow[3]};
    appState->arrow = (Entity) {0, 0, 2, 0, 1, false, false, &shadow[4]};
    appState->s0 = (Select) {false, (u16 *) select0};
    appState->s1 = (Select) {false, (u16 *) select1};
    appState->s2 = (Select) {false, (u16 *) select2};
    appState->s3 = (Select) {false, (u16 *) select3};
    appState->clear = (Select) {false, (u16 *) clear};
    appState->enter = (Select) {false, (u16 *) enter};

    appState->mc = (MC) {MC_STARTX, MC_STARTY, 0, 3, &shadow[0], NORM, true, 0, 0, false, (u16 *) ring1, 0};
    appState->mc.oam->attr2 = MC1_PALETTE_ID | MC1_ID;
    appState->mc.oam->attr1 = MC_STARTX | MC1_SPRITE_SIZE;
    appState->mc.oam->attr0 = MC_STARTY | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;

    appState->god.oam->attr2 = GOD_PALETTE_ID | GOD_ID;
    appState->god.oam->attr0 = GOD_STARTY | SPRITES_PALETTE_TYPE | GOD_SPRITE_SHAPE;
    appState->god.oam->attr1 = GOD_STARTX | GOD_SPRITE_SIZE;

    appState->ansIndex = 0;
    sprintf(appState->ans, "xxxx");
    appState->help = false;
}

void mcAnimation(volatile MC *mc, const int animation[], int animationLength) {
    if ((mc->animateC < animationLength) && (vBlankCounter - mc->svBlankCounter) % ANIMATION_DELAY == 0) {
        mc->oam->attr2 = MC1_PALETTE_ID | SPRITE_ALL[animation[mc->animateC]]; 
        mc->animateC++;
    }
}

void mcCollisionMovement(volatile MC *mc, AppState *state, int startx, int starty) {
    if (state->location == RIDDLE_ROOM) {
        if ((state->locEventCount == 10 && ISCOLLIDE(mc->x, mc->y, 32, 32, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT))
            || (state->enter.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT))
            || (state->clear.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, CLEARX, CLEARY, CLEAR_WIDTH, CLEAR_HEIGHT))) {
            mc->x = startx;
            mc->y = starty;
        }
    } else if (state->location == HOME) {
        if ((state->s0.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, S0X, S0Y, ENTER_WIDTH, ENTER_HEIGHT))
            || (state->s1.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, S1X, S1Y, ENTER_WIDTH, ENTER_HEIGHT))
            || (state->s2.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, S2X, S2Y, ENTER_WIDTH, ENTER_HEIGHT))) {
            mc->x = startx;
            mc->y = starty;
        }
    } else if (state->location == OUTDOORS && state->s3.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, S3X, S3Y, ENTER_WIDTH, ENTER_HEIGHT)) {
        mc->x = startx;
        mc->y = starty;
    }
    // Select s0;
    // Select s1;
    // Select s2;
    // Select s3;
    // Select clear;
    // Select enter;
    // if (state->s0.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, ENTERX, ENTERY, ENTER_WIDTH, ENTER_WIDTH)) {
    //     mc->x = start;
    // } else if (state->s1.isActive && ISCOLLIDE(mc->x, mc->y, 32, 32, ENTERX, ENTERY, ENTER_WIDTH, ENTER_WIDTH))
}

AppState arrowCollisionMovement(AppState nextAppState) {
    if (nextAppState.arrow.facingRight) {
        nextAppState.arrow.x = nextAppState.arrow.x + nextAppState.arrow.dx;
        nextAppState.arrow.oam->attr1 = nextAppState.arrow.x | ARROW_SPRITE_SIZE | ATTR1_NOFLIP;
    } else {
        nextAppState.arrow.x = nextAppState.arrow.x - nextAppState.arrow.dx;
        nextAppState.arrow.oam->attr1 = nextAppState.arrow.x | ARROW_SPRITE_SIZE | ATTR1_HFLIP;
    }
    nextAppState.arrow.oam->attr2 = ARROW_PALETTE_ID | SPRITE_ALL[ARROW];
    nextAppState.arrow.oam->attr0 = nextAppState.arrow.y | SPRITES_PALETTE_TYPE | ARROW_SPRITE_SHAPE;
    if (nextAppState.arrow.x < 0 || nextAppState.arrow.x > 240) {
        nextAppState.arrow.oam->attr0 = ATTR0_HIDE;
        nextAppState.arrow.isActive = false;
    } else if (nextAppState.location == RIDDLE_ROOM) {
        if ((nextAppState.locEventCount == 10 && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT))
            || (nextAppState.enter.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT)) 
            || (nextAppState.clear.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, CLEARX, CLEARY, CLEAR_WIDTH, CLEAR_HEIGHT))) {
            nextAppState.arrow.oam->attr0 = ATTR0_HIDE;
            nextAppState.arrow.isActive = false;
        }
    } else if (nextAppState.location == HOME) {
        if ((nextAppState.s0.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S0X, S0Y, ENTER_WIDTH, ENTER_HEIGHT))
            || (nextAppState.s1.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S1X, S1Y, ENTER_WIDTH, ENTER_HEIGHT))
            || (nextAppState.s2.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S2X, S2Y, ENTER_WIDTH, ENTER_HEIGHT))) {
            nextAppState.arrow.oam->attr0 = ATTR0_HIDE;
            nextAppState.arrow.isActive = false;
        }
    } else if (nextAppState.location == OUTDOORS && nextAppState.s3.isActive && ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S3X, S3Y, ENTER_WIDTH, ENTER_HEIGHT)) {
        nextAppState.arrow.oam->attr0 = ATTR0_HIDE;
        nextAppState.arrow.isActive = false;
    }
    return nextAppState;
}

void moveMCLR(AppState *state, volatile MC *mc, u32 keysNow, bool animate) {
    if (vBlankCounter % FRAME_DELAY != 0)
        return;
    int start = mc->x;
    if (KEY_DOWN(BUTTON_LEFT, keysNow)) {
        if (mc->x > 0) {
            mc->x--;
            mcCollisionMovement(mc, state, start, mc->y);
            mc->oam->attr1 = mc->x | MC1_SPRITE_SIZE | ATTR1_HFLIP;
            if (animate)
                mc->oam->attr2 = MC1_PALETTE_ID | SPRITE_ALL[MC_RIGHT];
            mc->facingRight = false;
        }
    } else if (KEY_DOWN(BUTTON_RIGHT, keysNow)) 
        if (mc->x < 240 - 22) {
            mc->x++;
            mcCollisionMovement(mc, state, start, mc->y);
            mc->oam->attr1 = mc->x | MC1_SPRITE_SIZE | ATTR1_NOFLIP;
            if (animate)
                mc->oam->attr2 = MC1_PALETTE_ID | SPRITE_ALL[MC_RIGHT];
            mc->facingRight = true;
        }
    if (animate && mc->x == start)
        mc->oam->attr2 = MC1_PALETTE_ID | SPRITE_ALL[MC_STAND];
}

void moveMCV(AppState *state, volatile MC *mc, u32 keysNow, int upper, int lower) {
    if (vBlankCounter % FRAME_DELAY != 0)
        return;
    int start = mc->y;
    if (mc->dy > 0) {
        mc->dy -= GRAVITY;
        mc->y += mc->dy;
    }
    if (KEY_DOWN(BUTTON_UP, keysNow) && mc->y > upper)
        mc->y--;
    else if (KEY_DOWN(BUTTON_DOWN, keysNow) && mc->y < lower) 
        mc->y++;
    mcCollisionMovement(mc, state, mc->x, start);
    mc->oam->attr0 = mc->y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
}

AppState mcAction(AppState nextAppState, u32 keysPressedNow, u32 keysPressedBefore) {
    switch (nextAppState.mc.a) {
        case DEAD:
            mcAnimation(&nextAppState.mc, MC_DIE, MC_DIE_LENGTH);
            if (nextAppState.mc.animateC > MC_SHOOT_LENGTH) {
                for(int i = 1; i < 128; i++)
                    shadow[i].attr0 = ATTR0_HIDE;
                nextAppState.gameOver = true;
            }
            break;
        case SHOOT:
            mcAnimation(&nextAppState.mc, MC_SHOOT, MC_SHOOT_LENGTH);
            moveMCLR(&nextAppState, &nextAppState.mc, keysPressedNow, false);
            if (nextAppState.mc.animateC == MC_SHOOT_LENGTH) {
                nextAppState.mc.a = NORM;
                if (!nextAppState.arrow.isActive) {
                    nextAppState.arrow.x = nextAppState.mc.x + 5;
                    nextAppState.arrow.y = nextAppState.mc.y + 13;
                    nextAppState.arrow.isActive = true;
                    nextAppState.arrow.facingRight = nextAppState.mc.facingRight;
                }
            }
            break;
        case SWING:
            mcAnimation(&nextAppState.mc, MC_SWING, MC_SWING_LENGTH);
            if (nextAppState.mc.animateC == MC_SWING_LENGTH) {
                nextAppState.mc.a = NORM;
            }
            moveMCLR(&nextAppState, &nextAppState.mc, keysPressedNow, false);
            break;
        case NORM:
            if (KEY_JUST_PRESSED(BUTTON_L, keysPressedNow, keysPressedBefore)) {
                nextAppState.mc.a = DEAD;
                nextAppState.mc.animateC = 0;
                nextAppState.mc.svBlankCounter = vBlankCounter - 1;
                mcAnimation(&nextAppState.mc, MC_DIE, MC_DIE_LENGTH);
                return nextAppState;
            }
            moveMCLR(&nextAppState, &nextAppState.mc, keysPressedNow, true);
            nextAppState.mc.oam->attr0 = nextAppState.mc.y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
            if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
                nextAppState.mc.a = SWING;
                nextAppState.mc.animateC = 0;
                nextAppState.mc.svBlankCounter = vBlankCounter;
            }
            if (KEY_JUST_PRESSED(BUTTON_R, keysPressedNow, keysPressedBefore) && !nextAppState.arrow.isActive) {
                nextAppState.mc.a = SHOOT;
                nextAppState.mc.animateC = 0;
                nextAppState.mc.svBlankCounter = vBlankCounter;
            }
    }
    if (nextAppState.locEventCount > 10 && KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
        nextAppState.showQuestion = !nextAppState.showQuestion;
        nextAppState.stateUpdate = true;
    }
    return nextAppState;
}

AppState processHome(AppState *state, u32 keysPressedBefore, u32 keysPressedNow) {
    AppState nextAppState = *state;
    
    switch (nextAppState.locEventCount) {
        case 0: 
            if (nextAppState.mc.x > 102) {
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
            } else if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
            }
        case 1: case 2: case 3: case 4:
            moveMCLR(&nextAppState, &nextAppState.mc, keysPressedNow, true);
            if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
                nextAppState.mc.svBlankCounter = vBlankCounter;
            }
            return nextAppState;
        case 5:
            if (nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1) {
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
            }
            break;
        case 6:
            if (nextAppState.mc.a == SHOOT && nextAppState.mc.animateC == MC_SHOOT_LENGTH - 1) {
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
            }
            break;
        case 7:
            if (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 32, 32, RINGX, RINGY, 16, 16)) {
                nextAppState.mc.ringCount++;
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
            }
            break;
        case 8:
            break;
        default:
            moveMCV(&nextAppState, &nextAppState.mc, keysPressedNow, 35, 160-32);
            break;
    }

    if (nextAppState.arrow.isActive) {
        nextAppState = arrowCollisionMovement(nextAppState);
        if (ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S0X, S0Y, ENTER_WIDTH, ENTER_HEIGHT) || 
            (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, S0X, S0Y, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1)) {
                nextAppState.ans[nextAppState.ansIndex] = '0';
                nextAppState.ansIndex = (nextAppState.ansIndex + 1) % 4;
                nextAppState.stateUpdate = true;
        }
        if (ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S1X, S1Y, ENTER_WIDTH, ENTER_HEIGHT) || 
            (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, S1X, S1Y, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1)) {
                nextAppState.ans[nextAppState.ansIndex] = '1';
                nextAppState.ansIndex = (nextAppState.ansIndex + 1) % 4;
                nextAppState.stateUpdate = true;
        }
        if (ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, S2X, S2Y, ENTER_WIDTH, ENTER_HEIGHT) || 
            (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, S2X, S2Y, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1)) {
                nextAppState.ans[nextAppState.ansIndex] = '2';
                nextAppState.ansIndex = (nextAppState.ansIndex + 1) % 4;
                nextAppState.stateUpdate = true;
        }
    }
    
    nextAppState = mcAction(nextAppState, keysPressedNow, keysPressedBefore);
    if (nextAppState.locEventCount > 6 && nextAppState.mc.x > 240-24) {
        nextAppState.showQuestion = false;
        nextAppState.mc.x = 1;
        nextAppState.mc.y = 105;
        nextAppState.mc.oam->attr1 = state->mc.x | MC1_SPRITE_SIZE;
        nextAppState.mc.oam->attr0 = nextAppState.mc.y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
        if (nextAppState.locEventCount < 10)
            nextAppState.locEventCount = 10;
        for(int i = 1; i < 128; i++)
            shadow[i].attr0 = ATTR0_HIDE;
        nextAppState.arrow.isActive = false;
        nextAppState.lastLocation = HOME;
        nextAppState.location = RIDDLE_ROOM;
    }
    return nextAppState;
}

AppState processRiddleRoom(AppState *state, u32 keysPressedBefore, u32 keysPressedNow) {
    AppState nextAppState = *state;
    
    if (!nextAppState.mc.hasRing && ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 32, 32, RINGX, RINGY, RING1_WIDTH, RING1_HEIGHT)) {
        nextAppState.mc.hasRing = true;
        nextAppState.mc.ringCount++;
        nextAppState.stateUpdate = true;
    }

    switch (nextAppState.locEventCount) {
        case 10: 
            if (ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT) || 
            (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1)) {
                nextAppState.arrow.oam->attr0 = ATTR0_HIDE;
                nextAppState.arrow.isActive = false;
                nextAppState.enter.isActive = true;
                nextAppState.locEventCount++;
                nextAppState.stateUpdate = true;
                nextAppState.clear.isActive = true;
                nextAppState.s0.isActive = true;
                nextAppState.s1.isActive = true; 
                nextAppState.s2.isActive = true;
                nextAppState.s3.isActive = true;
            }
            break;
        case 11:
            if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
                nextAppState.locEventCount++;
            }
            break;
        default:
            break;
    }

    if ((ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT) || 
        (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, ENTERX, ENTERY, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1))) {
            if (nextAppState.ans[0] == '2' && nextAppState.ans[1] == '0' && nextAppState.ans[2] == '2' && nextAppState.ans[3] == '0') {
                nextAppState.locEventCount = 100;
                nextAppState.stateUpdate = true;
                state->boss.isActive = true;
                state->boss.oam->attr2 = BOSS1_PALETTE_ID | BOSS1_ID;
                state->boss.oam->attr0 = BOSS_STARTY | SPRITES_PALETTE_TYPE | BOSS1_SPRITE_SHAPE;
                state->boss.oam->attr1 = BOSS_STARTX | BOSS1_SPRITE_SIZE;
            } else {
                nextAppState.stateUpdate = true;
                nextAppState.ans[0] = 'n';
                nextAppState.ans[1] = 'o';
                nextAppState.ans[2] = 'p';
                nextAppState.ans[3] = 'e';
            }
    }

    if (nextAppState.arrow.isActive) {
        nextAppState = arrowCollisionMovement(nextAppState);
    }

    if (ISCOLLIDE(nextAppState.arrow.x, nextAppState.arrow.y, ARROW_HW, ARROW_HW, CLEARX, CLEARY, ENTER_WIDTH, ENTER_HEIGHT) || 
        (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, CLEARX, CLEARY, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1)) {
            sprintf(nextAppState.ans, "xxxx");
            nextAppState.ansIndex = 0;
            nextAppState.stateUpdate = true;
    }
    
    if (nextAppState.mc.x > 80 && nextAppState.mc.x < 160 - 32) {
            moveMCV(&nextAppState, &nextAppState.mc, keysPressedNow, 45, 160-32);
    } else {
        moveMCV(&nextAppState, &nextAppState.mc, keysPressedNow, 105-32, 160-32);
    }
    
    nextAppState = mcAction(nextAppState, keysPressedNow, keysPressedBefore);
    if (nextAppState.locEventCount != 11) {
        if (nextAppState.mc.x < 1) {
            nextAppState.lastLocation = RIDDLE_ROOM;
            nextAppState.location = HOME;
            nextAppState.showQuestion = false;
            nextAppState.mc.x = 240 - 25;
            state->mc.oam->attr1 = state->mc.x | MC1_SPRITE_SIZE;
            nextAppState.mc.y = 35;
            nextAppState.mc.oam->attr0 = nextAppState.mc.y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
            for(int i = 1; i < 128; i++)
                shadow[i].attr0 = ATTR0_HIDE;
            nextAppState.arrow.isActive = false;
        }
        if (nextAppState.mc.y >= 160-32 && nextAppState.mc.x >= 65 && nextAppState.mc.x <= 150 && KEY_DOWN(BUTTON_DOWN, keysPressedNow)) {
            nextAppState.lastLocation = RIDDLE_ROOM;
            nextAppState.location = OUTDOORS;
            nextAppState.showQuestion = false;
            nextAppState.mc.y = 75;
            nextAppState.mc.oam->attr0 = nextAppState.mc.y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
            for(int i = 1; i < 128; i++)
                shadow[i].attr0 = ATTR0_HIDE;
            nextAppState.arrow.isActive = false;
        }
    }
    return nextAppState;
}

AppState processOutside(AppState *state, u32 keysPressedBefore, u32 keysPressedNow) {
    AppState nextAppState = *state;

    if (ISCOLLIDE(nextAppState.mc.x, nextAppState.mc.y, 33, 33, S3X, S3Y, ENTER_WIDTH, ENTER_HEIGHT) && nextAppState.mc.a == SWING && nextAppState.mc.animateC == MC_SWING_LENGTH - 1) {
        nextAppState.help = true;
        nextAppState.stateUpdate = true;
    }

    if (nextAppState.arrow.isActive) {
        nextAppState = arrowCollisionMovement(nextAppState);
    }

    moveMCV(&nextAppState, &nextAppState.mc, keysPressedNow, 75, 160-32);
    nextAppState = mcAction(nextAppState, keysPressedNow, keysPressedBefore);

    if (nextAppState.mc.x >=65 && nextAppState.mc.x <= 150 && nextAppState.mc.y <= 75 && KEY_DOWN(BUTTON_UP, keysPressedNow)) {
        nextAppState.lastLocation = OUTDOORS;
        nextAppState.location = RIDDLE_ROOM;
        nextAppState.showQuestion = false;
        nextAppState.mc.y = 160-32;
        nextAppState.mc.oam->attr0 = nextAppState.mc.y | SPRITES_PALETTE_TYPE | MC1_SPRITE_SHAPE;
        for(int i = 1; i < 128; i++)
            shadow[i].attr0 = ATTR0_HIDE;
        nextAppState.arrow.isActive = false;
        nextAppState.help = false;
    }

    return nextAppState;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    // AppState nextAppState = *currentAppState;

    switch(currentAppState->location) {
        case HOME:
            return processHome(currentAppState, keysPressedBefore, keysPressedNow);
        case RIDDLE_ROOM:
            return processRiddleRoom(currentAppState, keysPressedBefore, keysPressedNow);
        default:
            return processOutside(currentAppState, keysPressedBefore, keysPressedNow);
    }
}
