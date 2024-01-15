#include "raylib.h"
#include "Camera controls.h"
#include "General.h"


Camera2D Camera = {0};
Objects Ball;         // used externally from Ball_class.cpp
void Camera_initialize(){
    //camera.target = (Vector2){ ball.x + 20.0f, player.y + 20.0f };
    Camera.target = (Vector2){0,0};
    Camera.offset = (Vector2){constants::screenWidth/2.0f, constants::screenHeight/2.0f };
    Camera.rotation = 0.0f;
    Camera.zoom = 1.0f;
}


void CameraZoomControls(){
        Camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        Camera.target = (Vector2){ball.position.x, ball.position.y};
        if(IsKeyDown(KEY_R))
            Camera.zoom -= 0.00001f;

        if(IsKeyDown(KEY_F))
            Camera.zoom -= 0.005f;

        if(IsKeyPressed(KEY_A)){
            Camera.zoom = 1.0f;
        }
        if (IsKeyDown(KEY_S)){
            Camera.zoom +=  9.0f;
        }
}