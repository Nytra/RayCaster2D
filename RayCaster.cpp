#include "RayCaster.h"

RayCaster::RayCaster(int x, int y) {
	mX = x;
	mY = y;
	mRayHits.clear();
}

void RayCaster::setPos(int x, int y) {
	mX = x;
	mY = y;
}

void RayCaster::addRayHit(SDL_Point* p) {
	mRayHits.push_back(*p);
	//printf("adding ray hit x %d y %d\n", p->x, p->y);
}

SDL_Point RayCaster::getPos() {
	SDL_Point p;
	p.x = mX;
	p.y = mY;
	return p;
}

void RayCaster::cast(int nRays) {
	int interval = 360.0 / nRays;
	SDL_Rect* geometry = getRects();
	SDL_Point rayEnd;
	bool collides;
	SDL_Rect debug;
	double rad;

	//printf("casting...\n");
	for (double a = 0; a < 360; a += interval) {
		//printf("casting ray at angle %d\n", a);
		// cast a ray in this direction
		rayEnd.x = mX;
		rayEnd.y = mY;
		//SDL_Rect r{ 0, 0, 0, 0 };
		collides = false;
		rad = a * 3.14 / 180.0;
		while (!collides) {
			for (int i = 0; i < getNumRects(); i++) {
				if (SDL_PointInRect(&rayEnd, &geometry[i])) {
					//printf("collision with wall at x %d y %d\n", rayEnd.x, rayEnd.y);
					collides = true;
					addRayHit(&rayEnd);
					break;
				}
			}
			if (!collides) {
				rayEnd.x = (double)rayEnd.x + 15.0 * sin(rad);
				rayEnd.y = (double)rayEnd.y + 15.0 * -cos(rad);
			}

			for (int i = 0; i < getNumRects(); i++) {
				if (SDL_PointInRect(&rayEnd, &geometry[i])) {
					//printf("collision with wall at x %d y %d\n", rayEnd.x, rayEnd.y);
					//collides = true;
					//addRayHit(&rayEnd);
					//break;
					while (SDL_PointInRect(&rayEnd, &geometry[i])) { // go back along the line until not intersecting with the wall
						rayEnd.x = (double)rayEnd.x - 5.0 * sin(rad);
						rayEnd.y = (double)rayEnd.y - 5.0 * -cos(rad);
					}
					rayEnd.x = (double)rayEnd.x + 5.0 * sin(rad);
					rayEnd.y = (double)rayEnd.y + 5.0 * -cos(rad);
					break;
				}
			}

			// if point exits window, break
			if ((rayEnd.x < 0 || rayEnd.x >= mScreenWidth) || (rayEnd.y < 0 || rayEnd.y >= mScreenHeight)) {
				//goto end;
				addRayHit(&rayEnd);
				break; // trust that collides is always false in here
			}
			//debug = { rayEnd.x, rayEnd.y, 1, 1 };
			//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			//SDL_RenderFillRect(renderer, &debug);
			//SDL_RenderPresent(renderer);
			//SDL_Delay(5);
			//printf("ray at x %d y %d\n", rayEnd.x, rayEnd.y);
		}
		//if (collides) {
		//	
		//}
		//end:
	}
	//printf("done\n");
	geometry = nullptr;
}

std::vector<SDL_Point> RayCaster::getRayHits() {
	return mRayHits;
}

void RayCaster::clear() {
	mRayHits.clear();
}