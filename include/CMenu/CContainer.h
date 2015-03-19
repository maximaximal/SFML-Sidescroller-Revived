#ifndef CCONTAINER_H
#define CCONTAINER_H

#include <SFML/Graphics.hpp>

namespace CMenuNew
{
    class CContainerManager;
    enum type {
        button,
        slider,
        label,
        image
    };

    class CContainer : public sf::Drawable, public sf::NonCopyable
    {
        public:
            CContainer();
            virtual ~CContainer();
            CContainerManager *containerManager;
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            virtual void update(float frametime);
            virtual void handleEvent(sf::Event *event);
            virtual void handleMouseMove(sf::Vector2i pos);
            virtual void setPosition(sf::Vector2f pos);
            int getType() {return type;}
            int getID() {return ID;}
            void (*onClick)(void);
            void (*onHover)(void);
            void (*onHoverLeave)(void);
            void (*onUpdate)(float frametime);
        protected:
            int type;
            int ID;
    };
}


#endif // CCONTAINER_H
