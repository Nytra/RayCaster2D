#pragma once
#include <SDL_ttf.h>

class FontController
{
public:
	TTF_Font* getFont();
	static TTF_Font* mFont;
};

