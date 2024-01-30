#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "globals.h"
#include "config.h"
#include "structs.h"

int main(void){
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
        .height=1.5f
    };

    //world generation - TODO: move this to generate_world function
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
    for(int i=10; i<WORLD_WIDTH-10; i++){
        for(int k=10; k<WORLD_LENGTH-10; k++){
            int random=rand()%100;
            if(random==1){
                for(int a=0; a<5; a++){
                    for(int b=0; b<5; b++){
                        for(int c=0; c<3; c++){
                            world[i-2+a][WORLD_HEIGHT/2+4+c][k-2+b]=LEAVES;
                        }
                    }
                }
                world[i-2][WORLD_HEIGHT/2+6][k-2]=world[i-2][WORLD_HEIGHT/2+6][k+2]=world[i+2][WORLD_HEIGHT/2+6][k-2]=world[i+2][WORLD_HEIGHT/2+6][k+2]=AIR;
                for(int a=1; a<6; a++)
                    world[i][WORLD_HEIGHT/2+a][k]=WOOD;
            }
        }
    }

    while (!WindowShouldClose())
    {
        dt=GetFrameTime();

        //TODO: gravity - player falls through blocks, create a safe space around the edges
        //TODO: blocks are not placed in the right position, they are shifted for some reason, cast a ray from camera and find an intersection with a block 

        //gravity
        if(world[(int)player.position.x][(int)(player.position.y-player.height)][(int)player.position.z]==AIR)
            player.speed_y-=20*dt;
        else
            player.speed_y=0.f;

        update_player(&player,dt);

        //update player pos
        player.position.y+=player.speed_y*dt;
    
        //mouse input
        if(IsMouseButtonPressed(ATTACK)) //TODO: cast a ray from the camera or try using .target.position 
            world[(int)player.position.x][(int)(player.position.y-player.height)][(int)player.position.z]=AIR;
        if(IsMouseButtonPressed(PLACE)) //TODO: check if world[x][y][z]==AIR
            world[(int)player.position.x][(int)(player.position.y-player.height)][(int)player.position.z]=STONE;

        BeginDrawing();

            ClearBackground((Color){.r=120,.g=255,.b=255,.a=255});

            begin_3d(&player);
                for(int i=player.position.x-RENDER_DIST; i<=player.position.x+RENDER_DIST; i++){
                    for(int j=0; j<WORLD_HEIGHT; j++){
                        for(int k=player.position.z-RENDER_DIST; k<=player.position.z+RENDER_DIST; k++){
                            if(world[i][j][k]==AIR) continue;

                            //TODO: if block not visible, continue
                            if(!((player.position.x<player.target.x && i+50>player.position.x) || //do not add constant values, add more the further we are from the player (delta i)
                                (player.position.x>player.target.x && i-50<player.position.x)) ||
                            //!((player.position.y<player.target.y && j>player.position.y) ||
                            //    (player.position.y>player.target.y && j<player.position.y)) &&
                            !((player.position.z<player.target.z && k+50>player.position.z) ||
                                (player.position.z>player.target.z && k-50<player.position.z))) continue;

                            bool sides[6];

                            sides[0]=(player.position.z>k && (k==WORLD_LENGTH-1 || world[i][j][k+1]==AIR))?1:0;
                            sides[1]=(player.position.z<k && (k==0 || world[i][j][k-1]==AIR))?1:0;
                            sides[2]=(player.position.y>j && (j==WORLD_HEIGHT-1 || world[i][j+1][k]==AIR))?1:0;
                            sides[3]=(player.position.y<j && (j==0 || world[i][j-1][k]==AIR))?1:0;
                            sides[4]=(player.position.x>i && (i==WORLD_WIDTH-1 || world[i+1][j][k]==AIR))?1:0;
                            sides[5]=(player.position.x<i && (i==0 || world[i-1][j][k]==AIR))?1:0;

                            draw_block(&TextureHolder.blocks[world[i][j][k]-1],i,j,k,sides);
                        }
                    }
                }
            
            EndMode3D();

            DrawFPS(10,10);
            
        EndDrawing();
    }
    
    for(int i=0; i<NUM_BLOCKS; i++)
        UnloadTexture(TextureHolder.blocks[i]);

    CloseWindow();

    return 0;
}
