#include "GeometryController.h"

int GeometryController::getNumRects() {
	return mNumRects;
}

void GeometryController::addRect(SDL_Rect* r) {
	SDL_Rect* copy = new SDL_Rect[mNumRects];
	for (int i = 0; i < mNumRects; i++) {
		copy[i] = mRects[i];
	}
	mRects = new SDL_Rect[mNumRects + 1];
	for (int i = 0; i < mNumRects; i++) {
		mRects[i] = copy[i];
	}
	mRects[mNumRects] = *r;
	mNumRects += 1;
	delete[] copy;
}

SDL_Rect* GeometryController::getRects() {
	return mRects;
}

SDL_Rect* GeometryController::mRects = nullptr;
int GeometryController::mNumRects = 0;
int GeometryController::mScreenHeight = 0;
int GeometryController::mScreenWidth = 0;