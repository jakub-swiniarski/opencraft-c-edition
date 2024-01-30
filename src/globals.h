#ifndef GLOBALS_H
#define GLOBALS_H

#include "config.h"

//world
static int world[WORLD_WIDTH][WORLD_HEIGHT][WORLD_LENGTH]; //TODO: uint8_t? save ram, define this in main?
#define NUM_BLOCKS 5
enum {AIR,STONE,DIRT,GRASS,WOOD,LEAVES};

//movement
static const int MOVE_SPEED=5;
static const int JUMP_SPEED=8;

static const char *DIRECTORY="res/";
static const char *VERSION="1.0.0";

#endif
