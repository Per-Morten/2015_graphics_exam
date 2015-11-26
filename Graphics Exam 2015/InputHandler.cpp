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
    eventRepeatRate[ActionEnum::LATER] = 0;
    eventRepeatRate[ActionEnum::EARLIER] = 0;

    eventRepeatRate[ActionEnum::FORWARD] = 0;
    eventRepeatRate[ActionEnum::BACK] = 0;
    eventRepeatRate[ActionEnum::LEFT] = 0;
    eventRepeatRate[ActionEnum::RIGHT] = 0;
    eventRepeatRate[ActionEnum::DOWN] = 0;
    eventRepeatRate[ActionEnum::UP] = 0;
    eventRepeatRate[ActionEnum::MOUSEMOTION] = 0;
    eventRepeatRate[ActionEnum::CREATE] = 0;
    eventRepeatRate[ActionEnum::ENABLEMOVEMENT] = 10;

    eventRepeat[ActionEnum::RAISE] = INACTIVE;
    eventRepeat[ActionEnum::LOWER] = INACTIVE; // Make sure all new events are inactive
    eventRepeat[ActionEnum::RESET] = INACTIVE; // Make sure all new events are inactive
    // 2) make sure it is initialised to inactive
    eventRepeat[ActionEnum::LATER] = INACTIVE;
    eventRepeat[ActionEnum::EARLIER] = INACTIVE;

    eventRepeat[ActionEnum::FORWARD] = INACTIVE;
    eventRepeat[ActionEnum::BACK] = INACTIVE;
    eventRepeat[ActionEnum::LEFT] = INACTIVE;
    eventRepeat[ActionEnum::RIGHT] = INACTIVE;
    eventRepeat[ActionEnum::DOWN] = INACTIVE;
    eventRepeat[ActionEnum::UP] = INACTIVE;

    eventRepeat[ActionEnum::MOUSEMOTION] = INACTIVE;
    eventRepeat[ActionEnum::CREATE] = INACTIVE;
    eventRepeat[ActionEnum::ENABLEMOVEMENT] = INACTIVE;
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
                case SDLK_1:
                    action = ActionEnum::EARLIER;
                    break;

                case SDLK_2:
                    action = ActionEnum::LATER;
                    break;
                
                case SDLK_w:
                    action = ActionEnum::FORWARD;
                    break;

                case SDLK_s:
                    action = ActionEnum::BACK;
                    break;

                case SDLK_a:
                    action = ActionEnum::LEFT;
                    break;
                case SDLK_d:
                    action = ActionEnum::RIGHT;
                    break;

                case SDLK_x:
                    action = ActionEnum::DOWN;
                    break;

                case SDLK_c:
                    action = ActionEnum::UP;
                    break;

                case SDLK_k:
                    action = ActionEnum::CREATE;
                    break;

                case SDLK_i:
                    action = ActionEnum::DESTROY;
                    break;

                case SDLK_p:
                    action = ActionEnum::ENABLEMOVEMENT;
                    break;

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
                case SDLK_1:
                    action = ActionEnum::EARLIER;
                    break;

                case SDLK_2:
                    action = ActionEnum::LATER;
                    break;

                case SDLK_w:
                    action = ActionEnum::FORWARD;
                    break;

                case SDLK_s:
                    action = ActionEnum::BACK;
                    break;
                
                case SDLK_a:
                    action = ActionEnum::LEFT;
                    break;
                
                case SDLK_d:
                    action = ActionEnum::RIGHT;
                    break;

                case SDLK_x:
                    action = ActionEnum::DOWN;
                    break;

                case SDLK_c:
                    action = ActionEnum::UP;
                    break;

                case SDLK_k:
                    action = ActionEnum::CREATE;
                    break;

                case SDLK_i:
                    action = ActionEnum::DESTROY;
                    break;

                case SDLK_p:
                    action = ActionEnum::ENABLEMOVEMENT;
                    break;


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

void InputHandler::handleMouse(SDL_Event& eventHandler, std::queue<GameEvent>& events, glm::vec2& mousePosition)
{
    ActionEnum action = ActionEnum::NOACTION;
    int x = 0;
    int y = 0;
    switch (eventHandler.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            std::cout << "Button down" << std::endl;
            break;
        case SDL_MOUSEBUTTONUP:
            std::cout << "Button up" << std::endl;
            break;
        case SDL_MOUSEWHEEL:
            std::cout << "Button wheel" << std::endl;
            break;
        case SDL_MOUSEMOTION:
                              // Not really nice to cast here
                              // But Visual studio generates warnings for possible loss of data, which makes it hard to see other warnings
                              // so as I am aware of what I am doing, I cast it instead.
            mousePosition.x = static_cast<float>(eventHandler.motion.x);
            mousePosition.y = static_cast<float>(eventHandler.motion.y);
            action = ActionEnum::MOUSEMOTION;
            break;
    }
    if (eventRepeat[action] < 0)
    {
        events.push(GameEvent{ 0, action }); //trigger event
        eventRepeat[action] = eventRepeatRate[action]; // set the repeat cool down
    }
}


InputHandler::~InputHandler()
{
}

//returns continue true for continue
bool InputHandler::processEvents(SDL_Event& eventHandler, std::queue<GameEvent>& events, glm::vec2& mousePosition)
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
        if (eventHandler.type == SDL_KEYDOWN ||
            eventHandler.type == SDL_KEYUP)
        {
            keyContinue = handleKeys(eventHandler, events);
        }
        if (eventHandler.type == SDL_MOUSEBUTTONDOWN ||
            eventHandler.type == SDL_MOUSEBUTTONUP ||
            eventHandler.type == SDL_MOUSEMOTION ||
            eventHandler.type == SDL_MOUSEWHEEL)
        {
            handleMouse(eventHandler, events, mousePosition);
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



