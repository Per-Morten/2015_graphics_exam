#include <iostream>
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#define GLM_FORCE_RADIANS //Using degrees with glm is deprecated.
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>

#include "inputHandler.h"
#include "gameEvent.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
std::string windowName = "Graphics Exam 2015 - Student Name";

SDL_Window* gWindow = NULL;

SDL_GLContext gContext;

bool init();
bool initGL();


using namespace std;
SDL_Event input;

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



bool initGL()
{
	//Success flag
	bool success = true;
	// As part of am you should work out how to include this
	return success;
}

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
	std::queue<gameEvent> eventQueue;
	inputHandler inputs;
	
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
			running = inputs.processEvents(eventHandler, eventQueue);
			while (!eventQueue.empty())
			{
				if (eventQueue.front().action == ActionEnum::RAISE)
					std::cout << ' ' << "raise" << endl;
				if (eventQueue.front().action == ActionEnum::LOWER)
					std::cout << ' ' << "lower" << endl;
				eventQueue.pop();
			}
			SDL_Delay(30);
		}
	}
	return 0;
}