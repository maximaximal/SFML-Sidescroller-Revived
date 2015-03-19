#ifndef CMENU_H
#define CMENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class CMenu;

struct MenuButton
{
    bool hover;
    void (CMenu::*OnClick)(void);
    int ID;
    sf::Text label;
    sf::Sprite sprite;
};

class CMenu : public sf::Drawable
{
    public:
        CMenu();
        virtual ~CMenu();
        void update(float frametime);
        void loadMenu(int ID);
        void handleMouseover(sf::Vector2i MousePosition);
        void handleMouseclick();
        void handleKeyInput(sf::Keyboard::Key Key, bool Shift);
        void handleScroll(int direction);
        void resetMenu();
        //OnButtonClick Events
            void OnButtonClick_QuitGame();
            void OnButtonClick_Credits();
            void OnButtonClick_Back();
            void OnButtonClick_BackToGame();
            void OnButtonClick_NewGame();
            void OnButtonClick_StartUpdate();
            void OnButtonClick_OpenScoreList();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite *Background;
        std::vector<MenuButton> Buttons;
        std::vector<sf::Sprite> Sprites;
        std::vector<sf::Text> Labels;
        std::string nickname;
        bool submitted;
        float *rotation;
        int menuID;
        int lastMenuID;
        bool updateTextures;
        bool isBig;
        bool locked;
    private:
};

#endif // CMENU_H
