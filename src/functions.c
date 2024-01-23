#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rlgl.h>
#include "config.h"
#include "globals.h"
#include "structs.h"

char *path_to_file(char *name){
    char *path=malloc(sizeof(char)*strlen(DIRECTORY)+strlen(name)+1);
    sprintf(path,"%s%s",DIRECTORY,name);

    return path;
}

void draw_block(Texture *tx, int x, int y, int z, int *sides)
{
    rlSetTexture(tx->id);

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

Vector3 get_player_right(Player *p)
{
    Vector3 forward=Vector3Normalize(Vector3Subtract(p->target, p->position));
    Vector3 up=Vector3Normalize(p->up);

    return Vector3CrossProduct(forward, up);
}

void player_yaw(Player *p, float angle)
{
    Vector3 up=Vector3Normalize(p->up);
    Vector3 target_position=Vector3Subtract(p->target, p->position);
    target_position=Vector3RotateByAxisAngle(target_position, up, angle);
    p->target=Vector3Add(p->position, target_position);
}

void player_pitch(Player *p, float angle)
{
    Vector3 up=Vector3Normalize(p->up); 
    Vector3 target_position=Vector3Subtract(p->target, p->position);
    float max_angle_up=Vector3Angle(up, target_position);
    max_angle_up-=0.001f;
    if(angle>max_angle_up) angle = max_angle_up;
    float max_angle_down=Vector3Angle(Vector3Negate(up), target_position);
    max_angle_down*=-1.0f;
    max_angle_down+=0.001f;
    if(angle<max_angle_down) angle=max_angle_down;
    Vector3 right=get_player_right(p);
    target_position=Vector3RotateByAxisAngle(target_position, right, angle);
    p->target = Vector3Add(p->position, target_position);
}

void player_move_forward(Player *p, float distance)
{
    Vector3 forward=Vector3Normalize(Vector3Subtract(p->target, p->position));
    forward.y=0;
    forward=Vector3Normalize(forward);
    forward=Vector3Scale(forward, distance);
    p->position=Vector3Add(p->position, forward);
    p->target=Vector3Add(p->target, forward);
}

void player_move_right(Player *p, float distance)
{
    Vector3 right=get_player_right(p);
    right.y=0;
    right=Vector3Normalize(right);
    right=Vector3Scale(right, distance);
    p->position=Vector3Add(p->position, right);
    p->target=Vector3Add(p->target, right);
}

//------------------------------------------------------------------

void update_player(Player *p, float dt){
    Vector2 mousePositionDelta = GetMouseDelta();

    player_yaw(p, -mousePositionDelta.x*MOUSE_SENS);
    player_pitch(p, -mousePositionDelta.y*MOUSE_SENS);

    if (IsKeyDown(KEY_W)) player_move_forward(p, MOVE_SPEED*dt);
    if (IsKeyDown(KEY_A)) player_move_right(p, -MOVE_SPEED*dt);
    if (IsKeyDown(KEY_S)) player_move_forward(p, -MOVE_SPEED*dt);
    if (IsKeyDown(KEY_D)) player_move_right(p, MOVE_SPEED*dt);
}

void begin_3d(Player *p)
{
    rlDrawRenderBatchActive();

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

    float aspect=(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT;

    double top=RL_CULL_DISTANCE_NEAR*tan(FOV*0.5*DEG2RAD);
    double right=top*aspect;

    rlFrustum(-right, right, -top, top, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    Matrix matView = MatrixLookAt(p->position, p->target, p->up);
    rlMultMatrixf(MatrixToFloat(matView));

    rlEnableDepthTest();
}
