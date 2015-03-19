#include "CMenu/Slider.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <CSoundEffect.h>
#include <Manager/CTextureManager.h>
using namespace std;
using namespace CMenuNew;

Slider::Slider(sf::Vector2f pos, int length)
{
    this->m_barBox = new sf::RectangleShape(sf::Vector2f(length, 20));
    this->m_sliderBox = new sf::Sprite(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(0, 582, 6, 18));
    this->m_backgroundBox = new sf::RectangleShape(sf::Vector2f(length + 4, 24));
    this->m_width = length;
    this->m_pos = pos;
    this->m_width = length;
    this->m_sliderBox->setPosition(sf::Vector2f(this->m_pos.x + this->m_width / 3, this->m_barBox->getPosition().y + 3));
    this->reAlign();
    this->m_backgroundBox->setFillColor(sf::Color(20, 20, 20, 120));
    this->m_barBox->setFillColor(sf::Color::Blue);
    this->m_sliderBox->setColor(sf::Color(80, 80, 80, 255));
    this->m_hover = false;
    this->onChange = NULL;
}
Slider::~Slider()
{
    delete this->m_barBox;
    delete this->m_sliderBox;
    delete this->m_backgroundBox;
}
void Slider::handleEvent(sf::Event *event)
{
    if(event->type == sf::Event::MouseButtonPressed)
    if(this->m_hover)
        CSoundEffect::Get()->playSound(SOUND_BUTTONPRESSED);
}
void Slider::handleMouseMove(sf::Vector2i pos)
{
    if(this->m_hover)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->m_sliderBox->setColor(sf::Color(250, 250, 250, 255));
            if(this->m_sliderBox->getPosition().x + (pos.x - this->m_sliderBox->getPosition().x - 2) < this->m_barBox->getPosition().x + this->m_width - 6
                && this->m_sliderBox->getPosition().x + (pos.x - this->m_sliderBox->getPosition().x - 2) > this->m_barBox->getPosition().x)
            {
                this->m_sliderBox->move(pos.x - this->m_sliderBox->getPosition().x - 2, 0);
                if(this->onChange != NULL)
                    (*this->onChange)(this->getPercent());
            }
        }
        else
            this->m_sliderBox->setColor(sf::Color(160, 160, 160, 255));
    }
    if(pos.x - 6 < (this->m_sliderBox->getPosition().x + this->m_sliderBox->getLocalBounds().width)
           && pos.x + 6 > this->m_sliderBox->getPosition().x
           && pos.y - 6 < (this->m_sliderBox->getPosition().y + this->m_sliderBox->getLocalBounds().height)
           && pos.y + 6 > this->m_sliderBox->getPosition().y)
    {
        this->m_hover = true;
    }
    else
    {
        this->m_sliderBox->setColor(sf::Color(80, 80, 80, 255));
        this->m_hover = false;
    }
}
void Slider::setPosition(sf::Vector2f pos)
{
    this->m_pos = pos;
}
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->m_backgroundBox);
    target.draw(*this->m_barBox);
    target.draw(*this->m_sliderBox);
}
void Slider::reAlign()
{
    this->m_backgroundBox->setPosition(this->m_pos);
    this->m_backgroundBox->setSize(sf::Vector2f(this->m_width, 24));
    this->m_barBox->setPosition(sf::Vector2f(this->m_pos.x + 2, this->m_pos.y + 10));
    this->m_barBox->setSize(sf::Vector2f(this->m_width - 4, 4));
    this->m_sliderBox->setPosition(sf::Vector2f(this->m_sliderBox->getPosition().x, this->m_pos.y + 3));
}
float Slider::getPercent()
{
    float relativeX = this->m_sliderBox->getPosition().x - this->m_barBox->getPosition().x;
    return relativeX / ((this->m_width - 4) / 100.0f);
}
void Slider::setPercent(float percent)
{
    float posX = this->m_pos.x + 2 + (m_width - 4.f) * (percent / 100.00f);
    this->m_sliderBox->setPosition(posX, this->m_sliderBox->getPosition().y);
}
