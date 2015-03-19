#include "CBackgroundMusic.h"
#include <CConfig.h>
#include <Diluculum/LuaState.hpp>
#include <iostream>
#include <time.h>
CBackgroundMusic::CBackgroundMusic()
{
    this->music = new sf::Music();
    this->music->setVolume(40);
    ls.doFile("Data/Script/backgroundMusic.lua");
    Playlist = 1;
}
void CBackgroundMusic::stop()
{
    music->stop();
}
void CBackgroundMusic::update()
{
    using namespace std;
    sf::Music::Status Status = music->getStatus();
    srand( (unsigned)time( NULL ) * 7812);
    music->setVolume(CConfig::Get()->getBackgroundMusicVolume());
    if(CConfig::Get()->getBackgroundMusic())
    {
        if(CConfig::Get()->getGameState() == STATE_CREDITS && CreditsSong)
            music->stop();
        if(CConfig::Get()->getGameState() != STATE_CREDITS && !CreditsSong)
            music->stop();
        if(CConfig::Get()->getGameState() == STATE_CREDITS && Status == 0 && CreditsSong)
        {
            music->openFromFile("Data/Music/Concob.ogg");
            music->play();
            CreditsSong = false;
        }
        if(ls["usePlaylist"].value().asBoolean() && Status == 0 && CConfig::Get()->getGameState() != STATE_CREDITS)
        {
            cout << "Now Playing: (Playlist): " << ls["tracks"][ls["playlist"][Playlist].value().asNumber()].value().asString() << endl;
            music->openFromFile(ls["tracks"][ls["playlist"][Playlist].value().asNumber()].value().asString());
            Playlist++;
            if(Playlist > ls["playlistCount"].value().asNumber())
            Playlist = 1;
            music->play();
            CreditsSong = true;
        }
        if(!ls["usePlaylist"].value().asBoolean() && Status == 0 && CConfig::Get()->getGameState() != STATE_CREDITS)
        {
            int random = rand()%(int)ls["trackCount"].value().asNumber() + 1;
            cout << "Now Playing (Random): " << ls["tracks"][random].value().asString() << endl;
            music->openFromFile(ls["tracks"][random].value().asString());
            music->play();
            CreditsSong = true;
        }
    }
}
CBackgroundMusic::~CBackgroundMusic()
{
    delete this->music;
}
