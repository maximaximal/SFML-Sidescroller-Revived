#include <CMenu.h>
#include <CConfig.h>
#include <Manager/CTextureManager.h>
#include <Manager/CWebManager.h>
#include <Manager/CFontManager.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

void CMenu::loadMenu(int ID)
{
    this->resetMenu();
    if(ID == 0) //Main Menu
    {
        Background->setColor(sf::Color(255, 255, 255, 255));
        sf::Sprite Logo(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(0, 75, 150, 500));
        Logo.setPosition(300, 80);
        Logo.setRotation(90);
        this->Sprites.push_back(Logo);
        sf::Sprite HowTo(CTextureManager::Get()->getTexture("HowTo"));
        HowTo.setPosition(50, 130);
        this->Sprites.push_back(HowTo);
        sf::Text Label_ByMax;
        Label_ByMax.setFont(CFontManager::Get()->getFont("Beeb Mode One"));
        Label_ByMax.setCharacterSize(26);
        Label_ByMax.setString("by maximaximal & ruabmbua");
        Label_ByMax.setPosition(10, CConfig::Get()->getWindowY() - 40);
        Labels.push_back(Label_ByMax);
        if(CWebManager::Get()->getNewestVersion() > CConfig::Get()->getVersion() && CWebManager::Get()->getVersionStatus() == "Download Update")
        {
            MenuButton updateButton;
            updateButton.hover = false;
            updateButton.label.setString("Download Update");
            updateButton.OnClick = &CMenu::OnButtonClick_StartUpdate;
            updateButton.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -60);
            updateButton.ID = 4;
            Buttons.push_back(updateButton);
        }
        updateTextures = true;
        isBig = false;
        CConfig::Get()->setGameState(STATE_MAINMENU);
    }
    if(ID == 1) //Pause Menu
    {
        Background->setColor(sf::Color(255, 255, 255, 230));
        MenuButton Button_QuitGame;
        Button_QuitGame.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120);
        Button_QuitGame.label.setString("Quit Game");
        Button_QuitGame.hover = false;
        Button_QuitGame.OnClick = &CMenu::OnButtonClick_QuitGame;
        this->Buttons.push_back(Button_QuitGame);
        MenuButton Button_BackToGame;
        Button_BackToGame.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -180);
        Button_BackToGame.label.setString("Back to Game");
        Button_BackToGame.hover = false;
        Button_BackToGame.OnClick = &CMenu::OnButtonClick_BackToGame;
        this->Buttons.push_back(Button_BackToGame);
        MenuButton Button_Credits;
        Button_Credits.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -90);
        Button_Credits.label.setString("Credits");
        Button_Credits.hover = false;
        Button_Credits.OnClick = &CMenu::OnButtonClick_Credits;
        this->Buttons.push_back(Button_Credits);
        MenuButton Exit;
        Exit.label.setString("View Highscores");
        Exit.hover = false;
        Exit.OnClick = &CMenu::OnButtonClick_OpenScoreList;
        Exit.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() - 60);
        Buttons.push_back(Exit);
        sf::Sprite Logo(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(0, 75, 150, 500));
        Logo.setRotation(90);
        Logo.setPosition(510, 10);
        this->Sprites.push_back(Logo);
        MenuButton Button_NewGame;
        Button_NewGame.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -150);
        Button_NewGame.label.setString("New Game");
        Button_NewGame.hover = false;
        Button_NewGame.OnClick = &CMenu::OnButtonClick_NewGame;
        this->Buttons.push_back(Button_NewGame);
        updateTextures = true;
        CConfig::Get()->setGameState(STATE_PAUSEMENU);
    }
    if(ID == 2) //Game Over Menu
    {
        submitted = false;
        Background->setColor(sf::Color(255, 0, 0, 255));
        MenuButton Button_QuitGame;
        Button_QuitGame.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -120);
        Button_QuitGame.label.setString("Quit Game");
        Button_QuitGame.hover = false;
        Button_QuitGame.OnClick = &CMenu::OnButtonClick_QuitGame;
        this->Buttons.push_back(Button_QuitGame);
        MenuButton Button_NewGame;
        Button_NewGame.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() -150);
        Button_NewGame.label.setString("New Game");
        Button_NewGame.hover = false;
        Button_NewGame.OnClick = &CMenu::OnButtonClick_NewGame;
        this->Buttons.push_back(Button_NewGame);
        sf::Sprite GameOver(CTextureManager::Get()->getTexture("GuiSheet"), sf::IntRect(150, 0, 450, 75));
        GameOver.setPosition(20, 50);
        this->Sprites.push_back(GameOver);
        sf::Text Score;
        std::stringstream ScoreString;
        ScoreString << "Your Score: " << (int)CConfig::Get()->getHighscore() << std::endl;
        ScoreString << "Level: " << CConfig::Get()->getGameLevel() << std::endl;
        if(!CWebManager::Get()->isConfigValid())
            Score.setColor(sf::Color::Red);
        Score.setString(ScoreString.str());
        Score.setFont(CFontManager::Get()->getFont("Computerfont"));
        Score.setPosition(50, 200);
        Score.setCharacterSize(40);
        this->Labels.push_back(Score);
        updateTextures = true;
        sf::Text Scores("Loading...");
        CWebManager::Get()->web_getScores();
        Scores.setFont(CFontManager::Get()->getFont("Monospace"));
        Scores.setCharacterSize(16);
        Scores.setPosition(50, 350);
        Labels.push_back(Scores);
        sf::Text name;
        name.setCharacterSize(16);
        name.setFont(CFontManager::Get()->getFont("Monospace"));
        name.setPosition(50, 300);
        name.setColor(sf::Color::Red);
        Labels.push_back(name);
        CConfig::Get()->setGameState(STATE_GAMEOVER);
    }
    if(ID == 3) //Credits
    {
        Background->setColor(sf::Color(255, 255, 255, 255));
        std::stringstream CreditsString;
        sf::Text CreditsText;
        using namespace std;
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
        CreditsString << "          the Boost C++ Libraries" << endl << endl;
        CreditsString << "Graphics used:" << endl;
        CreditsString << "          SpaceshipSheet v4 - by gregah on deviantART" << endl;
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
        CreditsText.setString(CreditsString.str());
        CreditsText.setCharacterSize(15);
        CreditsText.setFont(CFontManager::Get()->getFont("Beeb Mode One"));
        CreditsText.setPosition(20, CConfig::Get()->getWindowY());
        Labels.push_back(CreditsText);
        MenuButton Exit;
        Exit.label.setString("Back");
        Exit.hover = false;
        Exit.OnClick = &CMenu::OnButtonClick_Back;
        Exit.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() - 50);
        Buttons.push_back(Exit);
        sf::Sprite srcttpLogo;
        srcttpLogo.setTexture(CTextureManager::Get()->getTexture("GuiSheet"));
        srcttpLogo.setTextureRect(sf::IntRect(150, 130, 200, 200));
        srcttpLogo.setPosition(CConfig::Get()->getWindowX() - 220, 0);
        this->Sprites.push_back(srcttpLogo);
        sf::Sprite sfmlLogo;
        sfmlLogo.setTexture(CTextureManager::Get()->getTexture("GuiSheet"));
        sfmlLogo.setTextureRect(sf::IntRect(350, 130, 149, 90));
        sfmlLogo.setPosition(CConfig::Get()->getWindowX() - 169, 200);
        this->Sprites.push_back(sfmlLogo);
        sf::Sprite austria;
        austria.setTexture(CTextureManager::Get()->getTexture("GuiSheet"));
        austria.setTextureRect(sf::IntRect(350, 220, 152, 121));
        austria.setPosition(CConfig::Get()->getWindowX() - 169, 295);
        this->Sprites.push_back(austria);
        sf::Sprite freeSFX;
        freeSFX.setTexture(CTextureManager::Get()->getTexture("GuiSheet"));
        freeSFX.setTextureRect(sf::IntRect(150, 331, 138, 47));
        freeSFX.setPosition(CConfig::Get()->getWindowX() - 169, 400);
        this->Sprites.push_back(freeSFX);
        updateTextures = true;
        CConfig::Get()->setGameState(STATE_CREDITS);
    }
    if(menuID == 4) //Config Menu
    {
        MenuButton ToggleMusic;
        ToggleMusic.sprite.setPosition(10, 10);
        ToggleMusic.label.setString("Toggle Music");
        ToggleMusic.hover = false;
        Buttons.push_back(ToggleMusic);
        MenuButton ToggleSound;
        ToggleSound.sprite.setPosition(10, 40);
        ToggleSound.label.setString("Toggle Sound");
        ToggleSound.hover = false;
        Buttons.push_back(ToggleSound);
        MenuButton Exit;
        Exit.OnClick = &CMenu::OnButtonClick_Back;
        Exit.hover = false;
        Exit.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() - 50);
        Buttons.push_back(Exit);
        updateTextures = true;
    }
        if(ID == 5) //Scores Menu
    {
        submitted = false;
        Background->setColor(sf::Color(255, 255, 255, 255));
        MenuButton Exit;
        Exit.label.setString("Back");
        Exit.hover = false;
        Exit.OnClick = &CMenu::OnButtonClick_Back;
        Exit.sprite.setPosition(CConfig::Get()->getWindowX() - 200, CConfig::Get()->getWindowY() - 50);
        Buttons.push_back(Exit);
        updateTextures = true;
        sf::Text Scores("Loading...");
        CWebManager::Get()->web_getScores();
        Scores.setFont(CFontManager::Get()->getFont("Monospace"));
        Scores.setCharacterSize(16);
        Scores.setPosition(50, 50);
        Labels.push_back(Scores);
    }
    this->menuID = ID;
}
