#include "CApp/CApp.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player/CPLayer.h"
#include <iostream>
#include <Container/CBulletContainer.h>
#include <CSoundEffect.h>
#include <Manager/CPowerupManager.h>
void CApp::onEvent(sf::Event &Event)
{
    if(Event.type == sf::Event::Closed)
    {
        CConfig::Get()->quitGame();
    }
    if(CConfig::Get()->getGameState() == STATE_GAMEOVER)
    {

    }
    if (Event.type == sf::Event::KeyPressed)
    {
        if(Event.key.code == sf::Keyboard::Escape)
        {
            if(CConfig::Get()->getGameState() == STATE_GAME)
            {
                CConfig::Get()->setGameState(STATE_PAUSEMENU);
                MenuLoader->PauseMenu();
                return;
            }
            if(CConfig::Get()->getGameState() == STATE_PAUSEMENU)
            {
                GameMenuNew->clearHistory();
                CConfig::Get()->setGameState(STATE_GAME);
            }
        }
        if(Event.key.code == sf::Keyboard::F2)
        {
            this->takeScreenshot();
        }
        if (Event.key.code == sf::Keyboard::F3)
        {
            CConfig::Get()->toggleDebug();
        }
    }
    if (Event.type == sf::Event::KeyReleased)
    {
        if(Event.key.code == sf::Keyboard::Q || Event.key.code == sf::Keyboard::Numpad1)
        {
            Player->stabilize();
        }
        if(Event.key.code == sf::Keyboard::W || Event.key.code == sf::Keyboard::Up)
        {
            if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == UP_)
            {
                this->Player->quickMove(UP_);
                this->DoubleclickCache = -1;
            }
            else
                this->DoubleclickCache = UP_;
            this->DoubleclickClock->restart();
        }
        if(Event.key.code == sf::Keyboard::A || Event.key.code == sf::Keyboard::Left)
        {
            if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == LEFT_)
            {
                this->Player->quickMove(LEFT_);
                this->DoubleclickCache = -1;
            }
            else
                this->DoubleclickCache = LEFT_;
            this->DoubleclickClock->restart();
        }
        if(Event.key.code == sf::Keyboard::S || Event.key.code == sf::Keyboard::Down)
        {
            if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == DOWN_)
            {
                this->Player->quickMove(DOWN_);
                this->DoubleclickCache = -1;
            }
            else
                this->DoubleclickCache = DOWN_;
            this->DoubleclickClock->restart();
        }
        if(Event.key.code == sf::Keyboard::D || Event.key.code == sf::Keyboard::Right)
        {
            if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == RIGHT_)
            {
                this->Player->quickMove(RIGHT_);
                this->DoubleclickCache = -1;
            }
            else
                this->DoubleclickCache = RIGHT_;
            this->DoubleclickClock->restart();
        }
    }
    if(CConfig::Get()->getGameState() == STATE_GUI || CConfig::Get()->getGameState() == STATE_PAUSEMENU)
    {
        this->GameMenuNew->handleEvent(&Event);
    }
}
