#include "CConfig.h"
#include <string>
#include <iostream>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <CApp/CApp.h>
#include <Diluculum/LuaState.hpp>
#include <PausableClock.hpp>
#include <sstream>
#include <fstream>

using namespace std;

CConfig::CConfig()
{
    dataDir = "./";
    //Set the Version
        this->version = 0.08;
    //default settings (in case there is no config file)
        this->WindowX = 800;
        this->WindowY = 500;
        this->backgroundStarsCount = (-1);
        this->backgroundStarsCountDefault = (-1);
        this->backgroundStarsStyle = 1;
        this->debug = false;
        this->doubleTapSpeed = 150;
        this->backgroundMusic = true;
        this->gameSounds = true;
        this->fullscreen = false;
        this->soundVolume = 100;
    //Physics Variables
        this->timeStep = 1.0/60.0;
        this->velocityIterations = 6;
        this->positionIterations = 2;
    //Set the firstrun variable
        this->firstrun = true;
    //Running true
        this->running = true;
    std::cout << "Loading Config..." << std::endl;
    this->highscoreCache = 0;
}
void CConfig::toggleDebug()
{
    if(this->debug)
        this->debug=false;
    else
        this->debug=true;
}
void CConfig::setGameState(int gameState)
{
    this->gameState = gameState;
    if(gameState == STATE_PAUSEMENU)
    {
        this->HighscoreClock.Pause();
    }
    if(gameState == STATE_GAME)
    {
        this->HighscoreClock.Start();
    }
    if(gameState == STATE_LOADINGGAME)
    {
        this->HighscoreClock.Reset();
    }
}
int CConfig::getGameLevel()
{
    if(extremeMode)
        return (int) ((this->getHighscore()) / 20);
    else
        return (int) ((this->getHighscore()) / 200);
}
bool CConfig::load()
{
    Diluculum::LuaState ls;
    ls.doFile(dataDir + "/Data/Script/config.lua");
    this->backgroundStarsStyle = ls["backgroundStarsStyle"].value().asNumber();
    this->backgroundStarsCount = ls["backgroundStarsCount"].value().asNumber();
    this->backgroundStarsCountDefault = this->backgroundStarsCount;
    this->debug = ls["debug"]["active"].value().asBoolean();
    this->pigaInputs = ls["pigaInputs"].value().asBoolean();
    this->WindowX = ls["WindowX"].value().asNumber();
    this->WindowY = ls["WindowY"].value().asNumber();
    this->doubleTapSpeed = ls["doubleTapSpeed"].value().asNumber();
    this->shiftMoveForce = ls["Forces"]["shiftMove"].value().asNumber();
    this->normalMoveForce = ls["Forces"]["normalMove"].value().asNumber();
    this->quickMoveForce = ls["Forces"]["quickMove"].value().asNumber();
    this->shootRate = ls["shootRate"].value().asNumber();
    this->backgroundMusic = ls["backgroundMusic"].value().asBoolean();
    this->gameSounds = ls["gameSounds"].value().asBoolean();
    this->fullscreen = ls["fullscreen"].value().asBoolean();
    this->debug_FontManager = ls["debug"]["FontManager"].value().asBoolean();
    this->debug_TextureManager = ls["debug"]["TextureManager"].value().asBoolean();
    this->debug_SoundManager = ls["debug"]["SoundManager"].value().asBoolean();
    this->ScreenSaverMode = ls["ScreenSaverMode"].value().asBoolean();
    this->backgroundMusicVolume = ls["backgroundMucicVolume"].value().asNumber();
    this->soundVolume = ls["gameSoundsVolume"].value().asNumber();
    if(fullscreen)
    {
        this->WindowX = sf::VideoMode::getDesktopMode().width;
        this->WindowY = sf::VideoMode::getDesktopMode().height;
    }
    this->maxAsteroids = this->WindowX * this->WindowY / 12000;
    this->extremeMode = ls["extremeMode"].value().asBoolean();
    this->OS = ls["OS"].value().asNumber();
    this->startLaser = ls["startLaser"].value().asNumber();
    this->startLaserLevel = ls["startLaserLevel"].value().asNumber();
    if(this->backgroundStarsCount < 0)
        this->backgroundStarsCount = (int) (this->WindowX * this->WindowY) / 1800; //Calculate the backgroundStarsCount based on the standard ratio
    //Detect OS - if it is not recognized, the selection of the config file will be applied.
    #ifdef _WIN32
        this->OS = OS_WINDOWS;
    #endif
    #ifdef __gnu_linux__
        this->OS = OS_LINUX64;
        #ifdef __X86_64__
            this->OS = OS_LINUX64;
        #endif
        #ifdef __i386__
            this->OS = OS_LINUX32;
        #endif
    #endif
    return true;
}
CConfig::~CConfig()
{

}
void CConfig::writeToScript()
{
    stringstream write;
    write << "-- window resolution" << endl;
    write << "	WindowX = " << this->WindowX << ";" << endl;
    write << "  WindowY = " << this->WindowY << ";" << endl;
    write << "	fullscreen = " << this->toLuaBoolean(this->fullscreen) << ";" << endl;
    write << "-- debug mode" << endl;
    write << "	debug = {" << endl;
    write << "		active = " << this->toLuaBoolean(this->debug) << ";" << endl;
    write << "		TextureManager = " << this->toLuaBoolean(this->debug_TextureManager) << ";" << endl;
    write << "		SoundManager = " << this->toLuaBoolean(this->debug_SoundManager) << ";" << endl;
    write << "		FontManager = " << this->toLuaBoolean(this->debug_FontManager) << ";" << endl;
    write << "	};" << endl;
    write << "-- OS" << endl;
    write << "-- 0 = Linux64;" << endl;
    write << "-- 1 = Linux32;" << endl;
    write << "-- 2 = Windows;" << endl;
    write << "	OS = " << this->OS << ";" << endl;
    write << "-- extreme Mode (Sets the levelup-points from 200 to 20)" << endl;
    write << "	extremeMode = " << this->toLuaBoolean(this->extremeMode) << ";			--RESTRICTED" << endl;
    write << "-- piga inputs (needs a piga-host to be run!)" << endl;
    write << "  pigaInputs = " << this->toLuaBoolean(this->pigaInputs);
    write << "-- Screensaver Mode" << endl;
    write << "	ScreenSaverMode = " << this->toLuaBoolean(this->ScreenSaverMode) << ";" << endl;
    write << "-- number of stars in the background (-1 = automatic)" << endl;
    write << "	backgroundStarsCount = " << this->backgroundStarsCountDefault << ";" << endl;
    write << "-- background style" << endl;
    write << "	backgroundStarsStyle = " << this->backgroundStarsStyle << ";" << endl;
    write << "-- Delay between key presses to trigger a double click/tab (in milliseconds)" << endl;
    write << "	doubleTapSpeed = " << this->doubleTapSpeed << "; --Deactivated because it sucks xD - Standard Value would be around 180 though" << endl;
    write << "-- Shoot Rate (Delay between a shot - in milliseconds)" << endl;
    write << "	shootRate = " << this->shootRate << ";			--RESTRICTED" << endl;
    write << "-- Start Laser" << endl;
    write << "-- 1 = RED" << endl;
    write << "-- 2 = BLUE" << endl;
    write << "-- 3 = GREEN" << endl;
    write << "-- 4 = MAGENTA" << endl;
    write << "-- The startLaserLevel is a value from 1 to 4 (1 is normal, 4 is the best)" << endl;
    write << "	startLaser = " << this->startLaser << ";				--RESTRICTED" << endl;
    write << "	startLaserLevel = " << this->startLaserLevel << ";			--RESTRICTED" << endl;
    write << "-- Sound Configuration" << endl;
    write << "	backgroundMusic = " << this->toLuaBoolean(this->backgroundMusic) << ";" << endl;
    write << "	backgroundMucicVolume = " << this->backgroundMusicVolume << ";" << endl;
    write << "	gameSounds = " << this->toLuaBoolean(this->gameSounds) << ";" << endl;
    write << "	gameSoundsVolume = " << this->soundVolume << ";" << endl;
    write << "-- Physic variables" << endl;
    write << "	Forces = {" << endl;
    write << "		normalMove = " << this->normalMoveForce << ";		--RESTRICTED" << endl;
    write << "		shiftMove = " << this->shiftMoveForce << ";		--RESTRICTED" << endl;
    write << "		quickMove = " << this->quickMoveForce << ";		--RESTRICTED" << endl;
    write << "	}" << endl;
    ofstream file(CConfig::Get()->getDataDir() + "/Data/Script/config.lua", ofstream::binary);
    file << write.str();
    file.close();
}
std::string CConfig::toLuaBoolean(int boolean)
{
    if(boolean == 0)
        return "false";
    else
        return "true";
}
void CConfig::setDataDir(const string &dataDir)
{
    this->dataDir = dataDir;
}
