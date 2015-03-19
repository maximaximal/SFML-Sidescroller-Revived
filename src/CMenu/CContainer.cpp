#include "CMenu/CContainer.h"
#include <CMenu/CContainerManager.h>
using namespace std;
using namespace CMenuNew;

CContainer::CContainer()
{
    this->onUpdate = NULL;
    this->onHover = NULL;
    this->onHoverLeave = NULL;
    this->onClick = NULL;
}

CContainer::~CContainer()
{

}
void CContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
void CContainer::update(float frametime)
{

}
void CContainer::handleEvent(sf::Event *event)
{

}
void CContainer::handleMouseMove(sf::Vector2i pos)
{

}
void CContainer::setPosition(sf::Vector2f pos)
{

}
