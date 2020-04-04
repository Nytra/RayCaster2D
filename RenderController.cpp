#include "RenderController.h"

SDL_Renderer* RenderController::getRenderer() {
	return RenderController::renderer;
}

SDL_Renderer* RenderController::renderer = nullptr;