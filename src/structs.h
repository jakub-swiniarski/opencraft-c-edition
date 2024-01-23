#ifndef STRUCTS_H
#define STRUCTS_H

#include <raylib.h>
#include "globals.h"

static struct{
    Texture blocks[NUM_BLOCKS];
} TextureHolder;

typedef struct{
    Vector3 position;

    //cam
    Vector3 target;
    Vector3 up;
} Player;

#endif
