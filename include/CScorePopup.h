#ifndef CSCOREPOPUP_H
#define CSCOREPOPUP_H
#include <CSingleton.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class CScorePopup : public TSingleton<CScorePopup>, public sf::Drawable
{
    public:
        CScorePopup();
        virtual ~CScorePopup();
        void popup(int score, sf::Vector2f pos);
        sf::IntRect calculateRect(int score);
        void update(float frametime);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        struct ScorePopup
        {
            float life;
            sf::Sprite *sprite;
        };
        std::vector<ScorePopup> popups;
        int guiSheetSlot;

};

#endif // CSCOREPOPUP_H
