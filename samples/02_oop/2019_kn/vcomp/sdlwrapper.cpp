#include "sdlwrapper.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

//global variables for SLD window and renderer
SDL_Window *SDLWin = 0;
SDL_Renderer *SDLRen = 0;

class SdlInit
{
  public:
    SdlInit() 
    {
        assert(SDL_Init(SDL_INIT_VIDEO) == 0);
        TTF_Init();

        SDLWin = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        assert(SDLWin != nullptr);

        SDLRen = SDL_CreateRenderer(SDLWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        assert(SDLRen != nullptr);

        SDL_RenderClear(SDLRen);
      }
    ~SdlInit() 
    {
        SDL_DestroyRenderer(SDLRen);
        SDL_DestroyWindow(SDLWin);
        TTF_Quit();
        SDL_Quit();
    }
};

//global variable: constructor/destructor
//will handle SLD init/destroy
SdlInit sdlInit;

void drawTexture(SDL_Renderer *SDLRen, int x, int y, int w, int h, const char *file)
{
    SDL_Texture *texture = IMG_LoadTexture(SDLRen, file);
    /*	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);*/
    SDL_Rect texr;
    texr.x = x;
    texr.y = y;
    texr.w = w;
    texr.h = h;

    SDL_RenderCopy(SDLRen, texture, NULL, &texr);
    SDL_DestroyTexture(texture);
}

void setColor (int r, int g, int b)
{
    SDL_SetRenderDrawColor(SDLRen, r, g, b, SDL_ALPHA_OPAQUE);
} 

void drawPixel(int x, int y)
{
     SDL_RenderDrawPoint(SDLRen, x, y);
}

void drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(SDLRen, x1, y1, x2, y2);
} 

void drawFillRect(int x, int y, int w, int h)            \
{                                   
    SDL_Rect r = {x, y, w, h};      
    SDL_RenderFillRect(SDLRen, &r); 
}

void drawFile (int x, int y, int w, int h, const char* file)
{
    drawTexture(SDLRen, x, y, w, h, file);
} 

void updateGraphics()
{
    SDL_RenderPresent(SDLRen);
} 

void drawText ()
{
    TTF_Font *font = TTF_OpenFont("roboto.ttf", 25);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font,
                                                "Welcome to Gigi Labs", color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(SDLRen, surface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {0, 0, texW, texH};

    SDL_RenderCopy(SDLRen, texture, NULL, &dstrect);
    SDL_RenderPresent(SDLRen);
     
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}