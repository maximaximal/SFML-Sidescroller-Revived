#ifndef SLIDER_H
#define SLIDER_H

#include <CMenu/CContainer.h>
#include <SFML/Graphics.hpp>
#include <string>


namespace CMenuNew
{
    class Slider : public CContainer
    {
        public:
            Slider(sf::Vector2f pos, int length);
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void setPosition(sf::Vector2f pos);
            virtual void handleEvent(sf::Event *event);
            virtual void handleMouseMove(sf::Vector2i pos);
            void reAlign();
            void setPercent(float percent);
            float getPercent();
            void (*onChange)(float percent);
            virtual ~Slider();
        protected:
            sf::RectangleShape *m_barBox;
            sf::Sprite *m_sliderBox;
            sf::RectangleShape *m_backgroundBox;
            sf::Vector2f m_pos;
            float m_percent;
            float m_width;
            float m_hover;
        private:
    };
}
#endif // SLIDER_H
