#include "raylib.h"
#include "screens.h"
#include <chrono>


//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = GAMEPLAY;
Font font = { 0 };

static void UpdateDrawFrame(void);

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Mandelbrot Window");

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/mecha.png");

    // Setup and init first screen
    currentScreen = GAMEPLAY;
    //InitLogoScreen();
    InitGameplayScreen();

    SetTargetFPS(60); 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    switch (currentScreen)
    {
        case GAMEPLAY: UnloadGameplayScreen(); break;
        default: break;
    }

    UnloadFont(font);

    CloseAudioDevice(); 

    CloseWindow(); 
    //--------------------------------------------------------------------------------------
    
    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    UpdateGameplayScreen();

    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case GAMEPLAY: DrawGameplayScreen(); break;
            default: break;
        }

    EndDrawing();
}
