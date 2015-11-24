#include "inputHandler.h"
#include <SDL.h>
#include <iostream>
#include <queue>
#include <map>


inputHandler::inputHandler()
{
	eventRepeatRate[ActionEnum::RAISE] = 10; // this is the cooldown in update cycles - currently 10
	eventRepeatRate[ActionEnum::LOWER] = 10; // non repeating keys have eventRepeatRate[action] = INACTIVE
	// You need to add to here to have new keys 


	eventRepeat[ActionEnum::RAISE] = INACTIVE; 
	eventRepeat[ActionEnum::LOWER] = INACTIVE; // Make sure all new events are inactive
}


inputHandler::~inputHandler()
{
}

//returns continue true for continue
bool inputHandler::processEvents(SDL_Event& eventHandler, std::queue<gameEvent>& events)
{
	bool keyContinue = true;
	//Handle new events on queue
	while (SDL_PollEvent(&eventHandler) != 0)
	{
		//User requests quit
		if (eventHandler.type == SDL_QUIT){
			return false;
		}
		else {
			keyContinue = handleKeys(eventHandler, events);
		}
	}
	/*This will trigger all events that have reached cool down */
	for (auto it = eventRepeat.begin(); it != eventRepeat.end(); ++it){
		if (it->second != INACTIVE){
			if (it->second == 0){
				events.push(gameEvent{ 0, it->first }); // raise the event
				it->second = eventRepeatRate[it->first];  // set to cool down
			}
			else {
				--it->second;  // cool down toward triggering
			}
		}
	}
	return keyContinue;
}


/* Handles the keyboard events.  Updates the events queue with new Game Events. quits on esc*/
bool inputHandler::handleKeys(SDL_Event &eventHandler, std::queue<gameEvent>& events)
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
		case SDLK_ESCAPE:
			return false;
			break;
		}
		//This checks if the event is active and on cool down
		if (eventRepeat[action] < 0){
			events.push(gameEvent{ 0, action }); //trigger event
			eventRepeat[action] = eventRepeatRate[action]; // set the repeat cool down
		}

		break;
	case SDL_KEYUP:
		switch (eventHandler.key.keysym.sym){
		case SDLK_9:
			action = ActionEnum::RAISE;
			break;
		case SDLK_8:
			action = ActionEnum::LOWER;
			break;

// remember to add the key up to turn off repeating.

		default:
			break;
		}
		eventRepeat[action] = -1;
		break;

	default:
		break;
	}
	return true; // no exit key pressed.
}
