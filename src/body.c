/* 	@file body.c
 *  @brief 
 */
 
#include "body.h"

typedef struct NBody_Body_t
{
    Vector2D_t position;
    Vector2D_t velocity;
    Vector2D_t acceleration;
    Vector2D_t force;

    unsigned int mass;
    float t;
	double eps;
	double g;
}
NBody_Body_t, *NBody_Body_p;

NBody_Body_p NBody_Body_Create(Vector2D_t pos, Vector2D_t vel, unsigned int mass, float t, double g, double eps)
{
    NBody_Body_p new_body = malloc(sizeof(NBody_Body_t));
    if (NULL != new_body)
    {
        new_body->position = pos;
        new_body->velocity = vel;
        new_body->acceleration = Vector2D_New(0,0);
        new_body->force = Vector2D_New(0,0);

        new_body->mass = mass;
        new_body->t = t;
		new_body->g = g;
		new_body->eps = eps;
    }
    return new_body;
}

int NBody_Body_Render(SDL_Renderer* renderer, NBody_Body_p body)
{
	return SDL_RenderPoint(renderer, body->position.x, body->position.y);
}

Vector2D_t NBody_Body_Get_Pos(NBody_Body_p a)
{
    return a->position;
}
unsigned int NBody_Body_Get_Mass(NBody_Body_p a)
{
    return a->mass;
}

//call this once per influence per body
void NBody_Body_Update_Influence(NBody_Body_p a, NBody_Body_p b)
{
    unsigned int total_mass = a->mass + b->mass;
    float r = Vector2D_Distance(a->position, b->position);
    if (r<a->eps) return; //TODO; later consider doing a or b even if the other ignores due to eps
    float g = a->g * ((total_mass)/r); //TODO; later consider allowing for diff g

    Vector2D_t a_b_diff = Vector2D_Subtract(a->position, b->position);
    Vector2D_t b_a_diff = Vector2D_Subtract(b->position, a->position);

    a_b_diff = Vector2D_Scale(a_b_diff, 1.0/r);
    b_a_diff = Vector2D_Scale(b_a_diff, 1.0/r);

    a->force = Vector2D_Add(a->force, Vector2D_Scale(a_b_diff, g));
    b->force = Vector2D_Add(b->force, Vector2D_Scale(b_a_diff, g));
    return;
}

//once all influences are updated, step should be called
void NBody_Body_Step(NBody_Body_p a)
{
    a->acceleration = Vector2D_Scale(a->force, a->mass);
    a->velocity = Vector2D_Add(a->velocity, Vector2D_Scale(a->acceleration, a->t));
    a->position = Vector2D_Add(a->position, Vector2D_Scale(a->velocity, a->t));
    a->force = Vector2D_New(0,0);
}