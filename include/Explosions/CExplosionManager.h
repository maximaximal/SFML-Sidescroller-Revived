#ifndef CEXPLOSIONMANAGER_H
#define CEXPLOSIONMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CSingleton.h>
#include <Explosions/CExplosion.h>
class CExplosionManager : public TSingleton<CExplosionManager>, public sf::Drawable
{
    public:
        CExplosionManager();
        virtual ~CExplosionManager();
        void createExplosion(sf::Vector2f pos, float rotation, int size);
        void update(float frametime);
    protected:
        std::vector<CExplosion*> explosions;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};

#endif // CEXPLOSIONMANAGER_H
