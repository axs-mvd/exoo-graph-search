#ifndef __EXOO_HELPER_HH
#define __EXOO_HELPER_HH
///////////////////////////////////////////////////////////////////////////////
// c library
///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <cmath>
#include <ctime>
///////////////////////////////////////////////////////////////////////////////
// stl 
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// boost
///////////////////////////////////////////////////////////////////////////////
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace exoo {

    typedef vector<int> exoo_matrix;
    typedef adjacency_list<vecS, vecS, undirectedS> exoo_graph;
    typedef exoo_graph::vertex_descriptor Vertex;

//===============================================================================
    exoo_matrix **create_matrix(const int &r);
    exoo_matrix **copy_matrix(exoo_matrix** matrix, const int &r);

    void add_element(exoo_matrix **matrix, const int i, const int j, const int s, const int value);
    
    void remove_element(exoo_matrix **matrix, const int i, const int j, const int s, const int value);
    void remove_element_one_side(exoo_matrix **matrix, const int i, const int j, const int value);
    

    string to_string_matrix(exoo_matrix **matrix, const int &r);

    void change_random_value(exoo_matrix **matrix, 
                        const int &r, 
                        const int &s,
                        const int &d); 

    void randomize_matrix(exoo_matrix **matrix,
                          const int &r,
                          const int &s,
                          const int &d,
                          const int i);

    exoo_matrix ** generate_random_matrix(const int &r, 
                                          const int &s, 
                                          const int &d);

    bool check_matrix(exoo_matrix **matrix, const int &r, const int &s, const int &d);

    void delete_matrix(exoo_matrix **matrix, const int &r);

    string matrix_signature(exoo_matrix **matrix, const int &r);

//===============================================================================
    exoo_graph translate(vector<int> **m, const int &r, const int &s);

    pair<int, int> compute_diameters(const exoo_graph &, const int &vertex_count, const vector<int> &agents); 
    pair<int, int> compute_diameters(const exoo_graph &, const int &vertex_count); 

    double evaluate_matrix(exoo_matrix **matrix, const int &r, const int &s);
     

    int get_random(const int &limit);
    bool flip();
    bool flip(double prob);

//===============================================================================
    //unstable section (uo-o)
    
    void perturb_matrix(exoo_matrix **matrix, const int &r, const int &s, const int &d);
    
    void perturb_matrix_interlaced(exoo_matrix **matrix, const int &r, const int &s, const int &d);

    int degree(exoo_matrix **matrix, const int &r, const int s, const int i);

    void select_random_edge(exoo_matrix **matrix, const int &r, int &i, int &j, int &value);

    vector<vector<int> > get_list(exoo_matrix **matrix, const int &r);

    void put_list(exoo_matrix **matrix, const int &r, const int &s, 
            const int &d, vector<vector<int> > &list); 

    void perturb_list(vector<vector<int> > &list, const int &s);
//===============================================================================
}

#endif
