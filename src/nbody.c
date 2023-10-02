/* 	@file body.c
 *  @brief 
 */
 
#include "nbody.h"

#define GRAV_CONST -0.0000000000667
#define EPS 1

//TODO: Move nbody stufdf to their own file (nbody). Rename nbody to main. Remove main.h
typedef struct NBody_t
{
	List_p bodies;//later i want to implement something like a quadtree i think
	double time_step;
    double g;
    double eps;
}
NBody_t, *NBody_p;

NBody_p NBody_Init(size_t numBodies, double timestep)
{
	NBody_p nbs = malloc(sizeof(NBody_t));
	nbs->time_step = timestep;
    nbs->g = GRAV_CONST;
    nbs->eps = EPS;
	nbs->bodies = List_Create(0, NULL, free);
	srand(time(0));
	for (size_t i = 0; i < numBodies; i++)
	{
		NBody_Body_p newBody = NBody_Body_Create(
            Vector2D_New(rand()%1000, rand()%1000),
            Vector2D_New(0,0),
            1,
            60*60,
            GRAV_CONST,
            EPS
        );
		List_Push(newBody, nbs->bodies);
	}
	return nbs;
}

int NBody_Step(NBody_p sim)
{
    //return 0;
    NBody_Body_p i_body = NULL, j_body = NULL;
    for (
        List_Iterator_p i_iter_p = List_Iterator_Create(sim->bodies);
        (i_body = List_Iterator_Next(i_iter_p))!=NULL;
    ) 
    {
        for (
            List_Iterator_p j_iter_p = List_Iterator_Copy(i_iter_p);
            (j_body = List_Iterator_Next(j_iter_p))!=NULL;
        ) 
        {
            NBody_Body_Update_Influence(i_body, j_body);
        }
    }
    List_For_Each(sim->bodies, (List_Do_Fnc)NBody_Body_Step);
    return 0;
}

int NBody_Render(SDL_Renderer* renderer, NBody_p nbs)
{
	List_Iterator_p iter = List_Iterator_Create(nbs->bodies);
	for (void* body = List_Iterator_Next(iter); body != NULL; body = List_Iterator_Next(iter))
	{
		NBody_Body_Render(renderer, body);
	}

	return 0;
}