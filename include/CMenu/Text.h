#ifndef TEXT_H
#define TEXT_H

#include <CMenu/CContainer.h>
#include <SFML/Graphics.hpp>
#include <string>
namespace CMenuNew
{
    class Text : public CContainer
    {
        public:
            Text(sf::Vector2f pos, std::string text);
            virtual ~Text();
            void setString(std::string text);
            void setFont(std::string fontname);
            virtual void setPosition(sf::Vector2f);
            virtual void handleEvent(sf::Event *event);
            virtual void handleMouseMove(sf::Vector2i pos);
            sf::Vector2f getPosition();
            void move(float x, float left);
            void reAlign();
            void setSize(int size);
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            void setScrollable(bool scrollable);
            void setColor(sf::Color color);
            void setEditable(bool editable);
            void (*onFinished)();
            std::string getString() {return text->getString();}
        protected:
            sf::Text *text;
            sf::Vector2f *pos;
            sf::Color color;
            sf::RectangleShape *editbox;
            bool hover;
            bool scrollable;
            bool editable;
            bool hasBeenEdited;
        private:
    };
}
#endif // TEXT_H
