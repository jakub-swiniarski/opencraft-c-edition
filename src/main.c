#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "globals.h"
#include "config.h"
#include "structs.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenCraft");
    
    int display=GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display),GetMonitorHeight(display));
    ToggleFullscreen();

    SetTargetFPS(FPS);
    float dt=1.0f;

    DisableCursor();

    //texture loading
    for(int i=0; i<NUM_BLOCKS; i++){
        char name[16];
        sprintf(name,"block%d.png",i);
        TextureHolder.blocks[i]=LoadTexture(path_to_file(name));
    }

    Player player={
        .position=(Vector3){.x=(int)(WORLD_WIDTH/2),.y=WORLD_HEIGHT,.z=(int)(WORLD_LENGTH/2)},
        .speed_y=0.f,
        .target=(Vector3){.x=0.0f,.y=0.0f,.z=0.0f},
        .up=(Vector3){.x=0.0f,.y=1.0f,.z=0.0f},
    };

    //world generation
    srand(time(NULL));
    for(int i=0; i<WORLD_WIDTH; i++){
        for(int j=0; j<WORLD_HEIGHT; j++){
            for(int k=0; k<WORLD_LENGTH; k++){
                if(j<WORLD_HEIGHT/4)
                    world[i][j][k]=STONE;
                else if(j<WORLD_HEIGHT/2)
                    world[i][j][k]=DIRT;
                else if(j==WORLD_HEIGHT/2)
                    world[i][j][k]=GRASS;
                else
                    world[i][j][k]=AIR;
            }
        }
    }
    //generate trees
    for(int i=0; i<WORLD_WIDTH; i++){
        for(int k=0; k<WORLD_LENGTH; k++){
            int random=rand()%100;
            if(random==1){
                world[i][WORLD_HEIGHT/2+1][k]=WOOD;
            }
        }
    }

    while (!WindowShouldClose())
    {
        dt=GetFrameTime();

        //gravity
        if(world[(int)player.position.x][(int)(player.position.y-2)][(int)player.position.z]==AIR)
            player.speed_y-=20*dt;
        else
            player.speed_y=0.f;

        update_player(&player,dt);

        //update player pos
        player.position.y+=player.speed_y*dt;

        BeginDrawing();

            ClearBackground((Color){.r=120,.g=255,.b=255,.a=255});

            begin_3d(&player);
                for(int i=player.position.x-RENDER_DIST; i<player.position.x+RENDER_DIST; i++){
                    for(int j=0; j<WORLD_HEIGHT; j++){
                        for(int k=player.position.z-RENDER_DIST; k<player.position.z+RENDER_DIST; k++){
                            if(world[i][j][k]!=AIR){
                                int sides[6];
                                sides[0]=(k==WORLD_LENGTH-1 || world[i][j][k+1]==AIR)?1:0;
                                sides[1]=(k==0 || world[i][j][k-1]==AIR)?1:0;
                                sides[2]=(j==WORLD_HEIGHT-1 || world[i][j+1][k]==AIR)?1:0;
                                sides[3]=(j==0 || world[i][j-1][k+1]==AIR)?1:0;
                                sides[4]=(i==WORLD_WIDTH-1 || world[i+1][j][k]==AIR)?1:0;
                                sides[5]=(i==0 || world[i-1][j][k]==AIR)?1:0;
                                draw_block(&TextureHolder.blocks[world[i][j][k]-1],i,j,k,sides);
                            }
                        }
                    }
                }
            
            EndMode3D();

            DrawFPS(10,10);
            
        EndDrawing();
    }
    
    for(int i=0; i<NUM_BLOCKS; i++){
        UnloadTexture(TextureHolder.blocks[i]);
    }

    CloseWindow();

    return 0;
}
