/* 	@file nbody.h
 *  @brief 
 */
 
#ifndef body_h
#define body_h

#include <SDL3/SDL.h>
#include <list.h>
#include <vec2.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NBody_Body_t NBody_Body_t, *NBody_Body_p;

void NBody_Body_Update_Influence(NBody_Body_p a, NBody_Body_p b);
void NBody_Body_Step(NBody_Body_p a);

unsigned int NBody_Body_Get_Mass(NBody_Body_p a);
Vector2D_t NBody_Body_Get_Pos(NBody_Body_p a);
int NBody_Body_Render(SDL_Renderer* renderer, NBody_Body_p body);
NBody_Body_p NBody_Body_Create(Vector2D_t pos, Vector2D_t vel, unsigned int mass, float t, double g, double eps);

#endif
