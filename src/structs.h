#ifndef STRUCTS_H
#define STRUCTS_H

#include <raylib.h>
#include "globals.h"

static struct{
    Texture blocks[NUM_BLOCKS];
} TextureHolder;

typedef struct{
    //movement
    Vector3 position;
    float speed_y;

    //cam
    Vector3 target;
    Vector3 up;

    //size
    float height;
} Player;

#endif
