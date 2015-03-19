#ifndef BUTTON_H
#define BUTTON_H

#include <CMenu/CContainer.h>
#include <string>

namespace CMenuNew
{
    class Button : public CMenuNew::CContainer
    {
        public:
            Button(sf::Vector2i pos, std::string text);
            virtual ~Button();
            virtual void handleEvent(sf::Event *event);
            virtual void handleMouseMove(sf::Vector2i pos);
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            void setText(std::string text);
            virtual void setPosition(sf::Vector2f pos);
            void move(float x, float y);
            sf::Vector2f getPosition();
            void (*onClick)(void);
            bool getState() {return hover;}
            void reAlign();
        protected:
            bool hover;
            sf::Sprite *sprite;
            sf::Text *text;
        private:
    };
}
#endif // BUTTON_H
