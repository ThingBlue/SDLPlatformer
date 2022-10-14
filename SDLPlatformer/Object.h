#pragma once

#include "Header.h"
#include "Vector2.h"
#include "Texture.h"

namespace Biff
{
	class Object
	{
	public:

		Object();
		Object(Texture* texture);

		void virtual update();

		Texture* texture;
		bool shouldDraw;
	};
}
