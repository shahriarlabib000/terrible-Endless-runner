#pragma once
#include "SDL2/SDL.h"
struct Entity{
    Entity(SDL_Texture* tex);
    Entity(){};
    ~Entity();
    void setTexture(SDL_Texture* tex){
        m_tex=tex;
        }
    SDL_Texture* getTexture(){ return m_tex ;}
    SDL_Rect src={0,0,32,32};
    SDL_Rect dest={0,0,500,500};
    private:
    SDL_Texture* m_tex;
};