#include "Manager/CPhysicsManager.h"
#include <Box2D/Box2D.h>
#include <CConfig.h>
#include <iostream>
#include <sstream>
#include <Player/CPLayer.h>
#include <Container/CAsteroidContainer.h>
#include <Container/CBulletContainer.h>
#include <vector>
#include <CSoundEffect.h>
#include <Manager/CPowerupManager.h>
#include <PhysicsDefinitions.hpp>

CContactListener ContactListener;

void physicsThread(b2World *World);
float physics_frametime;


CPhysicsManager::CPhysicsManager()
{
    b2Vec2 gravity(0, 0);
    this->World = new b2World(gravity); //Create a new World: no gravity
    m_timeStep = new float;
    *m_timeStep = 1.f/60.f;

    //Read Fixtures from lua "Data/Script/fixtures.lua"
        ls.doFile("Data/Script/fixtures.lua");

    //Set Contact Listener
        this->World->SetContactListener(&ContactListener);

    //Create Walls
        //Length
            WallID_Left = new PhysID;
            WallID_Left->slot = 0;
            WallID_Left->type = PhysID_TYPE_WALL_LEFT;
            b2BodyDef WallDef;
            b2EdgeShape WallShape;
            b2FixtureDef WallFixtureDef;
            WallDef.type = b2_staticBody;
            WallShape.Set(b2Vec2(-5, -5), b2Vec2(10 + CConfig::Get()->getWindowX() * PIXELSTOMETERS, -5));
            WallFixtureDef.shape = &WallShape;
            this->Wall_Top = World->CreateBody(&WallDef);
            WallDef.position.Set(-5, (PIXELSTOMETERS * CConfig::Get()->getWindowY()) + 10);
            this->Wall_Bottom = World->CreateBody(&WallDef);
            this->Wall_Bottom->CreateFixture(&WallFixtureDef);
            this->Wall_Top->CreateFixture(&WallFixtureDef);
            WallShape.Set(b2Vec2(-5, -5), b2Vec2(-5, PIXELSTOMETERS * CConfig::Get()->getWindowY() + 10));
            WallDef.position.Set(-5, -5);
            this->Wall_Left = World->CreateBody(&WallDef);
            this->Wall_Left->SetUserData(WallID_Left);
            Wall_Left->CreateFixture(&WallFixtureDef);
            WallDef.position.Set(10 + CConfig::Get()->getWindowX() * PIXELSTOMETERS, -5);
            Wall_Right = World->CreateBody(&WallDef);
            Wall_Right->CreateFixture(&WallFixtureDef);
    //Start the Physics Thread
        PhysicsStepThread = new sf::Thread(&physicsThread, World);
        PhysicsStepThread->launch();
}
std::unique_ptr<b2FixtureDef> CPhysicsManager::getFixtureFromScript(std::string name)
{
    std::unique_ptr<b2FixtureDef> Fixture(new b2FixtureDef);
    b2PolygonShape *Shape = new b2PolygonShape;
    int verticesCount = ls[name]["vertices"].value().asNumber();
    b2Vec2 *vertices = new b2Vec2[verticesCount];
    std::stringstream vertID;
    std:: string vertIDString;
    float vertX, vertY;
    int i;
    for(i = 0; i < verticesCount; i++)
    {
        vertID << "vert_" << i << "_x";
        vertIDString = vertID.str();
        vertX = ls[name][vertIDString].value().asNumber();
        vertID.str("");
        vertID << "vert_" << i << "_y";
        vertIDString = vertID.str();
        vertY = ls[name][vertIDString].value().asNumber();
        vertices[i].x = vertX * PIXELSTOMETERS;
        vertices[i].y = vertY * PIXELSTOMETERS;
        vertID.str("");
    }
    Shape->Set(vertices, verticesCount);
    Fixture.get()->shape = Shape;
    Fixture.get()->friction = ls[name]["friction"].value().asNumber();
    Fixture.get()->restitution = ls[name]["restitution"].value().asNumber();
    Fixture.get()->density = ls[name]["density"].value().asNumber();
    return Fixture;
}
CPhysicsManager::~CPhysicsManager()
{
    PhysicsStepThread->wait();
    delete(m_timeStep);
    delete this->WallID_Left;
    delete(World);
}
void CPhysicsManager::step()
{
    World->Step(*m_timeStep, 6, 2);
}
float CPhysicsManager::getPhysicsThreadFrameTime()
{
    return physics_frametime;
}
void CContactListener::BeginContact(b2Contact *contact)
{
    CPhysicsManager::Get()->WorldMutex.lock();
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if(bodyUserData)
    {
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_PLAYER)
        {
            void *OtherBodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
            PhysID ID;
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_POWERUP && static_cast<PhysID*>(OtherBodyUserData)->extraData != 1)
                {
                    CPowerupManager::Get()->apply(static_cast<PhysID*>(OtherBodyUserData)->slot);
                    static_cast<PhysID*>(OtherBodyUserData)->extraData = 1;
                }
                else
                {
                    ID.type = static_cast<PhysID*>(OtherBodyUserData)->type;
                    ID.slot = static_cast<PhysID*>(OtherBodyUserData)->slot;
                    static_cast<CPlayer*>(static_cast<PhysID*>(bodyUserData)->p)->hit(ID);
                }
            }
            else
            {
                ID.type = -1;
                ID.slot = -1;
                static_cast<CPlayer*>(static_cast<PhysID*>(bodyUserData)->p)->hit(ID);
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_ASTEROID)
        {
            void *OtherBodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_WALL_LEFT)
                {
                    static_cast<CAsteroidContainer*>(static_cast<PhysID*>(bodyUserData)->p)->deleteAsteroid(static_cast<PhysID*>(bodyUserData)->slot);
                }
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET || static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_ASTEROID || static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_PLAYER)
        {
            void *OtherBodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                {
                    if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET && static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                        static_cast<CAsteroidContainer*>(static_cast<PhysID*>(OtherBodyUserData)->p)->hitByBullet(static_cast<PhysID*>(OtherBodyUserData)->slot, static_cast<PhysID*>(bodyUserData)->extraData);
                    else
                        static_cast<CAsteroidContainer*>(static_cast<PhysID*>(OtherBodyUserData)->p)->hitAsteroid(static_cast<PhysID*>(OtherBodyUserData)->slot);

                }
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET)
        {
            void *OtherBodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type != PhysID_TYPE_PLAYER && static_cast<PhysID*>(OtherBodyUserData)->type != PhysID_TYPE_POWERUP)
                    static_cast<CBulletContainer*>(static_cast<PhysID*>(bodyUserData)->p)->destroyBullet(static_cast<PhysID*>(bodyUserData)->slot);
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                {
                    if(CConfig::Get()->getGameSounds())
                        CSoundEffect::Get()->playSound(SOUND_ASTEROIDHIT);
                }

            }
            else
                static_cast<CBulletContainer*>(static_cast<PhysID*>(bodyUserData)->p)->destroyBullet(static_cast<PhysID*>(bodyUserData)->slot);
        }
    }
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserData)
    {
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_PLAYER)
        {
            void *OtherBodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
            PhysID ID;
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_POWERUP && static_cast<PhysID*>(OtherBodyUserData)->extraData != 1)
                {
                    CPowerupManager::Get()->apply(static_cast<PhysID*>(OtherBodyUserData)->slot);
                    static_cast<PhysID*>(OtherBodyUserData)->extraData = 1;
                }
                else
                {
                    ID.type = static_cast<PhysID*>(OtherBodyUserData)->type;
                    ID.slot = static_cast<PhysID*>(OtherBodyUserData)->slot;
                    static_cast<CPlayer*>(static_cast<PhysID*>(bodyUserData)->p)->hit(ID);
                }
            }
            else
            {
                ID.type = -1;
                ID.slot = -1;
                static_cast<CPlayer*>(static_cast<PhysID*>(bodyUserData)->p)->hit(ID);
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_ASTEROID)
        {
            void *OtherBodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_WALL_LEFT)
                {
                    static_cast<CAsteroidContainer*>(static_cast<PhysID*>(bodyUserData)->p)->deleteAsteroid(static_cast<PhysID*>(bodyUserData)->slot);
                }
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET || static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_ASTEROID || static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_PLAYER)
        {
            void *OtherBodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                {
                    if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET && static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                        static_cast<CAsteroidContainer*>(static_cast<PhysID*>(OtherBodyUserData)->p)->hitByBullet(static_cast<PhysID*>(OtherBodyUserData)->slot, static_cast<PhysID*>(bodyUserData)->extraData);
                    else
                        static_cast<CAsteroidContainer*>(static_cast<PhysID*>(OtherBodyUserData)->p)->hitAsteroid(static_cast<PhysID*>(OtherBodyUserData)->slot);

                }
            }
        }
        if(static_cast<PhysID*>(bodyUserData)->type == PhysID_TYPE_BULLET)
        {
            void *OtherBodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
            if(OtherBodyUserData)
            {
                if(static_cast<PhysID*>(OtherBodyUserData)->type != PhysID_TYPE_PLAYER && static_cast<PhysID*>(OtherBodyUserData)->type != PhysID_TYPE_POWERUP)
                    static_cast<CBulletContainer*>(static_cast<PhysID*>(bodyUserData)->p)->destroyBullet(static_cast<PhysID*>(bodyUserData)->slot);
                if(static_cast<PhysID*>(OtherBodyUserData)->type == PhysID_TYPE_ASTEROID)
                {
                    if(CConfig::Get()->getGameSounds())
                        CSoundEffect::Get()->playSound(SOUND_ASTEROIDHIT);
                }
            }
            else
                static_cast<CBulletContainer*>(static_cast<PhysID*>(bodyUserData)->p)->destroyBullet(static_cast<PhysID*>(bodyUserData)->slot);
        }
    }
    CPhysicsManager::Get()->WorldMutex.unlock();
}
void CContactListener::EndContact(b2Contact *contact)
{

}
void physicsThread(b2World *World)
{
    using namespace std;
    sf::Clock Clock;
    Clock.restart();
    while(CConfig::Get()->isRunning())
    {
        sf::sleep(sf::seconds(1.f/60.f - Clock.getElapsedTime().asSeconds() - 0.0005));
        if(CConfig::Get()->getGameState() == STATE_GAME)
        {
            CPhysicsManager::Get()->WorldMutex.lock();
            Clock.restart();
            World->Step(1.f/60.f, 6, 2);
            physics_frametime = Clock.getElapsedTime().asSeconds();
            CPhysicsManager::Get()->WorldMutex.unlock();
        }
    }
}
