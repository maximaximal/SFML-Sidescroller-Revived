#include "Entity.h"
#include "CApp/CApp.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <Box2D/Box2D.h>
#include <CConfig.h>

Entity::Entity()
{
    this->speed = 1.8;
}

void Entity::setPosition(sf::Vector2<int> Position)
{
    this->Position.x = Position.x;
    this->Position.y = Position.y;
}
void Entity::setPosition(int X, int Y)
{
    this->Position.x = X;
    this->Position.y = Y;
}
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(EntitySprite, states);
}
void Entity::move(int Direction)
{
    Position = this->EntitySprite.getPosition();
    switch (Direction)
    {
        case 0:
            if((this->Position.x + this->speed + this->EntitySprite.getGlobalBounds().width) < CConfig::Get()->getWindowX())
                this->Position.x = this->Position.x + this->speed;
            break;
        case 1:
            if((this->Position.y + this->speed + this->EntitySprite.getGlobalBounds().height) < CConfig::Get()->getWindowY())
                this->Position.y = this->Position.y + this->speed;
            break;
        case 2:
            if((this->Position.x - this->speed) >! 0)
                this->Position.x = this->Position.x - this->speed;
            break;
        case 3:
            if((this->Position.y - this->speed) >! 0)
            this->Position.y = this->Position.y - this->speed;
            break;
    }
    this->EntitySprite.setPosition(Position);
}
Entity::~Entity()
{
    //dtor
}
