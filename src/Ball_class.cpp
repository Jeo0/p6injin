#include "raylib.h"
#include "Ball_class.h"

typedef struct Objects Ball;



void Ball_initialize(){
    Ball.radius = 14.0;
    Ball.weight = 5;
    Ball.bounceCoefficient = 0.5f;
    Ball.position = {GetScreenWidth()/2 - Ball.radius, GetScreenHeight()/2 - Ball.radius};     // @ center of window

    // physics
    Ball.velocity = 0.0;
}