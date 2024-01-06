#include "RenderWindow.hpp"

RenderWindow:: RenderWindow(){
    running=true;
    }
RenderWindow:: ~RenderWindow(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}
void RenderWindow::draw(){
 
     SDL_RenderPresent(renderer);
}
void RenderWindow::renderEntity(Entity& entity){
    SDL_RenderCopy(renderer,entity.getTexture(),&entity.src,&entity.dest);
}
SDL_Texture* RenderWindow::createTexture(const char* path){
    return  IMG_LoadTexture(renderer, path);
}
void RenderWindow::renderTexture(SDL_Texture* tex){
           
           SDL_RenderCopy(renderer,tex,NULL,NULL);
       }
 void RenderWindow:: renderTexture (SDL_Texture* tex,SDL_Rect dest){
            SDL_RenderCopy(renderer,tex,NULL,&dest);
  }
       
void RenderWindow::handleEvents(SDL_Event e){
    switch(e.type){
        case SDL_QUIT:
            running=false;
            break;
         default:
             break;
    }
}