#include "Manager/CTextureManager.h"

#include <CSingleton.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <CConfig.h>

CTextureManager::CTextureManager()
{
    this->createTexture("Data/Textures/TextureError.png", "TextureError");
}

int CTextureManager::textureLoaded(std::string Name)
{
    unsigned int i;
    for(i = 0;i < this->TextureNames.size(); i++)
    {
        if(TextureNames[i] == Name)
            return i;
    }
    return -1;
}
sf::IntRect CTextureManager::getTextureRect(int spriteX, int spriteY, int Slot, int Number, bool space)
{
    sf::Vector2u TextureSize = this->Textures[Slot]->getSize();
    sf::IntRect TextureRect;
    TextureRect.width = spriteX;
    TextureRect.height = spriteY;
    if(space)
    {
        //Add the space between the sprites (black space in the image, to seperate the sprites)
        spriteX +=2;
        spriteY += 2;
    }
    int rows = TextureSize.x / spriteX ;
    int lines = TextureSize.y / spriteY ;
    int row = 0;
    int line = 0;
    if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
        std::cout << "[DEBUG] [Texture Manager] TextureRect for " << TextureNames[Slot] << " (Slot " << Slot << ")" << std::endl << "    -Number: " << Number << " Size: " << spriteX << "x" << spriteY << " Space: " << space << std::endl;

    for(int i = 0;i != Number;i++)
    {
        row += 1;
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "    [Cycle] Row: " << row << " Line: " << line << std::endl;
        if(row == rows)
        {
            row = 0;
            line += 1;
        }
        if(line > lines)
            return TextureRect;
    }
    if(space)
    {
        TextureRect.left = row * (spriteX) + 1;
        TextureRect.top = line * (spriteY) + 1;
    }
    else
    {
        TextureRect.left = row * spriteX;
        TextureRect.top = line * spriteY;
    }
    if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
        std::cout << "[DEBUG] [Texture Manager] returned texturerect: X=" << TextureRect.left << ", top=" << TextureRect.top << ", width=" << TextureRect.width << ", height=" << TextureRect.height << std::endl;
    return TextureRect;
}
sf::Texture& CTextureManager::getTexture(std::string Name)
{
    bool end = false;
    unsigned int i;
    if(Name == this->RequestCacheName)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "[DEBUG] [Texture Manager] Texture \"" << Name << "\" was saved in the cache. Slot: " << this->RequestCacheSlot << std::endl;
        return *this->Textures[this->RequestCacheSlot];
    }
    for(i = 0 ;i < this->TextureNames.size() && end == false; i++)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "[DEBUG] [Texture Manager] Cycle through " << TextureNames[i] << "." << std::endl;
        if (TextureNames[i] == Name)
        {
            if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
                std::cout << "[DEBUG] [Texture Manager] Found Texture " << Name << " in slot " << i << "." << std::endl;
            //Save the request in the request-cache
                this->RequestCacheName = Name;
                this->RequestCacheSlot = i;
            return *this->Textures[i];
        }
    }
    if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
        std::cout << "![DEBUG] [Texture Manager] Can't find texture \"" << Name << "\"!" << std::endl;
    return *this->Textures[0];
}

sf::Texture& CTextureManager::getTexture(unsigned int Slot)
{
    if(Slot < this->TextureNames.size())
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "[DEBUG] [Texture Manager] Returning texture " << Slot << " as requested. Name: " << this->TextureNames[Slot] << std::endl;
        return *this->Textures[Slot];
    }
    else
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "![DEBUG] [Texture Manager] Did not find texture in slot " << Slot << ". Returning Error!" << std::endl;
        return *this->Textures[0];
    }
}

void CTextureManager::clear()
{
    this->TextureNames.erase(TextureNames.begin() + 1, this->TextureNames.end());
    for(unsigned int i = 0; i < Textures.size(); i++)
    {
        delete Textures[i];
    }
    this->Textures.erase(Textures.begin() + 1, this->Textures.end());
}

void CTextureManager::deleteTexture(std::string name)
{
    int slot = this->textureLoaded(name);
    if(slot != -1)
        this->deleteTexture(slot);
}

void CTextureManager::deleteTexture(int slot)
{
    this->Textures.erase(Textures.begin() + slot);
    this->TextureNames.erase(TextureNames.begin() + slot);
}

int CTextureManager::createTexture(std::string Image, std::string Name)
{
    int slot = this->textureLoaded(Name);
    if(slot != -1)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
            std::cout << "[DEBUG] [Texture Manager] Texture " << Name << " is already loaded in slot " << slot << "." << std::endl;
        return slot;
    }

    sf::Texture *Texture = new sf::Texture();
    if(!Texture->loadFromFile(Image))
        return -1;
    this->TextureNames.push_back(Name);
    this->Textures.push_back(Texture);
    if(CConfig::Get()->getDebug() && CConfig::Get()->getTextureManagerDebug())
        std::cout << "[DEBUG] [Texture Manager] Loaded Texture " << Name << " into slot " << Textures.size() - 1 << "." << std::endl;
    this->RequestCacheName = Name;
    this->RequestCacheSlot = Textures.size() - 1;
    return Textures.size() - 1;
}
void CTextureManager::saveTexture(sf::Texture *Texture, std::string Name)
{
    this->TextureNames.push_back(Name);
    this->Textures.push_back(Texture);
}

CTextureManager::~CTextureManager()
{
    TextureNames.clear();
    Textures.clear();
}
