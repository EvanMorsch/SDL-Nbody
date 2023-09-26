/* 	@file nbody.h
 *  @brief 
 */
 
#ifndef body_h
#define body_h

#include <SDL3/SDL.h>

typedef struct NBody_Simulation_t NBody_Simulation_t;
typedef struct NBody_Body_t NBody_Body_t;

int renderBodies(SDL_Renderer*, NBody_Simulation_t*);

#endif
