#pragma once

#include "Vector2.h"
#include "Window.h"
#include "Header.h"

namespace Biff
{
    class Texture
    {
    public:
        // Constructor/Destructor
        Texture();
        Texture(Window* window, SDL_Renderer* renderer, int layer = 0);
        ~Texture();

        // Management functions
        bool loadFromFile(std::string path);
        void free();
        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void renderToRect(SDL_Renderer* renderer, SDL_Rect* dstrect, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void setAlpha(Uint8 alpha);

        // Information functions
        Vector2 getSize();

        // The actual hardware texture
        SDL_Texture* texture;

        // Image dimensions
        Vector2 size;

        // Layer to render texture on
        int layer;

    private:
        // Pointers
        Window* window;
        SDL_Renderer* renderer;
    };
}

