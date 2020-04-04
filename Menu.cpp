#include "Menu.h"

Menu::Menu(int x, int y) {
	mOptionCount = 0;
	mOptionStrings = nullptr;
	mUnselectedFg = { 255, 255, 255, 255 };
	mSelectedFg = {0, 0, 0, 255};
	mSelectedBg = { 255, 255, 255, 255 };
	mX = x;
	mY = y;
	mOptionSelected = 0;
}

void Menu::addOption(std::string str) {

	if (mOptionCount == 0) {
		mOptionStrings = new std::string[mOptionCount + 1];
		mOptionStrings[mOptionCount] = str;
		mOptionCount += 1;
	}
	else {
		std::string* copy = new std::string[mOptionCount];
		for (int i = 0; i < mOptionCount; i++) {
			copy[i] = mOptionStrings[i];
		}
		mOptionStrings = new std::string[mOptionCount + 1];
		for (int i = 0; i < mOptionCount; i++) {
			mOptionStrings[i] = copy[i];
		}
		mOptionStrings[mOptionCount] = str;
		mOptionCount += 1;
	}
}

void Menu::draw() {
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect dstRect;
	for (int i = 0; i < mOptionCount; i++) {
		if (i == mOptionSelected) {
			//surface = TTF_RenderText_Solid(getFont(), mOptionStrings[i].c_str(), mSelectedColor);
			surface = TTF_RenderText_Shaded(getFont(), mOptionStrings[i].c_str(), mSelectedFg, mSelectedBg);
		}
		else {
			surface = TTF_RenderText_Solid(getFont(), mOptionStrings[i].c_str(), mUnselectedFg);
		}

		
		
		dstRect.w = surface->w;
		dstRect.h = surface->h;
		dstRect.x = mX;
		dstRect.y = mY + i * dstRect.h;
		texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		SDL_RenderCopy(getRenderer(), texture, NULL, &dstRect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void Menu::moveCursor(int nPos) {
	if (nPos < 0) {
		while (abs(nPos) > 0) {
			if (mOptionSelected <= 0) {
				mOptionSelected = mOptionCount - 1;
			}
			else {
				mOptionSelected -= 1;
			}
			nPos += 1;
		}
	}
	else {
		while (abs(nPos) > 0) {
			if (mOptionSelected >= mOptionCount - 1) {
				mOptionSelected = 0;
			}
			else {
				mOptionSelected += 1;
			}
			nPos -= 1;
		}
	}
	printf("%d\n", mOptionSelected);
}