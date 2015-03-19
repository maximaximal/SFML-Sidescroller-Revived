#include "Manager/CFontManager.h"

#include <CSingleton.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <CConfig.h>

CFontManager::CFontManager()
{
    this->createFont("Data/Fonts/arial.ttf", "Arial");
}

int CFontManager::fontLoaded(std::string Name)
{
    unsigned int i;
    for(i = 0;i < this->FontNames.size(); i++)
    {
        if(FontNames[i] == Name)
            return i;
    }
    return -1;
}
sf::Font& CFontManager::getFont(std::string Name)
{
    bool end = false;
    unsigned int i;
    if(Name == this->RequestCacheName)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
            std::cout << "[DEBUG] [Font Manager] Font \"" << Name << "\" was saved in the cache. Slot: " << this->RequestCacheSlot << std::endl;
        return this->Fonts[this->RequestCacheSlot];
    }
    for(i = 0 ;i < this->FontNames.size() && end == false; i++)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
            std::cout << "[DEBUG] [Font Manager] Cycle through " << FontNames[i] << "." << std::endl;
        if (FontNames[i] == Name)
        {
            if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
                std::cout << "[DEBUG] [Font Manager] Found font " << Name << " in slot " << i << "." << std::endl;
            //Save the request in the request-cache
                this->RequestCacheName = Name;
                this->RequestCacheSlot = i;
            return this->Fonts[i];
        }
    }
    if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
        std::cout << "![DEBUG] [Font Manager] Can't find font \"" << Name << "\"!" << std::endl;
    return this->Fonts[0];
}

sf::Font& CFontManager::getFont(unsigned int Slot)
{
    if(Slot < this->FontNames.size())
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
            std::cout << "[DEBUG] [Font Manager] Returning font " << Slot << " as requested. Name: " << this->FontNames[Slot] << std::endl;
        return this->Fonts[Slot];
    }
    else
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
            std::cout << "![DEBUG] [Font Manager] Did not find font in slot " << Slot << ". Returning Arial!" << std::endl;
        return this->Fonts[0];
    }
}

void CFontManager::clear()
{
    this->FontNames.erase(FontNames.begin() + 1, this->FontNames.end());
    this->Fonts.erase(Fonts.begin() + 1, this->Fonts.end());
}

void CFontManager::deleteFont(std::string name)
{
    int slot = this->fontLoaded(name);
    if(slot != -1)
        this->deleteFont(slot);
}

void CFontManager::deleteFont(int slot)
{
    this->Fonts.erase(Fonts.begin() + slot);
    this->FontNames.erase(FontNames.begin() + slot);
}

int CFontManager::createFont(std::string FontFile, std::string Name)
{
    int slot = this->fontLoaded(Name);
    if(slot != -1)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
            std::cout << "[DEBUG] [Font Manager] Font " << Name << " is already loaded in slot " << slot << "." << std::endl;
        return slot;
    }

    sf::Font Font;
    if(!Font.loadFromFile(FontFile))
        return -1;
    this->FontNames.push_back(Name);
    this->Fonts.push_back(Font);
    if(CConfig::Get()->getDebug() && CConfig::Get()->getFontManagerDebug())
        std::cout << "[DEBUG] [Font Manager] Loaded Font " << Name << " into slot " << Fonts.size() - 1 << "." << std::endl;
    this->RequestCacheName = Name;
    this->RequestCacheSlot = Fonts.size() - 1;
    return Fonts.size() - 1;
}
void CFontManager::saveFont(sf::Font *Font, std::string Name)
{
    this->FontNames.push_back(Name);
    this->Fonts.push_back(*Font);
}

CFontManager::~CFontManager()
{
    FontNames.clear();
    Fonts.clear();
}
