#include "CApp/CApp.h"
#include <SFML/System.hpp>
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Player/CPLayer.h"
#include <Manager/CTextureManager.h>
#include <Manager/CFontManager.h>
#include <CConfig.h>
#include <CMenu.h>
#include <CBackgroundMusic.h>
#include <CSoundEffect.h>
#include <Manager/CWebManager.h>
#include <CScorePopup.h>
using namespace std;

void CApp::onInit()
{
//Cout creator Information
    cout << "###############################################" << endl;
    cout << "## SFML Sidescroller - Version " << CConfig::Get()->getVersion() << endl;
    cout << "##     Credits:                              ##" << endl;
    cout << "##         Programming:                      ##" << endl;
    cout << "##             Max Heisinger (maximaximal)   ##" << endl;
    cout << "##         Testing & Scripting:              ##" << endl;
    cout << "##             Roland Ruckerbauer            ##" << endl;
    cout << "##         See the Credits menu!             ##" << endl;
    cout << "##     Website:                              ##" << endl;
    cout << "##         Not there yet :)                  ##" << endl;
    cout << "###############################################" << endl << endl;
//Init Render Window
    cout << "Init RenderWindow" << endl;
    CConfig::Get();
    if(!CConfig::Get()->getFullscreen())
        this->App = new sf::RenderWindow(sf::VideoMode(CConfig::Get()->getWindowX(), CConfig::Get()->getWindowY()), "SFML Sidescroller");
    if(CConfig::Get()->getFullscreen())
        this->App = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SFML Sidescroller", sf::Style::Fullscreen);
    this->App->setFramerateLimit(60);
//Init the Fonts
    cout << "Loading Fonts" << endl;
    CTextureManager::Get()->createTexture("Data/Textures/Logo.png", "Logo");
    CFontManager::Get()->createFont("Data/Fonts/Beeb Mode One.ttf", "Beeb Mode One");
    CFontManager::Get()->createFont("Data/Fonts/LiquidCrystal-Normal.otf", "Computerfont");
    CFontManager::Get()->createFont("Data/Fonts/Inconsolata.otf", "Monospace");
//Init the Major textures
    cout << "Loading Graphics" << endl;
    CTextureManager::Get()->createTexture("Data/Textures/StarSheet2.png", "StarSheet");
    CTextureManager::Get()->createTexture("Data/Textures/SpaceshipSheet.png", "SpaceshipSheet");
    CTextureManager::Get()->createTexture("Data/Textures/explosionsSheet.png", "ExplosionsSheet");
//Init the Web Manager
    CWebManager::Get();
//Validate Config
    sf::Thread ConfigValidatorThread(&CWebManager::validateConfig, CWebManager::Get());
    ConfigValidatorThread.launch();
//Check for the newest version
    CWebManager::Get()->web_getNewestVersion();
//Init the Bullet Container
    BulletContainer = new CBulletContainer();
//Init the background
    cout << "Create the Star-Background" << endl;
    this->Background = new CBackground();
    Background->setStarSpeed(1, 2);
//Init the Menu --OBSOLETE!!!!!!
    cout << "Create the Game Menu" << endl;

    //button1->setText("Hallo!");
//Init the Asteroid Container
    this->AsteroidContainer = new CAsteroidContainer();
//Init the ScorePopups
    cout << "Create the ScorePopup Manager" << endl;
    CScorePopup::Get();
//Initialize the FPS-Text
    this->FPSCounter = 0;
    this->FPSCache = 0;
    this->T_DebugText = new sf::Text("Loading debug...", CFontManager::Get()->getFont("Beeb Mode One"), 12);
    this->T_DebugText->move(10, 10);
    this->T_Score = new sf::Text("Your Score: ", CFontManager::Get()->getFont("Computerfont"), 20);
    this->T_Score->setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() - 25);
//Init the SoundEffects
    if(CConfig::Get()->getGameSounds())
    {
        CSoundEffect::Get();
    }
//Initialize the background music
    this->BackgroundMusic = NULL;
    if(CConfig::Get()->getBackgroundMusic())
    {
        cout << "Init the background music" << endl;
        this->BackgroundMusic = new CBackgroundMusic;
    }
//Set the Time variables
    this->FrameClock = new sf::Clock;
    this->DoubleclickClock = new sf::Clock;
    this->ShootTimer = new sf::Clock;
    CConfig::Get()->setMP(false);

//Create the Player Entity
    cout << "Create the Player" << endl;
    this->Player = new CPlayer();
    this->Player->init(0);
    this->Player->BulletContainer = BulletContainer;
//Init the Menu System
    cout << "Create the (new) Game Menu" << endl;
    this->GameMenuNew = new CMenuNew::CContainerManager(this->App);
    this->MenuLoader = new CMenuNew::Load(GameMenuNew);
    this->GameMenuNew->loader = MenuLoader;
    this->GameMenuNew->activateBackgroundImage();
//Init & setup the infoBr (health & fuel)
    this->infoBar = new sf::Sprite(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(150, 370, 147, 10));
    this->infoBar_health = new sf::RectangleShape(sf::Vector2f(138, 4));
    this->infoBar_fuel = new sf::RectangleShape(sf::Vector2f(56, 2));
    this->infoBar_health->setFillColor(sf::Color(205,0,0, 190));
    this->infoBar_fuel->setFillColor(sf::Color(238,201,0, 190));
    this->infoBar->setColor(sf::Color(255, 255, 255, 190));
    this->infoBar->setScale(sf::Vector2f(2 * (CConfig::Get()->getWindowX() / 700.f), 1 * (CConfig::Get()->getWindowX() / 700.f)));
    this->infoBar_health->setScale(sf::Vector2f(2 * (CConfig::Get()->getWindowX() / 700.f), 1 * (CConfig::Get()->getWindowX() / 700.f)));
    this->infoBar_fuel->setScale(sf::Vector2f(2 * (CConfig::Get()->getWindowX() / 700.f), 1 * (CConfig::Get()->getWindowX() / 700.f)));
    this->infoBar->setPosition(sf::Vector2f(5 * this->infoBar->getScale().x, CConfig::Get()->getWindowY() - (25 * this->infoBar->getScale().y)));
    this->infoBar_health->setPosition(sf::Vector2f(10 * this->infoBar->getScale().x, CConfig::Get()->getWindowY() - (24 * this->infoBar->getScale().y)));
    this->infoBar_fuel->setPosition(sf::Vector2f(6 * this->infoBar->getScale().x, CConfig::Get()->getWindowY() - (18 * this->infoBar->getScale().y)));
//Load Menu 1
    MenuLoader->MainMenu();

//Start the Game-Loop
    CConfig::Get()->setGameState(STATE_GUI);

    cout << "Starting the Game-Loop" << endl;
    while(CConfig::Get()->isRunning())
    {
        this->onEvent();
        this->onUpdate();
        this->onRender();
        if(CConfig::Get()->isFirstRun())
            CConfig::Get()->isntFirstRun();
    }
    cout << "Exit the game..." << endl;
    this->onExit();
}
