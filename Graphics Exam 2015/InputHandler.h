#pragma once
#include <SDL.h>
#include "gameEvent.h"
#include <map>
#include <queue>

#define INACTIVE -1

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	//Key repeat system if key still down issue event
	std::map<ActionEnum, int> eventRepeat; // this holds the count down to the next trigger of the event 
	std::map<ActionEnum, int> eventRepeatRate; // This holds the repeat rate per event

	bool processEvents(SDL_Event& eventHandler, std::queue<gameEvent>& events);
	bool handleKeys(SDL_Event &eventHandler, std::queue<gameEvent>& events);
	void handleMouse(SDL_Event &eventHandler, std::queue<gameEvent>& events);

};

