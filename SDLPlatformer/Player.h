#pragma once

#include "Header.h"
#include "Texture.h"
#include "Animation.h"
#include "Hitbox.h"
#include "Window.h"
#include "Object.h"

namespace Biff
{
	class Player : public Object
	{
	public:
		// Constructor
		Player(Vector2 hitboxPos, Vector2 hitboxSize, Texture* sprite, Vector2 imageCount, Window* window, SDL_Renderer* renderer);
		~Player();

		// State machine functions
		void deadState(float deltaTime);
		void idleState(float deltaTime);
		void walkState(float deltaTime);
		void runState(float deltaTime);
		void jumpState(float deltaTime);
		void crouchState(float deltaTime);

		// Function for handling event
		void handleEvent(SDL_Event& e);

		// Update functions
		void updateAnimation(float deltaTime);
		void update(float deltaTime);
		void render();

		// Information functions
		Vector2 getPos();
		Vector2 getSize();
		Vector2 getVel();
		Hitbox* getHitbox();
		PlayerState getState();

		// Management functions
		void setPos(Vector2 pos);
		void setVel(Vector2 vel);
		void setCanJump(bool canJump);

	protected:
		// Associated hitbox
		Hitbox hitbox;

		// Graphics
		Animation animation;
		int row;
		int colBegin;
		int colEnd;
		float switchTime;
		bool faceRight;
		SDL_Renderer* renderer;

		// Movement
		float speed;
		float jumpHeight;
		Vector2 vel;
		bool canJump;

		// State
		PlayerState state;

		// Keys
		bool keyW, keyS, keyA, keyD;
	};
}
