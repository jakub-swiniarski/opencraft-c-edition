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

//------------------------------------------------------------------

Vector3 GetCameraForward(Camera *cam)
{
    return Vector3Normalize(Vector3Subtract(cam->target, cam->position));
}

Vector3 GetCameraUp(Camera *cam)
{
    return Vector3Normalize(cam->up);
}

Vector3 GetCameraRight(Camera *cam)
{
    Vector3 forward = GetCameraForward(cam);
    Vector3 up = GetCameraUp(cam);

    return Vector3CrossProduct(forward, up);
}

void CameraYaw(Camera *cam, float angle)
{
    Vector3 up = GetCameraUp(cam);
    Vector3 targetPosition = Vector3Subtract(cam->target, cam->position);
    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);
    cam->target = Vector3Add(cam->position, targetPosition);
}

void CameraPitch(Camera *cam, float angle)
{
    Vector3 up = GetCameraUp(cam);
    Vector3 targetPosition = Vector3Subtract(cam->target, cam->position);
    float maxAngleUp = Vector3Angle(up, targetPosition);
    maxAngleUp -= 0.001f;
    if (angle > maxAngleUp) angle = maxAngleUp;
    float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
    maxAngleDown *= -1.0f;
    maxAngleDown += 0.001f;
    if (angle < maxAngleDown) angle = maxAngleDown;
    Vector3 right = GetCameraRight(cam);
    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);
    cam->target = Vector3Add(cam->position, targetPosition);
}

void CameraMoveForward(Camera *cam, float distance)
{
    Vector3 forward = GetCameraForward(cam);
    forward.y = 0;
    forward = Vector3Normalize(forward);
    forward = Vector3Scale(forward, distance);
    cam->position = Vector3Add(cam->position, forward);
    cam->target = Vector3Add(cam->target, forward);
}

void CameraMoveRight(Camera *cam, float distance)
{
    Vector3 right = GetCameraRight(cam);
    right.y = 0;
    right = Vector3Normalize(right);
    right = Vector3Scale(right, distance);
    cam->position = Vector3Add(cam->position, right);
    cam->target = Vector3Add(cam->target, right);
}

//------------------------------------------------------------------

void update_camera(Camera *cam){ //TODO: DELTA TIME ARGUMENT FOR MOVING AND LOOKING AROUND
    Vector2 mousePositionDelta = GetMouseDelta();

    CameraYaw(cam, -mousePositionDelta.x*MOUSE_SENS);
    CameraPitch(cam, -mousePositionDelta.y*MOUSE_SENS);

    if (IsKeyDown(KEY_W)) CameraMoveForward(cam, MOVE_SPEED);
    if (IsKeyDown(KEY_A)) CameraMoveRight(cam, -MOVE_SPEED);
    if (IsKeyDown(KEY_S)) CameraMoveForward(cam, -MOVE_SPEED);
    if (IsKeyDown(KEY_D)) CameraMoveRight(cam, MOVE_SPEED);
}
