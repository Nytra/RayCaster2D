#include "GeometryController.h"

int GeometryController::getNumRects() {
	return GeometryController::mNumRects;
}

void GeometryController::addRect(SDL_Rect* r) {
	GeometryController::mRects.push_back(r);
	GeometryController::mNumRects += 1;
}

std::vector<SDL_Rect*> GeometryController::getRects() {
	return GeometryController::mRects;
}

std::vector<SDL_Rect*> GeometryController::mRects{};
int GeometryController::mNumRects = 0;
int GeometryController::mScreenHeight = 0;
int GeometryController::mScreenWidth = 0;