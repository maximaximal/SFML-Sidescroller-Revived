#include "Manager/CWebManager.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <iostream>
#include <CConfig.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <MD5/hashlibpp.h>
CWebManager::CWebManager()
{
    this->configValid = false;
    this->scores = "Loading...";
    this->versionStatus = "Download Update";
    this->getNewVersionThread = NULL;
    this->getScoresThread = NULL;
    this->submitScoreThread = NULL;
}
CWebManager::~CWebManager()
{
    if(this->getNewVersionThread)
    {
        this->getNewVersionThread->wait();
        delete getNewVersionThread;
        this->getNewVersionThread = NULL;
    }
    if(this->getScoresThread)
    {
        this->getScoresThread->wait();
        delete this->getScoresThread;
        this->getScoresThread = NULL;
    }
    if(this->submitScoreThread)
    {
        this->submitScoreThread->wait();
        delete this->submitScoreThread;
        this->submitScoreThread = NULL;
    }
}
using namespace std;
string CWebManager::readFile2(const string &fileName)
{
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);

    return string(&bytes[0], fileSize);
}

void CWebManager::validateConfig()
{
    using namespace std;
    sf::Http http;
    http.setHost("http://update.srcttp.org");
    std::stringstream HostStream;
    std::stringstream md5stream;
    md5stream << "MD5-VALIDATOR http://update.srcttp.org/SFML-Sidescroller/validate.php" << endl;
    md5stream << CConfig::Get()->getShootRate() << CConfig::Get()->getNormalMoveForce() << CConfig::Get()->getShiftMoveForce() << CConfig::Get()->getQuickMoveForce();
    md5stream << CConfig::Get()->getStartLaser() << CConfig::Get()->getStartLaserLevel();
    md5stream << CConfig::Get()->getVersion();
    md5stream << this->readFile2(CConfig::Get()->getDataDir() + "/Data/Script/fixtures.lua");
    hashwrapper *h = new md5wrapper();
	h->test();
	std::string md5 = h->getHashFromString(md5stream.str());
	delete h;
	HostStream << "SFML-Sidescroller/validate.php?md5=";
    HostStream << md5;
    sf::Http::Request HTTPRequest(HostStream.str());
    sf::Http::Response Response = http.sendRequest(HTTPRequest);
    cout << "Validator Hash: " << md5;
    if(Response.getStatus() == sf::Http::Response::Ok)
    {
        if(Response.getBody() == "valid")
            this->configValid = true;
        else
            this->configValid = false;
    }
    else
        this->configValid = false;
    if (configValid)
        cout << " - Validated!" << endl;
    else
        cout << " - Invalid!" << endl;
}
void getScoresThreadFunction(std::string *scores)
{
    using namespace std;
    *scores = "Loading...";
    sf::Http http;
    http.setHost("http://update.srcttp.org");
    sf::Http::Request request("SFML-Sidescroller/getScore.php");
    sf::Http::Response Response = http.sendRequest(request);
    if(Response.getStatus() == sf::Http::Response::Ok)
    {
        *scores = Response.getBody();
        cout << "Get the global highsores succefully!" << endl;
    }
    else
    {
        *scores = "Failed at requesting the scores";
        cout << "Cannot get the global highscores" << endl;
    }
}
void CWebManager::web_getScores()
{
    if(this->getScoresThread)
    {
        getScoresThread->terminate();
        delete this->getScoresThread;
        this->getScoresThread = NULL;
    }
    this->getScoresThread = new sf::Thread(&getScoresThreadFunction, &scores);
    getScoresThread->launch();
}

void submitScoreThreadFunction(std::string *scores)
{
    *scores = "Generating the hash...";
    using namespace std;
    sf::Http http;
    http.setHost("http://update.srcttp.org");
    stringstream stream;
    std::stringstream md5stream;
    md5stream << "MD5-VALIDATOR http://update.srcttp.org/SFML-Sidescroller/validate.php" << endl;
    md5stream << CConfig::Get()->getShootRate() << CConfig::Get()->getNormalMoveForce() << CConfig::Get()->getShiftMoveForce() << CConfig::Get()->getQuickMoveForce();
    md5stream << CConfig::Get()->getStartLaser() << CConfig::Get()->getStartLaserLevel();
    md5stream << CConfig::Get()->getVersion();
    md5stream << CWebManager::Get()->readFile2(CConfig::Get()->getDataDir() + "/Data/Script/fixtures.lua");
    hashwrapper *h = new md5wrapper();
	h->test();
	std::string md5 = h->getHashFromString(md5stream.str());
	delete h;
    stream << "SFML-Sidescroller/publishScore.php?md5=";
    stream << md5;
    stream << "&score=";
    stream << (int) CConfig::Get()->getHighscore();
    stream << "&v=";
    stream << CConfig::Get()->getVersion();
    stream << "&time=";
    stream << (int) CConfig::Get()->getGameTime();
    stream << "&name=";
    stream << CConfig::Get()->getNickname();
    *scores = "Submitting the score...";
    sf::Http::Request request(stream.str());
    sf::Http::Response Response = http.sendRequest(request);
    if(Response.getStatus() == sf::Http::Response::Ok)
    {
        *scores = Response.getBody();
        cout << "Submitted Score Succefully!" << endl;
    }
    else
    {
        *scores = "Failed at submitting the score...";
        cout << "Cannot publish the highscore!" << endl;
    }
}
void CWebManager::web_submitScore()
{
    if(this->submitScoreThread)
    {
        this->submitScoreThread->wait();
        delete this->submitScoreThread;
        this->submitScoreThread = NULL;
    }
    this->submitScoreThread = new sf::Thread(&submitScoreThreadFunction, &scores);
    submitScoreThread->launch();
}
void CWebManager::web_getNewestVersion()
{
    using namespace std;
    sf::Http http;
    http.setHost("http://update.srcttp.org");
    stringstream hoststream;
    hoststream << "SFML-Sidescroller/version_";
    if(CConfig::Get()->getOS() == OS_WINDOWS)
        hoststream << "win";
    if(CConfig::Get()->getOS() == OS_LINUX64)
        hoststream << "linux64";
    if(CConfig::Get()->getOS() == OS_LINUX32)
        hoststream << "linux32";
    sf::Http::Request request(hoststream.str());
    sf::Http::Response Response = http.sendRequest(request);
    if(Response.getStatus() == sf::Http::Response::Ok)
    {
        stringstream version;
        version << Response.getBody();
        version >> this->newestVersion;
        cout << "Get the newest Version for ";
        if(CConfig::Get()->getOS() == OS_WINDOWS)
            cout << "Windows";
        if(CConfig::Get()->getOS() == OS_LINUX64)
            cout << "Linux64";
        if(CConfig::Get()->getOS() == OS_LINUX32)
            cout << "Linux32";
        cout << " succefully: " << this->newestVersion << endl;
    }
    else
    {
        this->newestVersion = CConfig::Get()->getVersion();
        cout << "!! Cannot get the newest version..." << endl;
    }
}
void downloadNewVersionThread(std::string *versionStatus)
{
    using namespace std;
    sf::Http http;
    http.setHost("http://update.srcttp.org");
    stringstream hoststream;
    hoststream << "SFML-Sidescroller/update/V";
    hoststream << CWebManager::Get()->getNewestVersion() << "_";
    if(CConfig::Get()->getOS() == OS_WINDOWS)
        hoststream << "win.zip";
    if(CConfig::Get()->getOS() == OS_LINUX64)
        hoststream << "linux64.tar.gz";
    if(CConfig::Get()->getOS() == OS_LINUX32)
        hoststream << "linux32.tar.gz";
    sf::Http::Request request(hoststream.str());
    *versionStatus = "~ Downloading ~";
    sf::Http::Response Response = http.sendRequest(request);
    if(Response.getStatus() == sf::Http::Response::Ok)
    {
        stringstream filepath;
        filepath << "update_";
        if(CConfig::Get()->getOS() == OS_WINDOWS)
            filepath << "win.zip";
        if(CConfig::Get()->getOS() == OS_LINUX64)
            filepath << "linux64.tar.gz";
        if(CConfig::Get()->getOS() == OS_LINUX32)
            filepath << "linux32.tar.gz";
        ofstream file(filepath.str(), ofstream::binary);
        *versionStatus = "~ Saving ~";
        file << Response.getBody();
        file.close();
        cout << "Saved!" << " - Saved to file: " << filepath.str() << endl;
        *versionStatus = "~ Wait ~";
        if(CConfig::Get()->getOS() == OS_WINDOWS)
        {
            sf::sleep(sf::seconds(1));
            *versionStatus = "~ Installing ~";
            system("start Data\\Libraries_win32\\windows_update.bat");
            CConfig::Get()->quitGame();
        }
    }
    else
    {
        cout << "!! Cannot download the file!" << endl;
        *versionStatus = "CANNOT DOWNLOAD";
    }
}
void CWebManager::web_downloadNewestVersion()
{
    this->versionStatus = "Initializing...";
    this->getNewVersionThread = new sf::Thread(&downloadNewVersionThread, &versionStatus);
    getNewVersionThread->launch();
}
