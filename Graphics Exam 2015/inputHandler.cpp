#include "inputHandler.h"
#include <SDL.h>
#include <iostream>


inputHandler::inputHandler()
{
	eventRepeatRate[ActionEnum::RAISE] = 10;
	eventRepeatRate[ActionEnum::LOWER] = 10;
	eventRepeat[ActionEnum::RAISE] = -1;
	eventRepeat[ActionEnum::LOWER] = -1;
}


inputHandler::~inputHandler()
{
}

//returns continue true for continue
bool inputHandler::processEvents(SDL_Event& eventHandler, std::queue<gameEvent>& events)
{
	//Handle new events on queue
	while (SDL_PollEvent(&eventHandler) != 0)
	{
		//User requests quit
		if (eventHandler.type == SDL_QUIT){
			return false;
		}
		else {
			handleKeys(eventHandler, events);
		}
	}
	for (auto it = eventRepeat.begin(); it != eventRepeat.end(); ++it){
		if (it->second == 0){
			events.push(gameEvent(it->first));
			it->second = eventRepeatRate[it->first];
		}
		else if (it->second > 0){
			--it->second;
		}
	}


	return true;
}

void inputHandler::handleKeys(SDL_Event &eventHandler, std::queue<gameEvent>& events)
{
	ActionEnum action;
	switch (eventHandler.type){
	case SDL_KEYDOWN:
		switch (eventHandler.key.keysym.sym){
		case SDLK_9:
			action = ActionEnum::RAISE;
			break;
		case SDLK_8:
			action = ActionEnum::LOWER;
			break;
		}
		if (eventRepeat[action] < 0){
			events.push(gameEvent(action));
			eventRepeat[action] = eventRepeatRate[action];
		}

		break;
	case SDL_KEYUP:
		switch (eventHandler.key.keysym.sym){
		case SDLK_9:
			eventRepeat[ActionEnum::RAISE] = -1;
			break;
		case SDLK_8:
			eventRepeat[ActionEnum::LOWER] = -1;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

}
