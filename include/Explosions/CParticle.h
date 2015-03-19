#ifndef CPARTICLE_H
#define CPARTICLE_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Manager/CPhysicsManager.h>

class CParticle : public sf::Drawable
{
    public:
        CParticle(sf::Vector2f pos, std::string texture, sf::IntRect textureRect);
        virtual ~CParticle();
    protected:
        sf::Sprite *sprite;
        b2Body *body;
        PhysID *ID;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};

#endif // CPARTICLE_H
