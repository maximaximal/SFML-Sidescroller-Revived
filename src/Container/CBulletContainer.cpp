#include "Container/CBulletContainer.h"
#include <math.h>
#include <Manager/CPhysicsManager.h>
#include <Manager/CTextureManager.h>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Manager/CPowerupManager.h>
#include <PhysicsDefinitions.hpp>

using namespace std;

CBulletContainer::CBulletContainer()
{
    //Bullet 1
        //Bullet Definition
            this->BulletBodyDef1 = new b2BodyDef;
            this->BulletBodyDef1->type = b2_dynamicBody;
            this->BulletBodyDef1->angle = 0;
            this->BulletBodyDef1->fixedRotation = true;
            this->BulletBodyDef1->bullet = true;
        //Bullet Shape
            this->BulletShape1 = new b2PolygonShape; //RED
            b2Vec2 vertices[8];
            vertices[0].Set(0, 1 * PIXELSTOMETERS);
            vertices[1].Set(1 * PIXELSTOMETERS, 0);
            vertices[2].Set(8 * PIXELSTOMETERS, 0);
            vertices[3].Set(9 * PIXELSTOMETERS, 1 * PIXELSTOMETERS);
            vertices[4].Set(9 * PIXELSTOMETERS, 4*PIXELSTOMETERS);
            vertices[5].Set(8 * PIXELSTOMETERS, 5 * PIXELSTOMETERS);
            vertices[6].Set(1 * PIXELSTOMETERS, 5 * PIXELSTOMETERS);
            vertices[7].Set(0 * PIXELSTOMETERS, 4 * PIXELSTOMETERS);
            this->BulletShape1->Set(vertices, 8);
        //Bullet Magenta Shape
            this->BulletShape2 = new b2PolygonShape; //MAGENTA
            b2Vec2 vertices2[8];
            vertices2[0].Set(5 * PIXELSTOMETERS, 0 * PIXELSTOMETERS);
            vertices2[1].Set(10 * PIXELSTOMETERS, 0);
            vertices2[2].Set(14 * PIXELSTOMETERS, 4 * PIXELSTOMETERS);
            vertices2[3].Set(14 *PIXELSTOMETERS, 11 * PIXELSTOMETERS);
            vertices2[4].Set(10 * PIXELSTOMETERS, 14 *PIXELSTOMETERS);
            vertices2[5].Set(4 * PIXELSTOMETERS, 14 * PIXELSTOMETERS);
            vertices2[6].Set(0 * PIXELSTOMETERS, 10 * PIXELSTOMETERS);
            vertices2[7].Set(0 * PIXELSTOMETERS, 4 * PIXELSTOMETERS);
            this->BulletShape2->Set(vertices2, 8);
        //Bullet Blue Shape
            this->BulletShape3 = new b2PolygonShape; //MAGENTA
            b2Vec2 vertices3[4];
            vertices3[0].Set(0 * PIXELSTOMETERS, 0 * PIXELSTOMETERS);
            vertices3[1].Set(4 * PIXELSTOMETERS, 0);
            vertices3[2].Set(4 * PIXELSTOMETERS, 1 * PIXELSTOMETERS);
            vertices3[3].Set(0 *PIXELSTOMETERS, 1 * PIXELSTOMETERS);
            this->BulletShape3->Set(vertices3, 4);
        //Bullet Green Shape
            this->BulletShape4 = new b2PolygonShape; //MAGENTA
            b2Vec2 vertices4[4];
            vertices4[0].Set(0 * PIXELSTOMETERS, 0 * PIXELSTOMETERS);
            vertices4[1].Set(3 * PIXELSTOMETERS, 0);
            vertices4[2].Set(3 * PIXELSTOMETERS, 3 * PIXELSTOMETERS);
            vertices4[3].Set(0 *PIXELSTOMETERS, 3 * PIXELSTOMETERS);
            this->BulletShape4->Set(vertices4, 4);
    //Set the ID-Iterator to 0
        IDIterator = 0;
}

CBulletContainer::~CBulletContainer()
{
    for(unsigned int i = 0; i < this->Bullets.size();i++)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        CPhysicsManager::Get()->World->DestroyBody(Bullets[i].body);
        CPhysicsManager::Get()->WorldMutex.unlock();
        delete Bullets[i].sprite;
    }
    delete(this->BulletBodyDef1);
    delete(this->BulletShape1);
    delete(this->BulletShape2);
    delete(this->BulletShape3);
    delete(this->BulletShape4);
}
void CBulletContainer::createBullet(sf::Vector2f pos, sf::Vector2f force, int type, int origin)
{
    if(type == 1) //Red
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        SBullet Bullet;
        b2FixtureDef BulletFixtureDef;
        Bullet.sprite = new sf::Sprite;
        BulletFixtureDef.shape = this->BulletShape1;
        BulletFixtureDef.density = 1;
        BulletFixtureDef.restitution = 0.1;
        Bullet.body = CPhysicsManager::Get()->World->CreateBody(this->BulletBodyDef1);
        Bullet.body->CreateFixture(&BulletFixtureDef);
        Bullet.dead = false;
        Bullet.body->ApplyLinearImpulse(b2Vec2(force.x, force.y), Bullet.body->GetPosition(), true);
        Bullet.sprite->setColor(sf::Color(255, 255, 255, 255));
        Bullet.sprite->setTexture(CTextureManager::Get()->getTexture("SpaceshipSheet"));
        Bullet.sprite->setTextureRect(sf::IntRect(5, 207, 10,5));
        Bullet.type = 1;
        Bullet.age = 0;
        Bullet.body->SetTransform(b2Vec2(PIXELSTOMETERS * pos.x, PIXELSTOMETERS * pos.y), 0);
        Bullet.body->SetAngularVelocity(0);
        Bullet.origin = origin;
        PhysID *ID = new PhysID();
        ID->slot = IDIterator;
        Bullet.ID = IDIterator;
        IDIterator++;
        ID->type = PhysID_TYPE_BULLET;
        ID->p = this;
        ID->extraData = POWERUP_LASER_RED;
        Bullet.hitCount = 0;
        Bullet.body->SetUserData(ID);
        Bullets.push_back(Bullet);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    if(type == 2) //Magenta
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        SBullet Bullet;
        b2FixtureDef BulletFixtureDef;
        Bullet.sprite = new sf::Sprite;
        BulletFixtureDef.shape = this->BulletShape2;
        BulletFixtureDef.density = 2.5;
        BulletFixtureDef.restitution = 0.1;
        Bullet.body = CPhysicsManager::Get()->World->CreateBody(this->BulletBodyDef1);
        Bullet.body->CreateFixture(&BulletFixtureDef);
        Bullet.dead = false;
        Bullet.body->ApplyLinearImpulse(b2Vec2(force.x, force.y), Bullet.body->GetPosition(), true);
        Bullet.sprite->setColor(sf::Color(255, 255, 255, 255));
        Bullet.sprite->setTexture(CTextureManager::Get()->getTexture("SpaceshipSheet"));
        Bullet.sprite->setTextureRect(sf::IntRect(5, 217, 15,15));
        Bullet.type = 2;
        Bullet.age = 0;
        Bullet.body->SetTransform(b2Vec2(PIXELSTOMETERS * pos.x, PIXELSTOMETERS * pos.y), 0);
        Bullet.body->SetAngularVelocity(0);
        Bullet.origin = origin;
        PhysID *ID = new PhysID();
        ID->slot = IDIterator;
        Bullet.ID = IDIterator;
        IDIterator++;
        ID->type = PhysID_TYPE_BULLET;
        ID->p = this;
        ID->extraData = POWERUP_LASER_MAGENTA;
        Bullet.hitCount = 0;
        Bullet.body->SetUserData(ID);
        Bullets.push_back(Bullet);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    if(type == 3) //Green
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        SBullet Bullet;
        b2FixtureDef BulletFixtureDef;
        Bullet.sprite = new sf::Sprite;
        BulletFixtureDef.shape = this->BulletShape3;
        BulletFixtureDef.density = 1;
        BulletFixtureDef.restitution = 0.1;
        Bullet.body = CPhysicsManager::Get()->World->CreateBody(this->BulletBodyDef1);
        Bullet.body->CreateFixture(&BulletFixtureDef);
        Bullet.dead = false;
        Bullet.body->ApplyLinearImpulse(b2Vec2(force.x, force.y), Bullet.body->GetPosition(), true);
        Bullet.sprite->setColor(sf::Color(255, 255, 255, 255));
        Bullet.sprite->setTexture(CTextureManager::Get()->getTexture("SpaceshipSheet"));
        Bullet.sprite->setTextureRect(sf::IntRect(5, 232, 3, 3));
        Bullet.type = 3;
        Bullet.age = 0;
        Bullet.body->SetTransform(b2Vec2(PIXELSTOMETERS * pos.x, PIXELSTOMETERS * pos.y), 0);
        Bullet.body->SetAngularVelocity(0);
        Bullet.origin = origin;
        PhysID *ID = new PhysID();
        ID->slot = IDIterator;
        Bullet.ID = IDIterator;
        IDIterator++;
        ID->type = PhysID_TYPE_BULLET;
        ID->p = this;
        ID->extraData = POWERUP_LASER_GREEN;
        Bullet.hitCount = 0;
        Bullet.body->SetUserData(ID);
        Bullets.push_back(Bullet);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
    if(type == 4) //Blue
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        SBullet Bullet;
        b2FixtureDef BulletFixtureDef;
        Bullet.sprite = new sf::Sprite;
        BulletFixtureDef.shape = this->BulletShape4;
        BulletFixtureDef.density = 1;
        BulletFixtureDef.restitution = 0.1;
        Bullet.body = CPhysicsManager::Get()->World->CreateBody(this->BulletBodyDef1);
        Bullet.body->CreateFixture(&BulletFixtureDef);
        Bullet.dead = false;
        Bullet.body->ApplyLinearImpulse(b2Vec2(force.x, force.y), Bullet.body->GetPosition(), true);
        Bullet.sprite->setColor(sf::Color(255, 255, 255, 255));
        Bullet.sprite->setTexture(CTextureManager::Get()->getTexture("SpaceshipSheet"));
        Bullet.sprite->setTextureRect(sf::IntRect(5, 235, 5,2));
        Bullet.type = 4;
        Bullet.age = 0;
        Bullet.body->SetTransform(b2Vec2(PIXELSTOMETERS * pos.x, PIXELSTOMETERS * pos.y), 0);
        Bullet.body->SetAngularVelocity(0);
        Bullet.origin = origin;
        PhysID *ID = new PhysID();
        ID->slot = IDIterator;
        Bullet.ID = IDIterator;
        IDIterator++;
        ID->type = PhysID_TYPE_BULLET;
        ID->p = this;
        ID->extraData = POWERUP_LASER_BLUE;
        Bullet.hitCount = 0;
        Bullet.body->SetUserData(ID);
        Bullets.push_back(Bullet);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
void CBulletContainer::destroyBullet(unsigned int ID)
{
    for(unsigned int i = 0; i < Bullets.size();i++)
    {
        if(Bullets[i].ID == ID)
        {
            if(Bullets[i].type == POWERUP_LASER_GREEN)
            {
                Bullets[i].hitCount++;
                if(Bullets[i].hitCount > 2)
                    Bullets[i].dead = true;
            }
            else
                Bullets[i].dead = true;
        }
    }
}
void CBulletContainer::reset()
{
    for(unsigned int i = 0; i < Bullets.size();i++)
    {
        Bullets[i].dead = true;
    }
}
void CBulletContainer::update()
{
    for(unsigned int i = 0; i < Bullets.size(); i++)
    {
        CPhysicsManager::Get()->WorldMutex.lock();
        if(Bullets[i].body->GetLinearVelocity().x < 2 && Bullets[i].body->GetLinearVelocity().y < 2)
            Bullets[i].dead = true;
        if(Bullets[i].dead || Bullets[i].age > 2000)
        {
            delete static_cast<PhysID*>(Bullets[i].body->GetUserData());
            CPhysicsManager::Get()->World->DestroyBody(Bullets[i].body);
            delete Bullets[i].sprite;
            Bullets.erase(Bullets.begin() + i);
        }
        Bullets[i].age++;
        b2Vec2 Position = Bullets[i].body->GetPosition();
        Bullets[i].sprite->setPosition(METERSTOPIXELS * Position.x, METERSTOPIXELS * Position.y);
        Bullets[i].sprite->setRotation(Bullets[i].body->GetAngle() * RADTODEG);
        CPhysicsManager::Get()->WorldMutex.unlock();
    }
}
void CBulletContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i = 0;i < Bullets.size();i++)
    {
        target.draw(*Bullets[i].sprite, states);
    }
}
