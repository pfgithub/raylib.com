/*******************************************************************************************
*
*   raylib [core] example - Scissor test
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by Chris Dill (@MysteriousSpace) and reviewed by Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2019 Chris Dill (@MysteriousSpace)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

static Rectangle scissorArea = { 0, 0, 300, 300 };
static bool scissorMode = true;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Program Main Entry Point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - scissor test");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definitions
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_S)) scissorMode = !scissorMode;

    // Centre the scissor area around the mouse position
    scissorArea.x = GetMouseX() - scissorArea.width/2;
    scissorArea.y = GetMouseY() - scissorArea.height/2;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        if (scissorMode) BeginScissorMode(scissorArea.x, scissorArea.y, scissorArea.width, scissorArea.height);

        // Draw full screen rectangle and some text
        // NOTE: Only part defined by scissor area will be rendered
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RED);
        DrawText("Move the mouse around to reveal this text!", 190, 200, 20, LIGHTGRAY);

        if (scissorMode) EndScissorMode();

        DrawRectangleLinesEx(scissorArea, 1, BLACK);
        DrawText("Press S to toggle scissor test", 10, 10, 20, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
