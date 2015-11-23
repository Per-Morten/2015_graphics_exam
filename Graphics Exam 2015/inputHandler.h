#pragma once
#include <SDL.h>
#include "gameEvent.h"
#include <map>


class inputHandler
{
public:
	inputHandler();
	~inputHandler();

	//Key repeat system if key still down issue event
	std::map<ActionEnum, int> eventRepeat;
	std::map<ActionEnum, int> eventRepeatRate;

	bool processEvents(SDL_Event& eventHandler, std::queue<gameEvent>& events);
	void handleKeys(SDL_Event &eventHandler, std::queue<gameEvent>& events);
	void handleMouse(SDL_Event &eventHandler, std::queue<gameEvent>& events);

};

