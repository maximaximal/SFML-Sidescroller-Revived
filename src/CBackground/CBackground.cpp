#include "CBackground/CBackground.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <CConfig.h>
#include <Manager/CTextureManager.h>
#include <CConfig.h>
#include <sstream>
#include <time.h>
CBackground::CBackground()
{
    this->WindowX = CConfig::Get()->getWindowX();
    this->WindowY = CConfig::Get()->getWindowY();
    using namespace std;
    if(CConfig::Get()->getBackgroundStarsCount() < 0)
        CConfig::Get()->quitGame();
    this->Stars.resize(CConfig::Get()->getBackgroundStarsCount());
    this->starSpeed.resize(CConfig::Get()->getBackgroundStarsCount());
    //Set starRectangles
        int i;
        if(CConfig::Get()->getBackgroundStarsStyle() == 1)
        {
            int row = 0;
            int line = 0;
            this->starRectangles.resize(35);
            for(i = 0;i < 35;i++)
            {
                this->starRectangles[i].width = 5;
                this->starRectangles[i].height = 5;
                this->starRectangles[i].left = row * 5;
                this->starRectangles[i].top = line * 5;
                if(i == 12)
                {
                    row = 0;
                    line = 1;
                }
                if(i == 24)
                {
                    row = 0;
                    line = 2;
                }
                row = row + 1;
            }
        }
        if(CConfig::Get()->getBackgroundStarsStyle() == 0)
        {
            CTextureManager::Get()->deleteTexture("StarSheet");
            CTextureManager::Get()->createTexture(CConfig::Get()->getDataDir() + "/Data/Textures/StarSheet.png", "StarSheet");
            this->starRectangles.resize(7);
            for(i = 0;i < 3;i++)
            {
                this->starRectangles[i].width = 20;
                this->starRectangles[i].height = 20;
                this->starRectangles[i].left = i * 20;
                this->starRectangles[i].top = 0;
            }
            //this->starRectangles[3].width = 30;
            //this->starRectangles[3].height = 30;
            //this->starRectangles[3].left = 0;
            //this->starRectangles[3].top = 20;

            this->starRectangles[3].width = 10;
            this->starRectangles[3].height = 10;
            this->starRectangles[3].top = 50;
            this->starRectangles[3].left = 0;

            this->starRectangles[4].width = 10;
            this->starRectangles[4].height = 10;
            this->starRectangles[4].top = 50;
            this->starRectangles[4].left = 0;

            this->starRectangles[5].width = 10;
            this->starRectangles[5].height = 10;
            this->starRectangles[5].top = 50;
            this->starRectangles[5].left = 10;

            this->starRectangles[6].width = 15;
            this->starRectangles[6].height = 15;
            this->starRectangles[6].top = 60;
            this->starRectangles[6].left = 0;
        }
    this->firstRun = true;
}

void CBackground::setStarSpeed(float minSpeed, float maxSpeed)
{
    if(minSpeed > 0)
        this->starMinSpeed = minSpeed;
    if(maxSpeed > 0)
        this->starMaxSpeed = maxSpeed;
}

CBackground::~CBackground()
{
    int i;
    for(i = 0;i < CConfig::Get()->getBackgroundStarsCount();i++)
    {
        if(Stars[i] != NULL)
        {
            delete this->Stars[i];
            Stars[i] = NULL;
            this->starSpeed[i] = 0;
        }
    }
}

sf::IntRect CBackground::calculateStarRect(unsigned int Star)
{
    return this->starRectangles[rand()%this->starRectangles.size()];
}

void CBackground::updateStars()
{
    using namespace std;
    int i;
    srand ( time(NULL) / CConfig::Get()->getHighscore());
    for(i = 0;i < CConfig::Get()->getBackgroundStarsCount();i++)
    {
        if(this->Stars[i] != NULL)
        {
            sf::Vector2f Position = Stars[i]->getPosition();
            if(Position.x < -50)
            {
                Stars[i]->setPosition(WindowX, rand()%WindowY);
                Stars[i]->setTextureRect(this->calculateStarRect(i));
                starSpeed[i] = 0;
                continue;
            }
            if(starSpeed[i] == 0)
            {
                starSpeed[i] = this->calculateStarSpeed();
            }
            Stars[i]->move(-starSpeed[i] * ((CConfig::Get()->getGameLevel() + 1) * 0.1),0);
        }
        else if(this->Stars[i] == NULL)
        {
            Stars[i] = new sf::Sprite();
            Stars[i]->setTexture(CTextureManager::Get()->getTexture("StarSheet"));
            sf::IntRect Rect = this->calculateStarRect(i);
            Stars[i]->setTextureRect(Rect);
            if(firstRun)
                Stars[i]->setPosition(rand()%WindowX, rand()%WindowY);
            else
                Stars[i]->setPosition(WindowX, rand()%WindowY);
        }
    }
}

float CBackground::calculateStarSpeed()
{
    float Speed;
    do
    {
        Speed = this->starMinSpeed + ((float) (rand()%100)/100) * this->starMaxSpeed;
    } while(Speed < starMinSpeed || Speed > starMaxSpeed);
    return Speed;
}

void CBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int i;
    for(i = 0;i < CConfig::Get()->getBackgroundStarsCount();i++)
    {
        if(this->Stars[i] != NULL)
            target.draw(*Stars[i], states);
    }
}
