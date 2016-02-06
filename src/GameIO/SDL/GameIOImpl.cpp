/**
 * @file GameIOImpl.cpp
 * 
 * @author C. Smith
 * @date Jan 13, 2016
 */

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "GameIOImpl.h"

struct ioInternals
{
    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
    SDL_Texture* pBlockTexture;
    Mix_Music* pBgMusic;
    TTF_Font* pGameFont;
};

GameIOImpl::GameIOImpl()
{
    this->pInternals = new ioInternals;

    this->pInternals->pWindow = NULL;
    this->pInternals->pRenderer = NULL;
    this->pInternals->pBlockTexture = NULL;
    this->pInternals->pBgMusic = NULL;
    this->pInternals->pGameFont = NULL;
}

GameIOImpl::~GameIOImpl()
{
    delete this->pInternals;
}

bool GameIOImpl::Init(const int windowHeight, const int windowWidth, const Color bgColor)
{
    SDL_Surface* loadedSurface;
    const char * blockImagePath = "media/block.bmp";

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
    }

    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        SDL_Log("Error: Could not initialize mixer: %s", Mix_GetError());
    }

    if (Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2046 ) != 0)
    {
        SDL_Log("Error: Could not open audio: %s", Mix_GetError());
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Error: Could not initialize TTF: %s", TTF_GetError());
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        SDL_Log("Warning: Linear texture filtering not enabled");
    }

    this->pInternals->pWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
            SDL_WINDOW_SHOWN);

    if (this->pInternals->pWindow == NULL)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    this->pInternals->pRenderer = SDL_CreateRenderer(this->pInternals->pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!this->pInternals->pRenderer)
    {
        SDL_Log("SDL ERROR: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(this->pInternals->pRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->pInternals->pRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    loadedSurface = SDL_LoadBMP(blockImagePath);
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", blockImagePath, SDL_GetError() );
        return false;
    }

    this->pInternals->pBlockTexture = SDL_CreateTextureFromSurface(this->pInternals->pRenderer, loadedSurface);
    if( this->pInternals->pBlockTexture == NULL )
    {
        SDL_Log( "Unable to create texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    SDL_FreeSurface(loadedSurface);

    return true;
}

void GameIOImpl::Close()
{
    if( this->pInternals->pBgMusic )
    {
        if( Mix_PlayingMusic() )
        {
            Mix_HaltMusic();
        }

        Mix_FreeMusic(this->pInternals->pBgMusic);
    }

    if(this->pInternals->pGameFont)
    {
    	TTF_CloseFont(this->pInternals->pGameFont);
    }

    if( this->pInternals->pBlockTexture )
    {
        SDL_DestroyTexture(this->pInternals->pBlockTexture);
        this->pInternals->pBlockTexture = NULL;
    }
    if(this->pInternals->pRenderer)
    {
        SDL_DestroyRenderer(this->pInternals->pRenderer);
        this->pInternals->pRenderer = NULL;
    }

    if(this->pInternals->pWindow)
    {
        SDL_DestroyWindow(this->pInternals->pWindow);
        this->pInternals->pWindow = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();

    SDL_Quit();
}

void GameIOImpl::ClearScreen(const Color bgColor)
{
    SDL_SetRenderDrawColor(this->pInternals->pRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderClear(this->pInternals->pRenderer);
}

void GameIOImpl::DrawRect(const int x, const int y, const int w, const int h, const Color color)
{
    SDL_Rect fill_rect;

    fill_rect.x = x;
    fill_rect.y = y;
    fill_rect.w = w;
    fill_rect.h = h;

    SDL_SetRenderDrawColor(this->pInternals->pRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->pInternals->pRenderer, &fill_rect);
}

void GameIOImpl::DrawTexture(const int x, const int y, const int w, const int h, const Color color)
{
    SDL_Rect fill_rect;

    fill_rect.x = x;
    fill_rect.y = y;
    fill_rect.w = w;
    fill_rect.h = h;

    SDL_SetTextureColorMod(this->pInternals->pBlockTexture, color.r, color.g, color.b);
    SDL_RenderCopy(this->pInternals->pRenderer, this->pInternals->pBlockTexture, NULL, &fill_rect);
}

void GameIOImpl::PrintText(const char* text, const int x, const int y, hAlignment hAlign, vAlignment vAlign, const Color color)
{
    SDL_Surface* tempSurface;
    SDL_Texture* tempTexture;
    SDL_Color fgColor = { color.r, color.g, color.b, color.a };
    SDL_Rect fill_rect;


    tempSurface = TTF_RenderText_Solid(this->pInternals->pGameFont, text, fgColor);
    if (tempSurface == NULL)
    {
        SDL_Log("Error: Unable to create surface from font");
        return;
    }

    tempTexture = SDL_CreateTextureFromSurface(this->pInternals->pRenderer, tempSurface);
    if (tempTexture == NULL)
    {
        SDL_Log("Error: Unable to create texture from font surface");
    }

    fill_rect.x = x;
    fill_rect.y = y;
    fill_rect.w = tempSurface->w;
    fill_rect.h = tempSurface->h;

    if (hAlign == HALIGN_RIGHT)
    {
        fill_rect.x -= fill_rect.w;
    }
    else if (hAlign == HALIGN_CENTERED)
    {
        fill_rect.x -= fill_rect.w / 2;
    }

    if (vAlign == VALIGN_BOTTOM)
    {
        fill_rect.y -= fill_rect.h;
    }
    else if (hAlign == VALIGN_CENTERED)
    {
        fill_rect.y -= fill_rect.w / 2;
    }

    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(this->pInternals->pRenderer, tempTexture, NULL, &fill_rect);

    SDL_DestroyTexture(tempTexture);
}

void GameIOImpl::Present()
{
    SDL_RenderPresent(this->pInternals->pRenderer);
}

void GameIOImpl::LoadFontFromFile(const char* filename, int size)
{
    if (this->pInternals->pGameFont)
        return;

    this->pInternals->pGameFont = TTF_OpenFont(filename, size);
    if (this->pInternals->pGameFont == NULL)
    {
        SDL_Log("Error: Could not load font from file %s: %s", filename, TTF_GetError());
    }
}

void GameIOImpl::LoadBgMusicFromFile(const char* filename)
{
    if (this->pInternals->pBgMusic)
        return;

    this->pInternals->pBgMusic = Mix_LoadMUS(filename);
    if (this->pInternals->pBgMusic == NULL)
    {
        SDL_Log("Error: Could not load music from file %s: %s", filename, Mix_GetError());
    }
}

void GameIOImpl::PlayBgMusic()
{
    if (!this->pInternals->pBgMusic)
        return;

    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(this->pInternals->pBgMusic, -1);
    }
    else if (Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
}

void GameIOImpl::PauseBgMusic()
{
    if (!this->pInternals->pBgMusic)
        return;

    if (Mix_PlayingMusic())
    {
        Mix_PauseMusic();
    }
}

void GameIOImpl::callKeyCallback(eKeyCode keycode, eKeyDirection direction, const KeyCallback callbacks[4])
{
    if (callbacks[keycode].callback != NULL)
    {
        callbacks[keycode].callback(callbacks[keycode].context, direction);
    }
}

bool GameIOImpl::PollInputs(const KeyCallback callbacks[4])
{
    SDL_Event oEvent;

    while(SDL_PollEvent(&oEvent) != 0)
    {
        if (oEvent.type == SDL_QUIT ||
            (oEvent.type == SDL_KEYDOWN && oEvent.key.keysym.sym == SDLK_ESCAPE))
        {
            Mix_HaltMusic();
            return false;
        }
        else if (oEvent.type == SDL_KEYDOWN || oEvent.type == SDL_KEYUP)
        {
            switch (oEvent.key.keysym.sym)
            {
                case SDLK_w:
                case SDLK_UP:
                    this->callKeyCallback(KEYCODE_UP, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    this->callKeyCallback(KEYCODE_DOWN, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    this->callKeyCallback(KEYCODE_LEFT, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    this->callKeyCallback(KEYCODE_RIGHT, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case SDLK_SPACE:
                    this->callKeyCallback(KEYCODE_SPACE, (oEvent.type == SDL_KEYDOWN) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                default:
                    break;
            }
        }
    }

    return true;
}


