#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include "FontController.h"
#include "RenderController.h"
#include "GeometryController.h"
#include "RayCaster.h"
#include "Menu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int WALL_COUNT = 100;

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("OpenSans-Light.ttf", 16);

	FontController::mFont = font;

	Menu m1(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m1.addOption("Option 1");
	m1.addOption("Option 2");
	m1.addOption("Option 3");
	m1.addOption("Option 4");
	m1.addOption("Option 5");
	m1.addOption("Option 6");

	SDL_Event e;
	bool quit = false;

	SDL_Window* window = SDL_CreateWindow("Menu Framework Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	RenderController::renderer = renderer;

	int optionSelected = 0;

	SDL_Rect walls[WALL_COUNT];
	for (int i = 0; i < WALL_COUNT; i++) {
		walls[i].w = (rand() % (int)(SCREEN_WIDTH * 0.1)) + 20;
		walls[i].h = (rand() % (int)(SCREEN_HEIGHT * 0.1)) + 20;
		walls[i].x = rand() % (SCREEN_WIDTH - walls[i].w);
		walls[i].y = rand() % (SCREEN_HEIGHT - walls[i].h);
		GeometryController::addRect(&walls[i]);
	}

	GeometryController::mScreenHeight = SCREEN_HEIGHT;
	GeometryController::mScreenWidth = SCREEN_WIDTH;

	SDL_Rect* geometry = nullptr;

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	SDL_Point p{ x, y };
	bool good;
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
	}
	RayCaster rayCaster(p.x, p.y);
	SDL_Point m;
	//SDL_Point p;
	SDL_Rect r;
	std::vector<SDL_Point> hits;

	while (!quit) {
		while (SDL_PollEvent(&e) != NULL) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					m1.moveCursor(-1);
					printf("up\n");
					break;
				case SDLK_DOWN:
					m1.moveCursor(1);
					printf("down\n");
					break;
				default:
					break;
				}
			}
		}

		
		SDL_GetMouseState(&m.x, &m.y);
		rayCaster.setPos(m.x, m.y);
		rayCaster.clear();

		geometry = GeometryController::getRects();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
		for (int i = 0; i < GeometryController::getNumRects(); i++) {
			SDL_RenderFillRect(renderer, &geometry[i]);
		}

		geometry = nullptr;

		p = rayCaster.getPos();
		r = { p.x, p.y, 4, 4 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);

		rayCaster.cast(360);
		hits = rayCaster.getRayHits();

		for (int i = 0; i < hits.size(); i++) {
			p = hits[i];
			r = { p.x, p.y, 5, 5 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &r);
			//printf("drew rect at x %d y %d\n", p.x, p.y);
		}

		//m1.draw();

		hits.clear();

		SDL_RenderPresent(renderer);

		//SDL_Delay(1000);
	}

	return 0;
}