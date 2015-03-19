#ifndef CBACKGROUNDMUSIC_H
#define CBACKGROUNDMUSIC_H

#include <Diluculum/LuaState.hpp>
#include <SFML/Audio.hpp>

class CBackgroundMusic
{
    public:
        CBackgroundMusic();
        virtual ~CBackgroundMusic();
        void stop();
        void update();
    protected:
        Diluculum::LuaState ls;
        sf::Music *music;
        int Playlist;
        bool CreditsSong;
    private:
};

#endif // CBACKGROUNDMUSIC_H
