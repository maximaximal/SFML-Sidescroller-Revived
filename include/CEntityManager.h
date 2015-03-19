#ifndef CENTITYMANAGER_H
#define CENTITYMANAGER_H

#include <CSingleton.h>

class CEntityManager : public TSingleton<CEntityManager>
{
    public:
        CEntityManager();
        virtual ~CEntityManager();
    protected:
    private:
};

#endif // CENTITYMANAGER_H
