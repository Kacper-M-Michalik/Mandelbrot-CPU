#include "raylib.h"

struct ColorTexture
{
	int Width;
	int Height;

	Color* ColorArray;
};

void SimpleMandelbrot(ColorTexture& Text, Vector2&, Vector2&, Vector2&, int);
void OptimisedSimpleMandelbrot(ColorTexture& Text, Vector2&, Vector2&, Vector2&, int);
void OptimisedMandelbrotThreadable(const ColorTexture& Text, const Vector2 TileOffset, const Vector2 TileSize, const DVector2 Offset, const double Zoom, const int MaxIterations);
void OptimisedSIMDMandelbrotThreadable(const ColorTexture& Text, const Vector2 TileOffset, const Vector2 TileSize, const DVector2 Offset, const double Zoom, const int MaxIterations);