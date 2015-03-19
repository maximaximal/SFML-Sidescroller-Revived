#ifndef CEXPLOSION_H
#define CEXPLOSION_H

#include <SFML/Graphics.hpp>
#include <Explosions/CParticle.h>
class CExplosion : public sf::Drawable
{
    public:
        CExplosion(sf::Vector2f pos, float rotation, int size);
        virtual ~CExplosion();
        void update(float frametime);
        void start();
        void setSprite(std::string texture, sf::IntRect textureRect);
        bool getAlive() {return alive;}
    protected:
        int explosionType;
        sf::Clock *timer;
        sf::Sprite *explosionSprite;
        sf::Vector2f pos;
        float rotation;
        bool alive;
        std::vector<CParticle*> particles;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};

#endif // CEXPLOSION_H
