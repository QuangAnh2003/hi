#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#include "Utils.h"
#include "common.h"
#include "Character.h"


using namespace std;

const int place[] = {100,300,500};

Character character;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* background = NULL;
SDL_Texture* characterTexture = NULL;
SDL_Texture* object[MAX];

SDL_Rect characterRect;
SDL_Rect objectRect[MAX];

Mix_Music *Music = NULL;
Mix_Chunk *Die = NULL;


bool check (SDL_Rect object1Rect, SDL_Rect& characterRect);
void open();
void close();

int main (int argc, char*argv[])
{

    initSDL(window, renderer);
    OpenAudio();
    open();

    for (int i = 0; i < MAX; i++)
    {
        object[i] = loadTexture("mouse.png", renderer);
        SDL_QueryTexture(object[i], nullptr, nullptr, &objectRect[i].w, &objectRect[i].h);
        objectRect[i].x = SCREEN_WIDTH - 200 + i * 400;
        objectRect[i].y = SCREEN_HEIGHT - 100;
        objectRect[i].w = objectRect[i].w/6;
        objectRect[i].h = objectRect[i].h/6;
    }
    Mix_PlayMusic( Music, -1 );

    SDL_Event e;
    int score = 0;
    srand(time(0));
    bool GameOver = false;
    while(!GameOver)
    {
        score++;
        for(int i = 0; i < MAX; i++)
        {
            objectRect[i].x-=5 + (score/500);
                    if(objectRect[i].x < 10)
                    {
                    int random = rand()%3;
                    objectRect[i].y = place[random];
                    objectRect[i].x = 1200;
                    }
            if(check(objectRect[i],characterRect))
            {
                GameOver = true;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
        character.render(renderer, characterTexture, characterRect);
        for (int i = 0; i < MAX; i++)
        {
            SDL_RenderCopy( renderer, object[i], NULL, &objectRect[i] );
        }
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        character.move(e);
        SDL_RenderPresent(renderer);
    }

    Mix_PlayChannel( -1, Die, 0 );
    cout << score;
    waitUntilKeyPressed();
    close();
    return 0;
}


bool check (SDL_Rect object1Rect, SDL_Rect& characterRect)
{
    int left1 = object1Rect.x;
    int right1 = object1Rect.x + object1Rect.w;
    int top1 = object1Rect.y;
    int bot1 = object1Rect.y + object1Rect.h;

    int left2 = characterRect.x;
    int right2 = characterRect.x + characterRect.w;
    int top2 = characterRect.y;
    int bot2 = characterRect.y + characterRect.h;

    if (left2 + 60 < right1 && right2 - 60 > right1 )
    {
        if (top2 < bot1 && bot2 > bot1)
            return true;
        else if (top2 < top1 && bot2 > top1)
            return true;
    }
    if (left2 + 60 < left1 && right2 - 60 > left1)
    {
        if (top2 < bot1 && bot2 > bot1)
            return true;
        else if (top2 < top1 && bot2 > top1)
            return true;
    }
    return false;
}

void open()
{
    background = loadTexture("Wallpaper.jpg", renderer);
    characterTexture = loadTexture("mon.png", renderer);
    Music = Mix_LoadMUS( "DoraemonNoUta.wav" );
	Die = Mix_LoadWAV( "doraemonsms.wav" );
}

void close()
{
    SDL_DestroyTexture( background );
    background = nullptr;
    SDL_DestroyTexture( characterTexture );
    characterTexture = nullptr;
    for ( int i = 0; i < MAX; i++ )
    {
    SDL_DestroyTexture( object[i] );
    object[i] = nullptr;
    }
    Mix_FreeChunk( Die );
    Die = nullptr;
    Mix_FreeMusic( Music );
    Music = nullptr;
    quitSDL(window, renderer);
}





