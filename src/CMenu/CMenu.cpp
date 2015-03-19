#include "CMenu.h"
#include <CConfig.h>
#include <Manager/CTextureManager.h>
#include <Manager/CFontManager.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <boost/foreach.hpp>
#include <sstream>
#define foreach BOOST_FOREACH
#include <Manager/CWebManager.h>
CMenu::CMenu()
{
    using namespace std;
    this->Background = new sf::Sprite;
    Background->setOrigin(1000, 1000);
    Background->setScale(CConfig::Get()->getWindowX() / 1100.f, CConfig::Get()->getWindowX() / 1100.f);
    Background->setPosition(CConfig::Get()->getWindowX() / 2, CConfig::Get()->getWindowY() / 2);
    this->rotation = new float;
    CTextureManager::Get()->createTexture("Data/Textures/HowTo.png", "HowTo");
    if(CTextureManager::Get()->createTexture("Data/Textures/MenuBackground2.png", "MenuBackground") == -1)
    {
        cout << "!! This Computer can't handle a 2000x2000px PNG." << endl;
        cout << "   Loading 1000x1000 alternative..." << endl;
        CTextureManager::Get()->deleteTexture("MenuBackground");
        CTextureManager::Get()->createTexture("Data/Textures/MenuBackground2_lowRes.png", "MenuBackground");
        Background->setOrigin(500, 500);
        Background->setScale(CConfig::Get()->getWindowX() / 600.f, CConfig::Get()->getWindowX() / 600.f);
    }
    CTextureManager::Get()->createTexture("Data/Textures/Gui.png", "GuiSheet");
    this->lastMenuID = 0;
    this->locked = false;
}
void CMenu::resetMenu()
{
    this->lastMenuID = menuID;
    this->Buttons.clear();
    this->Sprites.clear();
    this->Labels.clear();
    locked = false;
}
void CMenu::handleMouseclick()
{
    unsigned int i;
    for (i = 0;i < Buttons.size();i++)
    {
        if(Buttons[i].hover)
        {
            if(this->locked == false)
            {
                Buttons[i].sprite.setTextureRect(sf::IntRect(0, 50, 150, 25));
                if(Buttons[i].OnClick)
                    (this->*Buttons[i].OnClick)();
                else
                    std::cout << "!! This Button doesn't have an effect!" << std::endl;
            }
            else
                std::cout << "The GUI is locked!" << std::endl;
        }
    }
}
void CMenu::handleMouseover(sf::Vector2i MousePosition)
{
    unsigned int i;
            using namespace std;
    for(i = 0;i < Buttons.size();i++)
    {
        if(MousePosition.x < (Buttons[i].sprite.getPosition().x + Buttons[i].sprite.getLocalBounds().width)
           && MousePosition.x > Buttons[i].sprite.getPosition().x
           && MousePosition.y < (Buttons[i].sprite.getPosition().y + Buttons[i].sprite.getLocalBounds().height)
           && MousePosition.y > Buttons[i].sprite.getPosition().y)
        {
            Buttons[i].hover = true;
        }
        else
            Buttons[i].hover = false;
    }
}
void CMenu::update(float frametime)
{
    if(menuID != 2)
    {
        *rotation = this->Background->getRotation();
        if(*rotation >= 360) (*rotation = 0);
        if(frametime < 0.05)
            Background->setRotation(*rotation + (7 * frametime));
    }
    if(menuID == 2)
    {
        *rotation = this->Background->getRotation();
        if(*rotation >= 360) (*rotation = 0);
        if(frametime < 0.05)
            Background->setRotation(*rotation + (50 * frametime));
        Labels[1].setString(CWebManager::Get()->getScores());
        std::stringstream stream;
        if(CWebManager::Get()->isConfigValid())
        {
            stream << "Enter your Name & press Enter! ";
            stream << nickname;
        }
        else
            stream << "You do not have a valid config! Please reset your changes," << std::endl << "or download the newest version!";
        Labels[2].setString(stream.str());
    }
    if(menuID == 5)
    {
        Labels[0].setString(CWebManager::Get()->getScores());
    }
    if(menuID == 3)
    {
        this->Labels[0].move(0, frametime * -25);
    }
    unsigned int i;
    if(updateTextures)
    {
        Background->setTexture(CTextureManager::Get()->getTexture("MenuBackground"));
        for(i = 0;i < Buttons.size();i++)
        {
            Buttons[i].sprite.setTexture(CTextureManager::Get()->getTexture("GuiSheet"));
            Buttons[i].sprite.setTextureRect(sf::IntRect(0, 0, 150, 25));
            Buttons[i].label.setFont(CFontManager::Get()->getFont("Beeb Mode One"));
            Buttons[i].label.setCharacterSize(12);
            Buttons[i].label.setOrigin((int) Buttons[i].label.getLocalBounds().width / 2 + 0.5, (int) Buttons[i].label.getLocalBounds().height / 2 + 0.5);
            Buttons[i].label.setPosition((int) Buttons[i].sprite.getLocalBounds().width / 2 + Buttons[i].sprite.getPosition().x + 0.5, (int) Buttons[i].sprite.getLocalBounds().height / 2 + Buttons[i].sprite.getPosition().y + 0.5);
        }
        updateTextures = false;
    }
    for(i = 0;i < Buttons.size();i++)
    {
        if(Buttons[i].hover)
            Buttons[i].sprite.setTextureRect(sf::IntRect(0, 25, 150, 25));
        else
            Buttons[i].sprite.setTextureRect(sf::IntRect(0, 0, 150, 25));
    }
    if(menuID == 0)
    {
        if(Sprites[0].getScale().x > 0.5 && isBig)
        {
            this->Sprites[0].setScale(Sprites[0].getScale().x - 0.001, Sprites[0].getScale().y - 0.001);
            this->Sprites[0].setOrigin(Sprites[0].getLocalBounds().width / 2, Sprites[0].getLocalBounds().height / 2);
        }
        if(Sprites[0].getScale().x < 0.5)
            isBig = false;
        if(Sprites[0].getScale().x > 1)
            isBig = true;
        if(!isBig)
        {
            this->Sprites[0].setScale(Sprites[0].getScale().x + 0.001, Sprites[0].getScale().y + 0.001);
            this->Sprites[0].setOrigin(Sprites[0].getLocalBounds().width / 2, Sprites[0].getLocalBounds().height / 2);
        }
        for(i = 0; i < Buttons.size(); i++)
        {
            if(Buttons[i].ID == 4)
            {
                Buttons[i].label.setString(CWebManager::Get()->getVersionStatus());
                Buttons[i].label.setOrigin((int) Buttons[i].label.getLocalBounds().width / 2 + 0.5, (int) Buttons[i].label.getLocalBounds().height / 2 + 0.5);
                Buttons[i].label.setPosition((int) Buttons[i].sprite.getLocalBounds().width / 2 + Buttons[i].sprite.getPosition().x + 0.5, (int) Buttons[i].sprite.getLocalBounds().height / 2 + Buttons[i].sprite.getPosition().y + 0.5);
                if(CWebManager::Get()->getVersionStatus() == "Finished!")
                    this->locked = false;
                else if(CWebManager::Get()->getVersionStatus() == "CANNOT DOWNLOAD")
                    this->locked = false;
            }

        }
    }
}
CMenu::~CMenu()
{
    delete this->Background;
    delete this->rotation;
    resetMenu();
}
void CMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*Background, states);
    //Draw the Buttons
    unsigned int i = 0;
    for(i = 0;i < this->Sprites.size();i++)
    {
        target.draw(Sprites[i], states);
    }
    for(i = 0;i < this->Labels.size();i++)
    {
        target.draw(Labels[i], states);
    }
    for(i = 0;i < this->Buttons.size();i++)
    {
        target.draw(Buttons[i].sprite, states);
        target.draw(Buttons[i].label, states);
    }
}
void CMenu::handleKeyInput(sf::Keyboard::Key Key, bool Shift)
{
    if(Shift)
    {
        if(Key == sf::Keyboard::A)
            this->nickname.append("A");
        if(Key == sf::Keyboard::B)
            this->nickname.append("B");
        if(Key == sf::Keyboard::C)
            this->nickname.append("C");
        if(Key == sf::Keyboard::D)
            this->nickname.append("D");
        if(Key == sf::Keyboard::E)
            this->nickname.append("E");
        if(Key == sf::Keyboard::F)
            this->nickname.append("F");
        if(Key == sf::Keyboard::G)
            this->nickname.append("G");
        if(Key == sf::Keyboard::H)
            this->nickname.append("H");
        if(Key == sf::Keyboard::I)
            this->nickname.append("I");
        if(Key == sf::Keyboard::J)
            this->nickname.append("J");
        if(Key == sf::Keyboard::K)
            this->nickname.append("K");
        if(Key == sf::Keyboard::L)
            this->nickname.append("L");
        if(Key == sf::Keyboard::M)
            this->nickname.append("M");
        if(Key == sf::Keyboard::N)
            this->nickname.append("N");
        if(Key == sf::Keyboard::O)
            this->nickname.append("O");
        if(Key == sf::Keyboard::P)
            this->nickname.append("P");
        if(Key == sf::Keyboard::Q)
            this->nickname.append("Q");
        if(Key == sf::Keyboard::R)
            this->nickname.append("R");
        if(Key == sf::Keyboard::S)
            this->nickname.append("S");
        if(Key == sf::Keyboard::T)
            this->nickname.append("T");
        if(Key == sf::Keyboard::U)
            this->nickname.append("U");
        if(Key == sf::Keyboard::V)
            this->nickname.append("V");
        if(Key == sf::Keyboard::W)
            this->nickname.append("W");
        if(Key == sf::Keyboard::X)
            this->nickname.append("X");
        if(Key == sf::Keyboard::Y)
            this->nickname.append("Y");
        if(Key == sf::Keyboard::Z)
            this->nickname.append("Z");
        if(Key == sf::Keyboard::Num0)
            this->nickname.append("0");
        if(Key == sf::Keyboard::Num1)
            this->nickname.append("!");
        if(Key == sf::Keyboard::Num2)
            this->nickname.append("2");
        if(Key == sf::Keyboard::Num3)
            this->nickname.append("§");
        if(Key == sf::Keyboard::Num4)
            this->nickname.append("$");
        if(Key == sf::Keyboard::Num5)
            this->nickname.append("%");
        if(Key == sf::Keyboard::Num6)
            this->nickname.append("6");
        if(Key == sf::Keyboard::Num7)
            this->nickname.append("7");
        if(Key == sf::Keyboard::Num8)
            this->nickname.append("(");
        if(Key == sf::Keyboard::Num9)
            this->nickname.append(")");
    }
    if(!Shift)
    {
        if(Key == sf::Keyboard::A)
            this->nickname.append("a");
        if(Key == sf::Keyboard::B)
            this->nickname.append("b");
        if(Key == sf::Keyboard::C)
            this->nickname.append("c");
        if(Key == sf::Keyboard::D)
            this->nickname.append("d");
        if(Key == sf::Keyboard::E)
            this->nickname.append("e");
        if(Key == sf::Keyboard::F)
            this->nickname.append("f");
        if(Key == sf::Keyboard::G)
            this->nickname.append("g");
        if(Key == sf::Keyboard::H)
            this->nickname.append("h");
        if(Key == sf::Keyboard::I)
            this->nickname.append("i");
        if(Key == sf::Keyboard::J)
            this->nickname.append("j");
        if(Key == sf::Keyboard::K)
            this->nickname.append("k");
        if(Key == sf::Keyboard::L)
            this->nickname.append("l");
        if(Key == sf::Keyboard::M)
            this->nickname.append("m");
        if(Key == sf::Keyboard::N)
            this->nickname.append("n");
        if(Key == sf::Keyboard::O)
            this->nickname.append("o");
        if(Key == sf::Keyboard::P)
            this->nickname.append("p");
        if(Key == sf::Keyboard::Q)
            this->nickname.append("q");
        if(Key == sf::Keyboard::R)
            this->nickname.append("r");
        if(Key == sf::Keyboard::S)
            this->nickname.append("s");
        if(Key == sf::Keyboard::T)
            this->nickname.append("t");
        if(Key == sf::Keyboard::U)
            this->nickname.append("u");
        if(Key == sf::Keyboard::V)
            this->nickname.append("v");
        if(Key == sf::Keyboard::W)
            this->nickname.append("w");
        if(Key == sf::Keyboard::X)
            this->nickname.append("x");
        if(Key == sf::Keyboard::Y)
            this->nickname.append("y");
        if(Key == sf::Keyboard::Z)
            this->nickname.append("z");
        if(Key == sf::Keyboard::Num0)
            this->nickname.append("0");
        if(Key == sf::Keyboard::Num1)
            this->nickname.append("1");
        if(Key == sf::Keyboard::Num2)
            this->nickname.append("2");
        if(Key == sf::Keyboard::Num3)
            this->nickname.append("3");
        if(Key == sf::Keyboard::Num4)
            this->nickname.append("4");
        if(Key == sf::Keyboard::Num5)
            this->nickname.append("5");
        if(Key == sf::Keyboard::Num6)
            this->nickname.append("6");
        if(Key == sf::Keyboard::Num7)
            this->nickname.append("7");
        if(Key == sf::Keyboard::Num8)
            this->nickname.append("8");
        if(Key == sf::Keyboard::Num9)
            this->nickname.append("9");
    }
    if(Key == sf::Keyboard::BackSlash || Key == sf::Keyboard::BackSpace)
    {
        if(nickname != "")
            this->nickname.erase(nickname.size() - 1, nickname.size());
    }
    if(Key == sf::Keyboard::Space)
    {
        this->nickname.append(" ");
    }
    if(CConfig::Get()->getGameState() == STATE_GAMEOVER)
    {
        if(Key == sf::Keyboard::Return && CWebManager::Get()->isConfigValid() && !submitted)
        {
            CConfig::Get()->setNickname(nickname);
            sf::Thread submitScoreThread(&CWebManager::web_submitScore, CWebManager::Get());
            submitScoreThread.launch();
            submitted = true;
        }
    }
}
void CMenu::handleScroll(int direction)
{
    if(CConfig::Get()->getGameState() == STATE_GAMEOVER)
    {
        if(direction == 1)
        {
            Labels[1].move(0, -15);
        }
        if(direction == 0)
        {
            Labels[1].move(0, 15);
        }
        if(direction == 5)
        {
            Labels[1].setPosition(50, 350);
        }
    }
    if(this->menuID == 5)
    {
        if(direction == 1)
        {
            Labels[0].move(0, -15);
        }
        if(direction == 0)
        {
            Labels[0].move(0, 15);
        }
        if(direction == 5)
        {
            Labels[0].setPosition(50, 350);
        }
    }
}
