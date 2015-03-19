#ifndef CFONTMANAGER_H
#define CFONTMANAGER_H

#include <CSingleton.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class CFontManager : public TSingleton<CFontManager>
{
    public:
        CFontManager();
        sf::Font& getFont(std::string Name);
        sf::Font& getFont(unsigned int Slot);
        int createFont(std::string FontFile, std::string Name);
        void saveFont(sf::Font *Font, std::string Name);
        int fontLoaded(std::string Name);
        virtual ~CFontManager();
        void deleteFont(std::string Name);
        void deleteFont(int slot);
        void clear();
    protected:
        std::vector<std::string> FontNames;
        std::vector<sf::Font> Fonts;
        std::string RequestCacheName;
        int RequestCacheSlot;
    private:
};

#endif // CFONTMANAGER_H
