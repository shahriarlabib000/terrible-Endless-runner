#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow{
    public:
        RenderWindow();
        ~RenderWindow();
        static SDL_Window *window;
        static SDL_Renderer *renderer;
       void clear();
       void draw();
       void renderEntity(Entity& entity);
       SDL_Texture* createTexture(const char* path);
       void handleEvents(SDL_Event e);
       void renderTexture(SDL_Texture* tex);
       void renderTexture(SDL_Texture* tex,SDL_Rect dest);
       bool running;
};