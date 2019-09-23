/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=4 --for_bitmap --transparent=FF00FF sprites mc1.png mc2.png mc3.png mc4.png mc5.png mc6.png mc7.png mc8.png mc9.png mc10.png arrow.png boss-1.png boss-2.png fireball.png god.png wasp.png 
 * Time-stamp: Sunday 04/07/2019, 23:04:25
 * 
 * Image Information
 * -----------------
 * mc1.png 32@32
 * mc2.png 32@32
 * mc3.png 32@32
 * mc4.png 32@32
 * mc5.png 32@32
 * mc6.png 32@32
 * mc7.png 32@32
 * mc8.png 32@32
 * mc9.png 32@32
 * mc10.png 32@32
 * arrow.png 16@16
 * boss-1.png 32@32
 * boss-2.png 32@32
 * fireball.png 16@16
 * god.png 32@32
 * wasp.png 32@32
 * Transparent color: (255, 0, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef SPRITES_H
#define SPRITES_H

#define SPRITES_PALETTE_TYPE (0 << 13)
#define SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprites_palette[256];
#define SPRITES_PALETTE_SIZE 512
#define SPRITES_PALETTE_LENGTH 256

extern const unsigned short sprites[3712];
#define SPRITES_SIZE 7424
#define SPRITES_LENGTH 3712

//0
#define MC4_PALETTE_ID (0 << 12)
#define MC4_SPRITE_SHAPE (0 << 14)
#define MC4_SPRITE_SIZE (2 << 14)
#define MC4_ID 512

//1
#define MC5_PALETTE_ID (0 << 12)
#define MC5_SPRITE_SHAPE (0 << 14)
#define MC5_SPRITE_SIZE (2 << 14)
#define MC5_ID 528

//2
#define MC7_PALETTE_ID (0 << 12)
#define MC7_SPRITE_SHAPE (0 << 14)
#define MC7_SPRITE_SIZE (2 << 14)
#define MC7_ID 544

//3
#define MC10_PALETTE_ID (0 << 12)
#define MC10_SPRITE_SHAPE (0 << 14)
#define MC10_SPRITE_SIZE (2 << 14)
#define MC10_ID 560

//4
#define MC1_PALETTE_ID (0 << 12)
#define MC1_SPRITE_SHAPE (0 << 14)
#define MC1_SPRITE_SIZE (2 << 14)
#define MC1_ID 576

//5
#define MC2_PALETTE_ID (0 << 12)
#define MC2_SPRITE_SHAPE (0 << 14)
#define MC2_SPRITE_SIZE (2 << 14)
#define MC2_ID 592

//6
#define MC3_PALETTE_ID (0 << 12)
#define MC3_SPRITE_SHAPE (0 << 14)
#define MC3_SPRITE_SIZE (2 << 14)
#define MC3_ID 608

//7
#define MC6_PALETTE_ID (0 << 12)
#define MC6_SPRITE_SHAPE (0 << 14)
#define MC6_SPRITE_SIZE (2 << 14)
#define MC6_ID 624

//8
#define MC8_PALETTE_ID (0 << 12)
#define MC8_SPRITE_SHAPE (0 << 14)
#define MC8_SPRITE_SIZE (2 << 14)
#define MC8_ID 640

//9
#define MC9_PALETTE_ID (0 << 12)
#define MC9_SPRITE_SHAPE (0 << 14)
#define MC9_SPRITE_SIZE (2 << 14)
#define MC9_ID 656

//10
#define BOSS2_PALETTE_ID (0 << 12)
#define BOSS2_SPRITE_SHAPE (0 << 14)
#define BOSS2_SPRITE_SIZE (2 << 14)
#define BOSS2_ID 672

//11
#define BOSS1_PALETTE_ID (0 << 12)
#define BOSS1_SPRITE_SHAPE (0 << 14)
#define BOSS1_SPRITE_SIZE (2 << 14)
#define BOSS1_ID 688

//12
#define WASP_PALETTE_ID (0 << 12)
#define WASP_SPRITE_SHAPE (0 << 14)
#define WASP_SPRITE_SIZE (2 << 14)
#define WASP_ID 704

//13
#define ARROW_PALETTE_ID (0 << 12)
#define ARROW_SPRITE_SHAPE (0 << 14)
#define ARROW_SPRITE_SIZE (1 << 14)
#define ARROW_ID 720

//14
#define GOD_PALETTE_ID (0 << 12)
#define GOD_SPRITE_SHAPE (0 << 14)
#define GOD_SPRITE_SIZE (2 << 14)
#define GOD_ID 724

//15
#define FIREBALL_PALETTE_ID (0 << 12)
#define FIREBALL_SPRITE_SHAPE (0 << 14)
#define FIREBALL_SPRITE_SIZE (1 << 14)
#define FIREBALL_ID 740

#endif

