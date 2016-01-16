/**
 * @file GameIOImpl.cpp
 * 
 * @author C. Smith
 * @date Jan 13, 2016
 */

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameIOImpl.h"

struct ioInternals
{
    sf::RenderWindow* pWindow;
    sf::Texture* pBlockTexture;
    sf::Music* pBgMusic;
};

GameIOImpl::GameIOImpl()
{
    this->pInternals = new ioInternals;
}

GameIOImpl::~GameIOImpl()
{
    this->Destroy();

    delete this->pInternals;
}

bool GameIOImpl::Init(const int windowHeight, const int windowWidth, const Color* bgColor)
{
    const char * blockImagePath = "media/block.bmp";

    this->pInternals->pWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Tetris");

    this->pInternals->pBlockTexture = new sf::Texture();
    this->pInternals->pBlockTexture->loadFromFile(blockImagePath);

    sf::Color bgc(bgColor->r, bgColor->g, bgColor->b, bgColor->a);

    this->pInternals->pWindow->clear(bgc);

    this->pInternals->pBgMusic = new sf::Music();

    return true;
}

void GameIOImpl::Destroy()
{
    if (this->pInternals->pBgMusic)
    {
        if (this->pInternals->pBgMusic->getStatus() != sf::SoundSource::Status::Stopped)
        {
            this->pInternals->pBgMusic->stop();
        }
        delete this->pInternals->pBgMusic;
    }

    if (this->pInternals->pBlockTexture)
    {
        delete this->pInternals->pBlockTexture;
    }

    if (this->pInternals->pWindow)
    {
        delete this->pInternals->pWindow;
    }
}

void GameIOImpl::ClearScreen(const Color* bgColor)
{
    sf::Color bgc(bgColor->r, bgColor->g, bgColor->b, bgColor->a);

    this->pInternals->pWindow->clear(bgc);
}

void GameIOImpl::DrawRect(const int x, const int y, const int w, const int h, const Color* color)
{
    sf::Color col(color->r, color->g, color->b, color->a);
    sf::RectangleShape rect(sf::Vector2f(w,h));
    rect.setPosition(x,y);
    rect.setFillColor(col);

    this->pInternals->pWindow->draw(rect);
}

void GameIOImpl::DrawTexture(const int x, const int y, const int w, const int h, const Color* color)
{
    sf::Color col(color->r, color->g, color->b, color->a);
    sf::RectangleShape rect(sf::Vector2f(w,h));
    rect.setPosition(x,y);
    rect.setFillColor(col);

    rect.setTexture(this->pInternals->pBlockTexture);
    this->pInternals->pWindow->draw(rect);
}

void GameIOImpl::Present()
{
    this->pInternals->pWindow->display();
}

void GameIOImpl::LoadBgMusicFromFile(const char* filename)
{
    if (!this->pInternals->pBgMusic->openFromFile(filename))
    {
        std::cerr << "Error: Could not load Music file: " << filename << std::endl;
    }
    else
    {
        this->pInternals->pBgMusic->setLoop(true);
    }
}

void GameIOImpl::PlayBgMusic()
{
    this->pInternals->pBgMusic->play();
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
    sf::Event oEvent;

    while (this->pInternals->pWindow->pollEvent(oEvent))
    {
        if (oEvent.type == sf::Event::Closed ||
           (oEvent.type == sf::Event::KeyPressed && oEvent.key.code == sf::Keyboard::Escape))
        {
            this->pInternals->pBgMusic->stop();
            return false;
        }
        else if (oEvent.type == sf::Event::KeyPressed || oEvent.type == sf::Event::KeyReleased)
        {
            switch (oEvent.key.code)
            {
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    this->callKeyCallback(KEYCODE_UP, (oEvent.type == sf::Event::KeyPressed) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    this->callKeyCallback(KEYCODE_DOWN, (oEvent.type == sf::Event::KeyPressed) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    this->callKeyCallback(KEYCODE_LEFT, (oEvent.type == sf::Event::KeyPressed) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    this->callKeyCallback(KEYCODE_RIGHT, (oEvent.type == sf::Event::KeyPressed) ? IO_KEY_DOWN : IO_KEY_UP, callbacks);
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}


