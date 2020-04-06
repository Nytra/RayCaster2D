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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int WALL_COUNT = 100;

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

	//printf("entering loop\n");

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

void regenWalls(SDL_Rect* walls) {
	//SDL_Rect walls[WALL_COUNT];
	for (int i = 0; i < WALL_COUNT; i++) {
		walls[i].w = (rand() % (int)(SCREEN_WIDTH * 0.1)) + 20;
		walls[i].h = (rand() % (int)(SCREEN_HEIGHT * 0.1)) + 20;
		walls[i].x = rand() % (SCREEN_WIDTH - walls[i].w);
		walls[i].y = rand() % (SCREEN_HEIGHT - walls[i].h);
		//GeometryController::addRect(&walls[i]);
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("OpenSans-Light.ttf", 16);

	SDL_Init(SDL_INIT_VIDEO);

	FontController::mFont = font;

	//Menu m1(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//m1.addOption("Option 1");
	//m1.addOption("Option 2");
	//m1.addOption("Option 3");
	//m1.addOption("Option 4");
	//m1.addOption("Option 5");
	//m1.addOption("Option 6");

	SDL_Event e;
	bool quit = false;

	SDL_Window* window = SDL_CreateWindow("2D RayCaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	RenderController::renderer = renderer;

	int optionSelected = 0;

	SDL_Rect walls[WALL_COUNT];
	regenWalls(walls);
	for (int i = 0; i < WALL_COUNT; i++) {
		//walls[i].w = (rand() % (int)(SCREEN_WIDTH * 0.1)) + 20;
		//walls[i].h = (rand() % (int)(SCREEN_HEIGHT * 0.1)) + 20;
		//walls[i].x = rand() % (SCREEN_WIDTH - walls[i].w);
		//walls[i].y = rand() % (SCREEN_HEIGHT - walls[i].h);
		GeometryController::addRect(&walls[i]);
	}

	/*for (int i = 0; i < WALL_COUNT; i++) {
		printf("wall %d x %d y %d w %d h %d\n", i,
			GeometryController::getRects()[i].x, GeometryController::getRects()[i].y,
			GeometryController::getRects()[i].w, GeometryController::getRects()[i].h);
	}*/

	GeometryController::mScreenHeight = SCREEN_HEIGHT;
	GeometryController::mScreenWidth = SCREEN_WIDTH;

	//std::vector<SDL_Rect> geometry;

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	SDL_Point p{ x, y };
	/*bool good;
	while (true) {
		good = true;
		for (int i = 0; i < GeometryController::getNumRects(); i++) {
			if (SDL_PointInRect(&p, &GeometryController::getRects()[i])) {
				p.x = rand() % SCREEN_WIDTH;
				p.y = rand() % SCREEN_HEIGHT;
				good = false;
				break;
			}
		}
		if (good) {
			break;
		}
	}*/
	placeNoCollide(p);
	RayCaster rayCaster(p.x, p.y);
	SDL_Point m;
	//SDL_Point p;
	SDL_Rect r;
	std::vector<SDL_Point> hits;
	bool mouseMotion = false;

	SDL_Rect target{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 10, 10 };
	placeNoCollide(target);

	//printf("placed target\n");

	GeometryController::addRect(&target);

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
					regenWalls(walls);
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&m.x, &m.y);
				rayCaster.setPos(m.x, m.y);
				rayCaster.clear();
				mouseMotion = true;
			}
		}

		//geometry = GeometryController::getRects();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
		for (int i = 0; i < WALL_COUNT; i++) {
			SDL_RenderFillRect(renderer, GeometryController::getRects()[i]);
		}

		//geometry = nullptr;

		p = rayCaster.getPos();
		r = { p.x, p.y, 4, 4 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);

		if (mouseMotion) {

			rayCaster.cast(360);
			
			mouseMotion = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &target);

		hits = rayCaster.getRayHits();

		for (int i = 0; i < hits.size(); i++) {
			p = hits[i];
			r = { p.x, p.y, 1, 1 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, rayCaster.getPos().x, rayCaster.getPos().y, p.x, p.y);
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderFillRect(renderer, &r);
			//printf("drew rect at x %d y %d\n", p.x, p.y);
			//target = { target.x - 2, target.y - 2, target.w + 2, target.h + 2 };
			if (SDL_PointInRect(&p, &target)) {
				//printf("raycaster hit target at pos x %d y %d\n", p.x, p.y);
				//target = { target.x + 2, target.y + 2, target.w - 2, target.h - 2 };
				placeNoCollide(target);
			}
			else {
				//target = { target.x + 2, target.y + 2, target.w - 2, target.h - 2 };
				//p.x -= 1;
				//p.y -= 1;
				//if (SDL_PointInRect(&p, &target)) {
					//placeNoCollide(target);
				//}
			}
		}

		hits.clear();

		SDL_RenderPresent(renderer);

		//printf("%d\n", GeometryController::getNumRects());

		//SDL_Delay(1000);
	}

	return 0;
}