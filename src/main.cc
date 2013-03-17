#include <iostream>

#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <cmath>

#include <string> 
#include <fstream>


#include "exoo_tabu_search.hh"
#include "exoo_helper.hh"

#include "LocalHistory.hh"
#include "Properties.hh"

using namespace std;
using namespace exoo;

long tick();
void tabu_search_launcher(string filename);

int main(int argc, char *argv[]) {
    
    string properties_file;

    if (argc >= 2) {
        properties_file = string(argv[1]);
    } else {
        properties_file = "exoo_search.properties";
    }

    unsigned int seed = time(NULL); 
    
    srand(seed);

    cout << "[" << __FILE__ << ":" << __LINE__ 
         << "] using seed: " << seed << endl;

    tabu_search_launcher(properties_file);
}

long tick() {

    struct timeval start;

    gettimeofday(&start, NULL);
    return (long)(start.tv_sec*1000 + (int)start.tv_usec/1000);
}


void tabu_search_launcher(string properties_file) {

    Properties properties = Properties::load(properties_file.c_str());
    LocalHistory *tabu = new LocalHistory();
    
    int r                    = properties.get_int("r", 6);
    int s                    = properties.get_int("s", 16);
    int degree               = properties.get_int("degree", 4);
    int diameter             = properties.get_int("diameter", 4);
    int neighbourhood_size   = properties.get_int("neighbourhood_size", 100);
    int maximum_temperature  = properties.get_int("maximum_temperature", 30);
    int change_temp_interval = properties.get_int("change_temp_interval", 30);
    int loops_without_change = properties.get_int("loops_without_change", 20);
    bool use_interlaced      = properties.get_bool("use_interlaced", true);
    bool history_enabled     = properties.get_bool("history_enabled", true);
    string history_file      = properties.get("history_file", "history");

    cout << "_______________________________________________" << endl;
    cout << "Properties" << endl;
    cout << "r        " << r << endl;
    cout << "s        " << s << endl;
    cout << "degree   " << degree  << endl;
    cout << "diameter " << diameter << endl;
    cout << "neighbourhood size    " << neighbourhood_size   << endl;
    cout << "maximimum temperature " << maximum_temperature  << endl;
    cout << "change temp interval  " << change_temp_interval << endl;
    cout << "loops without change  " << loops_without_change << endl;
    cout << "use interlaced        " << use_interlaced  << endl;
    cout << "history enabled       " << history_enabled << endl;
    cout << "history file          " << history_file    << endl;
    cout << "_______________________________________________" << endl;
    
    ofstream history;
    if (history_enabled) history.open(history_file.c_str());

    exoo_matrix **random_matrix = 0;
    cout << "[" << __FILE__ << ":" << __LINE__ 
         << "] generating valid random matrix... " << endl;

    cout << endl;
    while (true) {
        random_matrix = generate_random_matrix(r, s, degree);
        cout << ".";
        if (evaluate_matrix(random_matrix, r, s) < 1000) {
            break;
        } else delete_matrix(random_matrix, r);
    }

    cout << "[done]" << endl;

//    random_matrix = create_modified_exoo_matrix(r, s, degree);

    cout << endl;
    cout << to_string_matrix(random_matrix, r) << endl; 
    cout << "value: " << evaluate_matrix(random_matrix, r, s) << endl;
    cout << endl;
    
    search(tabu, 
           r, 
           s, 
           degree, 
           neighbourhood_size, 
           maximum_temperature, 
           random_matrix, 
           change_temp_interval,
           loops_without_change, 
           diameter,
           use_interlaced,
           history_enabled,
           history);

    delete tabu;    
}
