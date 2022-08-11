#pragma once

#include "header.h"

class BRect
{
public:
	// Default constructor
	BRect()
	{
		// Set core float variables
		x = 0.0f;
		y = 0.0f;
		w = 0.0f;
		h = 0.0f;

		// Set actual SDL_Rect object
		rect.x = 0;
		rect.y = 0;
		rect.w = 0;
		rect.h = 0;
	}

	// Constructor with scalars
	BRect(float x, float y, float w, float h)
	{
		// Set core float variables
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		// Set actual SDL_Rect object
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	// Constructor with Vector2's
	BRect(Vector2 pos, Vector2 size)
	{
		// Set core float variables
		this->x = pos.x;
		this->y = pos.y;
		this->w = size.x;
		this->h = size.y;

		// Set actual SDL_Rect object
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	// Management functions
	// Set position using a Vector2
	void setPos(Vector2 pos)
	{
		// Set core float variables
		this->x = pos.x;
		this->y = pos.y;

		// Set actual SDL_Rect object
		rect.x = x;
		rect.y = y;
	}
	// Set size using a Vector2
	void setSize(Vector2 size)
	{
		// Set core float variables
		this->w = size.x;
		this->h = size.y;

		// Set actual SDL_Rect object
		rect.w = w;
		rect.h = h;
	}
	// Set all variables using a pointer to an SDL_Rect
	void setRect(SDL_Rect* rect)
	{
		// Set core float variables
		this->x = rect->x;
		this->y = rect->y;
		this->w = rect->w;
		this->h = rect->h;

		// Set actual SDL_Rect object
		this->rect.x = x;
		this->rect.y = y;
		this->rect.w = w;
		this->rect.h = h;
	}

	// Information functions
	Vector2 getPos()
	{
		return Vector2(x, y);
	}
	Vector2 getSize()
	{
		return Vector2(w, h);
	}
	SDL_Rect* getRect()
	{
		//Set rect values equal to float values
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		return &rect;
	}

	// Core variables
	float x;
	float y;
	float w;
	float h;

private:
	// Actual SDL_Rect object
	SDL_Rect rect;
};

