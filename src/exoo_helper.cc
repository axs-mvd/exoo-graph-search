#include "exoo_helper.hh"

using namespace exoo;
//=============================================================================== 
exoo_matrix **exoo::create_matrix(const int &r) {
    exoo_matrix **matrix = new exoo_matrix*[r];
    for (int i = 0; i < r; i++) matrix[i] = new exoo_matrix[r];
    
    return matrix;
}

//===============================================================================

exoo_matrix **exoo::copy_matrix(exoo_matrix **matrix, const int &r) {
    exoo_matrix **copy = create_matrix(r);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            vector<int> &vec = matrix[i][j];
            for (int k = 0; k < (int) vec.size(); k++) {
                copy[i][j].push_back(vec[k]);
            }
            std::sort(copy[i][j].begin(), copy[i][j].end());
        }
    }
    
    return copy;
}

//===============================================================================

void exoo::delete_matrix(exoo_matrix **matrix, const int &r) {
    for (int i = 0; i < r; i++) delete [] matrix[i];
    delete [] matrix;
}

//===============================================================================

bool exoo::check_matrix(exoo_matrix **matrix, const int &r, const int &s, const int &d) {
    for (int i = 0; i < r; i++) {
        int count = 0;
        for (int j = 0; j < r; j++) {
            std::vector<int> &vec = matrix[i][j];
            count += vec.size();
            for (int k = 0; k < (int) vec.size(); k++) {

                int value = vec[k];
                std::vector<int> &vec_complement = matrix[j][i];

                if (i != j && std::find(vec_complement.begin(), 
                    vec_complement.end(), (s - value) % s) == vec_complement.end()) {

                    std::cout << "[exoo::check_matrix] error: there is no complement for " 
                              << value << " in " << i << ", " << j << std::endl;
                
                    std::cout << to_string_matrix(matrix, r) << std::endl;

                    return false;
                }
            }
        }

        if (degree(matrix, r, s, i) > d) {
            //std::cout << "[exoo:check_matrix] error: the vertex " << i << " has illegal degree: " << degree(matrix, r, s, i) << std::endl;
            return false;
        }
    }

    return true;
}

//===============================================================================

void create_edges(exoo_graph &graph, 
                  const int &s, 
                  const int &i, 
                  const int &j, 
                  const int &k) {


    for (int x = 0;  x < s; x ++) {
        int v_1, v_2;

        v_1 = x % s + s * i;
        v_2 = (x + k) % s + s * j;


        std::pair<exoo_graph::adjacency_iterator, exoo_graph::adjacency_iterator> 
            iter = boost::adjacent_vertices(v_1, graph);

        if (std::find(iter.first, iter.second, v_2) == iter.second) {
            boost::add_edge(v_1, v_2, graph);
        }
    }
}

//===============================================================================

exoo_graph exoo::translate(std::vector<int> **m, const int &r, const int &s) {
    exoo_graph graph(r * s);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if (i <= j) { 
                std::vector<int> &ij = m[i][j]; 
                for (int k = 0; k < (int)(ij.size()); k++) {
                    create_edges(graph, s, i, j, ij[k]);
                }
            }
        }
    }

    return graph;
}

double exoo::evaluate_matrix(exoo_matrix **matrix, const int &r, const int &s) {
    vector<int> agents;
    for (int agent = 0; agent < r*s; agent += s) { 
        agents.push_back(agent);
    }

    pair<int, int> p = compute_diameters(translate(matrix, r, s), r*s, agents);
    return (double)p.first + ((double)p.second)/10000; 
}


//===============================================================================
std::pair<int, int> exoo::compute_diameters(const exoo_graph &graph, 
                                            const int &vertex_count) {

    vector<int> agents;

    for (int i = 0; i < vertex_count; i++) agents.push_back(i);

    return compute_diameters(graph, vertex_count, agents);
}

 
std::pair<int, int> exoo::compute_diameters(const exoo_graph &graph, 
                                            const int &vertex_count,
                                            const vector<int> &agents) {

    int diameter_size = 0;
    int diameter_count = 0;
    int distance[vertex_count];

    
//    for (int source_vertex = 0; source_vertex < vertex_count; source_vertex++) {
    for (vector<int>::const_iterator it = agents.begin();  it != agents.end(); it++) {
        int source_vertex =  *it;

        std::fill_n(distance, vertex_count, std::numeric_limits<int>::max());        
        distance[source_vertex] = 0;

        boost::breadth_first_search(graph, source_vertex, 
               boost::visitor(boost::make_bfs_visitor(
                              boost::record_distances(distance, boost::on_tree_edge())
                              )
               )
        );
        
        for (int i = 0; i < vertex_count; i++) {

            if (diameter_size < distance[i]) {

                diameter_size = distance[i];
                diameter_count = 1;

            } else if (diameter_size == distance[i]) {

                diameter_count++;

            }   
        }
    }

    return std::make_pair(diameter_size, diameter_count);
}

//===============================================================================

int exoo::get_random(const int &limit) {

    if (limit == 0) return 0;

    const float scale = rand()/float(RAND_MAX);

    int value = int(scale*limit);

    if (value == limit) return value -1;
    else return value;
}

bool exoo::flip() {
    return get_random(2) == 1;
}

bool exoo::flip(double prob) {
    return rand()/float(RAND_MAX) < prob;
}

//===============================================================================

std::string exoo::to_string_matrix(exoo_matrix **matrix, const int &r) {
    std::ostringstream stream;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            std::vector<int> vec = matrix[i][j];
            stream << "[ ";
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
                stream << *it << " ";
            }
            stream << "]";
        }
        stream << std::endl;
    }
    
    return stream.str();
}

//===============================================================================

void exoo::add_element(exoo_matrix **matrix, const int i, const int j, const int s, const int value) {
    std::vector<int> &vec = matrix[i][j]; 
    vec.push_back(value);
    std::sort(vec.begin(), vec.end());
    if (i != j) {
        std::vector<int> &vec_complement = matrix[j][i];
        vec_complement.push_back((s - value) %s);
        std::sort(vec_complement.begin(), vec_complement.end());
    }
}

void exoo::remove_element_one_side(exoo_matrix **matrix, const int i, const int j, const int value) {
    std::vector<int> &vec = matrix[i][j]; 
    vector<int>::iterator it = find(vec.begin(), vec.end(), value);
    if (it != vec.end()) vec.erase(it);
    else cout << "[" << __FILE__ << ":" <<  __LINE__ << "]" << 
             "could not find value: " << value;
 
    std::sort(vec.begin(), vec.end());
}

void exoo::remove_element(exoo_matrix **matrix, const int i, const int j, const int s, const int value) {
   
    remove_element_one_side(matrix, i, j, value);
    if (i != j) remove_element_one_side(matrix, j, i, (s - value) % s);
    
}

void exoo::change_random_value(exoo_matrix **matrix, 
                               const int &r, 
                               const int &s,
                               const int &d) {

    int i = get_random(r);
    int k_random = get_random(d);

    for (int j = 0; j < r; j++) {
        std::vector<int> &vec = matrix[i][j];
        for (int k = 0; k < (int)vec.size(); k++) {
            k_random--;
            if (k_random <= 0) {
                int value = vec[k];
                vec.erase(vec.begin() + k);
                if (i != j) {
                    std::vector<int> &vec_complement = matrix[j][i];
                    vec_complement.erase(std::find(vec_complement.begin(), vec_complement.end(), (s - value) %s));
                }
                
                int new_value = -1;
                while (std::find(vec.begin(), vec.end(), new_value) != vec.end()) new_value = get_random(s);
                
                add_element(matrix, i, j, s, new_value);
            }
        }
    } 
}


//===============================================================================

int count_elements_in_row(exoo_matrix **matrix, const int &r, const int i) {
    
    int count = 0;

    for (int j = 0; j < r; j++) count += (int) matrix[i][j].size();

    return count;
}

void exoo::randomize_matrix(exoo_matrix **matrix,
                            const int &r,
                            const int &s,
                            const int &d,
                            const int i_start) {

    bool matching_valid = s % 2 == 0;
    for (int i = i_start; i < r; i ++) {

        while (degree(matrix, r, s, i) < d) {
            int j = -1; 
            
            bool ok = false;
            int new_value = -1;

            int retry = 0;
            while (!ok && retry < 100) {

                j = i + get_random(r - i);

                int places = d - degree(matrix, r, s, j);

                retry++;

                if (places >= 1) {
                    new_value = get_random(s);
                    if (i != j) {
                        ok = true;
                    } else {
                        if (places >= 2) ok = true;
                        else if (matching_valid) {
                            new_value = s/2;
                            ok = true;
                        }
                    }
                }
            }

            std::vector<int> &vec = matrix[i][j];

            while (std::find(vec.begin(), vec.end(), new_value) != vec.end()) new_value = get_random(s);
            
            add_element(matrix, i, j, s, new_value); 
 
        }    
    }
}


exoo_matrix ** exoo::generate_random_matrix(const int &r, 
                                            const int &s, 
                                            const int &d) {
    
    exoo_matrix ** matrix = create_matrix(r);
    randomize_matrix(matrix, r, s, d, 0);
    return matrix;
}



/**
 * firma de la matriz es un string que tiene la posicion y los valores que estan en el vector
 * de la posición. 
 */
std::string exoo::matrix_signature(exoo_matrix **matrix, const int &r) {
    std::ostringstream stream;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            std::vector<int> &vec = matrix[i][j];
            if (!vec.empty()) {
                stream << "[" << i << "," << j << "] ";
                for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) 
                    stream << *it << " ";
            }
        }
    }
    
    return stream.str();

}

//===============================================================================

vector<vector<int> > exoo::get_list(exoo_matrix **matrix, const int &r) {
    vector<vector<int> > list;

    for (int i = 0; i < r; i++) {
        for (int j = i; j < r; j++) {
            vector<int> vec;
            for (int k = 0; k < (int) matrix[i][j].size(); k++) {
                vec.push_back(matrix[i][j][k]);
            } 
            list.push_back(vec);
        }   
    }
    
    return list;
}

void exoo::put_list(exoo_matrix **matrix, const int &r, const int &s, 
                                   const int &d, vector<vector<int> > &list) {

    vector<vector<int> >::iterator iter = list.begin();

    for (int i = 0; i < r && iter != list.end(); i++) {
        for (int j = i; j < r && iter != list.end(); j++) {
            vector<int> &vec = *iter;
            for (vector<int>::iterator k = vec.begin(); k != vec.end(); k++){
                int places = d - degree(matrix, r, s, i);
                if (places > 0) {
                    if (i != j) {
                        add_element(matrix, i, j, s, *k);
                    } else {
                        if (places == 1) {
                            add_element(matrix, i, j, s, s/2);   
                        } else if (places >= 2) {
                            add_element(matrix, i, j, s, *k);
                        }
                    }
                }
            } 
            iter++;
        }

        while (degree(matrix, r, s, i) < d) {
            int j = get_random(r-i-1);
            int value = get_random(s);
            if (i != j + i) add_element(matrix, i, j+i, s, value);
            else {
                int places = d - degree(matrix, r, s, i);
                if (places == 1) {
                    if (find(matrix[i][i].begin(), matrix[i][i].end(), s/2) != matrix[i][i].end()) {
                        break;
                    }

                    add_element(matrix, i, j+i, s, s/2);
                } else if (places >= 2){
                    add_element(matrix, i, j+i, s, value);
                }
            }
        } 
    }
}

void exoo::perturb_list(vector<vector<int> > &list, const int &s) {
    int count = 0;
    for (int i = 0; i < (int) list.size(); i++) count += (int)list[i].size();

    int position = get_random(count);
    bool change_value = flip();

    for (int i = 0; i < (int) list.size(); i++) {
        for (int j = 0; position > 0 && j < (int) list[i].size(); j++) {

            if (position == 1) {
                int value = list[i][j];
                list[i].erase(list[i].begin()+j);
                if (change_value) list[i].push_back(get_random(s));

                else {
                    int p = get_random((int)list.size());
                    list[p].push_back(value);
                }
            }

            position--;
       }
    }
}

void exoo::perturb_matrix(exoo_matrix **matrix, const int &r, 
                                    const int &s, const int &d) {

    vector<vector<int> > list = get_list(matrix, r);

    perturb_list(list, s);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < r; j++)
            matrix[i][j].clear();

    put_list(matrix, r, s, d, list); 
}

void exoo::select_random_edge(exoo_matrix **matrix, const int &r, int &i, int &j, int &value) {
     i = get_random(r);

    int count = 0;
    for (int k = 0; k < r; k++) count+= (int)matrix[i][k].size();

    int position = get_random(count) + 1;
    
    bool out = false;
    for (int k = 0; k < r && !out; k++) {
        for (int l = 0; l < (int)matrix[i][k].size() && !out; l++) {
            position--;
            if (position == 0) {
                j = k;
                if (i > j) {
                    int temp = j; 
                    j = i;
                    i = temp;
                }

                value = matrix[i][j][l];
                out = true;
            }
        }
    }

}

void exoo::perturb_matrix_interlaced(exoo_matrix **matrix, const int &r, 
                                    const int &s, const int &d) {

    int i1, j1, value1;
    int i2, j2, value2;

    i1 = j1 = value1 = -1;
    i2 = j2 = value2 = -1;

    bool change_value = flip(0.8);

    select_random_edge(matrix, r, i1, j1, value1);


    if (change_value) {
        remove_element(matrix, i1, j1, s, value1);
        add_element(matrix, i1, j1, s, (value1 + 1) % s);
    } else {

        select_random_edge(matrix, r, i2, j2, value2);
        
        while (i1 == i2 && j1 == j2 && value1 == value2) 
            select_random_edge(matrix, r, i2, j2, value2);

        
        remove_element(matrix, i1, j1, s, value1); 
        remove_element(matrix, i2, j2, s, value2); 

        add_element(matrix, i1, j2, s, value1);
        add_element(matrix, i2, j1, s, value2);

    }
}

int exoo::degree(exoo_matrix **matrix, const int &r, const int s, const int i) {
    int degree = 0;

    bool matching_valid = s % 2 == 0;

    for (int j= 0; j < r; j++) {
        vector<int> &vec = matrix[i][j];
        for (int k = 0; k < (int)vec.size(); k++) {
            int value = vec[k];
            //bool complement_found = (find(vec.begin() + k + 1, vec.end(), (s - value) % s) != vec.end());
            bool value_found      = (find(vec.begin() + k + 1, vec.end(), value) != vec.end());

            if (!value_found) {
                if (i != j) degree++;
                else {
                    bool complement_found = (find(vec.begin() + k + 1, vec.end(), (s - value) % s) != vec.end());
                    if (!complement_found) {
                        if (matching_valid && value == s/2) {
                            degree++;
                        } else degree+=2;
                    }
                }
            }
        }
    }
    return degree;
}

