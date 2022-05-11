#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <map>
#include <string>

class Input
{
public:
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
		{ "Up", SDL_SCANCODE_SPACE },
		{ "Down", SDL_SCANCODE_C },
		{ "RotLeft", SDL_SCANCODE_Q },
		{ "RotRight", SDL_SCANCODE_E },
		{ "Start", SDL_SCANCODE_X },
		{"ramps", SDL_SCANCODE_1},
		{"collide", SDL_SCANCODE_2},
		{"bounce", SDL_SCANCODE_3},
		{"spin", SDL_SCANCODE_4},
		{ "spin1", SDL_SCANCODE_RIGHT },
		{ "spin2", SDL_SCANCODE_LEFT }
	};
};
