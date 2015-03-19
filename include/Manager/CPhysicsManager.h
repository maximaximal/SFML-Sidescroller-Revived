#ifndef CPHYSICSMANAGER_H
#define CPHYSICSMANAGER_H
#include <vector>
#include <string>
#include <CSingleton.h>
#include <Box2D/Box2D.h>
#include <Diluculum/LuaState.hpp>
#include <SFML/System.hpp>
#include <memory>

//Define PhysID Types
    #define PhysID_TYPE_PLAYER 0
    #define PhysID_TYPE_BULLET 1
    #define PhysID_TYPE_ASTEROID 2
    #define PhysID_TYPE_WALL_LEFT 3
    #define PhysID_TYPE_POWERUP 4
    #define PhysID_TYPE_EXPLOSION_PARTICLE 5

struct PhysID
{
    int type;
    int slot;
    int extraData;
    void *p;
};

class CPhysicsManager : public TSingleton<CPhysicsManager>
{
    public:
        CPhysicsManager();
        virtual ~CPhysicsManager();
        void step();
        void addBody();
        float getPhysicsThreadFrameTime();
        sf::Mutex WorldMutex;
        b2World *World;
        std::unique_ptr<b2FixtureDef> getFixtureFromScript(std::string name);
    protected:
    private:
        sf::Thread *PhysicsStepThread;
        float *m_timeStep;
        Diluculum::LuaState ls;
        //Walls
            b2Body *Wall_Top;
            b2Body *Wall_Bottom;
            b2Body *Wall_Left;
            b2Body *Wall_Right;
            PhysID *WallID_Left;
};

class CContactListener : public b2ContactListener //Class from http://www.iforce2d.net/b2dtut/collision-callbacks
{
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // CPHYSICSMANAGER_H
