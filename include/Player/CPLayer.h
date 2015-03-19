#ifndef CPLAYER_H
#define CPLAYER_H

#include <Entity.h>
#include <Box2D/Box2D.h>
#include <Manager/CPhysicsManager.h>
#include <Container/CBulletContainer.h>

class CPlayer : public Entity
{
    public:
        CPlayer();
        bool init(int type);
        void toggleShield();
        void shoot();
        sf::Vector2f getPosition();
        sf::Vector2f getLinearVeloity();
        void move(int Direction, int force, int type);
        void stabilize();
        void quickMove(int Direction);
        void hit(PhysID hitByID);
        void update(float frametime);
        virtual ~CPlayer();
        int health;
        int fuel;
        void reset();
        void repair() {health = 10;}
        CBulletContainer *BulletContainer;
    protected:
        bool shield;
        float frametime;
        PhysID *ID;
        sf::IntRect *shieldOffPos;
        int type;
        b2Body *PlayerBody;
};

#endif // CPLAYER_H
