/*
WARNING: the code that follows will make you cry;
a safety pig has been provided below for your benefit
						 _
 _._ _..._ .-',     _.._(`))
'-. `     '  /-._.-'    ',/
  )         \            '.
 / _    _    |             \
|  a    a    /              |
 \   .-.                     ;
  '-('' ).-'       ,'       ;
	 '-;           |      .'
		\           \    /
		| 7  .__  _.-\   \
		| |  |  ``/  /`  /
	   /,_|  |   /,_/   /
		  /,_/      '`-'
*/

#include "Rect.h"
#include "Timer.h"
#include "Game.h"
#include "MainMenu.h"

#include "Header.h"

// Declare global objects
SDL_Window* window;
SDL_Renderer* renderer;

MainMenu* mainMenu;
Game* game;

// Declare global variables
GameState gameState;

map<SDL_Keycode, bool> keyMap;
map<SDL_Keycode, bool> keyDownMap;
map<SDL_Keycode, bool> keyUpMap;

// Declare camera
Rect* camera;
float cameraXMin, cameraXMax, cameraYMin, cameraYMax;

// Declare functions
bool init();
void handleCollisions(float deltaTime);
void updateCamera(float deltaTime);

int main(int argc, char* argv[])
{
	// Initialize SDL libraries
	if (!init())
	{
		cout << "Initialization failed!" << endl;
		return 1;
	}

	// Initialize background processes
	// Initialize window and renderer
	window = SDL_CreateWindow("SDLPlatformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN & SDL_WINDOW_MOUSE_FOCUS);
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Initialize global variables
	gameState = GameState::MAIN_MENU;

	// Initialize camera
	camera = new Rect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	cameraXMin = 0.0f;
	cameraXMax = 1280.0f;
	cameraYMin = -640.0f;
	cameraYMax = 0.0f;

	// Initialize timer
	Timer timer;
	float deltaTime = 0.0;
	float timeElapsed = 0.0;

	// Initialize media maps

	// Load media

	// Initialize game loop variables
	// Allows the program to exit
	bool quit = false;

	// For event handling
	SDL_Event e;

	// Main game loop
	while (!quit)
	{
		// Poll any user events
		while (SDL_PollEvent(&e) != 0)
		{
			// User clicks 'X' exit button
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				// Change key map
				keyMap[e.key.keysym.sym] = true;
				keyDownMap[e.key.keysym.sym] = true;
			}
			else if (e.type == SDL_KEYUP)
			{
				// Change key map
				keyMap[e.key.keysym.sym] = false;
				keyUpMap[e.key.keysym.sym] = true;
			}
		}

		// Update all objects
		switch (gameState)
		{
		case GameState::MAIN_MENU:
			game = new Game();
			break;
		case GameState::GAME:
			break;
		case GameState::PAUSE:
			break;

		}
		// Update game objects

		// Update UI objects

		// Do collisions

		// Detect state switches

		// Move all objects

		// Update camera

		// Render all objects
		// Clear screen
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// RENDER BLOCK HITBOXES FOR TESTING

		// Render player

		// Update the screen
		SDL_RenderPresent(renderer);

		// Reset key maps
		keyDownMap.clear();
		keyUpMap.clear();

		// Restart timer at the end of frame
		deltaTime = timer.elapsed();
		timeElapsed += timer.elapsed();
		timer.reset();

		// Limit deltaTime
		if (deltaTime > 0.05f) // 20 fps
		{
			deltaTime = 0.05f;
		}
	}


	//Halt music
	//audio.haltMusic();

	// Cleanup
	// Destroy objects
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Quit SDL
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();


	return 0;
}

bool init()
{
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	// Initialize SDL_image
	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags))
	{
		printf("SDL_image could not initialize! SDL Error: %s\n", IMG_GetError());
		success = false;
	}

	// Initialize SDL_mixer	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		printf("SDL_TTF could not initialize!SDL Error : % s\n", TTF_GetError());
		success = false;
	}

	return success;
}
/*
void handleCollisions(float deltaTime)
{
	// Player collision
	// Get player hitbox
	Hitbox* playerHitbox = player->getHitbox();

	// Player state variables
	bool isGround = false;
	// Enum to store direction of wall collision
	Direction wallDir = Direction::UP;

	// Loop through blocks
	size_t blocksSize = blocks.size();
	for (int i = 0; i < blocksSize; i++)
	{
		// Update player prediction box
		playerHitbox->updatePredict(deltaTime);

		// Get block hitbox and update its prediction box
		Hitbox* blockHitbox = blocks.at(i)->getHitbox();
		blockHitbox->updatePredict(deltaTime);

		// Detect incoming collision
		if (playerHitbox->predictCollision(blockHitbox))
		{
			// Information variables
			// Player variables
			Vector2 playerPos = playerHitbox->getPos();
			Vector2 playerSize = playerHitbox->getSize();
			Vector2 vel = playerHitbox->getVel();

			// Block variables
			Vector2 blockPos = blockHitbox->getPos();
			Vector2 blockSize = blockHitbox->getSize();

			// Get distance between player and block
			Vector2 dist = playerHitbox->getDistanceTo(blockHitbox);

			// Enum to store axis of collision
			Axis collisionAxis;

			bool noCollision = false;

			// Check for single axis collision
			bool singleAxis = false;
			bool playerMidColliding = false;
			// Check if any side of the player is eclipsed by the block
			// Eclipsed on X axis, collision must occur on Y axis
			if ((playerPos.x > blockPos.x) && (playerPos.x < (blockPos.x + blockSize.x)) || // Left side
				((playerPos.x + playerSize.x) > blockPos.x) && ((playerPos.x + playerSize.x) < (blockPos.x + blockSize.x)))   // Right side
			{
				singleAxis = true;
				collisionAxis = Axis::Y;
			}
			// Eclipsed on Y axis, collision must occur on X axis
			if ((playerPos.y > blockPos.y) && (playerPos.y < (blockPos.y + blockSize.y)) || // Top side
				((playerPos.y + playerSize.y) > blockPos.y) && ((playerPos.y + playerSize.y) < (blockPos.y + blockSize.y)))   // Bottom side
			{
				singleAxis = true;
				collisionAxis = Axis::X;
			}

			// Check if any side of the block is eclipsed by the player
			// Eclipsed on X axis, collision must occur on Y axis
			if ((blockPos.x > playerPos.x) && (blockPos.x < (playerPos.x + playerSize.x)) || // Left side
				((blockPos.x + blockSize.x) > playerPos.x) && ((blockPos.x + blockSize.x) < (playerPos.x + playerSize.x)))   // Right side
			{
				singleAxis = true;
				collisionAxis = Axis::Y;
			}
			// Eclipsed on Y axis, collision must occur on X axis
			if ((blockPos.y > playerPos.y) && (blockPos.y < (playerPos.y + playerSize.y)) || // Top side
				((blockPos.y + blockSize.y) > playerPos.y) && ((blockPos.y + blockSize.y) < (playerPos.y + playerSize.y)))   // Bottom side
			{
				singleAxis = true;
				collisionAxis = Axis::X;
			}

			// Check if the player's center pixel is colliding on the Y axis for wall jumping
			float playerMid = playerPos.y + (playerSize.y / 2.0f);
			if (playerMid > blockPos.y && playerMid < (blockPos.y + blockSize.y))
			{
				playerMidColliding = true;
			}

			// Collision on both axes
			if (!singleAxis)
			{
				// Get time of overlap on either axis
				float xOverlapTime = dist.x / (vel.x * deltaTime);
				float yOverlapTime = dist.y / (vel.y * deltaTime);

				// Check for overlap at the average time
				float avgTime = (xOverlapTime + yOverlapTime) / 2;

				// Collision occurs at the shorter time
				if ((playerPos.x + (avgTime * vel.x * deltaTime)) + playerSize.x >= blockPos.x &&
					blockPos.x + blockSize.x >= (playerPos.x + (avgTime * vel.x * deltaTime)) &&
					(playerPos.y + (avgTime * vel.y * deltaTime)) + playerSize.y >= blockPos.y &&
					blockPos.y + blockSize.y >= (playerPos.y + (avgTime * vel.y * deltaTime)))
				{
					// Y
					if (yOverlapTime < xOverlapTime)
					{
						collisionAxis = Axis::Y;
					}
					// X
					else if (yOverlapTime > xOverlapTime)
					{
						collisionAxis = Axis::X;
					}
					// No actual collision
					else
					{
						noCollision = true;
					}
				}
				// Collision occurs at the longer time
				else
				{
					// Y
					if (yOverlapTime > xOverlapTime)
					{
						collisionAxis = Axis::Y;
					}
					// X
					else if (yOverlapTime > xOverlapTime)
					{
						collisionAxis = Axis::X;
					}
					// No actual collision
					else
					{
						noCollision = true;
					}
				}
			}

			// Resolve collision
			if (!noCollision)
			{
				// X
				if (collisionAxis == Axis::X)
				{
					player->setPos(Vector2(round(playerPos.x + dist.x), playerPos.y));
					player->setVel(Vector2(0.0, vel.y));

					// If touching wall
					// Left
					if (playerHitbox->getBox()->x == (blockHitbox->getBox()->x + blockSize.x) && playerMidColliding)
					{
						wallDir = Direction::LEFT;
					}
					// Right
					if ((playerHitbox->getBox()->x + playerSize.x) == blockHitbox->getBox()->x && playerMidColliding)
					{
						wallDir = Direction::RIGHT;
					}
				}
				// Y
				else
				{
					player->setPos(Vector2(playerPos.x, round(playerPos.y + dist.y)));
					player->setVel(Vector2(vel.x, 0.0));

					// If touching ground
					if ((playerHitbox->getBox()->y + playerSize.y) == blockHitbox->getBox()->y)
					{
						isGround = true;
					}
				}
			}
		}
	}

	// Set player state variables
	// Only cling to wall if player is not on the ground
	if (isGround)
	{
		// Set grounded to true
		player->setGrounded(true);

		// Do not cling to wall
		player->setWallCling(Direction::UP);
	}
	// Not on ground
	else
	{
		// Reset grounded to false
		player->setGrounded(false);

		// Cling to wall if player is not on the ground
		if (wallDir == Direction::UP)
		{
			player->setWallCling(Direction::UP);
		}
		// Player is holding left
		else if (wallDir == Direction::LEFT && player->keyA)
		{
			player->setWallCling(Direction::LEFT);
		}
		// Player is holding right
		else if (wallDir == Direction::RIGHT && player->keyD)
		{
			player->setWallCling(Direction::RIGHT);
		}
	}
}

void updateCamera(float deltaTime)
{
	// Move camera towards player position
	camera->x += (player->getPos().x - camera->x - 640.0f) * deltaTime * 7;
	camera->y += (player->getPos().y - camera->y - 640.0f) * deltaTime * 7;

	// Stop camera from scrolling outside the level
	if (camera->x < cameraXMin)
		camera->x = cameraXMin;
	if (camera->x > cameraXMax)
		camera->x = cameraXMax;
	if (camera->y < cameraYMin)
		camera->y = cameraYMin;
	if (camera->y > cameraYMax)
		camera->y = cameraYMax;
}
*/
