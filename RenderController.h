#pragma once
#include <SDL.h>

class RenderController
{
public:
	SDL_Renderer* getRenderer();
	static SDL_Renderer* renderer;
};

