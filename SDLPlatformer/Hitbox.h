#pragma once

#include "Header.h"

namespace Biff
{
	enum Inertia
	{
		HARD = 0,
		MEDIUM,
		SOFT
	};

	class Hitbox
	{
	public:
		// Constructor
		Hitbox(Vector2 _pos, Vector2 _size, Inertia _inertia);

		// Update functions
		void move(float deltaTime);
		void updatePredict(float deltaTime);

		// Checks if self overlaps with target
		bool isColliding(Hitbox* target);
		bool predictCollision(Hitbox* target);
		Vector2 getDistanceTo(Hitbox* target);

		// Information functions
		SDL_Rect* getBox();
		SDL_Rect* getPredict();
		Vector2 getPos();
		Vector2 getSize();
		Vector2 getVel();
		Vector2 getPredictPos();

		// Management functions
		void setPos(Vector2 pos);
		void setVel(Vector2 vel);

		// Enabling triggers
		bool topEnabled;
		bool botEnabled;
		bool leftEnabled;
		bool rightEnabled;

		Inertia inertia;

	private:
		// Hitbox rectangle
		SDL_Rect box;
		SDL_Rect predict;

		// Physics vectors (Kept as floats)
		Vector2 pos;
		Vector2 vel;
		Vector2 predictPos;
	};
}

