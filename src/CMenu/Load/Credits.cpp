#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <sstream>
using namespace CMenuNew;
using namespace std;
CMenuNew::Text *creditsText;
CContainerManager *Manager;


void t_creditsText_onUpdate(float frametime)
{
    creditsText->move(0, frametime * (-25));
}
void b_Back_onClick()
{
    Manager->historyBack();
}


bool Load::Credits()
{
    manager->clearMenu();
    Manager = manager;
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::Credits;
    Entry->name = "Credits";
    manager->addToHistory(Entry);
    CMenuNew::Image *Austria = manager->newImage(sf::Vector2f(CConfig::Get()->getWindowX() - 189, 295), "GuiSheet", sf::IntRect(350, 220, 152, 121));
    CMenuNew::Image *SFML_Logo = manager->newImage(sf::Vector2f(CConfig::Get()->getWindowX() - 169, 150), "GuiSheet", sf::IntRect(350, 127, 152, 91));
    CMenuNew::Image *freeSFX_Logo = manager->newImage(sf::Vector2f(CConfig::Get()->getWindowX() - 169, 245), "GuiSheet", sf::IntRect(150, 331, 138, 38));
    CMenuNew::Image *SRCTTP_Games = manager->newImage(sf::Vector2f(CConfig::Get()->getWindowX() - 170, 10), "GuiSheet", sf::IntRect(150, 130, 200, 200));
    SRCTTP_Games->setScale(sf::Vector2f(0.7, 0.7));
    CMenuNew::Button *Back =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -50), "Back");
    Back->onClick = &b_Back_onClick;
    std::stringstream CreditsString;
    CreditsString << "Programming: " << endl;
    CreditsString << "          Max Heisinger (maximaximal)" << endl;
    CreditsString << "          Roland Ruckerbauer (ruabmbua)" << endl;
    CreditsString << "          (The Team SRCTTP - from srcttp.org)" << endl << endl;
    CreditsString << "Librarys/Code used: " << endl;
    CreditsString << "          SFML - by Laurent Gomila" << endl;
    CreditsString << "          PausableClock.hpp - by Marco Antognini" << endl;
    CreditsString << "          Lua - by PUC-Rio" << endl;
    CreditsString << "          Diluculum Lua Library - by Leandro Motta Barros (LMB)" << endl;
    CreditsString << "          Box2D - by Erin Catto" << endl;
    CreditsString << "          \"Read a whole file in a string\" - by Frank Krueger - http://stackoverflow.com/a/524843" << endl;
    CreditsString << "          the Boost C++ Libraries" << endl;
    CreditsString << "          Hashlib++ http://sourceforge.net/projects/hashlib2plus/?source=dlp" << endl;
    CreditsString << "          7-Zip Command Line Edition (for updating)" << endl << endl;
    CreditsString << "Graphics used:" << endl;
    CreditsString << "          SpaceshipSheet v4 - by gregah on deviantART" << endl;
    CreditsString << "          The SpaceshipSheet was altered by Lukas Magauer to fit better into the game." << endl;
    CreditsString << "          Explosions from the Explosions Generator POSIX" << endl;
    CreditsString << "          - Merged into one picture by a tutorial on http://www.xnaresources.com" << endl;
    CreditsString << "          Custom Sprites by me (Max Heisinger)" << endl;
    CreditsString << "          SPACE Sprites - drawn by Max Heisinger, used in SPACE" << endl << endl;
    CreditsString << "Sound Effects used:" << endl;
    CreditsString << "          various Sounds from freesfx.co.uk" << endl;
    CreditsString << "          shields1.ogg - by PhreaKsAccount on Freesound.org" << endl << endl;
    CreditsString << "Music used:" << endl;
    CreditsString << "          Cephelopod - by Kevin MacLeod (incompetech.com)" << endl;
    CreditsString << "          Concob - by Kevin MacLeod (incompetech.com)" << endl;
    CreditsString << "          Electrodoodle - by Kevin MacLeod (incompetech.com)" << endl;
    CreditsString << "          Latin Industries - by Kevin MacLeod (incompetech.com)" << endl;
    CreditsString << "          Rocket - by Kevin MacLeod (incompetech.com)" << endl;
    CreditsString << "          Zap Beat - by Kevin MacLeod (incompetech.com)" << endl;
    creditsText = manager->newText(sf::Vector2f(20, CConfig::Get()->getWindowY()), CreditsString.str());
    creditsText->setFont("Monospace");
    creditsText->setSize(18);
    creditsText->onUpdate = &t_creditsText_onUpdate;
    return true; //Succefully Created the menu!
}
