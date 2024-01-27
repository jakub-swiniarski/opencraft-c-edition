#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>

//world
#define WORLD_WIDTH 500
#define WORLD_HEIGHT 50
#define WORLD_LENGTH 500
static const int RENDER_DIST=100;

//display
static const int SCREEN_WIDTH=1920;
static const int SCREEN_HEIGHT=1080;
static const int FPS=60;

//mouse
static const float MOUSE_SENS=0.0017f;
static const MouseButton ATTACK=MOUSE_BUTTON_LEFT;

//keyboard
static const KeyboardKey MOVE_FORWARD=KEY_W;
static const KeyboardKey MOVE_BACKWARD=KEY_S;
static const KeyboardKey MOVE_LEFT=KEY_A;
static const KeyboardKey MOVE_RIGHT=KEY_D;
static const KeyboardKey JUMP=KEY_SPACE;

//other
static const float FOV=70.f;

#endif
