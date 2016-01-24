#include "Manager/CPowerupManager.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Manager/CTextureManager.h>
#include <CScorePopup.h>
#include <CConfig.h>
#include <CSoundEffect.h>
#include <PhysicsDefinitions.hpp>

using namespace std;

CPowerupManager::CPowerupManager()
{
    CTextureManager::Get()->createTexture(CConfig::Get()->getDataDir() + "/Data/Textures/Powerups.png", "PowerupSheet");
    this->weapon = POWERUP_LASER_RED;
    this->weaponLevel = 1;
}
void CPowerupManager::reset()
{
    this->weapon = CConfig::Get()->getStartLaser();
    this->weaponLevel = CConfig::Get()->getStartLaserLevel();
    for(unsigned int i = 0; i < powerups.size(); i++)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        CPhysicsManager::Get()->World->DestroyBody(powerups[i].body);
        CPhysicsManager::Get()->WorldMutex.unlock();
        delete powerups[i].sprite;
        delete powerups[i].ID;
    }
    powerups.clear();
}
CPowerupManager::~CPowerupManager()
{
    this->weapon = POWERUP_LASER_RED;
    this->weaponLevel = 1;
    for(unsigned int i = 0; i < powerups.size(); i++)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        CPhysicsManager::Get()->World->DestroyBody(powerups[i].body);
        CPhysicsManager::Get()->WorldMutex.unlock();
        delete powerups[i].sprite;
        delete powerups[i].ID;
    }
    powerups.clear();
}
void CPowerupManager::spawnRandomBuffer(sf::Vector2f pos)
{
    this->buffer.push_back(pos);
}
int CPowerupManager::getWeapon()
{
    return this->weapon;
}
int CPowerupManager::getWeaponLevel()
{
    return this->weaponLevel;
}
void CPowerupManager::spawnRandom(sf::Vector2f pos)
{
    srand(time(NULL));
    int random = rand()%15;
    if(random == 1 || random == 0)
    {
        int CategorySeed = rand()%100;
        if(CategorySeed >= 0 && CategorySeed < 40)
        {
            srand (time(NULL));
            this->spawn(rand()%4 + 1, pos); //Spawn a Powerup of a random Laser....
        }
        if(CategorySeed >= 40 && CategorySeed < 60)
        {
            this->spawn(POWERUP_REPAIR, pos);
        }
        //if(CategorySeed >= 60 && CategorySeed < 70)
        //{
        //    this->spawn(POWERUP_MULTIPLIKATOR, pos);
        //}
        if(CategorySeed >= 60 && CategorySeed < 100)
        {
            this->spawn(POWERUP_BONUS, pos);
        }
    }
}
void CPowerupManager::apply(int ID)
{
    for(unsigned int i = 0; i < powerups.size(); i++)
    {
        if(powerups[i].ID->slot == ID)
        {
            if(CConfig::Get()->getGameSounds())
                CSoundEffect::Get()->playSound(SOUND_POWERUPAPPLY);
            powerups[i].life += 80 * 255; //Increase the life of the powerup to delete it the next update cycle
            if(powerups[i].type == POWERUP_REPAIR)
                Player->repair();
            if(powerups[i].type == POWERUP_BONUS)
            {
                int score1 = rand()%20;
                int score2 = rand()%20;
                int score3 = rand()%20;
                int score4 = rand()%20;
                CScorePopup::Get()->popup(score1, sf::Vector2f(powerups[i].sprite->getPosition().x + 20, powerups[i].sprite->getPosition().y + 20));
                CScorePopup::Get()->popup(score2, sf::Vector2f(powerups[i].sprite->getPosition().x - 20, powerups[i].sprite->getPosition().y - 20));
                CScorePopup::Get()->popup(score3, sf::Vector2f(powerups[i].sprite->getPosition().x - 20, powerups[i].sprite->getPosition().y + 20));
                CScorePopup::Get()->popup(score4, sf::Vector2f(powerups[i].sprite->getPosition().x + 20, powerups[i].sprite->getPosition().y - 20));
                CConfig::Get()->addToHighscore(score1 + score2 + score3 + score4);
            }
            if(powerups[i].type == POWERUP_LASER_BLUE || powerups[i].type == POWERUP_LASER_GREEN || powerups[i].type == POWERUP_LASER_MAGENTA || powerups[i].type == POWERUP_LASER_RED)
            {
                if(powerups[i].type == weapon)
                    this->weaponLevel++;
                else
                {
                    this->weaponLevel = 1;
                    this->weapon = powerups[i].type;
                }
            }
        }
    }
}
void CPowerupManager::spawn(int type, sf::Vector2f pos)
{
    CPhysicsManager::Get()->WorldMutex.lock();
    powerup Powerup;
    Powerup.type = type;
    Powerup.life = 0;
    Powerup.ID = new PhysID;
    Powerup.ID->slot = IDIterator;
    Powerup.ID->type = PhysID_TYPE_POWERUP;
    Powerup.ID->extraData = 0;
    IDIterator = IDIterator + 1;
    if(IDIterator > 100000)
        IDIterator = 0;
    //Box2D Body Generator
        b2BodyDef BodyDef;
        BodyDef.position.Set(pos.x * PIXELSTOMETERS, pos.y * PIXELSTOMETERS);
        Powerup.body = CPhysicsManager::Get()->World->CreateBody(&BodyDef);
        Powerup.body->SetUserData(Powerup.ID);
    if(type == POWERUP_LASER_BLUE)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 6, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Laser");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_LASER_GREEN)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 7, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Laser");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_LASER_MAGENTA)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 8, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Laser");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_LASER_RED)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 5, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Laser");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_REPAIR)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 0, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Repair");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_MULTIPLIKATOR)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 4, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Star");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    if(type == POWERUP_BONUS)
    {
        Powerup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture("PowerupSheet"), CTextureManager::Get()->getTextureRect(32, 32, CTextureManager::Get()->textureLoaded("PowerupSheet"), 1, false));
        std::unique_ptr<b2FixtureDef> Fixture = CPhysicsManager::Get()->getFixtureFromScript("Powerup_Star");
        Fixture.get()->isSensor = true;
        Powerup.body->CreateFixture(Fixture.get());
        Fixture.release();
    }
    CPhysicsManager::Get()->WorldMutex.unlock();
    Powerup.sprite->setPosition(pos);
    if(CConfig::Get()->getGameSounds())
        CSoundEffect::Get()->playSound(SOUND_POWERUP);
    this->powerups.push_back(Powerup);

}
void CPowerupManager::update(float frametime)
{
    unsigned int i = 0;
    for(i = 0; i < this->buffer.size(); i++)
    {
        this->spawnRandom(buffer[i]);
        buffer.erase(buffer.begin() + i);
    }
    for(i = 0; i < this->powerups.size(); i++)
    {
        powerups[i].life += frametime;
        powerups[i].sprite->setColor(sf::Color(255, 255, 255, (powerups[i].life / 80) * (-1) + 255));
        if(powerups[i].life / 80 > 255)
        {
            CPhysicsManager::Get()->WorldMutex.lock();
            CPhysicsManager::Get()->World->DestroyBody(powerups[i].body);
            delete powerups[i].sprite;
            delete powerups[i].ID;
            powerups.erase(powerups.begin() + i);
            CPhysicsManager::Get()->WorldMutex.unlock();
        }
    }
}
void CPowerupManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i = 0; i < powerups.size(); i++)
    {
        target.draw(*powerups[i].sprite);
    }
}
