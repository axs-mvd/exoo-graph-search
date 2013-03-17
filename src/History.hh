#ifndef __EXOO_HISTORY_
#define __EXOO_HISTORY_

#include <string>

using namespace std;


namespace exoo {

    class History {

    public:
        History() {};
        virtual ~History() {};
        virtual void append(const string &signature) = 0;
        virtual bool exists(const string &signature) = 0;
    };
}

#endif
