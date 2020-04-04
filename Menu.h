#pragma once
#include <string>
#include <SDL.h>
#include "FontController.h"
#include "RenderController.h"

class Menu : FontController, RenderController
{
public:
	Menu(int x = 0, int y = 0);
	void addOption(std::string str);
	void draw();
	void moveCursor(int nPos);
private:
	std::string* mOptionStrings;
	int mOptionCount;
	SDL_Color mUnselectedFg, mSelectedFg, mSelectedBg;
	int mX, mY;
	int mOptionSelected;
};

