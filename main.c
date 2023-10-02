/* 	@file nbody.c
 *  @brief 
 */
 
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "nbody.h"
#include "body.h"

#define BODY_CNT 1000

int eventStep(void)
{
	int iRet = 0;
	SDL_Event e = {0};

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
			printf("closing\n");
			iRet = 1;
		}
	}

	return iRet;
}

int renderStep(SDL_Renderer* renderer, NBody_p nbs)
{
	int iRet = 1;
	SDL_Event e = {0};

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT){
			iRet = 0;
			goto exit;
		}
	}
	
	//draw bodies
   	if (0 != SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 )) goto exit;
	
	NBody_Step(nbs);
	NBody_Render(renderer, nbs);
	
	//present to window
	if (0 != SDL_RenderPresent(renderer)) goto exit;

	iRet = 0;
exit:
	return iRet;
}
 
int main(int argc, char *argv[])
{
	SDL_Window* win = NULL;
	SDL_Renderer* renderer = NULL;
	int quit = 0; //using int to cut down on return type conversion later
	NBody_p nbs = NULL;

	//init sdl
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Failed to init SDL: %s\n", SDL_GetError());
		goto exit;
    }

	//init window
    win = SDL_CreateWindowWithPosition(
		"N-Body Simulation",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 1000,
		0
	);
	if (NULL == win)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		goto exit;
	}

	//set up renderer
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal"); //macos woes, id prefer openGL, tried and true
	renderer = SDL_CreateRenderer(win, NULL, SDL_RENDERER_ACCELERATED);
	if (NULL == renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		goto exit;
	}

	nbs = NBody_Init(BODY_CNT, 1);

	if ( TTF_Init() < 0 ) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
	}
	TTF_Font* font;

	font = TTF_OpenFont("font.ttf", 24);
	if ( !font ) {
		printf("Failed to load font: %s", TTF_GetError());
	}
	SDL_Surface* text;
	// Set color to black
	SDL_Color color = { 255, 255, 255 };

	//main loop
	uint64_t lastFrameTick = SDL_GetTicks();
	uint64_t frameTick = SDL_GetTicks();
	double frameMS_Average = 0;
	uint64_t frameMS_Average_Points = 0;
	while (!quit)
	{
		frameTick = SDL_GetTicks();

		if (0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)) goto exit;
		if (0 != SDL_RenderClear(renderer)) goto exit;

		char buffer[64];
		uint64_t frameMS = (int)frameTick-(int)lastFrameTick;
		frameMS_Average = ((frameMS_Average*(frameMS_Average_Points))+frameMS);
		frameMS_Average /= ++frameMS_Average_Points;
		text = TTF_RenderText_Solid( font, SDL_itoa(1000.0/frameMS_Average, buffer, 10), color );
		if ( !text ) {
			printf("Failed to render text: %s", TTF_GetError());
		}

		SDL_Texture* text_texture;

		text_texture = SDL_CreateTextureFromSurface( renderer, text );

		SDL_FRect dest = { 100, 100, text->w, text->h };

		SDL_RenderTexture(renderer, text_texture, NULL, &dest );

		SDL_DestroyTexture( text_texture );
		SDL_DestroySurface( text );

		//definitely do "event", dont do "render" if "event" step told us to quit. but if either tell us to quit, do it
		quit = eventStep();
		if (!quit) {
			renderStep(renderer, nbs);
		}

		lastFrameTick = frameTick;
	}

exit:
	if (NULL != win) 
	{
		SDL_DestroyWindow(win);
	}
    SDL_Quit(); //pretty sure theres no downside to calling this if init failed
 
    return 0;
}