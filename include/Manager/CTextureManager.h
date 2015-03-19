#ifndef CTEXTUREMANAGER_H
#define CTEXTUREMANAGER_H

#include <CSingleton.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class CTextureManager : public TSingleton<CTextureManager>
{
    public:
        CTextureManager();
        sf::Texture& getTexture(std::string Name);
        sf::Texture& getTexture(unsigned int Slot);

        int createTexture(std::string Image, std::string Name);
        void saveTexture(sf::Texture *Texture, std::string Name);
        int textureLoaded(std::string Name);
        virtual ~CTextureManager();

        void deleteTexture(std::string Name);
        void deleteTexture(int slot);
        void clear();
        sf::IntRect getTextureRect(int spriteX, int spriteY, int Slot, int Number, bool space);
    protected:
        std::vector<std::string> TextureNames;
        std::vector<sf::Texture*> Textures;
        std::string RequestCacheName;
        int RequestCacheSlot;
    private:
};

#endif // CTEXTUREMANAGER_H
