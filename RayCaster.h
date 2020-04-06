#pragma once
#include <SDL.h>
#include <vector>
#include "GeometryController.h"
#include "RenderController.h"

class RayCaster : GeometryController, RenderController
{
public:
	RayCaster(int x, int y);
	void setPos(int x, int y);
	void cast(int nRays);
	void addRayHit(SDL_Point p);
	std::vector<SDL_Point> getRayHits();
	SDL_Point getPos();
	void clear();
	SDL_Point lineIntersect(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point d);
private:
	std::vector<SDL_Point> mRayHits;
	int mX, mY;
};

