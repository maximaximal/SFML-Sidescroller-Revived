#include "CMenu/Image.h"
#include <Manager/CTextureManager.h>
using namespace std;
using namespace CMenuNew;

Image::Image(sf::Vector2f pos, std::string textureName, sf::IntRect textureRect)
{
    this->sprite = new sf::Sprite();
    sprite->setPosition(pos);
    sprite->setTexture(CTextureManager::Get()->getTexture(textureName));
    sprite->setTextureRect(textureRect);
}
Image::Image(sf::Vector2f pos, std::string textureName)
{
    this->sprite = new sf::Sprite();
    sprite->setPosition(pos);
    sprite->setTexture(CTextureManager::Get()->getTexture(textureName));
}
void Image::setPosition(sf::Vector2f pos)
{
    this->sprite->setPosition(pos);
}
void Image::move(float x, float y)
{
    this->sprite->move(x, y);
}
void Image::reAlign()
{
    this->sprite->setPosition((int) this->sprite->getPosition().x + 0.5, (int) this->sprite->getPosition().y + 0.5);
}
sf::Vector2f Image::getPosition()
{
    return this->sprite->getPosition();
}
void Image::setScale(sf::Vector2f scale)
{
    this->sprite->setScale(scale);
}
Image::~Image()
{
    delete this->sprite;
}
void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->sprite);
}
