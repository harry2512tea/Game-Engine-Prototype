#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <map>
#include <string>

class Input
{
public:
	Input();
	static Input* getInstance();
	bool GetAxis(const std::string& axis);
	void SetAxis(const std::string& axis, SDL_Scancode key);
	void RemoveAxis(const std::string& axis);

private:
	static Input* instance;
	std::map<const std::string, SDL_Scancode> KeyMap = {
		{ "Forward", SDL_SCANCODE_W },
		{ "Back", SDL_SCANCODE_S },
		{ "Left", SDL_SCANCODE_A },
		{ "Right", SDL_SCANCODE_D },
		{ "Jump", SDL_SCANCODE_SPACE }
	};
};