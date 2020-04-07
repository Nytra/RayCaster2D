#pragma once
#include <SDL.h>
#include <vector>

class GeometryController
{
public:
	static std::vector<SDL_Rect*> getRects();
	static unsigned short getNumRects();
	static void addRect(SDL_Rect* r);
	static std::vector<SDL_Rect*> mRects;	
	static unsigned short mNumRects;
	static unsigned short mScreenWidth;
	static unsigned short mScreenHeight;
	void clear();
};

