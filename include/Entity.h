#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
class Entity : public sf::Drawable
{
    public:
        Entity();
        float speed;
        void setPosition(int X, int Y);
        void setPosition(sf::Vector2<int> Position);
        void move(int Direction);
        virtual ~Entity();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool Visible;
        sf::Sprite EntitySprite;
        sf::Vector2f Position;
};

#endif // ENTITY_H
