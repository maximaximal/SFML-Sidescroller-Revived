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
void CApp::onEvent()
{
    sf::Event Event;
    while(this->App->pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
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
                    continue;
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
                if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == UP)
                {
                    this->Player->quickMove(UP);
                    this->DoubleclickCache = -1;
                }
                else
                    this->DoubleclickCache = UP;
                this->DoubleclickClock->restart();
            }
            if(Event.key.code == sf::Keyboard::A || Event.key.code == sf::Keyboard::Left)
            {
                if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == LEFT)
                {
                    this->Player->quickMove(LEFT);
                    this->DoubleclickCache = -1;
                }
                else
                    this->DoubleclickCache = LEFT;
                this->DoubleclickClock->restart();
            }
            if(Event.key.code == sf::Keyboard::S || Event.key.code == sf::Keyboard::Down)
            {
                if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == DOWN)
                {
                    this->Player->quickMove(DOWN);
                    this->DoubleclickCache = -1;
                }
                else
                    this->DoubleclickCache = DOWN;
                this->DoubleclickClock->restart();
            }
            if(Event.key.code == sf::Keyboard::D || Event.key.code == sf::Keyboard::Right)
            {
                if(this->DoubleclickClock->getElapsedTime().asMilliseconds() < CConfig::Get()->getDoubleTapSpeed() && this->DoubleclickCache == RIGHT)
                {
                    this->Player->quickMove(RIGHT);
                    this->DoubleclickCache = -1;
                }
                else
                    this->DoubleclickCache = RIGHT;
                this->DoubleclickClock->restart();
            }
        }
        if(CConfig::Get()->getGameState() == STATE_GUI || CConfig::Get()->getGameState() == STATE_PAUSEMENU)
        {
            this->GameMenuNew->handleEvent(&Event);
        }
    }

    if(CConfig::Get()->getGameState() == STATE_GAME)
    {
        //Move-Events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                this->Player->move(UP, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                this->Player->move(LEFT, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                this->Player->move(DOWN, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                this->Player->move(RIGHT, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                this->Player->move(UP, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                this->Player->move(LEFT, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                this->Player->move(DOWN, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                this->Player->move(RIGHT, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                this->Player2->move(UP, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                this->Player2->move(LEFT, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                this->Player2->move(DOWN, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                this->Player2->move(RIGHT, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                this->Player2->move(UP, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                this->Player2->move(LEFT, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                this->Player2->move(DOWN, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                this->Player2->move(RIGHT, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
        }
        //Shoot Event
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            int ShootMultiplicator = 0; //Value to manipulate the shoot speed
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_RED)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 0;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-30);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = 80;
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = 170;
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_MAGENTA)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 300;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = 250;
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = 200;
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = 200;
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_GREEN)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 0;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-10);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = (-20);
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = (-20);
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_BLUE)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = (-20);
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-40);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = (-60);
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = (-65);
            }
            if(ShootTimer->getElapsedTime().asMilliseconds() > CConfig::Get()->getShootRate() + ShootMultiplicator && CConfig::Get()->getGameState() == STATE_GAME)
            {
                ShootCache = false;
                ShootTimer->restart();
            }
            if(ShootCache == false)
            {
                Player->shoot();
                ShootTimer->restart();
                ShootCache = true;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0))
        {
            int ShootMultiplicator = 0; //Value to manipulate the shoot speed
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_RED)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 0;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-30);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = 80;
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = 170;
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_MAGENTA)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 300;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = 250;
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = 200;
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = 200;
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_GREEN)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = 0;
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-10);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = (-20);
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = (-20);
            }
            if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_BLUE)
            {
                if(CPowerupManager::Get()->getWeaponLevel() == 1)
                    ShootMultiplicator = (-20);
                if(CPowerupManager::Get()->getWeaponLevel() == 2)
                    ShootMultiplicator = (-40);
                if(CPowerupManager::Get()->getWeaponLevel() == 3)
                    ShootMultiplicator = (-60);
                if(CPowerupManager::Get()->getWeaponLevel() > 3)
                    ShootMultiplicator = (-65);
            }
            if(ShootTimer2->getElapsedTime().asMilliseconds() > CConfig::Get()->getShootRate() + ShootMultiplicator && CConfig::Get()->getGameState() == STATE_GAME)
            {
                ShootCache2 = false;
                ShootTimer2->restart();
            }
            if(ShootCache2 == false)
            {
                Player2->shoot();
                ShootTimer2->restart();
                ShootCache2 = true;
            }
        }
    }
}
