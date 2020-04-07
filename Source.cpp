#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <type_traits>
#include "FontController.h"
#include "RenderController.h"
#include "GeometryController.h"
#include "RayCaster.h"
#include "Menu.h"

#define SCREEN_WIDTH GeometryController::mScreenWidth
#define SCREEN_HEIGHT GeometryController::mScreenHeight

const int WALL_COUNT = 100;
const int WALL_TIMEOUT = 10000;

template<typename T>
struct Record {
	Uint32 time;
	T val;
	Record(T _val) {
		time = SDL_GetTicks();
		val = _val;
	}
};

struct Vec3 {
	float x, y, z;

	Vec3 operator+(const Vec3& v) {
		Vec3 res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}

	// dot product
	float operator* (const Vec3& v) {
		float res;
		res = x * v.x + y * v.y + z * v.z;
		return res;
	}

	Vec3 cross (const Vec3& v) {
		Vec3 res;
		res.x = y * v.z - z * v.y;
		res.y = z * v.x - x * v.z;
		res.z = x * v.y - y * v.x;
		return res;
	}
};

template<typename T>
void placeNoCollide(T& obj) {
	bool good;
	SDL_Rect r;
	r.x = obj.x;
	r.y = obj.y;

	// check if obj is type SDL_Rect
	// because i don't want to overload this function. it would be messy.

	if constexpr (std::is_same_v<T, SDL_Rect>) {
		r.w = obj.w;
		r.h = obj.h;
	}
	else {
		r.w = 1;
		r.h = 1;
	}

	while (true) {
		good = true;
		for (int i = 0; i < GeometryController::getNumRects(); i++) {
			if (SDL_HasIntersection(&r, GeometryController::getRects()[i])) {
				r.x = rand() % SCREEN_WIDTH;
				r.y = rand() % SCREEN_HEIGHT;
				good = false;
				break;
			}
		}
		if (good) {
			break;
		}
	}
	obj.x = r.x;
	obj.y = r.y;
}

void regenWalls() {
	for (int i = 0; i < WALL_COUNT; i++) {
		GeometryController::getRects()[i]->w = (rand() % (int)(SCREEN_WIDTH * 0.1)) + 20;
		GeometryController::getRects()[i]->h = (rand() % (int)(SCREEN_HEIGHT * 0.1)) + 20;
		GeometryController::getRects()[i]->x = rand() % (SCREEN_WIDTH - GeometryController::getRects()[i]->w);
		GeometryController::getRects()[i]->y = rand() % (SCREEN_HEIGHT - GeometryController::getRects()[i]->h);
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("OpenSans-Light.ttf", 16);

	SDL_Init(SDL_INIT_VIDEO);

	FontController::mFont = font;

	SDL_Event e;
	bool quit = false;

	SDL_Window* window = SDL_CreateWindow("2D RayCaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	RenderController::renderer = renderer;

	//int optionSelected = 0;

	GeometryController::mRects.reserve(WALL_COUNT);

	for (int i = 0; i < WALL_COUNT; i++) {
		SDL_Rect* r = new SDL_Rect;

		r->w = (rand() % (int)(SCREEN_WIDTH * 0.1)) + 20;
		r->h = (rand() % (int)(SCREEN_HEIGHT * 0.1)) + 20;
		r->x = rand() % (SCREEN_WIDTH - r->w);
		r->y = rand() % (SCREEN_HEIGHT - r->h);

		GeometryController::addRect(r);
	}

	unsigned short x = SCREEN_WIDTH / 2;
	unsigned short y = SCREEN_HEIGHT / 2;

	RayCaster rayCaster;
	SDL_Point m{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	std::vector<SDL_Point> hits;
	bool mouseMotion = false;

	SDL_Rect target{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10, 10 };
	placeNoCollide(target);

	GeometryController::addRect(&target);

	bool mouseInsideWall = false;

	bool drawWalls = true;
	bool found;

	Uint32 lastShakeTime = SDL_GetTicks();

	while (!quit) {
		while (SDL_PollEvent(&e) != NULL) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					//m1.moveCursor(-1);
					printf("up\n");
					break;
				case SDLK_DOWN:
					//m1.moveCursor(1);
					printf("down\n");
					break;
				case SDLK_p:
					regenWalls();
					rayCaster.cast(360);
					break;
				case SDLK_w:
					drawWalls = !drawWalls;
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&m.x, &m.y);
				mouseInsideWall = false;
				
				for (int i = 0; i < WALL_COUNT; i++) {
					GeometryController::getRects()[i]->w += 1;
					GeometryController::getRects()[i]->h += 1;

					if (SDL_PointInRect(&m, GeometryController::getRects()[i])) {
						mouseInsideWall = true;
					}
					
					GeometryController::getRects()[i]->w -= 1;
					GeometryController::getRects()[i]->h -= 1;

					if (mouseInsideWall) {
						break;
					}
				}

				if (!mouseInsideWall) {
					rayCaster.setPos(m.x, m.y);
					mouseMotion = true;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawPoint(renderer, rayCaster.getPos().x, rayCaster.getPos().y);

		if (mouseMotion) {
			rayCaster.cast(360);
			mouseMotion = false;
		}
		else if (!mouseInsideWall && SDL_GetTicks() - lastShakeTime > 200){
			//rayCaster.setPos(m.x + (rand() % 3) - 1, m.y + (rand() % 3) - 1);
			//rayCaster.cast(360);
			//lastShakeTime = SDL_GetTicks();
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &target);

		for (int i = 0; i < rayCaster.getRayHits().size(); i++) {

			SDL_Point p = rayCaster.getRayHits()[i];

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, rayCaster.getPos().x, rayCaster.getPos().y, p.x, p.y);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawPoint(renderer, p.x, p.y);

			if (SDL_PointInRect(&p, &target)) {
				placeNoCollide(target);
			}

		}

		if (drawWalls) {
			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
			for (int j = 0; j < WALL_COUNT; j++) {
				SDL_RenderFillRect(renderer, GeometryController::getRects()[j]);
			}
		}

		SDL_RenderPresent(renderer);

	}

	return 0;
}