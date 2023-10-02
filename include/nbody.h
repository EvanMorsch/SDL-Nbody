/* 	@file nbody.h
 *  @brief 
 */
 
#ifndef nbody_h
#define nbody_h

#define GRAV_CONST -0.0000000000667
#define EPS 1

#include <SDL3/SDL.h>
#include <list.h>
#include <vec2.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "body.h"

typedef struct NBody_t NBody_t, *NBody_p;

NBody_p NBody_Init(size_t, double);

int NBody_Render(SDL_Renderer*, NBody_p);
int NBody_Step(NBody_p);

#endif
