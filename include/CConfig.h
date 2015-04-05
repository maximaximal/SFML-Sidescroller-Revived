#ifndef CCONFIG_H
#define CCONFIG_H

#include <CSingleton.h>
#include <string>
#include <SFML/System.hpp>

#include <PausableClock.hpp>

//Define Game States
    #define STATE_MAINMENU 0
    #define STATE_GAME 1
    #define STATE_PAUSEMENU 2
    #define STATE_GAMEOVER 3
    #define STATE_LOADINGGAME 4
    #define STATE_CREDITS 5
    #define STATE_GUI 6

//Define OSes
    #define OS_LINUX64 0
    #define OS_LINUX32 1
    #define OS_WINDOWS 2


class CConfig : public TSingleton<CConfig>
{
    public:
        CConfig();
        virtual ~CConfig();
        bool load();
        int getBackgroundStarsCount() {return backgroundStarsCount;}
        int getBackgroundStarsStyle() {return backgroundStarsStyle;}
        int getWindowX() const {return WindowX;}
        int getWindowY() const {return WindowY;}
        int getVelocityIterations() {return velocityIterations;}
        int getPositionIterations() {return positionIterations;}
        int getDoubleTapSpeed() {return doubleTapSpeed;}
        float getTimeStep() {return timeStep;}
        void toggleDebug();
        void setGameState(int State);
        int getGameState() {return gameState;}
        bool getDebug() const {return debug;}
        bool getTextureManagerDebug() const {return debug_TextureManager;}
        bool getSoundManagerDebug() const {return debug_SoundManager;}
        bool getFontManagerDebug() const {return debug_FontManager;}
        bool isFirstRun() {return firstrun;}
        bool getBackgroundMusic() {return backgroundMusic;}
        bool getGameSounds() {return gameSounds;}
        bool getFullscreen() {return fullscreen;}
        bool getScreenSaverMode() {return ScreenSaverMode;}
        bool getMP() {return LocalMultiplayer;}
        void isntFirstRun() {firstrun = false;}
        bool isRunning() {return running;}
        void quitGame() {running = false;}
        float getHighscore() {return (HighscoreClock.GetElapsedTime() * 0.01) + highscoreCache;}
        float getGameTime() {return HighscoreClock.GetElapsedTime() * 0.001;} //Returns the game time in seconds
        void resetHighscore() { HighscoreClock.Reset(); highscoreCache = 0;}
        void pauseHighscore() {HighscoreClock.Pause();}
        void setNickname(std::string nick) {nickname = nick;}
        void setBackgroundMusicVolume(int volume) {backgroundMusicVolume = volume;}
        void setSoundVolume(int volume) {soundVolume = volume;}
        void setMP(bool setTo) {LocalMultiplayer = setTo;}
        void setPigaInputs(bool setTo) {pigaInputs = setTo;}
        std::string getNickname() {return nickname;}
        int getShootRate() {return shootRate;}
        int getQuickMoveForce() {return quickMoveForce;}
        int getNormalMoveForce() {return normalMoveForce;}
        int getShiftMoveForce() {return shiftMoveForce;}
        int getGameLevel();
        int getMaxAsteroids() {return maxAsteroids;}
        int getOS() {return OS;}
        int getStartLaser() {return startLaser;}
        int getStartLaserLevel() {return startLaserLevel;}
        int getBackgroundMusicVolume() {return backgroundMusicVolume;}
        int getSoundVolume() {return soundVolume;}
        bool getPigaInputs() {return pigaInputs;}
        void addToHighscore(int amount) {highscoreCache += amount;}
        void setBackgroundMusic(bool backgroundMusic) {this->backgroundMusic = backgroundMusic;}
        float getVersion() {return version;}
        void writeToScript();
        std::string toLuaBoolean(int boolean);
    protected:
    private:
        int normalMoveForce, quickMoveForce, shiftMoveForce;
        int quickMove;
        int shootRate;
        int doubleTapSpeed;
        int maxAsteroids;
        int OS;
        int backgroundMusicVolume;
        int soundVolume;
        bool ScreenSaverMode;
        float version;
        int startLaser;
        int startLaserLevel;
        std::string nickname;
        bool extremeMode;
        bool debug;
        bool debug_TextureManager;
        bool debug_SoundManager;
        bool debug_FontManager;
        bool fullscreen;
        bool firstrun;
        bool running;
        bool backgroundMusic;
        bool gameSounds;
        bool LocalMultiplayer;
        sftools::PausableClock HighscoreClock;
        float highscoreCache;
        int gameState;
        int backgroundStarsCount;
        int backgroundStarsCountDefault;
        int backgroundStarsStyle; //0 = Same as in Space (StarSheet.png) //1 = new smaller stars
        int WindowX, WindowY;
        float timeStep;
        int velocityIterations, positionIterations;
        bool pigaInputs;
};

#endif // CCONFIG_H
