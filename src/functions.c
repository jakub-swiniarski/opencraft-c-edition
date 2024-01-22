#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rlgl.h>
#include "config.h"
#include "globals.h"

char *path_to_file(char *name){
    char *path=malloc(sizeof(char)*strlen(DIRECTORY)+strlen(name)+1);
    sprintf(path,"%s%s",DIRECTORY,name);

    return path;
}

void draw_block(Texture *texture, int x, int y, int z, int *sides)
{
    rlSetTexture(texture->id);

    rlBegin(RL_QUADS);
        rlColor4ub(255,255,255,255);

        //front
        if(sides[0]){
            rlNormal3f(0.0f, 0.0f, 1.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
        }

        //back
        if(sides[1]){
            rlNormal3f(0.0f, 0.0f, - 1.0f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
        }

        //top
        if(sides[2]){
            rlNormal3f(0.0f, 1.0f, 0.0f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
        }

        //bottom
        if(sides[3]){
            rlNormal3f(0.0f, - 1.0f, 0.0f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
        }

        //right
        if(sides[4]){
            rlNormal3f(1.0f, 0.0f, 0.0f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + 0.5f, y - 0.5f, z + 0.5f);
        }

        //left
        if(sides[5]){
            rlNormal3f( - 1.0f, 0.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z - 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - 0.5f, y - 0.5f, z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z + 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - 0.5f, y + 0.5f, z - 0.5f);
        }
    rlEnd();

    rlSetTexture(0);
}



Vector3 GetCameraForward(Camera *camera)
{
    return Vector3Normalize(Vector3Subtract(camera->target, camera->position));
}


Vector3 GetCameraUp(Camera *camera)
{
    return Vector3Normalize(camera->up);
}

Vector3 GetCameraRight(Camera *camera)
{
    Vector3 forward = GetCameraForward(camera);
    Vector3 up = GetCameraUp(camera);

    return Vector3CrossProduct(forward, up);
}

void CameraYaw(Camera *camera, float angle, bool rotateAroundTarget)
{
    // Rotation axis
    Vector3 up = GetCameraUp(camera);

    // View vector
    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    // Rotate view vector around up axis
    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);

    if (rotateAroundTarget)
    {
        // Move position relative to target
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else // rotate around camera.position
    {
        // Move target relative to position
        camera->target = Vector3Add(camera->position, targetPosition);
    }
}

void CameraPitch(Camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp)
{
    // Up direction
    Vector3 up = GetCameraUp(camera);

    // View vector
    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    if (lockView)
    {
        // In these camera modes we clamp the Pitch angle
        // to allow only viewing straight up or down.

        // Clamp view up
        float maxAngleUp = Vector3Angle(up, targetPosition);
        maxAngleUp -= 0.001f; // avoid numerical errors
        if (angle > maxAngleUp) angle = maxAngleUp;

        // Clamp view down
        float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
        maxAngleDown *= -1.0f; // downwards angle is negative
        maxAngleDown += 0.001f; // avoid numerical errors
        if (angle < maxAngleDown) angle = maxAngleDown;
    }

    // Rotation axis
    Vector3 right = GetCameraRight(camera);

    // Rotate view vector around right axis
    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);

    if (rotateAroundTarget)
    {
        // Move position relative to target
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else // rotate around camera.position
    {
        // Move target relative to position
        camera->target = Vector3Add(camera->position, targetPosition);
    }

    if (rotateUp)
    {
        // Rotate up direction around right axis
        camera->up = Vector3RotateByAxisAngle(camera->up, right, angle);
    }
}

void CameraMoveForward(Camera *camera, float distance, bool moveInWorldPlane)
{
    Vector3 forward = GetCameraForward(camera);

    if (moveInWorldPlane)
    {
        // Project vector onto world plane
        forward.y = 0;
        forward = Vector3Normalize(forward);
    }

    // Scale by distance
    forward = Vector3Scale(forward, distance);

    // Move position and target
    camera->position = Vector3Add(camera->position, forward);
    camera->target = Vector3Add(camera->target, forward);
}

void CameraMoveRight(Camera *camera, float distance, bool moveInWorldPlane)
{
    Vector3 right = GetCameraRight(camera);

    if (moveInWorldPlane)
    {
        // Project vector onto world plane
        right.y = 0;
        right = Vector3Normalize(right);
    }

    // Scale by distance
    right = Vector3Scale(right, distance);

    // Move position and target
    camera->position = Vector3Add(camera->position, right);
    camera->target = Vector3Add(camera->target, right);
}


void update_camera(Camera *camera){
    Vector2 mousePositionDelta = GetMouseDelta();

    bool moveInWorldPlane = 1;
    bool rotateAroundTarget = 0;
    bool lockView = 1;
    bool rotateUp = false;

    // Mouse support
    CameraYaw(camera, -mousePositionDelta.x*MOUSE_SENS, rotateAroundTarget);
    CameraPitch(camera, -mousePositionDelta.y*MOUSE_SENS, lockView, rotateAroundTarget, rotateUp);

    // Keyboard support
    if (IsKeyDown(KEY_W)) CameraMoveForward(camera, MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_D)) CameraMoveRight(camera, MOVE_SPEED, moveInWorldPlane);
}
