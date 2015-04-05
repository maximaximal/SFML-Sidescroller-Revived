#ifndef CAPP_H
#define CAPP_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <CBackground/CBackground.h>
#include <Player/CPLayer.h>
//Define Directions
    #define RIGHT_ 0
    #define DOWN_ 1
    #define LEFT_ 2
    #define UP_ 3

#include <CMenu.h>
#include <Container/CBulletContainer.h>
#include <Container/CAsteroidContainer.h>
#include <CBackgroundMusic.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CMenu/Load.h>
#include <piga/Interface.hpp>

class CPlayer;

class CApp
{
    public:
        void onInit();
        void onRender();
        void onUpdate();
        void onExit();
        void onEvent(sf::Event &Event);
        void takeScreenshot();
        CApp();
        virtual ~CApp();
        sf::RenderWindow *App;
    protected:
    private:
        int WindowX, WindowY;
        int FPSCounter, FPSCache;
        bool ShootCache;
        int FPSLimiterCache;
        float Framerate;
        int FPS;
        int DoubleclickCache;
        sf::Text *T_DebugText;
        sf::Text *T_Score;
        sf::Clock *FrameClock;
        sf::Clock *DoubleclickClock;
        sf::Clock *ShootTimer;
        sf::Time FrameTime;
        CBackgroundMusic *BackgroundMusic;
        CBackground *Background;

        piga::Interface *m_pigaInterface;
        //Health & Fuel Bar
            sf::Sprite *infoBar;
            sf::RectangleShape *infoBar_health;
            sf::RectangleShape *infoBar_fuel;
        //Game Menu
            CMenuNew::CContainerManager *GameMenuNew;
            CMenuNew::Load *MenuLoader;
        CBulletContainer *BulletContainer;
        CAsteroidContainer *AsteroidContainer;
        //Entities
            CPlayer *Player;

        bool up, down, left, right, shoot, stabilize, charge;
};

#endif // CAPP_H
