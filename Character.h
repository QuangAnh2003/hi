#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include "game.h"


using namespace std;

const int step = 200;

struct Character{
    int x;
    int y = 400;

    void render(SDL_Renderer* renderer, SDL_Texture* characterTexture, SDL_Rect &characterRect)
    {
    SDL_QueryTexture(characterTexture, nullptr, nullptr, &characterRect.w, &characterRect.h);
    characterRect.x = x;
    characterRect.y = y;
    characterRect.w = characterRect.w/4;
    characterRect.h = characterRect.h/4;
    SDL_RenderCopy( renderer, characterTexture, NULL, &characterRect );
    }

    void move(SDL_Event &e)
    {
    if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: x = (x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
        			break;
            	case SDLK_RIGHT: x = (x + step) % SCREEN_WIDTH;
            		break;
            	case SDLK_DOWN: y = (y + step) % SCREEN_HEIGHT;
					break;
            	case SDLK_UP: y = (y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            	    break;
                default: break;
			}
        }
    }

};

#endif // CHARACTER_H

