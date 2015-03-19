#ifndef CBULLETCONTAINER_H
#define CBULLETCONTAINER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <Box2D/Box2D.h>

struct SBullet
{
    int type;
    int origin;
    int age;
    int hitCount;
    unsigned int ID;
    b2Body *body;
    bool dead;
    sf::Sprite *sprite;
};

class CBulletContainer : public sf::Drawable
{
    public:
        CBulletContainer();
        virtual ~CBulletContainer();
        void createBullet(sf::Vector2f pos, sf::Vector2f force, int type, int origin);
        int getBulletCount() {return Bullets.size();}
        void destroyBullet(unsigned int ID);
        void update();
        void reset();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        unsigned int IDIterator;
        std::vector<SBullet> Bullets;
        b2BodyDef *BulletBodyDef1;
        b2PolygonShape *BulletShape1;
        b2PolygonShape *BulletShape2;
        b2PolygonShape *BulletShape3;
        b2PolygonShape *BulletShape4;
};

#endif // CBULLETCONTAINER_H
