#ifndef CWEBMANAGER_H
#define CWEBMANAGER_H
#include <CSingleton.h>
#include <string>
#include <SFML/System.hpp>
class CWebManager : public TSingleton<CWebManager>
{
    public:
        CWebManager();
        virtual ~CWebManager();
        void validateConfig();
        std::string getScores() {return scores;}
        std::string getVersionStatus() {return versionStatus;}
        void web_getScores();
        void web_submitScore();
        void web_getNewestVersion();
        void web_downloadNewestVersion();
        float getNewestVersion() {return newestVersion;}
        void publishScore();
        bool isConfigValid() {return configValid;}
        std::string readFile2(const std::string &filename);
    protected:
    private:
        std::string scores;
        std::string versionStatus;
        float newestVersion;
        sf::Thread *getNewVersionThread;
        sf::Thread *getScoresThread;
        sf::Thread *submitScoreThread;
        bool configValid;
};

#endif // CWEBMANAGER_H
