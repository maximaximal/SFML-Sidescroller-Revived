#include "CApp/CApp.h"
#include <iostream>
#include <sstream>
#include <string>
#include <CConfig.h>
#include <CMenu.h>
#include <Manager/CPhysicsManager.h>
#include <CSoundEffect.h>
#include <Manager/CWebManager.h>
#include <CScorePopup.h>
#include <Manager/CPowerupManager.h>
#include <CMenu/Load.h>
#include <Explosions/CExplosionManager.h>
void CApp::onUpdate()
{
    using namespace std;

    if(CConfig::Get()->getGameState() == STATE_GAME)
    {
        //Move-Events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || charge)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || up)
                this->Player->move(UP_, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || left)
                this->Player->move(LEFT_, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || down)
                this->Player->move(DOWN_, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || right)
                this->Player->move(RIGHT_, CConfig::Get()->getShiftMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 1);
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || up)
                this->Player->move(UP_, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || left)
                this->Player->move(LEFT_, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || down)
                this->Player->move(DOWN_, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || right)
                this->Player->move(RIGHT_, CConfig::Get()->getNormalMoveForce() / 60 * this->FrameTime.asMilliseconds() * 4, 0);
        }
        //Shoot Event
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || shoot)
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
    }


    this->FrameTime = this->FrameClock->getElapsedTime();
    this->FrameClock->restart();
    this->FPSCounter++;
    this->FPSCache = this->FPSCache + (int) (1/FrameTime.asSeconds() + 0.5);
    if(FPSCounter > 29)
    {
        this->FPSCounter = 0;
        this->FPS = (int) (this->FPSCache / 30 + 0.5);
        this->FPSCache = 0;
    }
    if(CConfig::Get()->getDebug())
    {
        stringstream debugstream(stringstream::in | stringstream::out);
        debugstream << "FPS: " << this->FPS << " - 1 Frame: " << FrameTime.asMilliseconds() << "ms" << endl;
        debugstream << "Resolution: " << CConfig::Get()->getWindowX() << "x" << CConfig::Get()->getWindowY() << " pixels" << endl;
        debugstream << "1 Physics Timestep (max 16,6ms): " << CPhysicsManager::Get()->getPhysicsThreadFrameTime() * 1000 << "ms" << endl;
        debugstream << "STARS: " <<CConfig::Get()->getBackgroundStarsCount() << " - max " << CConfig::Get()->getBackgroundStarsCount() << " stars with your resolution! " << endl;
        debugstream << "Player-Position: X= " << (int) Player->getPosition().x << " Y= " << (int) Player->getPosition().y << " Linear Velocity: X=" << Player->getLinearVeloity().x << " Y=" << Player->getLinearVeloity().y << endl;
        debugstream << "Bullet-Count: " << BulletContainer->getBulletCount() << endl;
        debugstream << "Asteroid-Count: " << AsteroidContainer->getAsteroidCount() << " Maximum Asteroids with your game resolution: " << AsteroidContainer->getMaxAsteroids() << endl;
        debugstream << "Version: " << CConfig::Get()->getVersion() << " - Newest Version for OS" << CConfig::Get()->getOS() << ": " << CWebManager::Get()->getNewestVersion() << " " << endl;
        debugstream << "Local-Multiplayer: " << CConfig::Get()->getMP() << endl;
        if(CWebManager::Get()->getNewestVersion() > CConfig::Get()->getVersion())
            debugstream << "A newer Version is available!" << endl;
        else
            debugstream << endl;
        string debugstring = debugstream.str();
        this->T_DebugText->setString(debugstring);
    }
    if(CConfig::Get()->getGameState() == STATE_PAUSEMENU)
    {
        this->GameMenuNew->update(FrameTime.asSeconds());
    }
    if(CConfig::Get()->getGameState() == STATE_MAINMENU || CConfig::Get()->getGameState() == STATE_GUI)
    {
        this->GameMenuNew->update(FrameTime.asSeconds());
    }
    if(CConfig::Get()->getGameState() == STATE_GAME)
    {
        //Info Bar
        this->infoBar_health->setSize(sf::Vector2f(138 * ((Player->health * 10.f) / 100.f), 4));
        this->infoBar_fuel->setSize(sf::Vector2f(56 * (Player->fuel / 1000.f), 2));
        this->Background->updateStars();
        if(Player->getPosition().x < CConfig::Get()->getWindowX() / 2 && Player->getPosition().y + 30> CConfig::Get()->getWindowY() - (25 * this->infoBar->getScale().y))
        {
            this->infoBar_health->setFillColor(sf::Color(205,0,0, 50));
            this->infoBar_fuel->setFillColor(sf::Color(238,201,0, 50));
            this->infoBar->setColor(sf::Color(255, 255, 255, 50));
        }
        else
        {
            this->infoBar_health->setFillColor(sf::Color(205,0,0, 190));
            this->infoBar_fuel->setFillColor(sf::Color(238,201,0, 190));
            this->infoBar->setColor(sf::Color(255, 255, 255, 190));
        }
        //Info Bar
        BulletContainer->update();
        AsteroidContainer->update(FrameTime.asMilliseconds());
        CScorePopup::Get()->update(FrameTime.asMilliseconds());
        CPowerupManager::Get()->update(FrameTime.asMilliseconds());
        Player->update(FrameTime.asMilliseconds());
        CExplosionManager::Get()->update(FrameTime.asMilliseconds());
        stringstream ScoreString;
        ScoreString << "Your Score: " << (int) (CConfig::Get()->getHighscore()) << " Lv " << (int) (CConfig::Get()->getGameLevel());
        if(CWebManager::Get()->isConfigValid())
            this->T_Score->setColor(sf::Color::Green);
        if(!CWebManager::Get()->isConfigValid())
            this->T_Score->setColor(sf::Color::Red);
        this->T_Score->setString(ScoreString.str());
        if(Player->health <= 0)
        {
            if(CConfig::Get()->getScreenSaverMode() == false)
            {
                CConfig::Get()->pauseHighscore();
                if(CConfig::Get()->getGameSounds())
                {
                    CSoundEffect::Get()->playSound(SOUND_EXPLOSION);
                }
                MenuLoader->GameOver();
                CConfig::Get()->setGameState(STATE_GUI);
            }
        }
    }
    if(CConfig::Get()->getGameState() == STATE_GAMEOVER)
    {

    }
    if(CConfig::Get()->getGameState() == STATE_CREDITS)
    {

    }
    if(CConfig::Get()->getGameState() == STATE_LOADINGGAME)
    {
        Player->reset();
        BulletContainer->reset();
        AsteroidContainer->resetAsteroids();
        CPowerupManager::Get()->reset();
        CConfig::Get()->resetHighscore();
        CConfig::Get()->setGameState(STATE_GAME);
    }
    if(CConfig::Get()->getBackgroundMusic())
        BackgroundMusic->update();
    if(CConfig::Get()->getGameSounds())
        CSoundEffect::Get()->update();
}
