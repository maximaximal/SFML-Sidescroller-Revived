#include <CMenu/Load.h>
#include <CMenu/CContainerManager.h>
#include <CMenu/Button.h>
#include <CConfig.h>
#include <sstream>
using namespace CMenuNew;
using namespace std;

CContainerManager *Manager4;


void b_Back2_onClick()
{
    CConfig::Get()->load();
    Manager4->historyBack();
}
void s_Slider1_onChange(float percent)
{
    CConfig::Get()->setBackgroundMusicVolume((int) percent);
}
void s_Slider2_onChange(float percent)
{
    CConfig::Get()->setSoundVolume((int) percent);
}
void b_button14_onClick()
{
    CConfig::Get()->writeToScript();
    Manager4->historyBack();
}
bool Load::Config()
{
    manager->clearMenu();
    Manager4 = manager;
    HistoryEntry *Entry = new HistoryEntry();
    Entry->load = &Load::Config;
    Entry->name = "Config";
    manager->addToHistory(Entry);
    CMenuNew::Button *button14 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -50), "Save & Back");
    button14->onClick = &b_button14_onClick;
    CMenuNew::Button *Back2 =  manager->newButton(sf::Vector2i(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -80), "Cancel");
    Back2->onClick = &b_Back2_onClick;
    //BackgroundMusicVolume Slider
        CMenuNew::Slider *slider1 = manager->newSlider(sf::Vector2f(60, 50), 300); //Background Volume
        CMenuNew::Text *label1 = manager->newText(sf::Vector2f(40, 32), "Background-Music-Volume");
        label1->setFont("Monospace");
        label1->setSize(16);
        slider1->onChange = &s_Slider1_onChange;
        slider1->setPercent(CConfig::Get()->getBackgroundMusicVolume());
    //SoundVolume Slider
        CMenuNew::Slider *slider2 = manager->newSlider(sf::Vector2f(60, 80), 300); //Background Volume
        CMenuNew::Text *label2 = manager->newText(sf::Vector2f(40, 62), "Sound-Volume");
        label2->setFont("Monospace");
        label2->setSize(16);
        slider2->onChange = &s_Slider2_onChange;
        slider2->setPercent(CConfig::Get()->getSoundVolume());
    return true; //Succefully Created the menu!
}
