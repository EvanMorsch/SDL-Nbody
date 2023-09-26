/* 	@file nbody.c
 *  @brief 
 */
 
#include "nbody.h"

int eventStep(void)
{
	int iRet = 1;
	SDL_Event e = {0};

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT) goto exit;
	}

	iRet = 0;
exit:
	return iRet;
}

int renderStep(SDL_Renderer* renderer)
{
	int iRet = 1;
	SDL_Event e = {0};
	SDL_FRect rect = {0};

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT){
			iRet = 0;
			goto exit;
		}
	}
	
	//clear to black
	if (0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)) goto exit;
	if (0 != SDL_RenderClear(renderer)) goto exit;
	
	//draw bodies
   	if (0 != SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 )) goto exit;
	
	renderBodies(renderer);

	rect.x = ((float)SDL_GetTicks()) / 100.0;
	rect.y = 50;
	rect.w = 1;
	rect.h = 1;

	if (0 != SDL_RenderFillRect(renderer, &rect)) goto exit;
	
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

	//main loop
	while (!quit)
	{
		//definitely do "event", dont do "render" if "event" step told us to quit. but if either tell us to quit, do it
		quit = eventStep() || renderStep(renderer);
	}

exit:
	if (NULL != win) 
	{
		SDL_DestroyWindow(win);
	}
    SDL_Quit(); //pretty sure theres no downside to calling this if init failed
 
    return 0;
}