#include "Input.h"

Input* Input::instance = nullptr;

//function to ensure only one instance of this class exists at any time
Input* Input::getInstance()
{
	//checks if the class is instantiated
	if (!instance)
	{
		//instantiates the class under the variable name instance
		instance = new Input();
	}

	//returns the static instance of the class
	return instance;
}

bool Input::GetAxis(const std::string& axis)
{
	//retrieves the current state of the keyboard
	const Uint8* Keystate = SDL_GetKeyboardState(NULL);

	//checks if the axis exists
	if (KeyMap.find(axis) == KeyMap.end())
	{
		//returns false if the axis doesn't exist
		return false;
	}
	else
	{
		//cheks if the axis' assigned key is pressed
		if (Keystate[KeyMap.find(axis)->second])
		{
			//key is pressed
			return true;
		}
		else
		{
			//key is not pressed
			return false;
		}
	}
}

void Input::SetAxis(const std::string& axis, SDL_Scancode key)
{
	//checks if the axis exists in the mapping
	if (KeyMap.find(axis) == KeyMap.end())
	{
		//adds a new axis by the specified name, linked to the specified key
		KeyMap.insert({ axis, key });
	}
	else
	{
		//changes the specified axis' assigned key to a new specified key
		KeyMap.find(axis)->second = key;
	}
}

void Input::RemoveAxis(const std::string& axis)
{
	//checks if the axis exists
	if (KeyMap.find(axis) != KeyMap.end())
	{
		//deletes the specified key binding
		KeyMap.erase(axis);
	}
}

