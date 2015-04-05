#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
using namespace CMenuNew;

Load *MenuLoader2;
CMenuNew::Button *StartGame2;
CMenuNew::CContainerManager *ConManager2;

void b_StartGame2_onClick()
{
    ConManager2->clearHistory();
    CConfig::Get()->setGameState(STATE_LOADINGGAME);
}
void b_QuitGame2_onClick()
{
    CConfig::Get()->quitGame();
}
void b_Credits2_onClick()
{
    MenuLoader2->Credits();
}
void b_button4_onClick()
{
    ConManager2->clearHistory();
    CConfig::Get()->setGameState(STATE_GAME);
}
void b_button5_onClick()
{
    MenuLoader2->ViewHighscores();
}
void b_button13_onClick()
{
    MenuLoader2->MainMenu();
}
bool Load::PauseMenu()
{
    ConManager2 = manager;
    manager->clearMenu();
    manager->setBackgroundRotationSpeed(7);
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::PauseMenu;
    Entry->name = "Pause Menu";
    manager->addToHistory(Entry);
    MenuLoader2 = this;
    manager->setBackgroundColor(sf::Color(255, 255, 255, 110));
    CMenuNew::Button *button4 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -210), "Resume");
    StartGame2 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -180), "New Game");
    CMenuNew::Button *button13 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -150), "Main Menu");
    CMenuNew::Button *button5 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120), "View Scores");
    CMenuNew::Button *Credits2 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -90), "Credits");
    CMenuNew::Button *QuitGame2 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -60), "Quit Game");
    button4->onClick = &b_button4_onClick;
    button4->downButton = StartGame2;
    button4->upButton = QuitGame2;
    button4->markHover(true);
    StartGame2->onClick = &b_StartGame2_onClick;
    StartGame2->downButton = button13;
    StartGame2->upButton = button4;
    button13->onClick = &b_button13_onClick;
    button13->downButton = button5;
    button13->upButton = StartGame2;
    button5->onClick = &b_button5_onClick;
    button5->downButton = Credits2;
    button5->upButton = button13;
    Credits2->onClick = &b_Credits2_onClick;
    Credits2->downButton = QuitGame2;
    Credits2->upButton = button5;
    QuitGame2->onClick = &b_QuitGame2_onClick;
    QuitGame2->downButton = StartGame2;
    QuitGame2->upButton = Credits2;
    CMenuNew::Image *Logo1 = manager->newImage(sf::Vector2f(20, 20), "Logo");
    Logo1->setScale(sf::Vector2f(1 * (CConfig::Get()->getWindowX() / 1300.f), 1 * (CConfig::Get()->getWindowX() / 1300.f)));
    return true; //Succefully Created the menu!
}
