#include "CSoundEffect.h"
#include <CConfig.h>
#include <iostream>

using namespace std;

CSoundEffect::CSoundEffect()
{
    this->powerupSound = new sf::SoundBuffer;
    this->laserShotSound = new sf::SoundBuffer;
    this->explosionSound = new sf::SoundBuffer;
    this->asteroidCollisionSound = new sf::SoundBuffer;
    this->powerupApplySound = new sf::SoundBuffer;
    this->buttonPressedSound = new sf::SoundBuffer;
    if(!powerupSound->loadFromFile("Data/Sounds/powerup.flac"))
        cout << "!! Could not load the Data/Sounds/powerup.flac Sound!" << endl;
    if(!powerupApplySound->loadFromFile("Data/Sounds/applyPowerup.flac"))
        cout << "!! Could not load the Data/Sounds/applyPowerup.flac Sound!" << endl;
    if(!laserShotSound->loadFromFile("Data/Sounds/laserShot.flac"))
        cout << "!! Could not load the Data/Sounds/laserShot.flac Sound!" << endl;
    if(!asteroidCollisionSound->loadFromFile("Data/Sounds/asteroidHit.flac"))
        cout << "!! Could not load the Data/Sounds/asteroidHit.flac Sound!" << endl;
    if(!explosionSound->loadFromFile("Data/Sounds/explosion.flac"))
        cout << "!! Could not load the Data/Sounds/explosion.flac Sound!" << endl;
    if(!buttonPressedSound->loadFromFile("Data/Sounds/button.flac"))
        cout << "!! Could not load the Data/Sounds/button.flac Sound!" << endl;
}
void CSoundEffect::playSound(int SoundID)
{
    sf::Sound *soundEffect = new sf::Sound;
    if(SoundID == SOUND_LASER)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (LaserShot Sound)" << endl;
        soundEffect->setBuffer(*this->laserShotSound);
        soundEffect->setVolume(20 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_LASER_BIG)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (LaserShot Sound)" << endl;
        soundEffect->setBuffer(*this->laserShotSound);
        soundEffect->setPitch(0.6);
        soundEffect->setVolume(20 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_LASER_SMALL)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (LaserShot Sound)" << endl;
        soundEffect->setBuffer(*this->laserShotSound);
        soundEffect->setPitch(2);
        soundEffect->setVolume(20 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_LASER_TINY)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (LaserShot Sound)" << endl;
        soundEffect->setBuffer(*this->laserShotSound);
        soundEffect->setPitch(3);
        soundEffect->setVolume(20 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_EXPLOSION)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (Explosion Sound)" << endl;
            soundEffect->setVolume(90 * (CConfig::Get()->getSoundVolume() / 100.f));
        soundEffect->setBuffer(*this->explosionSound);
    }
    if(SoundID == SOUND_ASTEROIDHIT)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (AsteroidHit Sound)" << endl;
        soundEffect->setBuffer(*this->asteroidCollisionSound);
        soundEffect->setVolume(40 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_ASTEROIDEXPLOSION)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (AsteroidExplosion Sound)" << endl;
        soundEffect->setBuffer(*this->explosionSound); //Only temporary!
        soundEffect->setVolume(40 * (CConfig::Get()->getSoundVolume() / 100.f));
    }
    if(SoundID == SOUND_POWERUP)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (PowerUp Sound)" << endl;
        soundEffect->setVolume(50 * (CConfig::Get()->getSoundVolume() / 100.f));
        soundEffect->setBuffer(*this->powerupSound);
    }
    if(SoundID == SOUND_POWERUPAPPLY)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (PowerUp Apply Sound)" << endl;
        soundEffect->setVolume(100 * (CConfig::Get()->getSoundVolume() / 100.f));
        soundEffect->setBuffer(*this->powerupApplySound);
    }
    if(SoundID == SOUND_BUTTONPRESSED)
    {
        if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
            cout << "[DEBUG] [Sound Effect] Play Sound " << SoundID << " (Button Pressed Sound)" << endl;
        soundEffect->setVolume(100 * (CConfig::Get()->getSoundVolume() / 100.f));
        soundEffect->setBuffer(*this->buttonPressedSound);
    }
    soundEffect->play();
    SoundCache.push_back(soundEffect);
}
void CSoundEffect::update()
{
    for(unsigned int i = 0 ; i < SoundCache.size() ; i++)
    {
        if(SoundCache[i]->getStatus() == 0)
        {
            delete SoundCache[i];
            SoundCache.erase(SoundCache.begin() + i);
            if(CConfig::Get()->getDebug() && CConfig::Get()->getSoundManagerDebug())
                cout << "[DEBUG] [Sound Effect] Cleared Sound #" << i << " of the queue" << endl;
        }
    }
}
CSoundEffect::~CSoundEffect()
{
    for(unsigned int i = 0;i < SoundCache.size();i++)
    {
        delete SoundCache[i];
    }
    delete this->laserShotSound;
    delete this->explosionSound;
    delete this->asteroidCollisionSound;
    delete this->asteroidExplosionSound;
    delete this->powerupApplySound;
    delete this->powerupSound;
}
