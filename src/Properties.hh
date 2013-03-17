#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class Properties {

private:
    map<string, string> data;
    static const int BUFFER_SIZE = 1024;

public:
    Properties() {
    }

    Properties(const Properties &properties) {
        data = properties.data;
    }

    ~Properties() {
    }

    Properties &operator=(const Properties &properties) {
        if (this != &properties) {
            this->data = properties.data;
        }

        return *this;
    }

    static Properties load(string filename) {
        ifstream stream (filename.c_str(), ifstream::in);

        char buffer[BUFFER_SIZE];

        Properties properties;

        while (stream.good()) {

            memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
            stream.getline(buffer, BUFFER_SIZE);
            stringstream sstream;
            string key, value;

            if (buffer[0] != '#') {
                sstream.str(buffer);

                if ((sstream >> key) && (sstream >> value)) {
                    properties.data[key] = value;
                }
            }
        }

        stream.close();

        return properties;
    }

    string get(string key, string default_value = "") {

        if (exists(key)) return data[key];

        else return default_value;

    }

    bool get_bool(string key, bool default_value = true) {

        if (exists(key)) return data[key] == "true";

        else return default_value;

    }

    int get_int(string key, int default_value = 0) {

        if (exists(key)) {

            istringstream sstream;
            sstream.str(data[key]);
            int value;

            sstream >> value;

            return value;

        } else return default_value;
    }

    double get_double(string key, double default_value = 0) {

        if (exists(key)) {

            istringstream sstream;
            sstream.str(data[key]);
            double value;

            sstream >> value;

            return value;

        } else return default_value;
    }

    void put(string key, string value) {
        data[key] = value;
    }

    int length() {
        return (int)data.size();
    }

    vector<string> get_keys() {
        vector<string> keys;
        for (map<string, string>::iterator it = data.begin(); it != data.end(); it++)
            keys.push_back(it->first);

        return keys;
    }

    bool exists(string key) {
        return (data.find(key) != data.end());
    }
};

#endif
