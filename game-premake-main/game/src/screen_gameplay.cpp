#include "raylib.h"
#include "screens.h"
#include "mandelbrot.h"
#include <string>
#include <stdio.h>
#include <chrono>

static Vector2 Offset;
static Vector2 Scale;
static Vector2 StartPan;

static Vector2 FractalTopLeft;
static Vector2 FractalBottomRight;

static ColorTexture Result;

void DrawInfo(float Input, int X, int Y);
void DrawInfo(std::chrono::duration<double>& Input, int X, int Y); 
void ScreenToWorld(const Vector2& n, Vector2& v);
void WorldToScreen(const Vector2& v, Vector2& n);

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    Result.Width = screenWidth;
    Result.Height = screenHeight;
    Result.ColorArray = new Color[screenWidth * screenHeight];

    Offset.x = 0;
    Offset.y = 0;
    StartPan.x = 0;
    StartPan.y = 0;
    Scale.x = screenWidth / 2;
    Scale.y = screenHeight;
    FractalTopLeft.x = 1;
    FractalTopLeft.y = 1;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    Vector2 D = GetMouseDelta();
    // Press enter or tap to change to ENDING screen
    if (IsMouseButtonPressed(0))
    {
        //StartPan = GetMousePosition();
    }

    if (IsMouseButtonDown(0))
    {
        Offset.x -= D.x / screenWidth;
        Offset.y -= D.y / screenHeight;
        /*Offset.x -= (M.x - StartPan.x) / Scale.x;
        Offset.x -= (M.y - StartPan.y) / Scale.y;
        StartPan = M;*/
    }

  
   // Vector2 MouseBeforeZoom;
   // ScreenToWorld(M, MouseBeforeZoom);

    float Scroll = GetMouseWheelMove();
    if (Scroll < -0.2f)
    {
        FractalTopLeft.x *= 1.1;
        FractalTopLeft.y *= 1.1;
    }
    if (Scroll > 0.2f)
    {
        FractalTopLeft.x *= 0.9;
        FractalTopLeft.y *= 0.9;
    }
   // 
   // Vector2 MouseAfterZoom;
   // MouseAfterZoom.x = 0;
   // MouseAfterZoom.y = 0;
   // ScreenToWorld(M, MouseAfterZoom);
   // Offset.x += MouseBeforeZoom.x - MouseAfterZoom.x;
   // Offset.y += MouseBeforeZoom.y - MouseAfterZoom.y;

   // FractalBottomRight.x = 0.47;
   // FractalBottomRight.y = 1.12;

   // Vector2 Zero;
   // Zero.x = 0;
   // Zero.y = 0;
   // //ScreenToWorld(Zero, FractalTopLeft);
   // 
   // Vector2 Max;
   // Max.x = screenWidth;
   // Max.y = screenHeight;
   //// ScreenToWorld(Max, FractalBottomRight);

}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);

    std::chrono::steady_clock::time_point Start = std::chrono::high_resolution_clock::now();

    OptimisedSimpleMandelbrot(Result, Offset, FractalTopLeft, FractalBottomRight, 64);

    for (int y = 0; y < Result.Height; y++)
    {
        for (int x = 0; x < Result.Width; x++)
        {
            DrawPixel(x, y, *(Result.ColorArray + Result.Width * y + x));
        }
    }
    DrawPixel(10, 10, BLACK);

    std::chrono::duration<double> ElapsedTime = std::chrono::high_resolution_clock::now() - Start;
    DrawInfo(ElapsedTime, 50, 100);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    delete[] Result.ColorArray;
    // TODO: Unload GAMEPLAY screen variables here!
}

void DrawInfo(float Input, int X, int Y)
{
    std::string str = std::to_string(Input) + 's';
    char* Arr = new char[str.length() + 1];
    strcpy(Arr, str.c_str());

    DrawText(Arr, X, Y, 20, BLACK);
    delete[] Arr;
}

void DrawInfo(std::chrono::duration<double>& Input, int X, int Y)
{
    std::string str = std::to_string(Input.count()) + 's';
    char* Arr = new char[str.length() + 1];
    strcpy(Arr, str.c_str());

    DrawText(Arr, X, Y, 20, BLACK);
    delete[] Arr;
}

void WorldToScreen(const Vector2& v, Vector2& n)
{
    n.x = (int)((v.x - Offset.x) * Scale.x);
    n.y = (int)((v.y - Offset.y) * Scale.y);
}

// Convert coordinates from Screen Space --> World Space
void ScreenToWorld(const Vector2& n, Vector2& v)
{
    v.x = (double)(n.x) / Scale.x + Offset.x;
    v.y = (double)(n.y) / Scale.y + Offset.y;
}