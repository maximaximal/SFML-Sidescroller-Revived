#ifndef CSINGLETON_INCLUDED
#define CSINGLETON_INCLUDED

template <class T_DERIVED>
class TSingleton
{
    public:
        inline static T_DERIVED* Get()
        {
            if(pInstance)
            {
                return pInstance;
            }

            pInstance = new T_DERIVED;
            return pInstance;
        }
        void destroy()
        {
            if(pInstance)
            {
                pInstance = 0;
                delete pInstance;
            }
        }
        void altDestroy()
        {
            if(pInstance)
            {
                pInstance = 0;
                delete pInstance;
            }
        }

    private:
        static T_DERIVED *pInstance;
};

template <class T>
T* TSingleton<T>::pInstance = 0;

// From Wikipedia; http://de.wikipedia.org/wiki/Singleton_%28Entwurfsmuster%29
//
// Verwendung
//   class CMySingleton : public CSingleton< CMySingleton >
//   {
//      friend class CSingleton< CMySingleton >;
//
//      private:
//         CMySingleton(){}
//
//      //...
//   };

#endif // CSINGLETON_INCLUDED
