#include "raylib.h"
#include "General.h"
#include "Camera controls.h"
#include "Ball_class.h"
using namespace constants;


int main()
{

    Objects Ball;
    InitAll();
    // for time releated 
    int frameCount =0 ;
    float timeElapsed = 0.0;


    


    float gravity = 9.81;


    // physics
    float previousPosition = Ball.position.y;
    float previousTime = timeElapsed;

    float Ball_acceleration = (gravity) / (timeElapsed*timeElapsed);
    //float Ball_ke = (0.5) * Ball.weight * Ball.velocity*Ball.velocity;
    float Ball_ke = 0;

    

    while (!WindowShouldClose())    
    {

        // camera zoom controls
        CameraZoomControls();



        Ball.velocity = (Ball.position.y - previousPosition) / (timeElapsed - previousTime);

        // // bounce when it goes out of bounds
        // if(Ball.position.y >= GetScreenHeight() - Ball.radius){

        // }
        
        
        previousPosition = Ball.position.y;
        previousTime = timeElapsed;
        Ball_ke = 0.01 + (0.5) * Ball.weight * Ball.velocity*Ball.velocity;

        Ball.position.y = gravity/(timeElapsed*timeElapsed);
        
        
        
        // calculate how much time has elapsed
        frameCount++;
        timeElapsed = (float)frameCount/GetFPS() ;



        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(Camera);
                DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
                DrawLine(39, 90,  450, 670, BLACK);
                DrawCircle(Ball.position.x, Ball.position.y, Ball.radius, BLACK);
            EndMode2D();

            // show time
            // everything under here are shown in screen constantly
            // i.e., in everyframe, they are shown at the same lcoation regardless of where the camera is
            DrawText(TextFormat("time: %f", timeElapsed), 10, 10, 40, BLUE);
            DrawText(TextFormat("%f\n\nvelocity", Ball.velocity), 10, 10+100, 40, BLUE);
            DrawText(TextFormat("%f\n\nkineitc enrgy", Ball_ke), 10, 10+200, 40, BLUE);
            DrawText(TextFormat("%f\n\nzoom", Camera.zoom), 10, 10+300, 40, BLUE);
        EndDrawing();
    }

    
	CloseWindow();

    
    return 0;
}
