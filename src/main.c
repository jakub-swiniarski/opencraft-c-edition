#include <raylib.h>
#include "functions.h"
#include "config.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TEST");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    Texture block=LoadTexture("res/block.png");

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                draw_cube_texture(block,cubePosition,1.0f,1.0f,1.0f,WHITE);
            
            EndMode3D();

        EndDrawing();
    }

    UnloadTexture(block);
    CloseWindow();

    return 0;
}
