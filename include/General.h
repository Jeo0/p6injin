#pragma once

namespace constants {
    inline constexpr int screenWidth = 1360;
    inline constexpr int screenHeight = 970;

}

//inline Camera2D Camera = {0};               // should inline?
//struct Objects Ball;             // should inline?
extern Camera2D Camera;         // from Camera controls.cpp
//extern struct Objects Ball;      // from Ball_class.cpp
typedef struct Objects{
//public:
    float radius;
    float weight;
    float bounceCoefficient;
    Vector2 position {};

    // physics
    float velocity;
}Objects;

extern Objects Ball;

void InitAll();
