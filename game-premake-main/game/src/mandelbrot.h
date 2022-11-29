#include "raylib.h"

struct ColorTexture
{
	int Width;
	int Height;

	Color* ColorArray;
};

void SimpleMandelbrot(ColorTexture& Text, Vector2&, Vector2&, Vector2&, int);
void OptimisedSimpleMandelbrot(ColorTexture& Text, Vector2&, Vector2&, Vector2&, int);