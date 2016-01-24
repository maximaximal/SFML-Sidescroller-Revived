#include "CScorePopup.h"
#include <Manager/CTextureManager.h>
#include <math.h>
#include <CConfig.h>

CScorePopup::CScorePopup()
{
    this->guiSheetSlot = CTextureManager::Get()->createTexture(CConfig::Get()->getDataDir() + "/Data/Textures/Gui.png", "GuiSheet");
}

CScorePopup::~CScorePopup()
{
    for(unsigned int i = 0; i < popups.size();i++)
    {
        delete popups[i].sprite;
    }
}
void CScorePopup::popup(int score, sf::Vector2f pos)
{
    ScorePopup Popup;
    Popup.sprite = new sf::Sprite(CTextureManager::Get()->getTexture(guiSheetSlot), this->calculateRect(score));
    Popup.life = 255;
    Popup.sprite->setPosition(pos);
    Popup.sprite->setScale(0.5, 0.5);
    Popup.sprite->setOrigin(Popup.sprite->getLocalBounds().width / 2, Popup.sprite->getLocalBounds().height / 2);
    popups.push_back(Popup);
}
void CScorePopup::update(float frametime)
{
    for(unsigned int i = 0; i < popups.size();i++)
    {
        popups[i].sprite->setScale(popups[i].sprite->getScale().x + 0.08, popups[i].sprite->getScale().y + 0.08);
        popups[i].sprite->setColor(sf::Color(255, 255, 255, popups[i].life));
        popups[i].life = popups[i].life - frametime / 1.5;
        if(popups[i].life <= 0)
        {
            delete popups[i].sprite;
            popups.erase(popups.begin() + i);
        }
    }
}
sf::IntRect CScorePopup::calculateRect(int score)
{
    //Calculates the Position of the Score Sprite in the GuiSheet (new Line every 10 sprites!)
    sf::IntRect Rect;
    Rect.height = 23;
    Rect.width = 32;
    Rect.top = 75 + (32 * (int) ((score - 1) / 10));
    if(score % 10 != 0)
        Rect.left = 150 + (32 * (score%10 - 1));
    else
        Rect.left = 150 + (32 * 9);
    return Rect;
}
void CScorePopup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i = 0; i < popups.size(); i++)
    {
        target.draw(*popups[i].sprite);
    }
}
