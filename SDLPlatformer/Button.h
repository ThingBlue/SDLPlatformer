#pragma once

#include <vector>
#include <SDL.h>
#include "Vector2.h"
#include "Texture.h"

typedef void (*onClickFunc)(void); //Function pointer typedef for OnClick

namespace Biff
{
	/**
	* Menu Button
	*/
	class Button
	{
	public:
		enum class ButtonStates
		{
			NORMAL,
			HOVERED,
			PRESSED
		};

		Vector2* size; //Size of button
		Vector2* pos; //Top left position of button
		bool isEnabled = true; //Button is clickable
		bool isPressed = false; //True if button is currently pressed
		bool wasClicked = false; //True if button was clicked. This is what should be checked to find out if a button was clicked
		int menuID = 0; //ID assigned by Menu owner
		ButtonStates state; //Current state of button. Decides current texture to display
		Texture* normal; //Normal texture
		Texture* hovered; //Texture when button is being hovered over
		Texture* pressed; //Texture when button is pressed

		Button(Vector2& pos, Vector2& size, Texture& normal, Texture& hovered, Texture& pressed, int menuID); //Constructor
		~Button(); //Destructor

		bool mouseIsInside(int x, int y);
		void updateButton(SDL_Event* e);
		void setState(ButtonStates state);
		void onClick(onClickFunc pFunc); //See function pointer typedef
		Texture* getTexture();
	};
}

