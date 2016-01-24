#include "CMenu/CContainerManager.h"
#include <CMenu/CContainer.h>
#include <CMenu/Button.h>
#include <CMenu/Text.h>
#include <CMenu/Load.h>
#include <CConfig.h>
#include <sstream>
#include <time.h>
using namespace CMenuNew;
using namespace std;

CContainerManager::CContainerManager(sf::RenderWindow *app)
{
    this->app = app;
    this->backgroundSpeed = 7;
}

CContainerManager::~CContainerManager()
{
    this->clearMenu();
    this->clearHistory();
}

Button* CContainerManager::newButton(sf::Vector2i pos, std::string text)
{
    CMenuNew::Button *button = new CMenuNew::Button(pos, text);
    this->elements.push_back(button);
    return button;
}
Text* CContainerManager::newText(sf::Vector2f pos, std::string textString)
{
    CMenuNew::Text *text = new CMenuNew::Text(pos, textString);
    this->elements.push_back(text);
    return text;
}
Image* CContainerManager::newImage(sf::Vector2f pos, std::string textureName, sf::IntRect textureRect)
{
    CMenuNew::Image *image = new CMenuNew::Image(pos, textureName, textureRect);
    this->elements.push_back(image);
    return image;
}
Image* CContainerManager::newImage(sf::Vector2f pos, std::string textureName)
{
    CMenuNew::Image *image = new CMenuNew::Image(pos, textureName);
    this->elements.push_back(image);
    return image;
}
Slider* CContainerManager::newSlider(sf::Vector2f pos, int length)
{
    CMenuNew::Slider *slider = new CMenuNew::Slider(pos, length);
    this->elements.push_back(slider);
    return slider;
}
bool CContainerManager::IDExists(int ID)
{
    for(unsigned int i = 0; i < this->elements.size(); i++)
    {
        if(elements[i]->getID() == ID)
            return false;
    }
    return true;
}
void CContainerManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->Background != NULL)
        target.draw(*this->Background);
    for(unsigned int i = 0; i < this->elements.size(); i++)
    {
        target.draw(*elements[i]);
    }
}
CContainer* CContainerManager::getElement(int ID)
{
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->getID() == ID)
        {
            return elements[i];
        }
    }
    return NULL;
}
void CContainerManager::handleEvent(sf::Event *event)
{
    if(event->type == sf::Event::MouseMoved)
    {
        for(unsigned int i = 0; i < elements.size(); i++)
        {
            elements[i]->handleMouseMove(sf::Mouse::getPosition(*this->app));
        }
    }
    else
    {
        for(unsigned int i = 0; i < elements.size(); i++)
        {
            elements[i]->handleEvent(event);
        }
    }
    if(event->type == sf::Event::KeyReleased)
    {
        if(event->key.code == sf::Keyboard::Key::PageDown)
            this->historyBack();
    }
}
void CContainerManager::clearMenu()
{
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        if(elements[i] != NULL)
            delete elements[i];
    }
    this->elements.clear();
}
void CContainerManager::update(float frametime)
{
    if(this->Background != NULL)
    {
        backgroundRotation = this->Background->getRotation();
        if(backgroundRotation >= 360) (backgroundRotation = 0);
        if(frametime < 0.05)
            Background->setRotation(backgroundRotation + (this->backgroundSpeed * frametime));
    }
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        if(elements[i]->onUpdate != NULL)
            (*elements[i]->onUpdate)(frametime);
    }
}
void CContainerManager::addToHistory(HistoryEntry *entry)
{
    this->history.push_back(entry);
}
void CContainerManager::historyBack()
{
    if(history.size() > 0)
    {
        delete this->history[history.size() - 1];
        this->history.erase(history.begin() + history.size() - 1);
        if(history[history.size() - 1]->load != NULL)
        {
            if((loader->*history[history.size() - 1]->load)())
            {
                cout << "Back through the GUI-History: \"" << this->history[history.size() - 1]->name << "\" - Level #" << history.size() - 2 << endl;
                delete this->history[history.size() - 2]; //Delete the old instance
                this->history.erase(history.begin() + history.size() - 2);
            }
            else
                cout << "!! Error loading \"" << this->history[history.size() - 1]->name << "\" from the GUI-History!" << endl;
        }
    }
}
void CContainerManager::clearHistory()
{
    if(this->history.size() > 0)
        cout << "Deleted GUI-History: ";
    for(unsigned int i = 0; i < history.size(); i++)
    {
        if(history[i] != NULL)
        {
            cout << history[i]->name << ", ";
            delete history[i];
        }
    }
    if(this->history.size() > 0)
        cout << endl;
    this->history.clear();
}
void CContainerManager::activateBackgroundImage()
{
    stringstream file;
    srand ( time(NULL) );
    file << CConfig::Get()->getDataDir() + "/Data/Textures/MenuBackground";
    file << rand() % 3 + 1;
    file << ".png";
    this->Background = new sf::Sprite();
    this->Background->setOrigin(1000, 1000);
    this->Background->setScale(CConfig::Get()->getWindowX() / 1700.f, CConfig::Get()->getWindowX() / 1700.f);
    if(CTextureManager::Get()->createTexture(file.str(), "MenuBackground") < 0)
    {
        cout << "!! This Computer can't handle a 2000x2000px PNG." << endl;
        cout << "   Loading 1000x1000 alternative..." << endl;
        CTextureManager::Get()->deleteTexture("MenuBackground");
        file.str("");
        file << CConfig::Get()->getDataDir() + "/Data/Textures/MenuBackground";
        file << rand() % 3 + 1;
        file << "_lowRes.png";
        CTextureManager::Get()->createTexture(file.str(), "MenuBackground");
        this->Background->setOrigin(500, 500);
        this->Background->setScale(CConfig::Get()->getWindowX() / 650.f, CConfig::Get()->getWindowX() / 650.f);
    }
    this->Background->setPosition(CConfig::Get()->getWindowX() / 2, CConfig::Get()->getWindowY() / 2);
    this->Background->setTexture(CTextureManager::Get()->getTexture("MenuBackground"));
}
void CContainerManager::setBackgroundColor(sf::Color color)
{
    this->Background->setColor(color);
}
void CContainerManager::setBackgroundRotationSpeed(int multiplier)
{
    this->backgroundSpeed = multiplier;
}
