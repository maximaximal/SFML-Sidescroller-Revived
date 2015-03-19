#include "CApp/CApp.h"
#include <Manager/CTextureManager.h>
#include <Manager/CFontManager.h>
#include <Manager/CPhysicsManager.h>
#include <Explosions/CExplosionManager.h>
void CApp::onExit()
{
    delete(this->App);
    delete(this->T_DebugText);
    delete(this->FrameClock);
    delete(this->DoubleclickClock);
    delete(this->ShootTimer);
    delete(this->ShootTimer2);
    delete(this->Player);
    delete(this->Player2);
    delete(this->infoBar);
    delete(this->infoBar_fuel);
    delete(this->infoBar_health);
    delete(this->infoBar2);
    delete(this->infoBar_fuel2);
    delete(this->infoBar_health2);
    delete(this->Background);
    delete(this->BulletContainer);
    delete(this->AsteroidContainer);
    delete(this->T_Score);
    if(this->BackgroundMusic)
        delete(this->BackgroundMusic);
    delete this->MenuLoader;
    delete this->GameMenuNew;
    CExplosionManager::Get()->destroy();
    CPhysicsManager::Get()->destroy();
    CTextureManager::Get()->destroy();
    CFontManager::Get()->destroy();
}
