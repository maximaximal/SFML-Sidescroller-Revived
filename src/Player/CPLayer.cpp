#include <Player/CPLayer.h>
#include <Entity.h>
#include <Manager/CTextureManager.h>
#include <Manager/CPhysicsManager.h>
#include <Container/CBulletContainer.h>
#include <CConfig.h>
#include <Box2D/Box2D.h>
#include <iostream>
#include <CSoundEffect.h>
#include <Manager/CPowerupManager.h>
#include <PhysicsDefinitions.hpp>

CPlayer::CPlayer()
{
    this->shield = false;
    this->shieldOffPos = new sf::IntRect(379, 130, 55, 20);
    this->health = 10;
    CPowerupManager::Get()->Player = this;
    this->fuel = 0;
}
bool CPlayer::init(int type)
{
    this->type = type;
    //Load Sprite
        CTextureManager::Get()->createTexture(CConfig::Get()->getDataDir() + "/Data/Textures/SpaceshipSheet.png", "SpaceshipSheet");
        this->EntitySprite.setTexture(CTextureManager::Get()->getTexture("SpaceshipSheet"));
    //Init Physics
        b2BodyDef PlayerBodyDef;
        PlayerBodyDef.bullet = true;
        PlayerBodyDef.type = b2_dynamicBody;
        PlayerBodyDef.angle = 0;
        PlayerBodyDef.fixedRotation = true;
        ID = new PhysID();
        ID->type = PhysID_TYPE_PLAYER;
        ID->p = this;
        std::unique_ptr<b2FixtureDef> Fixture;
    if(type == 0)
    {
        this->EntitySprite.setTextureRect(*this->shieldOffPos);
        Fixture = CPhysicsManager::Get()->getFixtureFromScript("Player_1");
        if(CConfig::Get()->getMP())
            PlayerBodyDef.position.Set(20, CConfig::Get()->getWindowY() / 3 * PIXELSTOMETERS);
        else
            PlayerBodyDef.position.Set(20, CConfig::Get()->getWindowY() / 2 * PIXELSTOMETERS);
        ID->slot = 0;
    }
    if(type == 1)
    {
        this->EntitySprite.setTextureRect(sf::IntRect(334, 132, 40, 19));
        Fixture = CPhysicsManager::Get()->getFixtureFromScript("Player_2");
        if(CConfig::Get()->getMP() == true)
            PlayerBodyDef.position.Set(20, CConfig::Get()->getWindowY() / 3 * 2 * PIXELSTOMETERS);
        if(CConfig::Get()->getMP() == false)
            PlayerBodyDef.position.Set(20, CConfig::Get()->getWindowY() / 2 * PIXELSTOMETERS);
        ID->slot = 1;
    }
    PlayerBody = CPhysicsManager::Get()->World->CreateBody(&PlayerBodyDef);
    PlayerBody->CreateFixture(Fixture.get());
    Fixture.release();
    PlayerBody->SetUserData(ID);
    return 1;
}
void CPlayer::hit(PhysID hitByID)
{
    if(hitByID.type == PhysID_TYPE_ASTEROID)
    {
        if(!CConfig::Get()->getScreenSaverMode())
            this->health--;
        if(CConfig::Get()->getGameSounds())
            CSoundEffect::Get()->playSound(SOUND_ASTEROIDHIT);
    }
}
void CPlayer::stabilize()
{
    b2Vec2 Velocity = this->PlayerBody->GetLinearVelocity();
    if(Velocity.x < 0)
        Velocity.x = Velocity.x * (-1);
    if(Velocity.y < 0)
        Velocity.y = Velocity.y * (-1);
    if(Velocity.x < 5 && Velocity.y < 5)
        PlayerBody->SetLinearVelocity(b2Vec2(0, 0));
}
void CPlayer::toggleShield()
{
    std::cout << "NO LONGER WORKING, OLD FEATURE!" << std::endl;
}
void CPlayer::shoot()
{
    sf::Vector2f Origin = this->getPosition();
    Origin.x = Origin.x + 50;
    Origin.y = Origin.y + 8;
    if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_RED)
    {
        if(CPowerupManager::Get()->getWeaponLevel() == 1)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2000, 0), 1, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 2)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 1, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 1, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 7), sf::Vector2f(2500, 0), 1, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() > 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(3000, 0), 1, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 7), sf::Vector2f(3000, 0), 1, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 7), sf::Vector2f(3000, 0), 1, 0);
        }
        if(CConfig::Get()->getGameSounds())
            CSoundEffect::Get()->playSound(SOUND_LASER);
    }
    if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_MAGENTA)
    {
        if(CPowerupManager::Get()->getWeaponLevel() == 1)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2000, 0), 2, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 2)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 2, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 2, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() > 3)
        {
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 8), sf::Vector2f(3000, 0), 2, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 8), sf::Vector2f(3000, 0), 2, 0);
        }
        if(CConfig::Get()->getGameSounds())
            CSoundEffect::Get()->playSound(SOUND_LASER_BIG);
    }
    if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_GREEN)
    {
        if(CPowerupManager::Get()->getWeaponLevel() == 1)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2000, 0), 3, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 2)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 3, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 5), sf::Vector2f(3000, 0), 3, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 3, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 5), sf::Vector2f(3000, 0), 3, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() > 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(3000, 0), 3, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 5), sf::Vector2f(3000, 0), 3, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 5), sf::Vector2f(3000, 0), 3, 0);
        }
        if(CConfig::Get()->getGameSounds())
            CSoundEffect::Get()->playSound(SOUND_LASER_SMALL);
    }
    if(CPowerupManager::Get()->getWeapon() == POWERUP_LASER_BLUE)
    {
        if(CPowerupManager::Get()->getWeaponLevel() == 1)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2000, 0), 4, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 2)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 5), sf::Vector2f(3000, 0), 4, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() == 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(2500, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 5), sf::Vector2f(3000, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 5), sf::Vector2f(3000, 0), 4, 0);
        }
        if(CPowerupManager::Get()->getWeaponLevel() > 3)
        {
            this->BulletContainer->createBullet(Origin, sf::Vector2f(3000, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 5), sf::Vector2f(3000, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 5), sf::Vector2f(3000, 0), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y + 10), sf::Vector2f(3000, 1500), 4, 0);
            this->BulletContainer->createBullet(sf::Vector2f(Origin.x, Origin.y - 10), sf::Vector2f(3000, -1500), 4, 0);
        }
        if(CConfig::Get()->getGameSounds())
            CSoundEffect::Get()->playSound(SOUND_LASER_TINY);
    }
}
sf::Vector2f CPlayer::getPosition()
{
    b2Vec2 Position = this->PlayerBody->GetPosition();
    return sf::Vector2f(METERSTOPIXELS * Position.x - 0, METERSTOPIXELS * Position.y - 0);
}
sf::Vector2f CPlayer::getLinearVeloity()
{
    b2Vec2 Velocity = this->PlayerBody->GetLinearVelocity();
    return (sf::Vector2f(Velocity.x, Velocity.y));
}
void CPlayer::reset()
{
    health = 10;
    fuel = 0;
    if(CConfig::Get()->getMP())
    {
        if(type == 0)
            this->PlayerBody->SetTransform(b2Vec2(20, CConfig::Get()->getWindowY() / 3 * PIXELSTOMETERS), 0);
        if(type == 1)
            this->PlayerBody->SetTransform(b2Vec2(20, CConfig::Get()->getWindowY() / 3 * 2 * PIXELSTOMETERS), 0);
    }
    else
        this->PlayerBody->SetTransform(b2Vec2(20, CConfig::Get()->getWindowY() / 2 * PIXELSTOMETERS), 0);
    this->PlayerBody->SetLinearVelocity(b2Vec2(0, 0));
}
CPlayer::~CPlayer()
{
    delete this->shieldOffPos;
    delete this->ID;
    CPhysicsManager::Get()->World->DestroyBody(PlayerBody);
}
void CPlayer::update(float frametime)
{
    this->Position.x = METERSTOPIXELS * this->PlayerBody->GetPosition().x;
    this->Position.y = METERSTOPIXELS * this->PlayerBody->GetPosition().y;
    EntitySprite.setPosition(Position.x -0, Position.y -0);
    EntitySprite.setRotation(this->PlayerBody->GetAngle() * RADTODEG);
    if(this->type == 0)
        this->EntitySprite.setTextureRect(sf::IntRect(379, 130 + ((this->health * (-1) + 10) * 20), 55, 20));
    if(this->type == 1)
        this->EntitySprite.setTextureRect(sf::IntRect(334, 132 + ((this->health * (-1) + 10) * 20), 40, 19));
    this->frametime = frametime;
    if(this->fuel <= 1000)
    {
        this->fuel += (int) this->frametime * 0.068;
    }
    if(this->PlayerBody->GetWorldCenter().y < 0)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        this->PlayerBody->ApplyForceToCenter(b2Vec2(0, frametime * 80.f), true);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    if(this->PlayerBody->GetWorldCenter().y > CConfig::Get()->getWindowY() * PIXELSTOMETERS)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        this->PlayerBody->ApplyForceToCenter(b2Vec2(-500, frametime * -80.f), true);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
void CPlayer::move(int Direction, int force, int type)
{

    if(this->fuel - (int) this->frametime * 0.08 > 0 && type == 1)
    {
        this->fuel -= (int) this->frametime * 0.08;
        CPhysicsManager::Get()->WorldMutex.lock();
        switch (Direction)
        {
            case 0:
                this->PlayerBody->ApplyForce(b2Vec2(force, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 1:
                this->PlayerBody->ApplyForce(b2Vec2(0, force), PlayerBody->GetWorldCenter(), true);
                break;
            case 2:
                this->PlayerBody->ApplyForce(b2Vec2(-force, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 3:
                this->PlayerBody->ApplyForce(b2Vec2(0, -force), PlayerBody->GetWorldCenter(), true);
                break;
        }
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    else if(type == 0)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        switch (Direction)
        {
            case 0:
                this->PlayerBody->ApplyForce(b2Vec2(force, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 1:
                this->PlayerBody->ApplyForce(b2Vec2(0, force), PlayerBody->GetWorldCenter(), true);
                break;
            case 2:
                this->PlayerBody->ApplyForce(b2Vec2(-force, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 3:
                this->PlayerBody->ApplyForce(b2Vec2(0, -force), PlayerBody->GetWorldCenter(), true);
                break;
        }
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
void CPlayer::quickMove(int Direction)
{
    if(this->fuel - 200 > 0)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        switch (Direction)
        {
            case 0:
                this->PlayerBody->ApplyLinearImpulse(b2Vec2(2000, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 1:
                this->PlayerBody->ApplyLinearImpulse(b2Vec2(0, 2000), PlayerBody->GetWorldCenter(), true);
                break;
            case 2:
                this->PlayerBody->ApplyLinearImpulse(b2Vec2(-2000, 0), PlayerBody->GetWorldCenter(), true);
                break;
            case 3:
                this->PlayerBody->ApplyLinearImpulse(b2Vec2(0, -2000), PlayerBody->GetWorldCenter(), true);
                break;
        }
        this->fuel -= 200;
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
