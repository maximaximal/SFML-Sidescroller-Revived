#ifndef CCONTAINERMANAGER_H
#define CCONTAINERMANAGER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <CMenu/CContainer.h>
#include <CMenu/Button.h>
#include <CMenu/Text.h>
#include <CMenu/Image.h>
#include <CMenu/Slider.h>

namespace CMenuNew
{
    class Load;
    struct HistoryEntry
    {
        bool (Load::*load)(void);
        std::string name;
    };
    class CContainerManager : public sf::Drawable
    {
        public:
            CContainerManager(sf::RenderWindow *app);
            virtual ~CContainerManager();
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            Button* newButton(sf::Vector2i pos, std::string text);
            Text* newText(sf::Vector2f pos, std::string textString);
            Image* newImage(sf::Vector2f pos, std::string textureName, sf::IntRect textureRect);
            Image* newImage(sf::Vector2f pos, std::string textureName);
            Slider* newSlider(sf::Vector2f pos, int length);
            void destroyElement(int ID);
            bool IDExists(int ID);
            CContainer* getElement(int ID);
            void update(float frametime);
            void handleEvent(sf::Event *event);
            void clearMenu();
            void addToHistory(HistoryEntry *entry);
            void historyBack();
            void clearHistory();
            void activateBackgroundImage();
            Load *loader;
            void setBackgroundRotationSpeed(int multiplier);
            void setBackgroundColor(sf::Color color);
        protected:
        private:
            //Deco Background
                int backgroundSpeed;
                sf::Sprite *Background;
                float backgroundRotation;
            //renderWindow
                sf::RenderWindow *app;
            //Container
                std::vector<CContainer*> elements;
                std::vector<HistoryEntry*> history;
    };
}


#endif // CCONTAINERMANAGER_H
