#ifndef CASTEROIDCONTAINER_H
#define CASTEROIDCONTAINER_H

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

struct PhysID;

struct SAsteroid
{
    int type;
    float damage;
    int maxDamage;
    b2Body *body;
    sf::Sprite *sprite;
    sf::Sprite *damageSprite;
    PhysID *ID;
    bool alive;
};
struct ScoreText
{
    sf::Text *text;
    int life;
};
class CAsteroidContainer : public sf::Drawable
{
    public:
        CAsteroidContainer();
        virtual ~CAsteroidContainer();
        void update(float frametime);
        void toggleAsteroids();
        void spawnAsteroid(int i);
        void deleteAsteroid(int ID);
        int getAsteroidCount() {return Asteroids.size();}
        void resetAsteroids();
        void hitAsteroid(int ID);
        void hitByBullet(int ID, int BulletType);
        int getMaxAsteroids() {return maxAsteroids;}
        void spawnScoreText(int score, sf::Vector2f pos);
        bool isAlive(int ID);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Clock *SpawnTimer;
        float spawnLimiter;
        int spawnLimiterSize;
        unsigned int maxAsteroids;
        int IDIterator;
        bool spawn;
        b2Vec2 generateShootVector();
        std::vector<SAsteroid> Asteroids;
};

#endif // CASTEROIDCONTAINER_H
