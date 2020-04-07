#pragma once
#include <SDL.h>
#include <vector>
#include "GeometryController.h"
#include "RenderController.h"

class RayCaster : GeometryController, RenderController
{
public:
	RayCaster(unsigned short x = 0, unsigned short y = 0);
	void setPos(unsigned short x, unsigned short y);
	void cast(unsigned short nRays);
	void addRayHit(SDL_Point p);
	std::vector<SDL_Point> getRayHits();
	SDL_Point getPos();
	void clear();
	SDL_Point lineIntersect(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point d);
private:
	std::vector<SDL_Point> mRayHits;
	unsigned short mX, mY;
};

