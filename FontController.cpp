#include "FontController.h"

TTF_Font* FontController::getFont() {
	return FontController::mFont;
}

TTF_Font* FontController::mFont = nullptr;