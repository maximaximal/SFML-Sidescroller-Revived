#include "Explosions/CExplosionManager.h"
#include <Explosions/CExplosion.h>

CExplosionManager::CExplosionManager()
{
    //ctor
}

CExplosionManager::~CExplosionManager()
{
    for(unsigned int i = 0; i < this->explosions.size(); i++)
    {
        delete this->explosions[i];
    }
}
void CExplosionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i = 0; i < this->explosions.size(); i++)
    {
        target.draw(*explosions[i]);
    }
}
void CExplosionManager::createExplosion(sf::Vector2f pos, float rotation, int size)
{
    CExplosion *explosion = new CExplosion(pos, rotation, size);
    this->explosions.push_back(explosion);
    explosion->start();
}
void CExplosionManager::update(float frametime)
{
    for(unsigned int i = 0; i < this->explosions.size(); i++)
    {
        if(!this->explosions[i]->getAlive())
        {
            delete this->explosions[i];
            explosions.erase(explosions.begin() + i);
        }
        else
        {
            this->explosions[i]->update(frametime);
        }
    }
}
