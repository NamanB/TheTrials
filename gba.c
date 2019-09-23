#include "gba.h"
#include "draw.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *) 0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {
    // TA-TODO: IMPLEMENT

    // Write a while loop that loops until we're NOT in vBlank anymore:
    // (This prevents counting one VBlank more than once if your app is too fast)
    while(*SCANLINECOUNTER > 160);

    // Write a while loop that keeps going until we're in vBlank:
    while(*SCANLINECOUNTER < 160);

    // Finally, increment the vBlank counter:
    vBlankCounter++;
}

static int __qran_seed= 42;
static int qran(void) {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}

int randint(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}

void setPixel(int x, int y, u16 color) {
    // TA-TODO: IMPLEMENT
    videoBuffer[y*WIDTH + x] = color;
}

void drawRectDMA(int x, int y, int width, int height, u16 color) {
    // TA-TODO: IMPLEMENT
    DMA[3].src = &color;
    for (int i = 0; i < height; i++) {
        DMA[3].dst = videoBuffer + (y + i) * WIDTH + x;
        DMA[3].cnt = DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON | width;
    }
}

void drawImageTransparent(int x, int y, int width, int height, int transparent, u16 *image) {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            u16 color = image[r * width + c];
            if (color != transparent)
                setPixel(c + x, r + y, color);
        }
    }
}

void drawFullScreenImageDMA(u16 *image) {
    // TA-TODO: IMPLEMENT
    DMA[3].src = image;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON | 240 * 160;
}

void drawImageDMA(int x, int y, int width, int height, u16 *image) {
    // TA-TODO: IMPLEMENT 
    for(int i = 0; i < height; i++) {
        DMA[3].src = image + i*width;
        DMA[3].dst = videoBuffer + (y + i) * WIDTH + x;
        DMA[3].cnt = DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON | width;
    }
}

void drawImageSpliceDMA(int x, int y, int srx, int sry, int width, int height, int srw, u16 *image) {
    for(int i = 0; i < height; i++) {
        DMA[3].src = image + (sry + i) * srw + srx;
        DMA[3].dst = videoBuffer + (y + i) * WIDTH + x;
        DMA[3].cnt = DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON | width;
    }
}

void fillScreenDMA(volatile u16 color) {
    DMA[3].src = &color;
    //videoBuffer starts at top left corner, but to choose local coord, use offset macro
    // &videoBuffer[OFFSET(x,y,240)]
    DMA[3].dst = videoBuffer;
    // images will have to be drawn on screen with a for loop and change v to width
    DMA[3].cnt = DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON | 240 * 160;
}

void drawSprites(void) {
    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128*4 | DMA_ON;
}

void drawChar(int col, int row, char ch, u16 color) {
    for(int r = 0; r<8; r++) {
        for(int c=0; c<6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
                setPixel(col+c, row+r, color);
            }
        }
    }
}

void drawString(int col, int row, char *str, u16 color) {
    while(*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}

void drawCenteredString(int x, int y, int width, int height, char *str, u16 color) {
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy) {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int col = x + ((width - strWidth) >> 1);
    int row = y + ((height - strHeight) >> 1);
    drawString(col, row, str, color);
}
