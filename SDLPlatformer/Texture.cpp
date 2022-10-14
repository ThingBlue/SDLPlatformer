#include "Texture.h"

Texture::Texture()
{
    layer = 0;
}

Texture::Texture(Window* window, SDL_Renderer* renderer, int layer)
{
    this->window = window;
    this->renderer = renderer;

    texture = NULL;
    size.x = 0;
    size.y = 0;
    this->layer = layer;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

bool Texture::loadFromFile(string path)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        // Colour key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
        }
        else
        {
            // Get image dimensions
            size.x = loadedSurface->w;
            size.y = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    texture = newTexture;
    return texture != NULL;
}

void Texture::free()
{
    // Free texture if it exists
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        size.x = 0;
        size.y = 0;
    }
}

void Texture::setAlpha(Uint8 alpha)
{
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, size.x, size.y };

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void Texture::renderToRect(SDL_Renderer* renderer, SDL_Rect* dstrect, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, dstrect, angle, center, flip);
}

Vector2 Texture::getSize()
{
    return size;
}

