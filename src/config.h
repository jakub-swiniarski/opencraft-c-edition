#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>

//display
static const int SCREEN_WIDTH=1920;
static const int SCREEN_HEIGHT=1080;
static const int FPS=60;

//mouse
static const float MOUSE_SENS=0.0017f;

//keyboard
static const KeyboardKey MOVE_FORWARD=KEY_W;
static const KeyboardKey MOVE_BACKWARD=KEY_S;
static const KeyboardKey MOVE_LEFT=KEY_A;
static const KeyboardKey MOVE_RIGHT=KEY_D;
static const KeyboardKey JUMP=KEY_SPACE;

//other
static const float FOV=70.f;

#endif
