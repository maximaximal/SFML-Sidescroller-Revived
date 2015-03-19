#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <Manager/CWebManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <sstream>
using namespace CMenuNew;
using namespace std;
Load *MenuLoader;
CMenuNew::Button *StartGame;
CMenuNew::CContainerManager *ConManager;
CMenuNew::Button *DownloadUpdate;
void b_StartGame_onClick()
{
    ConManager->clearHistory();
    CConfig::Get()->setGameState(4);
}
void b_QuitGame_onClick()
{
    CConfig::Get()->quitGame();
}
void b_Credits_onClick()
{
    MenuLoader->Credits();
}
void b_button7_onClick()
{
    MenuLoader->ViewHighscores();
}
void b_downloadUpdate_onClick()
{
    CWebManager::Get()->web_downloadNewestVersion();
}
void b_button12_onClick()
{
    MenuLoader->Config();
}
void b_downloadUpdate_onUpdate(float frametime)
{
    DownloadUpdate->setText(CWebManager::Get()->getVersionStatus());
}
void b_howTo_onClick()
{
    MenuLoader->HowTo();
}
bool Load::MainMenu()
{
    ConManager = manager;
    manager->clearMenu();
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::MainMenu;
    Entry->name = "Main Menu";
    manager->addToHistory(Entry);
    MenuLoader = this;
    manager->setBackgroundColor(sf::Color(255, 255, 255, 255));
    StartGame =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -210), "Start Game");
    CMenuNew::Button *HowTo =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -180), "How to Play");
    CMenuNew::Button *QuitGame =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -60), "Quit Game");
    CMenuNew::Button *button7 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120), "View Scores");
    CMenuNew::Button *button12 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -90), "Options");
    CMenuNew::Button *Credits =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -150), "Credits");
    CMenuNew::Text *madeBy = manager->newText(sf::Vector2f(5, CConfig::Get()->getWindowY() - 30), "made by maximaximal & ruabmbua");
    madeBy->setFont("Beeb Mode One");
    madeBy->setSize(20);
    madeBy->setColor(sf::Color::Yellow);
    if(CWebManager::Get()->getNewestVersion() > CConfig::Get()->getVersion() && CWebManager::Get()->getVersionStatus() == "Download Update")
    {
        DownloadUpdate =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -210), "DOWNLOAD UPDATE");
        DownloadUpdate->onClick = &b_downloadUpdate_onClick;
        DownloadUpdate->onUpdate = &b_downloadUpdate_onUpdate;
        stringstream howtoUpdateStream;
        howtoUpdateStream << "HOW TO UPDATE" << endl;
        howtoUpdateStream << "1.  Please wait until the download is finished!" << endl;
        howtoUpdateStream << "2.  Relax if you are on Windows, the update is going\n    to be installed automaticly!" << endl;
        howtoUpdateStream << "    If you are on an other system, then unpack \n    the downloaded zip file in the current directory!" << endl;
        howtoUpdateStream << "3.  Play the new update! ;D" << endl;
        CMenuNew::Text *howtoUpdate = manager->newText(sf::Vector2f(5, 200), howtoUpdateStream.str());
        howtoUpdate->setFont("Monospace");
        howtoUpdate->setSize(18);
        howtoUpdate->setColor(sf::Color::White);
    }
    std::stringstream versionIndicatorString;
    versionIndicatorString << "Version ";
    versionIndicatorString << CConfig::Get()->getVersion();
    CMenuNew::Text *versionIndicator =  manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 160, 0), versionIndicatorString.str());
    CMenuNew::Image *Logo1 = manager->newImage(sf::Vector2f(20, 20), "Logo");
    Logo1->setScale(sf::Vector2f(1 * (CConfig::Get()->getWindowX() / 1300.f), 1 * (CConfig::Get()->getWindowX() / 1300.f)));
    versionIndicator->setSize(18);
    versionIndicator->setFont("Beeb Mode One");
    StartGame->onClick = &b_StartGame_onClick;
    QuitGame->onClick = &b_QuitGame_onClick;
    Credits->onClick = &b_Credits_onClick;
    button7->onClick = &b_button7_onClick;
    button12->onClick = &b_button12_onClick;
    HowTo->onClick = &b_howTo_onClick;
    return true; //Succefully Created the menu!
}
