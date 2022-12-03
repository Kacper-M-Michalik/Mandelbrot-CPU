#include "raylib.h"

struct ColorTexture
{
	int Width;
	int Height;

	Color* ColorArray;
};

void SimpleMandelbrot(ColorTexture& Text, const Vector2 TileOffset, const Vector2 TileSize, const DVector2 Offset, const double Zoom, const int MaxIterations);
void OptimisedMandelbrot(const ColorTexture& Text, const Vector2 TileOffset, const Vector2 TileSize, const DVector2 Offset, const double Zoom, const int MaxIterations);
void OptimisedSIMDMandelbrot(const ColorTexture& Text, const Vector2 TileOffset, const Vector2 TileSize, const DVector2 Offset, const double Zoom, const int MaxIterations);