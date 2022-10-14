#pragma once

#include "Header.h"

namespace Biff
{
	class Window
	{
	public:
		// Constructor/destructor
		Window();
		~Window();

		// Information functions
		SDL_Window* getWindow();

	private:
		// Core window
		SDL_Window* window;
	};
}

