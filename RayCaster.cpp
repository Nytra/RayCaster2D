#include "RayCaster.h"

RayCaster::RayCaster(int x, int y) {
	mX = x;
	mY = y;
	mRayHits.clear();
	//lineIntersect(SDL_Point{ 0,0 }, SDL_Point{ 10,10 }, SDL_Point{ 0,10 }, SDL_Point{ 10,0 });
}

void RayCaster::setPos(int x, int y) {
	mX = x;
	mY = y;
}

void RayCaster::addRayHit(SDL_Point p) {
	mRayHits.push_back(p);
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
	//std::vector<SDL_Rect> geometry = getRects();
	SDL_Point rayStart;
	SDL_Point rayEnd;
	SDL_Point intersection;
	//bool collides;
	//SDL_Rect debug;
	double rad;
	const int rayLength = 10000;

	SDL_Point bottomLeft, bottomRight, topRight, topLeft;
	SDL_Rect r;

	std::vector<SDL_Point> intersections;

	double shortestDistance;
	int shortestIndex = 0;
	double distance;

	bool hasIntersected;

	//printf("casting...\n");
	for (double a = 0; a < 360; a += interval) {
		//printf("casting ray at angle %d\n", a);
		// cast a ray in this direction
		rayStart.x = mX;
		rayStart.y = mY;
		//SDL_Rect r{ 0, 0, 0, 0 };
		//collides = false;
		rad = a * 3.14 / 180.0;
		shortestDistance = 99999;

		rayEnd.x = (double)rayStart.x + rayLength * sin(rad);
		rayEnd.y = (double)rayStart.y + rayLength * -cos(rad); // we now have a line defined by two points (mX, mY) and (rayEnd.x, rayEnd.y)

		//addRayHit(rayEnd);

		for (int i = 0; i < getNumRects(); i++) {
			// x y w h
			r = *GeometryController::getRects()[i];

			//printf("geo %d x %d y %d w %d h %d\n", i, r.x, r.y, r.w, r.h);

			bottomLeft = { r.x, r.y + r.h };
			bottomRight = { r.x + r.w, r.y + r.h };
			topRight = { r.x + r.w, r.y };
			topLeft = { r.x, r.y };

			hasIntersected = false;

			intersection = lineIntersect(rayStart, rayEnd, bottomLeft, topLeft);
			if (intersection.x != -1 && intersection.y != -1) {
				//addRayHit(&intersection);
				intersections.push_back(intersection);
				hasIntersected = true;
				//break;
			}
			intersection = lineIntersect(rayStart, rayEnd, topRight, topLeft);
			if (intersection.x != -1 && intersection.y != -1) {
				//addRayHit(&intersection);
				if (hasIntersected && sqrt(pow(intersection.x - rayStart.x, 2) + pow(intersection.y - rayStart.y, 2)) < sqrt(pow(intersections[intersections.size() - 1].x - rayStart.x, 2) + pow(intersections[intersections.size() - 1].y - rayStart.y, 2))) {
					intersections[intersections.size() - 1] = intersection;
				}
				else {
					intersections.push_back(intersection);
				}
				hasIntersected = true;
				//break;
			}
			intersection = lineIntersect(rayStart, rayEnd, bottomLeft, bottomRight);
			if (intersection.x != -1 && intersection.y != -1) {
				//addRayHit(&intersection);
				if (hasIntersected && sqrt(pow(intersection.x - rayStart.x, 2) + pow(intersection.y - rayStart.y, 2)) < sqrt(pow(intersections[intersections.size() - 1].x - rayStart.x, 2) + pow(intersections[intersections.size() - 1].y - rayStart.y, 2))) {
					intersections[intersections.size() - 1] = intersection;
				}
				else {
					intersections.push_back(intersection);
				}
				hasIntersected = true;
				//break;
			}
			intersection = lineIntersect(rayStart, rayEnd, topRight, bottomRight);
			if (intersection.x != -1 && intersection.y != -1) {
				//addRayHit(&intersection);
				if (hasIntersected && sqrt(pow(intersection.x - rayStart.x, 2) + pow(intersection.y - rayStart.y, 2)) < sqrt(pow(intersections[intersections.size() - 1].x - rayStart.x, 2) + pow(intersections[intersections.size() - 1].y - rayStart.y, 2))) {
					intersections[intersections.size() - 1] = intersection;
				}
				else {
					intersections.push_back(intersection);
				}
				hasIntersected = true;
				//break;
			}
		}

		// find closest intersection to rayStart.

		for (int i = 0; i < intersections.size(); i++) {
			distance = sqrt(pow((intersections[i].x - rayStart.x), 2) + pow((intersections[i].y - rayStart.y), 2));
			if (distance < shortestDistance) {
				shortestDistance = distance;
				shortestIndex = i;
			}
			//addRayHit(intersections[i]);
		}

		//printf("%d\n", intersections.size());

		if (intersections.size() > 0) {
			intersection.x = intersections[shortestIndex].x;
			intersection.y = intersections[shortestIndex].y;

			addRayHit(intersection);

			//intersections.clear();
		}
		else {
			addRayHit(rayEnd);
		}

		intersections.clear();

		// ignore below

		//while (!collides) {
		//	for (int i = 0; i < getNumRects(); i++) {
		//		if (SDL_PointInRect(&rayEnd, &geometry[i])) {
		//			//printf("collision with wall at x %d y %d\n", rayEnd.x, rayEnd.y);
		//			collides = true;
		//			addRayHit(&rayEnd);
		//			break;
		//		}
		//	}
		//	if (!collides) {
		//		rayEnd.x = (double)rayEnd.x + rayLength * sin(rad);
		//		rayEnd.y = (double)rayEnd.y + rayLength * -cos(rad);
		//	}

		//	// if point exits window, break
		//	if ((rayEnd.x < 0 || rayEnd.x >= mScreenWidth) || (rayEnd.y < 0 || rayEnd.y >= mScreenHeight)) {
		//		addRayHit(&rayEnd);
		//		break; // trust that collides is always false in here
		//	}

		//	//debug = { rayEnd.x, rayEnd.y, 1, 1 };
		//	//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		//	//SDL_RenderFillRect(renderer, &debug);
		//	//SDL_RenderPresent(renderer);
		//	//SDL_Delay(5);
		//	//printf("ray at x %d y %d\n", rayEnd.x, rayEnd.y);
		//}
		//if (collides) {
		//	
		//}
		//end:
	}
	//printf("done\n");
	//geometry = nullptr;
}

std::vector<SDL_Point> RayCaster::getRayHits() {
	return mRayHits;
}

void RayCaster::clear() {
	mRayHits.clear();
}

SDL_Point RayCaster::lineIntersect(SDL_Point a, SDL_Point b, SDL_Point c, SDL_Point d) {
	SDL_Point intersection;
	double s1x, s2x, s1y, s2y, s, t, denom;

	//printf("a: x %d y %d\nb: x %d y %d\nc: x %d y %d\nd: x %d y %d\n", 
		//a.x, a.y,
		//b.x, b.y,
		//c.x, c.y,
		//d.x, d.y);

	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderDrawLine(renderer, c.x, c.y, d.x, d.y);

	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);

	s1x = b.x - a.x;
	s2x = d.x - c.x;
	s1y = b.y - a.y;
	s2y = d.y - c.y;

	denom = ((-s2x * s1y) + (s1x * s2y));

	s = (-s1y * (a.x - c.x) + s1x * (a.y - c.y)) / denom;
	t = (s2x * (a.y - c.y) - s2y * (a.x - c.x)) / denom;

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		intersection.x = a.x + (t * s1x);
		intersection.y = a.y + (t * s1y);
	}
	else {
		intersection.x = -1;
		intersection.y = -1;
	}

	//printf("intersect: x %d y %d\n\n", intersection.x, intersection.y);
	//SDL_Delay(1000000);
	return intersection;
}