#ifndef STRUCTS_H
#define STRUCTS_H

#include <raylib.h>
#include "globals.h"

static struct{
    Texture blocks[NUM_BLOCKS];
} TextureHolder;

typedef struct{
    float x,y,z;
    int speed_y;
    Camera3D cam;
} Player;

#endif
