#include <raylib.h>
#include "functions.h"
#include "config.h"

int main(void)
{
    //TODO: DELTA TIME
    //TODO: think of an efficient way to store and draw the world
    //3d array of block ids? get texture by id and draw cube with that texture
    //iterate over the array and draw cube at (i,j,k)
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenCraft");
    
    int display=GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display),GetMonitorHeight(display));
    ToggleFullscreen();

    SetTargetFPS(60);

    DisableCursor();

    Camera3D camera={
        .position=(Vector3){.x=5.0f,.y=5.0f,.z=5.0f},
        .target=(Vector3){.x=0.0f,.y=0.0f,.z=0.0f},
        .up=(Vector3){.x=0.0f,.y=1.0f,.z=0.0f},
        .fovy=45.f,
        .projection=CAMERA_PERSPECTIVE
    };

    Texture block=LoadTexture("res/stone.png");

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

            ClearBackground((Color){.r=120,.g=255,.b=255,.a=255});

            BeginMode3D(camera);

                draw_block(block,1.0f,1.0f,1.0f);
            
            EndMode3D();

            DrawFPS(10,10);
            
        EndDrawing();
    }

    UnloadTexture(block);
    CloseWindow();

    return 0;
}
