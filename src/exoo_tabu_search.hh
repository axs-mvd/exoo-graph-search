#ifndef _EXOO_TABU_SEARCH_
#define _EXOO_TABU_SEARCH_

#include "exoo_helper.hh"
#include "History.hh"
#include <iostream>

namespace exoo {

    void search(History *tabu, 
                const int &r, 
                const int &s, 
                const int &d, 
                const int &k, 
                const int &max_t, 
                exoo_matrix **v, 
                const int &change_t_interval,
                const int &loops_without_change_max,
                const double value_threshold,
                bool use_interlaced,
                bool history_enabled,
                ostream &history_stream); 
   
    bool compare(pair<double, exoo_matrix**> a, pair<double, exoo_matrix**> b);

}








#endif
