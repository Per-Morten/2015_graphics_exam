#include "InputHandler.h"
#include <SDL.h>
#include <iostream>
#include <queue>
#include <map>

/*
To add a new key change: 1) InputHandler eventRepeatRate 2) IntputHandler eventRepeat  3) handleKeys KeyDown 4) handleKeys KeyUp
To add a new Game Event add it to the GameEvent.h ActionEnum
*/

InputHandler::InputHandler()
{
    eventRepeatRate[ActionEnum::RAISE] = 10; // this is the cooldown in update cycles - currently 10 - repeatRate = 0 is every update
    eventRepeatRate[ActionEnum::LOWER] = 10; // non repeating keys have eventRepeatRate[action] = INACTIVE for keyboard default or INT_MAX for almost never repeat.
    eventRepeatRate[ActionEnum::RESET] = INACTIVE;  // This currently results in the standard key repeat of the Window keyboard
    // You need to add to here to have new keys 
    // 1) add a repeat rate


    eventRepeat[ActionEnum::RAISE] = INACTIVE;
    eventRepeat[ActionEnum::LOWER] = INACTIVE; // Make sure all new events are inactive
    eventRepeat[ActionEnum::RESET] = INACTIVE; // Make sure all new events are inactive
    // 2) make sure it is initialised to inactive

}

/* Handles the keyboard events.  Updates the events queue with new Game Events. quits on esc*/
bool InputHandler::handleKeys(SDL_Event &eventHandler, std::queue<GameEvent>& events)
{
    ActionEnum action;
    switch (eventHandler.type)
    {
        case SDL_KEYDOWN:
            switch (eventHandler.key.keysym.sym)
            {
                case SDLK_9:
                    action = ActionEnum::RAISE;
                    break;
                case SDLK_8:
                    action = ActionEnum::LOWER;
                    break;
                case SDLK_0:
                    action = ActionEnum::RESET;
                    break;

                    // 3) add the case for which key to set to the action


                case SDLK_ESCAPE:
                    return false;
                    break;
            }
            //This checks if the event is active and on cool down
            if (eventRepeat[action] < 0)
            {
                events.push(GameEvent{ 0, action }); //trigger event
                eventRepeat[action] = eventRepeatRate[action]; // set the repeat cool down
            }

            break;
        case SDL_KEYUP:
            switch (eventHandler.key.keysym.sym)
            {
                case SDLK_9:
                    action = ActionEnum::RAISE;
                    break;
                case SDLK_8:
                    action = ActionEnum::LOWER;
                    break;
                case SDLK_0:
                    action = ActionEnum::RESET;
                    break;

                    // 4 ) make sure the keyup resets the event to inactive
                    // remember to add the key up to turn off repeating.

                default:
                    break;
            }
            eventRepeat[action] = INACTIVE;
            break;

        default:
            break;
    }
    return true; // no exit key pressed.
}


InputHandler::~InputHandler()
{
}

//returns continue true for continue
bool InputHandler::processEvents(SDL_Event& eventHandler, std::queue<GameEvent>& events)
{
    bool keyContinue = true;
    //Handle new events on queue
    while (SDL_PollEvent(&eventHandler) != 0)
    {
        //User requests quit
        if (eventHandler.type == SDL_QUIT)
        {
            return false;
        }
        else
        {
            keyContinue = handleKeys(eventHandler, events);
        }
    }
    /*This will trigger all events that have reached cool down */
    for (auto it = eventRepeat.begin(); it != eventRepeat.end(); ++it)
    {
        if (it->second != INACTIVE)
        {
            if (it->second == 0)
            {
                events.push(GameEvent{ 0, it->first }); // raise the event
                it->second = eventRepeatRate[it->first];  // set to cool down
            }
            else
            {
                --it->second;  // cool down toward triggering
            }
        }
    }
    return keyContinue;
}



