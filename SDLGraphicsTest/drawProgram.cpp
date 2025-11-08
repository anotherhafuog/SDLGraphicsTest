#include <SDL.h>
#include <SDL_rect.h>
#undef main
#include <iostream>
#include <cmath>
using namespace std;

void DrawVec(SDL_Renderer* renderer, SDL_Point pts[], float thickness, SDL_Color color) {

	float x0 = pts[0].x;
	float x1 = pts[1].x;

	float y0 = pts[0].y;
	float y1 = pts[1].y;// define points from struct

	float dx = x1 - x0;
	float dy = y1 - y0;
	float length = sqrt((dx * dx) + (dy * dy));

	float ptx = (-dy / length) * (thickness / 2.0f);
	float pty = (dx / length) * (thickness / 2.0f);

	struct SDL_Vertex verts[4];
	verts[0].position = { x0 + ptx, y0 + pty };
	verts[1].position = { x1 + ptx, y1 + pty };
	verts[2].position = { x1 - ptx, y1 - pty };
	verts[3].position = { x0 - ptx, y0 - pty }; // Compute points for rect

	for (int i = 0; i < 4; ++i) {
		verts[i].color = color;
	} //set color

	const int indices[6] = { 0, 1, 2, 2, 3, 0 };

	SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); //set color to blue for now

	SDL_RenderGeometry(renderer, nullptr, verts, 4, indices, 6); //draw
}

int main() {
	int windowSizeX = 640;
	int windowSizeY = 480;//defines window size

	SDL_Color atariBlue = {0, 0, 128, 255}; //defines color

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

	struct SDL_Point angPoints[2];
	angPoints[0].x = 400;
	angPoints[0].y = 200;

	angPoints[1].x = 420;
	angPoints[1].y = 205;

	struct SDL_Point otherPoints[2] = {440, 200, 420, 205}; // initializer points
	
	DrawVec(renderer, angPoints, 4.0, atariBlue);
	DrawVec(renderer, otherPoints, 4.0, atariBlue); // draw new thicker lines

	/* todo:
	* attempt scaling
	* attempt animation using SDL time
	* make line intersections look good
	*/

	SDL_RenderPresent(renderer);
	SDL_Delay(5000); //keep open window for 5000 ticks

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();//deallocate and close

	return 0;
}