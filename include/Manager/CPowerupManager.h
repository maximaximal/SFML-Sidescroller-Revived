#ifndef CPOWERUPMANAGER_H
#define CPOWERUPMANAGER_H

#include <SFML/Graphics.hpp>
#include <CSingleton.h>
#include <vector>
#include <Manager/CPhysicsManager.h>
#include <Box2D/Box2D.h>
#include <Player/CPLayer.h>
//Define the Powerup Types
    #define POWERUP_REPAIR 0
    #define POWERUP_LASER_RED 1
    #define POWERUP_LASER_BLUE 2
    #define POWERUP_LASER_GREEN 3
    #define POWERUP_LASER_MAGENTA 4
    #define POWERUP_MULTIPLIKATOR 5
    #define POWERUP_BONUS 6


class CPowerupManager : public TSingleton<CPowerupManager>, public sf::Drawable
{
    public:
        CPowerupManager();
        virtual ~CPowerupManager();
        void spawnRandom(sf::Vector2f pos);
        void spawn(int type, sf::Vector2f pos);
        void update(float frametime);
        void spawnRandomBuffer(sf::Vector2f pos);
        void apply(int ID);
        void reset();
        int getWeapon();
        int getWeaponLevel();
        CPlayer *Player;
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        struct powerup
        {
            sf::Sprite *sprite;
            b2Body *body;
            PhysID *ID;
            float life;
            short type;
        };
        std::vector<powerup> powerups;
        std::vector<sf::Vector2f> buffer;
        unsigned IDIterator;
        int weapon;
        int weaponLevel;
};

#endif // CPOWERUPMANAGER_H
