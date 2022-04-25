#include "Input.h"

Input* Input::instance = nullptr;

Input::Input()
{
}

Input* Input::getInstance()
{
	if (!instance)
	{
		instance = new Input();
	}

	return instance;
}

bool Input::GetAxis(const std::string& axis)
{
	const Uint8* Keystate = SDL_GetKeyboardState(NULL);

	if (KeyMap.find(axis) == KeyMap.end())
	{
		return false;
	}
	else
	{
		if (Keystate[KeyMap.find(axis)->second])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Input::SetAxis(const std::string& axis, SDL_Scancode key)
{
	if (KeyMap.find(axis) == KeyMap.end())
	{
		KeyMap.insert({ axis, key });
	}
	else
	{
		KeyMap.find(axis)->second = key;
	}
}

void Input::RemoveAxis(const std::string& axis)
{
	
	if (KeyMap.find(axis) != KeyMap.end())
	{
		KeyMap.erase(axis);
	}
}

