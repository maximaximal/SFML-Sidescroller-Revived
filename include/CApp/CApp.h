#ifndef CAPP_H
#define CAPP_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <CBackground/CBackground.h>
#include <Player/CPLayer.h>
//Define Directions
    #define RIGHT 0
    #define DOWN 1
    #define LEFT 2
    #define UP 3

#include <CMenu.h>
#include <Container/CBulletContainer.h>
#include <Container/CAsteroidContainer.h>
#include <CBackgroundMusic.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CMenu/Load.h>
class CPlayer;

class CApp
{
    public:
        void onInit();
        void onRender();
        void onUpdate();
        void onExit();
        void onEvent();
        void takeScreenshot();
        CApp();
        virtual ~CApp();
        sf::RenderWindow *App;
    protected:
    private:
        int WindowX, WindowY;
        int FPSCounter, FPSCache;
        bool ShootCache;
        bool ShootCache2;
        int FPSLimiterCache;
        float Framerate;
        int FPS;
        int DoubleclickCache;
        sf::Text *T_DebugText;
        sf::Text *T_Score;
        sf::Clock *FrameClock;
        sf::Clock *DoubleclickClock;
        sf::Clock *ShootTimer;
        sf::Clock *ShootTimer2;
        sf::Time FrameTime;
        CBackgroundMusic *BackgroundMusic;
        CBackground *Background;
        //Health & Fuel Bar
            sf::Sprite *infoBar;
            sf::RectangleShape *infoBar_health;
            sf::RectangleShape *infoBar_fuel;
        //Health & Fuel Bar 2
            sf::Sprite *infoBar2;
            sf::RectangleShape *infoBar_health2;
            sf::RectangleShape *infoBar_fuel2;
        //Game Menu
            CMenuNew::CContainerManager *GameMenuNew;
            CMenuNew::Load *MenuLoader;
        CBulletContainer *BulletContainer;
        CAsteroidContainer *AsteroidContainer;
        //Entities
            CPlayer *Player;
            CPlayer *Player2;
};

#endif // CAPP_H
