#include <SDL.h>
#undef main
#include <iostream>
using namespace std;

int main() {
	int windowSizeX = 640;
	int windowSizeY = 480;//defines window size

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(windowSizeX*4, windowSizeY*4, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 4, 4); //initialize window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //set window to black

	SDL_RenderClear(renderer); //clear color

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); //set color to blue
	SDL_RenderDrawPoint(renderer, windowSizeX / 2, windowSizeY / 2); //draw blue pixel in the middle of the screen

	SDL_RenderPresent(renderer);
	SDL_Delay(10000); //keep open window for 10000 ticks

	return 0;
}