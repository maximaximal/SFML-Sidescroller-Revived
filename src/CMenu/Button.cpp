#include "CMenu/Button.h"
#include <Manager/CTextureManager.h>
#include <Manager/CFontManager.h>
#include <CSoundEffect.h>
#include <iostream>
#include <CConfig.h>

using namespace CMenuNew;
using namespace std;

Button::Button(sf::Vector2i pos, std::string text)
{
    this->type = CMenuNew::type::button;
    CTextureManager::Get()->createTexture(CConfig::Get()->getDataDir() + "/Data/Textures/Gui.png", "GuiSheet");
    this->sprite = new sf::Sprite(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(0, 0, 150, 25));
    this->sprite->setPosition(pos.x, pos.y);
    this->text = new sf::Text(text, CFontManager::Get()->getFont("Beeb Mode One"), 12);
    this->reAlign();
    this->onClick = NULL;
    this->hover = false;
    this->upButton = NULL;
    this->downButton = NULL;
    this->leftButton = NULL;
    this->rightButton = NULL;
}

Button::~Button()
{
    delete this->sprite;
    delete this->text;
}
void Button::handleEvent(sf::Event *event)
{
    if(this->hover)
    {
        if(event->type == sf::Event::MouseButtonPressed)
        {
            click();
        }

        if(event->type == sf::Event::KeyPressed)
        {
            if(event->key.code == sf::Keyboard::W && upButton != NULL)
            {
                this->markHover(false);
                upButton->markHover(true);
                //Ignore the key press in the further event processing (ugly hack - TODO)
                event->key.code = sf::Keyboard::I;
            }
            if(event->key.code == sf::Keyboard::S && downButton != NULL)
            {
                this->markHover(false);
                downButton->markHover(true);
                //Ignore the key press in the further event processing (ugly hack - TODO)
                event->key.code = sf::Keyboard::I;
            }
            if(event->key.code == sf::Keyboard::A && leftButton != NULL)
            {
                this->markHover(false);
                leftButton->markHover(true);
                //Ignore the key press in the further event processing (ugly hack - TODO)
                event->key.code = sf::Keyboard::I;
            }
            if(event->key.code == sf::Keyboard::S && rightButton != NULL)
            {
                this->markHover(false);
                rightButton->markHover(true);
                //Ignore the key press in the further event processing (ugly hack - TODO)
                event->key.code = sf::Keyboard::I;
            }
            if(event->key.code == sf::Keyboard::Space)
            {
                click();
            }
        }
    }
}
void Button::handleMouseMove(sf::Vector2i pos)
{
    if(pos.x < (this->sprite->getPosition().x + this->sprite->getLocalBounds().width)
           && pos.x > this->sprite->getPosition().x
           && pos.y < (this->sprite->getPosition().y + this->sprite->getLocalBounds().height)
           && pos.y > this->sprite->getPosition().y)
    {
        markHover(true);
    }
    else
    {
        markHover(false);
    }
}
void Button::setText(std::string text)
{
    this->text->setString(text);
    this->reAlign();
}
void Button::setPosition(sf::Vector2f pos)
{
    this->sprite->setPosition(pos.x, pos.y);
    this->reAlign();
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->sprite);
    target.draw(*this->text);
}
void Button::move(float x, float y)
{
    this->sprite->move(x, y);
    this->reAlign();
}
sf::Vector2f Button::getPosition()
{
    return this->sprite->getPosition();
}
void Button::reAlign()
{
    this->text->setOrigin((int) this->text->getLocalBounds().width / 2 + 0.5, (int) this->text->getLocalBounds().height / 2 + 0.5);
    this->text->setPosition((int) this->sprite->getLocalBounds().width / 2 + this->sprite->getPosition().x + 0.5, (int) this->sprite->getLocalBounds().height / 2 + this->sprite->getPosition().y + 0.5);
}
void Button::click()
{
    CSoundEffect::Get()->playSound(SOUND_BUTTONPRESSED);
    if(this->onClick != NULL)
        (*this->onClick)();
    else
        cout << "!! Theres no function connected to this button!" << endl;
}
void Button::markHover(bool hover)
{
    if(hover)
    {
        this->sprite->setTextureRect(sf::IntRect(0, 25, 150, 25));
    }
    else
    {
        this->sprite->setTextureRect(sf::IntRect(0, 0, 150, 25));
    }
    this->hover = hover;
}
