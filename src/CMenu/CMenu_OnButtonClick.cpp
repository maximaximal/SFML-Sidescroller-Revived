#include <CMenu.h>
#include <CConfig.h>
#include <Manager/CTextureManager.h>
#include <Manager/CWebManager.h>
#include <Manager/CFontManager.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>


void CMenu::OnButtonClick_QuitGame()
{
    CConfig::Get()->quitGame();
}
void CMenu::OnButtonClick_Back()
{
    this->loadMenu(this->lastMenuID);
}
void CMenu::OnButtonClick_BackToGame()
{
    CConfig::Get()->setGameState(STATE_GAME);
    this->resetMenu();
}
void CMenu::OnButtonClick_NewGame()
{
    CConfig::Get()->setGameState(4);
}
void CMenu::OnButtonClick_Credits()
{
    this->loadMenu(3);
}
void CMenu::OnButtonClick_StartUpdate()
{
    using namespace std;
    this->locked = true;
    CWebManager::Get()->web_downloadNewestVersion();
    stringstream HowToStr;
    HowToStr << "HOW TO UPDATE" << endl;
    HowToStr << "=============" << endl;
    HowToStr << "   1. Wait for the download to complete. This" << endl;
    HowToStr << "      may take a few minutes. You cannot click" << endl;
    HowToStr << "      on buttons while downloading (they are locked)." << endl;
    HowToStr << "   2. Go to your game folder (there where your exe is)" << endl;
    HowToStr << "   3. Extract the downloaded file right into this" << endl;
    HowToStr << "      folder. Exit the game first!" << endl;
    HowToStr << "      (on Windows, right click on the update_XXXX_win.zip and" << endl;
    HowToStr << "      select \"extract here\"" << endl;
    HowToStr << "   4. Delete the downloaded file." << endl;
    HowToStr << "   5. Play the game!" << endl;
    sf::Text HowTo(HowToStr.str());
    HowTo.setFont(CFontManager::Get()->getFont("Monospace"));
    HowTo.setPosition(20, 150);
    HowTo.setCharacterSize(16);
    this->Labels.push_back(HowTo);
}
void CMenu::OnButtonClick_OpenScoreList()
{
    this->loadMenu(5);
}
