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

	struct SDL_Point angPoints[8];
	angPoints[0].x = 400;
	angPoints[0].y = 200;

	angPoints[1].x = 420;
	angPoints[1].y = 205;

	angPoints[2].x = (angPoints[1].x);
	angPoints[2].y = (angPoints[1].y + 1);

	angPoints[3].x = (angPoints[0].x);
	angPoints[3].y = (angPoints[0].y + 1);
	
	// this is too many points to store!

	//SDL_RenderDrawLines(renderer, angPoints, 4);//draw thick line

	//^v these should draw the same result, but top results in overlapping pixels

	SDL_RenderDrawLine(renderer, angPoints[0].x, angPoints[0].y++, angPoints[1].x, angPoints[1].y++); //draw line
	SDL_RenderDrawLine(renderer, angPoints[0].x, angPoints[0].y--, angPoints[1].x, angPoints[1].y--); //draw line
	SDL_RenderDrawLine(renderer, (angPoints[0].x)+40, angPoints[0].y++, angPoints[1].x-1, angPoints[1].y++); //draw line
	SDL_RenderDrawLine(renderer, (angPoints[0].x)+40, angPoints[0].y, angPoints[1].x-1, angPoints[1].y); //draw line
	/* todo:
	* attempt scaling
	* attempt animation using SDL time
	*/

	SDL_RenderPresent(renderer);
	SDL_Delay(5000); //keep open window for 5000 ticks

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();//deallocate and close

	return 0;
}