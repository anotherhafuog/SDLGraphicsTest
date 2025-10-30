#include <SDL.h>
#include <SDL_rect.h>
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

	SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); //set color to blue
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD); // sets colors to additive blend
	SDL_RenderDrawPoint(renderer, windowSizeX / 2, windowSizeY / 2); //draw blue pixel in the middle of the screen
	SDL_RenderDrawLine(renderer, 100, 100, 200, 200); //draw line

	struct SDL_Point rectPoints[5];
	rectPoints[0].x = 300;
	rectPoints[0].y = 300;

	rectPoints[1].x = 320;
	rectPoints[1].y = 300;

	rectPoints[2].x = 320;
	rectPoints[2].y = 320;

	rectPoints[3].x = 300;
	rectPoints[3].y = 320; 

	rectPoints[4].x = rectPoints[0].x;
	rectPoints[4].y = rectPoints[0].y; // define points for square
	//todo: figure out a way to avoid storing duplicate points

	SDL_RenderDrawLines(renderer, rectPoints, 5); //draw square
	SDL_RenderDrawPoints(renderer, rectPoints, 4); //draw points on edges for atari-style vector effects

	/* todo:
	* test using drawrect for line thickness and less aliasing
	* try scaling draw rect
	* attempt animation using SDL time
	*/

	SDL_RenderPresent(renderer);
	SDL_Delay(5000); //keep open window for 5000 ticks

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();//deallocate and close

	return 0;
}