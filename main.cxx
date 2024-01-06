#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>

#include "RenderWindow.hpp"
#include "Entity.hpp"

SDL_Window *RenderWindow::window = NULL;
SDL_Renderer *RenderWindow::renderer = NULL;

Entity bg1, bg2, bg3;
Entity g1, g2, g3;
Entity player;
Entity e1, e2, e3;

int bgSpeed = 1;
int groundSpeed = 2;
///player animation vars
int frameWidth = 64;  // Adjust according to frame dimensions
int frameHeight = 64; // Adjust according to frame dimensions
int numRows = 2;
int numCols = 5;
int currentFrame = 0;
int numFrames = 6;
///
int playerdefpos;
float v0 = 0.0f;
float jumpVelocity = -7.0f;
float gravity = 0.1f;

bool gamePlaying=true;

void handleJump()
{
    if (player.dest.y == playerdefpos)
    {
        v0 = jumpVelocity; //jumpVelocity; // Adjust the jump velocity as needed
    }
}

void updatePlayerpos()
{
    player.dest.y += v0;
    v0 += gravity;

    // Clamp character position to the bottom of the screen
    if (player.dest.y >= playerdefpos)
    {
        player.dest.y = playerdefpos;
        v0 = 0.0f;
    }
}
    
void update();
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << SDL_GetError() << std::endl;
    // Get the display mode
    SDL_DisplayMode dm;
    if (SDL_GetCurrentDisplayMode(0, &dm) != 0)
    {
        // Handle getting display mode error
        SDL_Quit();
        return -1;
    }
    int screenWidth = dm.w;
    int screenHeight = dm.h;

    RenderWindow::window = SDL_CreateWindow("Endless runner", 0, 0, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    RenderWindow::renderer = SDL_CreateRenderer(RenderWindow::window, -1, SDL_RENDERER_ACCELERATED);
    RenderWindow rw;
    SDL_Texture *groundTex = rw.createTexture("assets/long ground.png");
    SDL_Texture *bgTexture = rw.createTexture("assets/bg.png");
    SDL_Texture *playerTex = rw.createTexture("assets/player.png");
    SDL_Texture *cactusTex = rw.createTexture("assets/cactus.png");

    bg1.setTexture(bgTexture);
    bg2.setTexture(bgTexture);
    bg3.setTexture(bgTexture);

    g1.setTexture(groundTex);
    g2.setTexture(groundTex);
    g3.setTexture(groundTex);

    player.setTexture(playerTex);

    e1.setTexture(cactusTex);
    e2.setTexture(cactusTex);
    e3.setTexture(cactusTex);

    SDL_QueryTexture(bgTexture, NULL, NULL, &bg1.dest.w, &bg1.dest.h);
    bg1.src = bg2.src = bg3.src = {0, 0, 1600, 720};
    bg2.dest = bg3.dest = bg1.dest;
    bg2.dest.y = bg3.dest.y = bg1.dest.y = 0;
    bg2.dest.x = bg1.dest.w; // Position the second rectangle to the right of the first one
    bg3.dest.x = bg1.dest.w * 2;

    g1.src = g2.src = g3.src = {0, 0, 1024, 64};
    g1.dest = g2.dest = g3.dest = {0, screenHeight - 64, 1024, 64};
    g2.dest.x = g1.dest.w; // Position the second rectangle to the right of the first one
    g3.dest.x = g1.dest.w * 2;

    e1.src = e2.src = e3.src = {0, 0, 16, 32};
    e1.dest = e2.dest = e3.dest = {0, g1.dest.y - 64, 32, 64};
    e2.dest.x = e1.dest.w + 1600; // Position the second rectangle to the right of the first one
    e3.dest.x = e1.dest.w * 2+ 1600;
    playerdefpos = screenHeight - 164;
    player.dest = {50, playerdefpos, 128, 128};
    SDL_Rect playerColiRect={50,playerdefpos,50,50};
    SDL_Event event;
    while (rw.running && gamePlaying)
    {
        while (SDL_PollEvent(&event))
        {
            rw.handleEvents(event);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                handleJump();
            }
        }

        update();
        playerColiRect.y=player.dest.y;
        if(SDL_HasIntersection(&playerColiRect,&e1.dest)||
        SDL_HasIntersection(&playerColiRect,&e2.dest)||
        SDL_HasIntersection(&playerColiRect,&e2.dest)){
        gamePlaying=false;
        SDL_Delay(1000);
        }

        rw.clear();

        rw.renderEntity(bg1);
        rw.renderEntity(bg2);
        rw.renderEntity(bg3);

        rw.renderEntity(g1);
        rw.renderEntity(g2);
        rw.renderEntity(g3);

        rw.renderEntity(e1);
        rw.renderEntity(e2);
        rw.renderEntity(e3);

        int currentRow = currentFrame / numCols;
        int currentCol = currentFrame % numCols;
        if (player.dest.y == playerdefpos)
        {
            player.src = {currentCol * frameWidth, currentRow * frameHeight, frameWidth, frameHeight};
        }
        updatePlayerpos();
        rw.renderEntity(player);
        currentFrame = (currentFrame + 1) % numFrames;

        rw.draw();
        SDL_Delay(10);
    }
    return 0;
}
int getRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}
void update()
{
    //  updating background
    bg1.dest.x -= bgSpeed;
    bg2.dest.x -= bgSpeed;
    bg3.dest.x -= bgSpeed;

    if (bg1.dest.x + bg1.dest.w <= 0)
    {
        bg1.dest.x = bg3.dest.x + bg3.dest.w;
    }
    if (bg2.dest.x + bg2.dest.w <= 0)
    {
        bg2.dest.x = bg1.dest.x + bg1.dest.w;
    }
    if (bg3.dest.x + bg3.dest.w <= 0)
    {
        bg3.dest.x = bg2.dest.x + bg2.dest.w;
    }
    ////////
    g1.dest.x -= groundSpeed;
    g2.dest.x -= groundSpeed;
    g3.dest.x -= groundSpeed;
    if (g1.dest.x + g1.dest.w <= 0)
    {
        g1.dest.x = g3.dest.x + g3.dest.w;
    }
    if (g2.dest.x + g2.dest.w <= 0)
    {
        g2.dest.x = g1.dest.x + g1.dest.w;
    }
    if (g3.dest.x + g3.dest.w <= 0)
    {
        g3.dest.x = g2.dest.x + g2.dest.w;
    }
    ///////
    e1.dest.x -= groundSpeed;
    e2.dest.x -= groundSpeed;
    e3.dest.x -= groundSpeed;
    if (e1.dest.x + e1.dest.w <= 0)
    {
        //  e1.dest.x = e3.dest.x + e3.dest.w+500;
        e1.dest.x = 1600 + getRandomNumber(0, 1600);
    }
    if (e2.dest.x + e2.dest.w <= 0)
    {
        //e2.dest.x = e1.dest.x + e1.dest.w+500;
        e2.dest.x = 1600 + getRandomNumber(0, 1600);
    }
    if (e3.dest.x + e3.dest.w <= 0)
    {
        //e3.dest.x = e2.dest.x + e2.dest.w+500;
        e3.dest.x = 1600 + getRandomNumber(0, 1600);
    }
}
