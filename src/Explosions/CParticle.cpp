#include "Explosions/CParticle.h"

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Manager/CTextureManager.h>

CParticle::CParticle(sf::Vector2f pos, std::string texture, sf::IntRect textureRect)
{
    this->sprite = new sf::Sprite();
    this->ID = new PhysID();
    this->ID->p = this;
    this->ID->type = PhysID_TYPE_EXPLOSION_PARTICLE;
    this->sprite->setTexture(CTextureManager::Get()->getTexture(texture));
    this->sprite->setTextureRect(textureRect);
}
CParticle::~CParticle()
{
    delete this->sprite;
}
void CParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->sprite);
}
