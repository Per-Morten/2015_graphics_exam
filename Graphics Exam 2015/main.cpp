/* Template Author:Simon McCallum
Notes:
Created for the IMT2531 Graphics Exam 2015

To get the naming right I have set.
Project-> Properties -> Configuration properties -> General -> Target name  = exam2015.exe
Project-> Properties -> Configuration properties -> Debugging -> Commande Arguments = terrain.pnm

I suggest you read and understand how the input handler works.  It uses and event queue system.  
The keyboard events create game events which are pushed onto the GameEvent queue.  These are the
events which the program should actually repond to rather than the actual keyboard presses.

You should have environment variables set up for home of SDL GLEW and GLM so the calls below work
$(SDL_HOME)\include;$(GLEW_HOME)\include;$(GLM_HOME);$(IncludePath)


*/


#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#define GLM_FORCE_RADIANS //Using degrees with glm is deprecated.
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//C++ 11 stuff to use
#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>

#include "InputHandler.h"
#include "GameEvent.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
std::string windowName = "Graphics Exam 2015 - Student Name"; //You should update this to your name



SDL_Window* gWindow = NULL;

SDL_GLContext gContext;

bool init();
bool initGL();

using namespace std;
SDL_Event input;


/*Does the initialisaiton of SDL*/
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		gWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL) {
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK) {
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}
				if (SDL_GL_SetSwapInterval(1) < 0){
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
				if (!initGL())	{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}
	return success;
}


/*
This is where all the initialisation for OpenGL would go.  You may want to move this to its own file.
*/
bool initGL()
{
	//Success flag
	bool success = true;
	// As part of am you should work out how to include this
	return success;
}

/*
This shows how to start loading the terrain file.  You should be able to find how to do the rest.
*/
void LoadTerrain(std::string terrainFilename){
	ifstream inputFile(terrainFilename); 
	stringstream lineStream;
	string inputLine = "";

	// First line : version
	getline(inputFile, inputLine);
	if (inputLine.compare("P2") != 0) {
		cerr << "Version error" << endl;
	}
	else {
		cout << "Version : " << inputLine << endl;
	}
	// Rest of file handling here.

}


int main(int argc, char * argv[])
{
	bool running = true;
	SDL_Event eventHandler;
	std::queue<GameEvent> eventQueue;
	InputHandler inputs;
	
	if (argc > 1){
		LoadTerrain(std::string(argv[1]));
	}
	else {
		std::cout << "No terrain file\nUsage exam2015.exe terrain.pnm" << endl;
		exit(-1);
	}
	
	if (!init()){
		printf("Failed to initialize!\n");
	} else {
		while (running){
			running = inputs.processEvents(eventHandler, eventQueue); // returns a quit and updates the eventQueue with events
			while (!eventQueue.empty())
			{
				GameEvent nextEvent = eventQueue.front();
				eventQueue.pop();

				if (nextEvent.action == ActionEnum::RAISE) { // use the Action Enum to decide what to do.
					std::cout << ' ' << "raise" << endl;
				}
				if (nextEvent.action == ActionEnum::LOWER){
					std::cout << ' ' << "lower" << endl;
				}
				if (nextEvent.action == ActionEnum::RESET){
					std::cout << ' ' << "reset" << endl;
				}

			}
			SDL_Delay(30); // you need to control frame rate so the input events do not go crazy fast.
		}
	}
	return 0;
}