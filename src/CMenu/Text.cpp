#include <CMenu/Text.h>
#include <Manager/CFontManager.h>
#include <sstream>
#include <stdlib.h>
using namespace CMenuNew;

Text::Text(sf::Vector2f pos, std::string text)
{
    this->text = new sf::Text();
    this->pos = new sf::Vector2f();
    this->editbox = NULL;
    *this->pos = pos;
    this->scrollable = false;
    this->editable = false;
    this->color = sf::Color::White;
    this->text->setString(text);
    this->text->setFont(CFontManager::Get()->getFont(0));
    this->hasBeenEdited = false;
    this->hover = false;
    this->reAlign();
    this->onFinished = NULL;
}

Text::~Text()
{
    delete this->text;
    delete this->pos;
    if(this->editbox != NULL)
        delete this->editbox;
}
void Text::reAlign()
{
    this->text->setPosition(sf::Vector2f((int) this->pos->x, (int) this->pos->y));
    this->text->setColor(this->color);
    if(this->editbox != NULL)
    {
        this->editbox->setSize(sf::Vector2f(this->text->getLocalBounds().width + 5, this->text->getLocalBounds().height +  10));
        this->editbox->setPosition(this->text->getPosition());
    }
}
void Text::setFont(std::string fontname)
{
    this->text->setFont(CFontManager::Get()->getFont(fontname));
    this->reAlign();
}
void Text::setPosition(sf::Vector2f pos)
{
    this->pos->x = pos.x;
    this->pos->y = pos.y;
    this->reAlign();
}
sf::Vector2f Text::getPosition()
{
    return this->text->getPosition();
}
void Text::move(float x, float y)
{
    *this->pos = sf::Vector2f(this->pos->x + (x), this->pos->y + (y));
    this->reAlign();
}
void Text::setString(std::string text)
{
    this->text->setString(text);
    this->reAlign();
}
void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->editbox != NULL)
        target.draw(*this->editbox);
    target.draw(*this->text);
}
void Text::setSize(int size)
{
    this->text->setCharacterSize(size);
    this->reAlign();
}
void Text::handleEvent(sf::Event *event)
{
    if(this->hover && event->type == sf::Event::MouseWheelMoved && this->scrollable)
    {
        int scroll = this->text->getCharacterSize();
        this->move(0, scroll * 2 * event->mouseWheel.delta);
    }
    if(this->hover && sf::Event::MouseLeft && this->editable)
    {
        this->text->setColor(sf::Color::Red);
        if(!this->hasBeenEdited)
            this->text->setString("");
        this->hasBeenEdited = true;
        if(this->editbox != NULL)
        {
            this->editbox->setOutlineColor(sf::Color::Red);
            this->editbox->setFillColor(sf::Color(100, 100, 100, 60));
        }
    }
    if(!this->hover && sf::Event::MouseLeft && this->editable)
    {
        this->text->setColor(color);
        if(this->editbox != NULL)
        {
            this->editbox->setOutlineColor(sf::Color::Yellow);
            this->editbox->setFillColor(sf::Color(100, 100, 100, 60));
        }
    }
    if(this->editable && this->hasBeenEdited && event->type == sf::Event::KeyPressed)
    {
        std::stringstream name;
        name << this->text->getString().toAnsiString();
        bool Shift = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
            Shift = true;
        sf::Keyboard::Key Key = event->key.code;
        if(Shift)
        {
            if(Key == sf::Keyboard::A)
                name << "A";
            if(Key == sf::Keyboard::B)
                name << "B";
            if(Key == sf::Keyboard::C)
                name << "C";
            if(Key == sf::Keyboard::D)
                name << "D";
            if(Key == sf::Keyboard::E)
                name << "E";
            if(Key == sf::Keyboard::F)
                name << "F";
            if(Key == sf::Keyboard::G)
                name << "G";
            if(Key == sf::Keyboard::H)
                name << "H";
            if(Key == sf::Keyboard::I)
                name << "I";
            if(Key == sf::Keyboard::J)
                name << "J";
            if(Key == sf::Keyboard::K)
                name << "K";
            if(Key == sf::Keyboard::L)
                name << "L";
            if(Key == sf::Keyboard::M)
                name << "M";
            if(Key == sf::Keyboard::N)
                name << "N";
            if(Key == sf::Keyboard::O)
                name << "O";
            if(Key == sf::Keyboard::P)
                name << "P";
            if(Key == sf::Keyboard::Q)
                name << "Q";
            if(Key == sf::Keyboard::R)
                name << "R";
            if(Key == sf::Keyboard::S)
                name << "S";
            if(Key == sf::Keyboard::T)
                name << "T";
            if(Key == sf::Keyboard::U)
                name << "U";
            if(Key == sf::Keyboard::V)
                name << "V";
            if(Key == sf::Keyboard::W)
                name << "W";
            if(Key == sf::Keyboard::X)
                name << "X";
            if(Key == sf::Keyboard::Y)
                name << "Y";
            if(Key == sf::Keyboard::Z)
                name << "Z";
            if(Key == sf::Keyboard::Num0)
                name << "0";
            if(Key == sf::Keyboard::Num1)
                name << "!";
            if(Key == sf::Keyboard::Num2)
                name << "2";
            if(Key == sf::Keyboard::Num3)
                name << "�";
            if(Key == sf::Keyboard::Num4)
                name << "$";
            if(Key == sf::Keyboard::Num5)
                name << "%";
            if(Key == sf::Keyboard::Num6)
                name << "6";
            if(Key == sf::Keyboard::Num7)
                name << "7";
            if(Key == sf::Keyboard::Num8)
                name << "(";
            if(Key == sf::Keyboard::Num9)
                name << ")";
        }
        if(!Shift)
        {
            if(Key == sf::Keyboard::A)
                name << "a";
            if(Key == sf::Keyboard::B)
                name << "b";
            if(Key == sf::Keyboard::C)
                name << "c";
            if(Key == sf::Keyboard::D)
                name << "d";
            if(Key == sf::Keyboard::E)
                name << "e";
            if(Key == sf::Keyboard::F)
                name << "f";
            if(Key == sf::Keyboard::G)
                name << "g";
            if(Key == sf::Keyboard::H)
                name << "h";
            if(Key == sf::Keyboard::I)
                name << "i";
            if(Key == sf::Keyboard::J)
                name << "j";
            if(Key == sf::Keyboard::K)
                name << "k";
            if(Key == sf::Keyboard::L)
                name << "l";
            if(Key == sf::Keyboard::M)
                name << "m";
            if(Key == sf::Keyboard::N)
                name << "n";
            if(Key == sf::Keyboard::O)
                name << "o";
            if(Key == sf::Keyboard::P)
                name << "p";
            if(Key == sf::Keyboard::Q)
                name << "q";
            if(Key == sf::Keyboard::R)
                name << "r";
            if(Key == sf::Keyboard::S)
                name << "s";
            if(Key == sf::Keyboard::T)
                name << "t";
            if(Key == sf::Keyboard::U)
                name << "u";
            if(Key == sf::Keyboard::V)
                name << "v";
            if(Key == sf::Keyboard::W)
                name << "w";
            if(Key == sf::Keyboard::X)
                name << "x";
            if(Key == sf::Keyboard::Y)
                name << "y";
            if(Key == sf::Keyboard::Z)
                name << "z";
            if(Key == sf::Keyboard::Num0)
                name << "0";
            if(Key == sf::Keyboard::Num1)
                name << "1";
            if(Key == sf::Keyboard::Num2)
                name << "2";
            if(Key == sf::Keyboard::Num3)
                name << "3";
            if(Key == sf::Keyboard::Num4)
                name << "4";
            if(Key == sf::Keyboard::Num5)
                name << "5";
            if(Key == sf::Keyboard::Num6)
                name << "6";
            if(Key == sf::Keyboard::Num7)
                name << "7";
            if(Key == sf::Keyboard::Num8)
                name << "8";
            if(Key == sf::Keyboard::Num9)
                name << "9";
        }
        if(Key == sf::Keyboard::BackSpace && name.str().size() > 0)
            this->text->setString(name.str().erase(name.str().size() - 1, name.str().size()));
        else
            this->text->setString(name.str());
        this->reAlign();
    }
    if(event->type == sf::Event::KeyPressed && this->hover)
    {
        if(event->key.code == sf::Keyboard::Key::Return)
            if(this->onFinished != NULL)
                (*this->onFinished)();
    }
}
void Text::handleMouseMove(sf::Vector2i pos)
{
    if(this->editable && this->editbox != NULL)
    {
        if(pos.x < (this->editbox->getPosition().x + this->editbox->getLocalBounds().width)
           && pos.x > this->editbox->getPosition().x
           && pos.y < (this->editbox->getPosition().y + this->editbox->getLocalBounds().height)
           && pos.y > this->editbox->getPosition().y)
                this->hover = true;
        else
            this->hover = false;
    }
    else
    {
        if(pos.x < (this->text->getPosition().x + this->text->getLocalBounds().width)
           && pos.x > this->text->getPosition().x
           && pos.y < (this->text->getPosition().y + this->text->getLocalBounds().height)
           && pos.y > this->text->getPosition().y)
                this->hover = true;
        else
            this->hover = false;
    }
    if(this->hover && this->editable)
    {
        this->text->setColor(sf::Color(255, 255, 051, 255));
        if(this->editbox != NULL)
        {
            this->editbox->setFillColor(sf::Color(100, 100, 100, 80));
        }
    }
    else
    {
        if(this->editbox != NULL)
        {
            this->editbox->setOutlineColor(sf::Color::Yellow);
            this->editbox->setFillColor(sf::Color(100, 100, 100, 40));
        }
        this->text->setColor(this->color);
    }

}
void Text::setScrollable(bool scrollable)
{
    this->scrollable = scrollable;
}
void Text::setColor(sf::Color color)
{
    this->text->setColor(color);
    this->color = color;
}
void Text::setEditable(bool editable)
{
    this->editable = editable;
    this->editbox = new sf::RectangleShape();
    this->editbox->setOutlineThickness(2);
    this->editbox->setFillColor(sf::Color(100, 100, 100, 40));
    this->reAlign();
}
