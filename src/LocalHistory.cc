#include "LocalHistory.hh"

namespace exoo {

    LocalHistory::LocalHistory() {
    }

    LocalHistory::~LocalHistory() {
    }

    void LocalHistory::append(const string &signature) {
        data.insert(signature);
    }

    bool LocalHistory::exists(const string &signature) {
        return data.find(signature) != data.end();
    }
}


