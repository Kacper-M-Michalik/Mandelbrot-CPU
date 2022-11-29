#include "raylib.h"
#include "mandelbrot.h"
#include <cmath>

void SimpleMandelbrot(ColorTexture& Text, Vector2& Offset, Vector2& FractalTopLeft, Vector2& FractalBottomRight, int MaxIterations)
{
	float MandelbrotX;
	float MandelbrotY;

	for (int PY = 0; PY < Text.Height; PY++)
	{
		for (int PX = 0; PX < Text.Width; PX++)
		{
			float ScaledX = (Offset.x + (float)PX / (float)Text.Width);
			float ScaledY = (Offset.y + (float)PY / (float)Text.Height);

			float x = 0;
			float y = 0;

			int Iteration = 0;

			while (x * x + y * y < 4.f && Iteration < MaxIterations)
			{
				float XTemp = x * x - y * y + ScaledX;
				y = 2 * x * y + ScaledY;
				x = XTemp;
				Iteration++;
			}

			float a = 0.1f;
			(*(Text.ColorArray + Text.Width * PY + PX)).r = unsigned char((0.5f * sin(a * Iteration) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).g = unsigned char((0.5f * sin(a * Iteration + 2.094f) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).b = unsigned char((0.5f * sin(a * Iteration + 4.188f) * 255));
		}
	}

}

void OptimisedSimpleMandelbrot(ColorTexture& Text, Vector2& Offset, Vector2& FractalTopLeft, Vector2& FractalBottomRight, int MaxIterations)
{
	float MandelbrotX;
	float MandelbrotY;

	for (int PY = 0; PY < Text.Height; PY++)
	{
		for (int PX = 0; PX < Text.Width; PX++)
		{
			float ScaledX = (Offset.x + (float)PX / (float)Text.Width) * FractalTopLeft.x;
			float ScaledY = (Offset.y + (float)PY / (float)Text.Height)* FractalTopLeft.x;

			float x = 0;
			float y = 0;
			float x2 = 0;
			float y2 = 0;

			int Iteration = 0;

			while (x2 + y2 < 4.f && Iteration < MaxIterations)
			{
				y = 2 * x * y + ScaledY;
				x = x2 - y2 + ScaledX;
				x2 = x * x;
				y2 = y * y;
				Iteration++;
			};

			float a = 0.1f;
			//(Text.ColorArray + Text.Width * PY + PX) = new Color();
			(*(Text.ColorArray + Text.Width * PY + PX)).r = unsigned char((0.5f * sin(a * Iteration) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).g = unsigned char((0.5f * sin(a * Iteration + 2.094f) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).b = unsigned char((0.5f * sin(a * Iteration + 4.188f) * 255));
			(*(Text.ColorArray + Text.Width * PY + PX)).a = 255;
		}
	}
}


void OptimisedSIMDMandelbrot(ColorTexture& Text, Vector2& Offset, Vector2& FractalTopLeft, Vector2& FractalBottomRight, int MaxIterations)
{
	float MandelbrotX;
	float MandelbrotY;

	for (int PY = 0; PY < Text.Height; PY++)
	{
		for (int PX = 0; PX < Text.Width; PX++)
		{
			float ScaledX = (Offset.x + (float)PX / (float)Text.Width) * FractalTopLeft.x;
			float ScaledY = (Offset.y + (float)PY / (float)Text.Height) * FractalTopLeft.x;

			float x = 0;
			float y = 0;
			float x2 = 0;
			float y2 = 0;

			int Iteration = 0;

			while (x2 + y2 < 4.f && Iteration < MaxIterations)
			{
				y = 2 * x * y + ScaledY;
				x = x2 - y2 + ScaledX;
				x2 = x * x;
				y2 = y * y;
				Iteration++;
			};

			float a = 0.1f;
			//(Text.ColorArray + Text.Width * PY + PX) = new Color();
			(*(Text.ColorArray + Text.Width * PY + PX)).r = unsigned char((0.5f * sin(a * Iteration) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).g = unsigned char((0.5f * sin(a * Iteration + 2.094f) + 0.5f) * 255);
			(*(Text.ColorArray + Text.Width * PY + PX)).b = unsigned char((0.5f * sin(a * Iteration + 4.188f) * 255));
			(*(Text.ColorArray + Text.Width * PY + PX)).a = 255;
		}
	}
}