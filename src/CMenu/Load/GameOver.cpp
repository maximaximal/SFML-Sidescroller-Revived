#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <Manager/CWebManager.h>
#include <iostream>
#include <sstream>
using namespace CMenuNew;

CMenuNew::CContainerManager *ConManager4;
CMenuNew::Text *scoreText2;
CMenuNew::Text *nameEnter1;
bool submitted = false;
void b_button8_onClick()
{
    CConfig::Get()->setGameState(STATE_LOADINGGAME);
}
void b_button9_onClick()
{
    if(!submitted && nameEnter1->getString() != "Your (Nick-)Name: ")
    {
        CConfig::Get()->setNickname(nameEnter1->getString());
        CWebManager::Get()->web_submitScore();
        scoreText2->setPosition(sf::Vector2f(20, 200));
        scoreText2->setScrollable(false);
        submitted = true;
    }
    else
        std::cout << "The score has already been submitted!" << std::endl;
}
void b_button10_onClick()
{
    CConfig::Get()->quitGame();
}
void t_scoreText2_onUpdate(float frametime)
{
    scoreText2->setString(CWebManager::Get()->getScores());
    if(CWebManager::Get()->getScores() == "Failed at submitting the score...")
        submitted = false;
}
bool Load::GameOver()
{
    submitted = false;
    ConManager4 = manager;
    manager->clearMenu();
    manager->setBackgroundColor(sf::Color(255, 0, 0, 255));
    manager->setBackgroundRotationSpeed(18);
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::GameOver;
    Entry->name = "Game Over";
    manager->addToHistory(Entry);
    CMenuNew::Button *button9 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120), "Submit!");
    CMenuNew::Button *button8 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -90), "New Game");
    CMenuNew::Button *button10 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -60), "Quit Game");
    button9->onClick = &b_button9_onClick;
    button9->markHover(true);
    button9->downButton = button8;
    button9->upButton = button10;
    button8->onClick = &b_button8_onClick;
    button8->downButton = button10;
    button10->upButton = button9;
    button10->onClick = &b_button10_onClick;
    button10->downButton = button9;
    button10->upButton = button8;
    scoreText2 = manager->newText(sf::Vector2f(20, 20), "Loading");
    scoreText2->setFont("Monospace");
    scoreText2->setSize(16);
    scoreText2->onUpdate = &t_scoreText2_onUpdate;
    scoreText2->setScrollable(true);
    nameEnter1 = manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 400, 120),  "Your (Nick-)Name: ");
    if(CConfig::Get()->getNickname() != "")
        nameEnter1->setString(CConfig::Get()->getNickname());
    CMenuNew::Text *text_1 = manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 300, 200),  "Your Score:");
    text_1->setFont("Beeb Mode One");
    text_1->setSize(22);
    std::stringstream highscore;
    highscore << CConfig::Get()->getHighscore();
    CMenuNew::Text *text_2 = manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 250, 225),  highscore.str());
    text_2->setFont("Computerfont");
    text_2->setSize(42);
    nameEnter1->setEditable(true);
    nameEnter1->setSize(18);
    nameEnter1->onFinished = &b_button9_onClick;
    CMenuNew::Text *howToSubmit = manager->newText(sf::Vector2f(CConfig::Get()->getWindowX() - 400, 20), "Use your Mouse-Wheel to\nscroll through the scores!\nEnter your name and\npress \"Submit!\" or hit \"Enter\" \nto submit your score!");
    howToSubmit->setSize(18);
    howToSubmit->setColor(sf::Color::Yellow);
    howToSubmit->setFont("Beeb Mode One");
    CWebManager::Get()->web_getScores();
    return true; //Succefully Created the menu!
}
