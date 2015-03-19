#include "Explosions/CExplosion.h"
#include <Manager/CTextureManager.h>
#include <stdlib.h>
#include <ctime>
#include <Explosions/CParticle.h>
CExplosion::CExplosion(sf::Vector2f pos, float rotation, int size)
{
    this->explosionSprite = new sf::Sprite();
    this->timer = new sf::Clock();
    //Init the Texture (For security reasons)
        CTextureManager::Get()->createTexture("Data/Textures/explosionsSheet.png", "ExplosionsSheet");
    //Set the protected variables
        this->pos = pos;
        this->rotation = rotation;
    //Set the texture
        this->explosionSprite->setTexture(CTextureManager::Get()->getTexture("ExplosionsSheet"));
    //Set the Scale
        this->explosionSprite->setScale(sf::Vector2f(size/64.f, size/64.f));
    //Set the sprite to the position & the rotation
        this->explosionSprite->setPosition(pos);
        this->explosionSprite->setRotation(rotation);
    //Set to alive
        this->alive = true;

}

CExplosion::~CExplosion()
{
    for(unsigned int i = 0; i < this->particles.size(); i++)
    {
        delete this->particles[i];
    }
    delete this->explosionSprite;
    delete this->timer;
}
void CExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->explosionSprite);
    for(unsigned int i = 0; i < this->particles.size(); i++)
    {
        target.draw(*this->particles[i]);
    }
}
void CExplosion::update(float frametime)
{
    int step = this->timer->getElapsedTime().asMilliseconds() * 0.03 ;
    this->explosionSprite->setTextureRect(sf::IntRect(step * 64, explosionType * 64, 64, 64));
    if(step > 15)
    {
        this->alive = false;
    }
}
void CExplosion::start()
{
    //srand(time(NULL));
    this->explosionType = rand()%8;
    this->explosionSprite->setTextureRect(sf::IntRect(0, explosionType * 64, 64, 64));
    this->timer->restart();
}
void CExplosion::setSprite(std::string texture, sf::IntRect textureRect)    //WIP!!!
{
    srand(time(NULL));
    int subWidth = textureRect.width / rand()%14 + 1;
    int subHeight = textureRect.height / rand()%14 + 1;
    bool finished = false;
    while(!finished)
    {

    }
}
