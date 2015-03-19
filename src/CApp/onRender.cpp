#include "CApp/CApp.h"
#include <iostream>
#include <CMenu.h>
#include <CScorePopup.h>
#include <Manager/CPowerupManager.h>
#include <Explosions/CExplosionManager.h>
using namespace std;

void CApp::onRender()
{
    this->App->clear();
    switch(CConfig::Get()->getGameState())
    {
        case STATE_GAME:
            this->App->draw(*this->Background);
            this->App->draw(*Player);
            if(CConfig::Get()->getMP())
                this->App->draw(*Player2);
            this->App->draw(*AsteroidContainer);
            this->App->draw(*CExplosionManager::Get());
            this->App->draw(*BulletContainer);
            this->App->draw(*CPowerupManager::Get());
            this->App->draw(*T_Score);
            this->App->draw(*CScorePopup::Get());
            this->App->draw(*this->infoBar_fuel);
            this->App->draw(*this->infoBar_health);
            this->App->draw(*this->infoBar);
            if(CConfig::Get()->getMP())
            {
                this->App->draw(*this->infoBar_fuel2);
                this->App->draw(*this->infoBar_health2);
                this->App->draw(*this->infoBar2);
            }
            break;
        case STATE_MAINMENU:
            this->App->draw(*this->GameMenuNew);
            break;
        case STATE_PAUSEMENU:
            this->App->draw(*this->Background);
            this->App->draw(*Player);
            this->App->draw(*AsteroidContainer);
            this->App->draw(*CExplosionManager::Get());
            this->App->draw(*BulletContainer);
            this->App->draw(*CPowerupManager::Get());
            this->App->draw(*CScorePopup::Get());
            this->App->draw(*this->infoBar_fuel);
            this->App->draw(*this->infoBar_health);
            this->App->draw(*this->infoBar);
            this->App->draw(*this->GameMenuNew);
            break;
        case STATE_GAMEOVER:
            break;
        case STATE_CREDITS:
            break;
        case STATE_GUI:
            this->App->draw(*this->GameMenuNew);
            break;
        default:
            cout << "!! UNKNOWN GAME STATE! - CConfig::Get()->getGameState() = " << CConfig::Get()->getGameState() << endl;
    }
    if(CConfig::Get()->getDebug())
        this->App->draw(*this->T_DebugText);

    this->App->display();
}
