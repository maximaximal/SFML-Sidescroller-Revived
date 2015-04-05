#include "CApp/CApp.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Entity.h>
#include <Player/CPLayer.h>
#include <sstream>
#include <iostream>
#include <time.h>
CApp::CApp()
{
    up = false;
    down = false;
    left = false;
    right = false;
    shoot = false;
    stabilize = false;
    charge = false;
}

CApp::~CApp()
{
    //dtor
}

void CApp::takeScreenshot()
{
    using namespace std;
    CPhysicsManager::Get()->WorldMutex.lock();
    cout << "Taking Screenshot..." << endl;
    sf::Image Screenshot;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    Screenshot = this->App->capture();
    stringstream filename;
    filename << "Data/Screenshots/";
    filename << time(NULL);
    filename << ".png";
    Screenshot.saveToFile(filename.str());
    cout << "Saved Screenshot!" << endl;
    CPhysicsManager::Get()->WorldMutex.unlock();
}

int main()
{
    CApp game;
    game.onInit();
}
