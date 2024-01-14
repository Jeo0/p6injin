#include "raylib.h"
#include "General.h"

int main()
{

    InitAll();
    // for time releated 
    int frameCount =0 ;
    float timeElapsed = 0.0;


    float gravity = 9.81;

    float ball_radius = 14.0;
    float ball_weight = 5;
    Vector2 ball_position = {GetScreenWidth()/2 - ball_radius, GetScreenHeight()/2 - ball_radius};     // @ center of window
    float ball_bounceCoefficient = 0.5f;

    // physics
    float previousPosition = ball_position.y;
    float previousTime = timeElapsed;

    float ball_velocity = 0.0;
    float ball_acceleration = (gravity) / (timeElapsed*timeElapsed);

    //float ball_ke = (0.5) * ball_weight * ball_velocity*ball_velocity;
    float ball_ke = 0;

    

    while (!WindowShouldClose())    
    {

        ball_velocity = (ball_position.y - previousPosition) / (timeElapsed - previousTime);

        // // bounce when it goes out of bounds
        // if(ball_position.y >= GetScreenHeight() - ball_radius){

        // }
        
        
        previousPosition = ball_position.y;
        previousTime = timeElapsed;
        ball_ke = 0.01 + (0.5) * ball_weight * ball_velocity*ball_velocity;

        ball_position.y -= gravity/(timeElapsed*timeElapsed);
        
        
        
        DrawLine(39, 90,  450, 670, BLACK);
        // calculate how much time has elapsed
        frameCount++;
        timeElapsed = (float)frameCount/GetFPS() ;



        BeginDrawing();
            DrawCircle(ball_position.x, ball_position.y, ball_radius, BLACK);
            // show time
            DrawText(TextFormat("time: %f", timeElapsed), 10, 10, 40, BLUE);
            DrawText(TextFormat("%f\n\nvelocity", ball_velocity), 10, 10+100, 40, BLUE);
            DrawText(TextFormat("%f\n\nkineitc enrgy", ball_ke), 10, 10+200, 40, BLUE);
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    
	CloseWindow();

    
    return 0;
}
