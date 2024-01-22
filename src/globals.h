#ifndef GLOBALS_H
#define GLOBALS_H

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 50
#define WORLD_LENGTH 50
static int world[WORLD_WIDTH][WORLD_HEIGHT][WORLD_LENGTH];
#define NUM_BLOCKS 3
enum {AIR,STONE,DIRT,GRASS};

static const char *DIRECTORY="res/";
static const char *VERSION="1.0.0";

#endif
