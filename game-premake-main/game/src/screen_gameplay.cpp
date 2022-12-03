#include "raylib.h"
#include "screens.h"
#include "mandelbrot.h"
#include <string>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <vector>

static DVector2 Offset;
static double Zoom;
static int Iterations = 64;

static Vector2 TileSize;
static Texture2D Texture;

static ColorTexture ResultTexture;

void DrawInfo(float Input, int X, int Y);
void DrawInfo(std::chrono::duration<double>& Input, int X, int Y);
void DrawInfo(double Input, int X, int Y);
void ScreenToWorld(const Vector2& n, Vector2& v);
void WorldToScreen(const Vector2& v, Vector2& n);

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    ResultTexture.Width = screenWidth;
    ResultTexture.Height = screenHeight;
    ResultTexture.ColorArray = new Color[screenWidth * screenHeight];

    Image screenImage;
    screenImage.data = ResultTexture.ColorArray;
    screenImage.width = screenWidth;
    screenImage.height = screenHeight;
    screenImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    screenImage.mipmaps = 1;
    Texture = LoadTextureFromImage(screenImage);

    Offset.x = 0;
    Offset.y = 0;
    Zoom = 1;

    TileSize.x = 100;
    TileSize.y = 100;     
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
        Offset.x -= Zoom * (double)D.x / screenWidth;
        Offset.y -= Zoom * (double)D.y / screenHeight;
    }

  
   // Vector2 MouseBeforeZoom;
   // ScreenToWorld(M, MouseBeforeZoom);

    float Scroll = GetMouseWheelMove();
    if (Scroll < -0.2f)
    {
        Zoom *= 1.15;
    }
    if (Scroll > 0.2f)
    {
        Zoom *= 0.85;
    }

    if (IsKeyPressed(KEY_E)) 
    {
        Iterations += 64;
    }
    if (IsKeyPressed(KEY_Q))
    {
        Iterations -= 64;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);

    double Start = GetTime();

    std::vector<std::thread> Threads;
    //TileSize.x = screenWidth;
    //TileSize.y = screenHeight;
    int XTiles = 0;
    int YTiles = 0;

    int DrawScreenWidth = screenWidth;
    int DrawScreenHeight = screenHeight;

    Vector2 Zero;
    Zero.x = 0;
    Zero.y = 0;
    Vector2 One;
    One.x = 4;
    One.y = 1;
    //OptimisedMandelbrotThreadable(ResultTexture, Zero, One, Offset, Zoom, Iterations);

    //OptimisedSimpleMandelbrot(Result, Offset, FractalTopLeft, FractalBottomRight, 64);   
    for (int x = 0; x < DrawScreenWidth; x += TileSize.x)
    {
        XTiles++;
        for (int y = 0; y < DrawScreenHeight; y += TileSize.y)
        {
            YTiles++;
            Vector2 ActualTileSize;
            ActualTileSize.x = TileSize.x;
            ActualTileSize.y = TileSize.y;

            Vector2 TileOffset;
            TileOffset.x = x;
            TileOffset.y = y;

            if (screenWidth - x < TileSize.x) 
            {
                ActualTileSize.x = DrawScreenWidth % (int)TileSize.x;
            }
            if (screenHeight - y < TileSize.y)
            {
                ActualTileSize.y = DrawScreenHeight % (int)TileSize.y;
            }

            //Threads.push_back(std::thread(OptimisedMandelbrotThreadable, ResultTexture, TileOffset, ActualTileSize, Offset, Zoom, Iterations));
            Threads.push_back(std::thread(OptimisedSIMDMandelbrotThreadable, ResultTexture, TileOffset, ActualTileSize, Offset, Zoom, Iterations));
        }
    }

    YTiles = YTiles / XTiles;

    for (int i = 0; i < Threads.size(); i++) 
    {
        Threads[i].join();
    }

    UpdateTexture(Texture, ResultTexture.ColorArray);
    DrawTexture(Texture, 0, 0, WHITE);

    double ElapsedTime = GetTime() - Start;
    DrawInfo(ElapsedTime, 50, 100);
    DrawInfo((float)XTiles, 50, 130);
    DrawInfo((float)YTiles, 50, 150);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    delete[] ResultTexture.ColorArray;
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

void DrawInfo(double Input, int X, int Y)
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
