#pragma once
#include <SDL.h>

class GeometryController
{
public:
	static SDL_Rect* getRects();
	static int getNumRects();
	static void addRect(SDL_Rect* r);
	static SDL_Rect* mRects;	
	static int mNumRects;
	static int mScreenWidth;
	static int mScreenHeight;
};

