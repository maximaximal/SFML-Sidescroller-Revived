#include "Container/CAsteroidContainer.h"
#include <Manager/CTextureManager.h>
#include <Manager/CPhysicsManager.h>
#include <stdlib.h>
#include <CConfig.h>
#include <sstream>
#include <iostream>
#include <CSoundEffect.h>
#include <Manager/CFontManager.h>
#include <CScorePopup.h>
#include <Manager/CPowerupManager.h>
#include <Explosions/CExplosionManager.h>
#include <PhysicsDefinitions.hpp>

CAsteroidContainer::CAsteroidContainer()
{
    CTextureManager::Get()->createTexture("Data/Textures/MeteorSheet1.png", "MeteorSheet");
    CTextureManager::Get()->createTexture("Data/Textures/DamageSheet_32x32.png", "DamageSheet_32x32");
    this->maxAsteroids = CConfig::Get()->getMaxAsteroids();
    this->SpawnTimer = new sf::Clock();
    IDIterator = 0;
}
bool CAsteroidContainer::isAlive(int ID)
{
    bool alive = false;
    for(unsigned int i = 0; i < this->Asteroids.size(); i++)
    {
        if(Asteroids[i].ID->slot == ID)
        {
            if(Asteroids[i].damage < Asteroids[i].maxDamage)
                alive = true;
        }
    }
    return alive;
}
CAsteroidContainer::~CAsteroidContainer()
{
    for(unsigned int i = 0; i < Asteroids.size();i++)
    {
        delete(Asteroids[i].sprite);
        delete(Asteroids[i].damageSprite);
        CPhysicsManager::Get()->World->DestroyBody(Asteroids[i].body);
        delete(Asteroids[i].ID);
    }
    delete this->SpawnTimer;
}
void CAsteroidContainer::update(float frametime)
{
    unsigned int i = 0;
    if(CConfig::Get()->getGameLevel() < 25)
        this->spawnLimiterSize = CConfig::Get()->getGameLevel() * (-1) + 25;
    else
    {
         this->spawnLimiterSize = 5;
         this->maxAsteroids = (int) CConfig::Get()->getMaxAsteroids() * 1.5;
    }
    if(CConfig::Get()->getGameLevel() > 30)
        this->maxAsteroids = CConfig::Get()->getMaxAsteroids() * 2;
    if(CConfig::Get()->getGameLevel() > 32)
        this->maxAsteroids = CConfig::Get()->getMaxAsteroids() * 3;
    if(CConfig::Get()->getGameLevel() > 34)
        this->maxAsteroids = CConfig::Get()->getMaxAsteroids() * 4;
    if(CConfig::Get()->getGameLevel() > 35)
        this->maxAsteroids = CConfig::Get()->getMaxAsteroids() * 5;

    if(this->Asteroids.size() < this->maxAsteroids && this->SpawnTimer->getElapsedTime().asMilliseconds() * CConfig::Get()->getWindowX() * CConfig::Get()->getWindowY() * 0.00000044 > spawnLimiterSize)
    {
        spawnAsteroid(IDIterator);
        IDIterator = IDIterator + 1;
        this->SpawnTimer->restart();
    }
    for(i = 0; i < this->Asteroids.size();i++)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        Asteroids[i].sprite->setPosition(Asteroids[i].body->GetPosition().x * METERSTOPIXELS, Asteroids[i].body->GetPosition().y * METERSTOPIXELS);
        Asteroids[i].sprite->setRotation(Asteroids[i].body->GetAngle() * RADTODEG);
        Asteroids[i].damageSprite->setPosition(Asteroids[i].body->GetPosition().x * METERSTOPIXELS, Asteroids[i].body->GetPosition().y * METERSTOPIXELS);
        Asteroids[i].damageSprite->setRotation(Asteroids[i].body->GetAngle() * RADTODEG);
        if(Asteroids[i].damage >= Asteroids[i].maxDamage)
        {
            if(Asteroids[i].sprite->getPosition().x > 0) //Only make a explosion if the asteroid is destroyed before it leaves the screen
                CExplosionManager::Get()->createExplosion(Asteroids[i].sprite->getPosition(), Asteroids[i].sprite->getRotation(), 32);
            delete Asteroids[i].sprite;
            delete Asteroids[i].damageSprite;
            CPhysicsManager::Get()->World->DestroyBody(Asteroids[i].body);
            delete(Asteroids[i].ID);
            Asteroids.erase(Asteroids.begin() + i);

        }
        if(Asteroids[i].body->GetWorldCenter().y < 0)
        {
            Asteroids[i].body->ApplyForceToCenter(b2Vec2(frametime * -50.f, frametime * 70.f), true);
        }
        if(Asteroids[i].body->GetWorldCenter().y > CConfig::Get()->getWindowY() * PIXELSTOMETERS)
        {
            Asteroids[i].body->ApplyForceToCenter(b2Vec2(frametime * -50.f, frametime * -70.f), true);
        }
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
void CAsteroidContainer::resetAsteroids()
{
    for(unsigned int i = Asteroids.size(); i != 0; i--)
    {
        delete Asteroids[i - 1].sprite;
        delete Asteroids[i - 1].damageSprite;
        CPhysicsManager::Get()->WorldMutex.lock();
        CPhysicsManager::Get()->World->DestroyBody(Asteroids[i - 1].body);
        delete(Asteroids[i - 1].ID);
        Asteroids.erase(Asteroids.begin() + i - 1);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    IDIterator = 0;
}
void CAsteroidContainer::deleteAsteroid(int ID)
{
    for(unsigned int i = 0;i < Asteroids.size();i++)
    {
        if(Asteroids[i].ID->slot == ID)
        {
            Asteroids[i].damage += 10;
        }
    }
}
void CAsteroidContainer::hitAsteroid(int ID)
{
    for(unsigned int i = 0; i < Asteroids.size();i++)
    {
        if(Asteroids[i].ID->slot == ID)
        {
            Asteroids[i].damage++;
            Asteroids[i].damageSprite->setTextureRect(sf::IntRect((int) Asteroids[i].damage * 32, 0, 32, 32));
        }
    }
}
void CAsteroidContainer::hitByBullet(int ID, int BulletType)
{
    for(unsigned int i = 0; i < Asteroids.size();i++)
    {
        if(Asteroids[i].ID->slot == ID)
        {
            if(BulletType == POWERUP_LASER_RED)
                Asteroids[i].damage++;
            if(BulletType == POWERUP_LASER_BLUE)
                Asteroids[i].damage += 0.3;
            if(BulletType == POWERUP_LASER_MAGENTA)
                Asteroids[i].damage += 2.8;
            if(BulletType == POWERUP_LASER_GREEN)
                Asteroids[i].damage += 0.3;
            Asteroids[i].damageSprite->setTextureRect(sf::IntRect(((int)(Asteroids[i].damage)) * 32, 0, 32, 32));
            if(Asteroids[i].damage >= Asteroids[i].maxDamage)
            {
                if(Asteroids[i].alive)
                {
                    CConfig::Get()->addToHighscore(Asteroids[i].maxDamage * 2);
                    CScorePopup::Get()->popup(Asteroids[i].maxDamage * 2, Asteroids[i].sprite->getPosition());
                    if(CConfig::Get()->getGameSounds())
                        CSoundEffect::Get()->playSound(SOUND_ASTEROIDEXPLOSION);
                    CPowerupManager::Get()->spawnRandomBuffer(sf::Vector2f(Asteroids[i].body->GetPosition().x * METERSTOPIXELS, Asteroids[i].body->GetPosition().y * METERSTOPIXELS));
                }
                Asteroids[i].alive = false;
            }
        }
    }
}
void CAsteroidContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    unsigned int i = 0;
    for(i = 0; i < Asteroids.size();i++)
    {
        target.draw(*Asteroids[i].sprite);
        target.draw(*Asteroids[i].damageSprite);
    }
}
void CAsteroidContainer::spawnAsteroid(int i)
{
    CPhysicsManager::Get()->WorldMutex.lock();
    using namespace std;
    srand(rand());
    SAsteroid Asteroid;
    int type = rand()%20;
    Asteroid.type = type;
    Asteroid.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("MeteorSheet"));
    Asteroid.damageSprite = new sf::Sprite(CTextureManager::Get()->getTexture("DamageSheet_32x32"));
    Asteroid.damageSprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    Asteroid.sprite->setTextureRect(CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("MeteorSheet"), type, false));
    b2BodyDef AsteroidBodyDef;
    AsteroidBodyDef.bullet = true;
    AsteroidBodyDef.angle = 0;
    AsteroidBodyDef.type = b2_dynamicBody;
    AsteroidBodyDef.position.Set(CConfig::Get()->getWindowX() *PIXELSTOMETERS, ((rand()%(CConfig::Get()->getWindowY() + 40) - 20) *PIXELSTOMETERS));
    Asteroid.body = CPhysicsManager::Get()->World->CreateBody(&AsteroidBodyDef);
    std::stringstream fixtureName;
    fixtureName << "Asteroid_32x32_" << type;
    std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript(fixtureName.str());
    Asteroid.body->CreateFixture(Fixture.get());
    Fixture.release();
    Asteroid.body->ApplyLinearImpulse(b2Vec2(rand()%1500 - 1500 - (CConfig::Get()->getGameLevel() + 1) * 100, (rand()%800 - 400)), Asteroid.body->GetWorldCenter(), true);
    Asteroid.body->SetAngularVelocity((rand()%400 - 200) *0.01);
    Asteroid.ID = new PhysID();
    Asteroid.ID->type = PhysID_TYPE_ASTEROID;
    Asteroid.ID->slot = Asteroids.size();
    Asteroid.ID->p = this;
    Asteroid.ID->slot = i;
    Asteroid.maxDamage = rand()%6 + 5;
    Asteroid.body->SetUserData(Asteroid.ID);
    Asteroid.damage = 0;
    Asteroid.alive = true;
    Asteroids.push_back(Asteroid);
    CPhysicsManager::Get()->WorldMutex.unlock();
}
