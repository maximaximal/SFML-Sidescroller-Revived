#ifndef IMAGE_H
#define IMAGE_H

#include <CMenu/CContainer.h>
#include <Manager/CTextureManager.h>

namespace CMenuNew
{
    class Image : public CContainer
    {
        public:
            Image(sf::Vector2f pos, std::string textureName, sf::IntRect textureRect);
            Image(sf::Vector2f pos, std::string textureName);
            virtual ~Image();
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void setPosition(sf::Vector2f pos);
            void move(float x, float y);
            void setScale(sf::Vector2f scale);
            sf::Vector2f getPosition();
            void reAlign();
        protected:
            sf::Sprite *sprite;
        private:
    };
}
#endif // IMAGE_H
