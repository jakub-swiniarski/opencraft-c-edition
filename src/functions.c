#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rlgl.h>
#include "globals.h"

char *path_to_file(char *name){
    char *path=malloc(sizeof(char)*strlen(DIRECTORY)+strlen(name)+1);
    sprintf(path,"%s%s",DIRECTORY,name);

    return path;
}

void draw_block(Texture *texture, int x, int y, int z)
{
    rlSetTexture(texture->id);

    rlBegin(RL_QUADS);
        rlColor4ub(255,255,255,255);

        //front
        if(world[x][y][z+1]==AIR || z==WORLD_LENGTH-1){
            rlNormal3f(0.0f, 0.0f, 1.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
        }

        //back
        if(world[x][y][z-1]==AIR || z==0){
            rlNormal3f(0.0f, 0.0f, - 1.0f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
        }

        //top
        if(world[x][y+1][z]==AIR || y==WORLD_HEIGHT-1){
            rlNormal3f(0.0f, 1.0f, 0.0f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
        }

        //bottom
        if(world[x][y-1][z]==AIR || y==0){
            rlNormal3f(0.0f, - 1.0f, 0.0f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
        }

        //right
        if(world[x+1][y][z]==AIR || x==WORLD_WIDTH-1){
            rlNormal3f(1.0f, 0.0f, 0.0f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
        }

        //left
        if(world[x-1][y][z]==AIR || x==0){
            rlNormal3f( - 1.0f, 0.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
        }
    rlEnd();

    rlSetTexture(0);
}
