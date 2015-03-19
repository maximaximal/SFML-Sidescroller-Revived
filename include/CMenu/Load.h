#ifndef LOAD_H
#define LOAD_H

#include <CMenu/CContainerManager.h>

namespace CMenuNew
{
    class Load
    {
        public:
            Load(CContainerManager *manager);
            CContainerManager *manager;
            virtual ~Load();

            //Menus
                bool MainMenu();
                bool Credits();
                bool PauseMenu();
                bool ViewHighscores();
                bool GameOver();
                bool Config();
                bool HowTo();
        protected:
        private:
    };
}
#endif // LOAD_H
