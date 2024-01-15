#include "raylib.h"
#include "General.h"
#include "Camera controls.h"
#include "Ball_class.h"



void InitAll(){
	InitWindow(constants::screenWidth, constants::screenHeight, "noice");
    Camera_initialize();
    Ball_initialize();

    SetTargetFPS(24);

}