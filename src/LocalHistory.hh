#ifndef __EXOO_LOCAL_HISTORY__
#define __EXOO_LOCAL_HISTORY__

#include "History.hh"
#include <set>
#include <string>

using namespace std;

namespace exoo {

    class LocalHistory : public History {
    private: 
        set<string> data;

    public:
        LocalHistory();

        virtual ~LocalHistory();

        virtual void append(const string &signature);

        virtual bool exists(const string &signature);
    };
}

#endif
