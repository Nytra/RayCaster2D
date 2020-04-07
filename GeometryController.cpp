#include "GeometryController.h"

unsigned short GeometryController::getNumRects() {
	return GeometryController::mNumRects;
}

void GeometryController::addRect(SDL_Rect* r) {
	//GeometryController::mRects.push_back(r);
	GeometryController::mRects.emplace_back(r);
	GeometryController::mNumRects += 1;
}

std::vector<SDL_Rect*> GeometryController::getRects() {
	return GeometryController::mRects;
}

void GeometryController::clear() {
	GeometryController::mRects.clear();
}

std::vector<SDL_Rect*> GeometryController::mRects;
unsigned short GeometryController::mNumRects = 0;
unsigned short GeometryController::mScreenHeight = 600;
unsigned short GeometryController::mScreenWidth = 800;