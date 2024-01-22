#ifndef GLOBALS_H
#define GLOBALS_H

//world
#define WORLD_WIDTH 500
#define WORLD_HEIGHT 50
#define WORLD_LENGTH 500
static int world[WORLD_WIDTH][WORLD_HEIGHT][WORLD_LENGTH];
static const int RENDER_DIST=10;
#define NUM_BLOCKS 3
enum {AIR,STONE,DIRT,GRASS};

//movement
static const int MOVE_SPEED=5;

static const char *DIRECTORY="res/";
static const char *VERSION="1.0.0";

#endif
