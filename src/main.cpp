#include "raylib.h"
#include "General.h"
#include <iostream>
#include "rlgl.h"
#include "raymath.h"
#include <vector>

std::vector<int> what {};

void Camera_initialize();
void CameraZoomControls();
void Ball_initialize();


class Objects {
	public:
    float radius;
    float weight;
    float bounceCoefficient;
    //custom_Vect2 position {0, 0};
    Vector2 position {};

    // physics
    float velocity;

};


Camera2D camera = {0};
Objects Ball;         // used externally from Ball_class.cpp

int main()
{


    InitAll();
    // for time releated 
    int frameCount =0 ;
    double timeElapsed = 0.0;
	Camera_initialize();
	Ball_initialize();
    SetTargetFPS(144);


    // float gravity = 9.81 * 100;
    float gravity = 9.81;

    // physics
    float previousVelocity = Ball.velocity;
    float previousPosition = Ball.position.y;
    float previousTime = timeElapsed;

    float ball_acceleration = (Ball.velocity) / (GetTime() * GetTime());

    //float ball_ke = (0.5) * ball_weight * ball_velocity*ball_velocity;
    float ball_ke = 0;



    

    while (!WindowShouldClose())    
    {

		CameraZoomControls();

        
        // Ball.velocity = gravity * GetTime();

        ////////////////////////////////// working
        /////////////////////////////////////////// fix why it slides down
        Ball.velocity += gravity * GetFrameTime();
        ball_acceleration = (Ball.velocity - previousVelocity) / (timeElapsed - previousTime);



        // ball_acceleration = (Ball.velocity - previousVelocity) / (GetTime() - previousTime);
        
        // Ball.velocity = (Ball.position.y - previousPosition) / (timeElapsed - previousTime);
        // Ball.velocity = (Ball.position.y - previousPosition) / (GetFrameTime());
        previousPosition = Ball.position.y;
        previousTime = timeElapsed;
        previousVelocity = Ball.velocity;

        ball_ke = (0.5) * Ball.weight * Ball.velocity*Ball.velocity;


        /************* handle gravity **********************/
        // Ball.position.y += (Ball.velocity * gravity * GetTime());       // much more higher (64.99 real) (67.7712) @ 6.625 seconds
                                                                        // this pertains to (calcualtion) (simulation)
                                                                        
        // handle gravity 
        //  usign kinematic eq 4
        // Ball.position.y += 0.5 * Ball.velocity * GetTime();     // (83.7927 real) (88.253761) @ 8.514667

        // handle gravity 
        // using kinemaitc eq 1
        // Ball.position.y += 0.5*gravity * GetTime() * GetTime() ;     // (11.445 real) (18.946) @ 1.16667

        // handle gravity
        // using example raylib 
        /////////////////////// working
        //////////////////////////////// fix why it slides down
        // Ball.position.y = Ball.position.y + Ball.velocity * GetFrameTime();
        // this sht code below is the culprit for sliding down
        // Ball.position.y += Ball.velocity * GetFrameTime();



        // Ball.position.y += Ball.velocity;                // linearly scaling velocity
        Ball.position.y += Ball.velocity * GetTime();       // mucuh more realsitic         // exponentially scaling velocity

		//Ball.position.y += gravity * GetFrameTime();
        std::cout << "ball accel : " << ball_acceleration << "\n\n";


        // bounce manually
        if(IsKeyPressed(KEY_P) && Ball.velocity >= 0){
            Ball.velocity = (Ball.velocity * -2 * Ball.bounceCoefficient);

        }
        // else if(IsKeyPressed(KEY_I) && Ball.velocity < 0){
        //     Ball.velocity = (Ball.velocity * -2 * Ball.bounceCoefficient);
        // }

        // jump controls
        if(IsKeyPressed(KEY_SPACE) ){
            Ball.velocity += (Ball.velocity * -5);

        }



        // bounce here if out of bounds
        if(Ball.position.y > GetScreenHeight()){
            Ball.velocity = (Ball.velocity * -2 * Ball.bounceCoefficient);
        }

       
        
        // calculate how much time has elapsed
        frameCount += 1.0;
        timeElapsed = (float)frameCount/GetFPS() ;



        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                // draw screen world
                DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
                DrawRectangle(0,0, GetScreenWidth(), GetScreenHeight(), RED);
                DrawLine(39, 90,  450, 670, BLACK);
                DrawCircle(Ball.position.x, Ball.position.y, Ball.radius, BLACK);
                // DrawCircle(Ball.position.x, newballpos, Ball.radius, BLACK);
                
            EndMode2D();

            // show time
            // everything under here are shown in screen constantly
            // i.e., in everyframe, they are shown at the same lcoation regardless of where the camera is
            DrawText(TextFormat("time: %f", timeElapsed), 10, 10, 40, BLUE);
            DrawText(TextFormat("%f\n\nposition Y", Ball.position.y), 10, 10+100, 40, BLUE);
            // DrawText(TextFormat("%f\n\nposition Y", newballpos), 10, 10+100, 40, BLUE);
            DrawText(TextFormat("%f\n\nBall.velocity", Ball.velocity), 10, 10+200, 40, BLUE);
            DrawText(TextFormat("%f\n\nkineitc enrgy", ball_ke), 10, 10+300, 40, BLUE);
            DrawText(TextFormat("%f\n\nzoom", camera.zoom), 10, 10+400, 40, BLUE);
            //DrawText(TextFormat("%f\n\ninitial ball position", GetScreenHeight()/2 - Ball.radius), 10, 10+500, 40, BLUE);
            DrawText(TextFormat("%f\n\nBall.veloctiy+gravity", Ball.velocity + (gravity* (timeElapsed - previousTime))), 10, 10+600, 40, BLUE);
            DrawText(TextFormat("%f\n\nGetFrameTime", GetFrameTime()), 10, 10+700, 40, BLUE);
            DrawText(TextFormat("%f\n\nGetTime", GetTime()), 10, 10+800, 40, BLUE);
        EndDrawing();
    }

    
	CloseWindow();

    
    return 0;
}




void Camera_initialize(){
    // camera.target = (Vector2){ Ball.position.x + 20.0f, Ball.position.y + 20.0f };
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
    // camera.target = (Vector2){0,0};
    camera.target = (Vector2){screenWidth/2, screenHeight/2};
    camera.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.8f;
}


void CameraZoomControls(){
    float zoomCoefficient = 0.1f;
    if(camera.zoom <=1.0f){                     // making zoom at longer distances smoother
        zoomCoefficient =  zoomCoefficient * 0.5f;
    }
    if((float)GetMouseWheelMove() <0 ){         // to make zoom out
        camera.zoom += ((float)GetMouseWheelMove() * (float)GetMouseWheelMove() * zoomCoefficient * -1);
    }
    else{                                       // to make zoom in
        camera.zoom += ((float)GetMouseWheelMove() * (float)GetMouseWheelMove() * zoomCoefficient);
    }



        // pan
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }



        // zoom controls
        if(IsKeyDown(KEY_Q))
            camera.zoom -= 0.00001f;

        if(IsKeyDown(KEY_W))
            camera.zoom -= 0.005f;

        if(IsKeyPressed(KEY_R)){
            // reset
            camera.zoom = 1.0f;
        }
        if (IsKeyDown(KEY_S)){
            camera.zoom +=  9.0f;
        }
        if (IsKeyDown(KEY_X)){
            camera.zoom -=  9.0f;
        }

        // handle reversing zoom / out of bounds
        if(camera.zoom <=0){
            camera.zoom = 0.01f;
        }
}

void Ball_initialize(){
    Ball.radius = 50.0;
    Ball.weight = 5;
    Ball.bounceCoefficient = 0.25f;
    // Ball.position = (custom_Vect2){GetScreenWidth()/2 - Ball.radius, GetScreenHeight()/2 - Ball.radius};     // @ center of window
    //Ball.position = (Vector2){GetScreenWidth()/2 - Ball.radius, GetScreenHeight()/2 - Ball.radius};     // @ center of window
    Ball.position = (Vector2){GetScreenWidth()/2 - Ball.radius, 0 - Ball.radius};     // @ center of window


    // physics
    Ball.velocity = 0.0;
}

