/* 	@file body.c
 *  @brief 
 */
 
#include "body.h"

//TODO: Move nbody stufdf to their own file (nbody). Rename nbody to main. Remove main.h
typedef struct NBody_Simulation_t
{
	//List_t bodies;//later i want to implement something like a quadtree i think
	double time_step;
}
NBody_Simulation_t;
typedef struct NBody_Body_t
{
	double mass;
	//int size;
	//Vector_t position; //make new lib for vectors
	//Vector_t velocity;
	//Vector_t acceleration;
	//Vector_t force;
}
NBody_Body_t;

int renderBodies(SDL_Renderer* renderer, NBody_Simulation_t* nbs)
{
	//foreach:
	//Body_Render(renderer, body)

	return 0;
}

int Body_Render(SDL_Renderer* renderer, NBody_Body_t* body)
{
	//SDL_FRect rect = {0};
	//rect.x = body.x;rect.y = body.y;
	//rect.w = 1;rect.h = 1;

	//if (0 != SDL_RenderFillRect(renderer, &rect)) goto exit;
}