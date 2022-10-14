#pragma once

#include "Header.h"
#include "Player.h"

class Camera;

namespace Biff
{
	class Game
	{
	public:
		Game();
		~Game();

	private:
		Camera* camera;
		Player* player;

	};
}

