#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <Manager/CWebManager.h>
#include <CMenu/Text.h>
using namespace CMenuNew;

CMenuNew::CContainerManager *ConManager3;
CMenuNew::Text *scoreText1;

void b_button6_onClick()
{
    ConManager3->historyBack();
}
void t_scoreText1_onUpdate(float frametime)
{
    scoreText1->setString(CWebManager::Get()->getScores());
}
bool Load::ViewHighscores()
{
    ConManager3 = manager;
    manager->clearMenu();
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::ViewHighscores;
    Entry->name = "View Highscores";
    manager->addToHistory(Entry);
    CMenuNew::Button *button6 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120), "Back");
    button6->onClick = &b_button6_onClick;
    button6->markHover(true);
    scoreText1 = manager->newText(sf::Vector2f(20, 20), "Loading");
    scoreText1->setFont("Monospace");
    scoreText1->setSize(16);
    scoreText1->onUpdate = &t_scoreText1_onUpdate;
    scoreText1->setScrollable(true);
    CMenuNew::Text *howToScrollScores = manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 400, 20), "Use your Mouse-Wheel to\nscroll through the scores!");
    howToScrollScores->setSize(18);
    howToScrollScores->setColor(sf::Color::Yellow);
    howToScrollScores->setFont("Beeb Mode One");
    CWebManager::Get()->web_getScores();
    return true; //Succefully Created the menu!
}
