#pragma once
#include <SDL.h>
#include <vector>

class GeometryController
{
public:
	static std::vector<SDL_Rect*> getRects();
	static int getNumRects();
	static void addRect(SDL_Rect* r);
	static std::vector<SDL_Rect*> mRects;	
	static int mNumRects;
	static int mScreenWidth;
	static int mScreenHeight;
	void clear();
};

