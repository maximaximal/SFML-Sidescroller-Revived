#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <CMenu/Text.h>
#include <string>
#include <fstream>
#include <Manager/CWebManager.h>
using namespace CMenuNew;
using namespace std;

CMenuNew::CContainerManager *ConManager5;

void b_button15_onClick()
{
    ConManager5->historyBack();
}

bool Load::HowTo()
{
    ConManager5 = manager;
    manager->clearMenu();
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::HowTo;
    Entry->name = "View HowTo";
    manager->addToHistory(Entry);
    CMenuNew::Text *howToText = manager->newText(sf::Vector2f(20, 20), CWebManager::Get()->readFile2("Data/howto.txt"));
    howToText->setFont("Monospace");
    howToText->setSize(16);
    howToText->setScrollable(true);
    howToText->setColor(sf::Color::White);
    CMenuNew::Button *button15 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -60), "Back");
    button15->onClick = &b_button15_onClick;
    return true; //Succefully Created the menu!
}
