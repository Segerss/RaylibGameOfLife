#include "raylib.h"
#include <iostream>

#include "Entity.h"

class testClass {
public:
    testClass() {}
    ~testClass() {}

    int getValue() { return 16; }

private:
};

int addNumbers(int a, int b) { return a + b; }

const int screenWidth = 800;
const int screenHeight = 450;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //---------------------------------------------------------

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight,
               "raylib [shapes] example - bouncing ball");

    Vector2 ballPosition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Vector2 ballSpeed = {5.0f, 4.0f};
    int ballRadius = 20;

    bool pause = 0;
    int framesCounter = 0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE))
            pause = !pause;

        if (!pause) {
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Check walls collision for bouncing
            if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) ||
                (ballPosition.x <= ballRadius))
                ballSpeed.x *= -1.0f;
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) ||
                (ballPosition.y <= ballRadius))
                ballSpeed.y *= -1.0f;
        } else
            framesCounter++;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ballPosition, (float)ballRadius, MAROON);
        // DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, GetScreenHeight()
        // - 25, 20, LIGHTGRAY);

        // On pause, we draw a blinking message
        if (pause && ((framesCounter / 30) % 2))
            DrawText("PAUSED", 350, 200, 30, GRAY);

        DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}
