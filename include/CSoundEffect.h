#ifndef CSOUNDEFFECT_H
#define CSOUNDEFFECT_H
#include <CSingleton.h>
#include <SFML/Audio.hpp>

#include <vector>

//Define Sound-Effects
    #define SOUND_EXPLOSION 0
    #define SOUND_LASER 1
    #define SOUND_ASTEROIDHIT 2
    #define SOUND_ASTEROIDEXPLOSION 3
    #define SOUND_POWERUP 4
    #define SOUND_LASER_BIG 5
    #define SOUND_LASER_SMALL 6
    #define SOUND_LASER_TINY 7
    #define SOUND_POWERUPAPPLY 8
    #define SOUND_BUTTONPRESSED 9

class CSoundEffect : public TSingleton<CSoundEffect>
{
    public:
        CSoundEffect();
        virtual ~CSoundEffect();
        void playSound(int SoundID);
        void update();
    protected:
        sf::SoundBuffer *explosionSound;
        sf::SoundBuffer *laserShotSound;
        sf::SoundBuffer *powerupSound;
        sf::SoundBuffer *asteroidCollisionSound;
        sf::SoundBuffer *asteroidExplosionSound;
        sf::SoundBuffer *powerupApplySound;
        sf::SoundBuffer *buttonPressedSound;
        std::vector<sf::Sound*> SoundCache;
    private:
};

#endif // CSOUNDEFFECT_H
