#include "exoo_helper.hh"

#include <cstdlib>
#include <ctime>

#include <sys/time.h>
#include <cmath>

using namespace std;
using namespace exoo;

void test_generate_random_matrix();
void test_evaluate_matrix();
void test_evaluate_matrix2();
void test_perturb();
void test_move_value();
long tick();

int main() {
    srand(time(NULL));
//    test_evaluate_matrix2();
    test_perturb();
//    test_move_value();

}

long tick() {

    struct timeval start;

    gettimeofday(&start, NULL);

    return (long)(start.tv_sec*1000 + (int)start.tv_usec/1000);
}

void test_evaluate_matrix2() {
    int r = 6, s = 16, d = 4;

//    int vertex_count = r*s;
    exoo::exoo_matrix **matrix = exoo::create_matrix(r);
    
//###############################
    matrix[0][1].push_back(8);
    matrix[0][2].push_back(1);
    matrix[0][3].push_back(8);
    matrix[0][4].push_back(3);
    matrix[0][4].push_back(13);

//###############################
    matrix[1][0].push_back(8);
    matrix[1][2].push_back(6);
    matrix[1][2].push_back(10);
    matrix[1][3].push_back(10);
    matrix[1][3].push_back(12);
    
//###############################
    matrix[2][0].push_back(15);
    matrix[2][1].push_back(10);
    matrix[2][1].push_back(6);
    matrix[2][2].push_back(8);
    matrix[2][4].push_back(14);
//###############################
    matrix[3][0].push_back(8);
    matrix[3][1].push_back(4);
    matrix[3][1].push_back(6);
    matrix[3][4].push_back(7);

//###############################
    matrix[4][0].push_back(3);
    matrix[4][0].push_back(13);
    matrix[4][2].push_back(2);
    matrix[4][3].push_back(9);
    matrix[4][5].push_back(5);

//###############################
    matrix[5][4].push_back(11);
    matrix[5][5].push_back(8);
    matrix[5][5].push_back(9);
    

//###############################
    std::cout << "checking matrix...";
    bool check = exoo::check_matrix(matrix, r, s, d);
    if (check) std::cout << "[ok]" << std::endl;
    else std::cout << "[fail]" << std::endl;

    std::cout << "________________________________________" << std::endl;
    std::cout << exoo::to_string_matrix(matrix, r) << std::endl << std::endl;
    std::cout << "value: " << evaluate_matrix(matrix, r, s) << std::endl;
    std::cout << "________________________________________" << std::endl;
}




void test_evaluate_matrix() {
    int r = 6, s = 16, d = 4;

//    int vertex_count = r*s;
    exoo::exoo_matrix **matrix = exoo::create_matrix(r);
    
//###############################
    matrix[0][1].push_back(8);
    matrix[0][3].push_back(9);
    matrix[0][4].push_back(3);
    matrix[0][5].push_back(8);

//###############################
    matrix[1][0].push_back(8);
    matrix[1][2].push_back(4);
    matrix[1][2].push_back(11);
    matrix[1][3].push_back(15);
    
//###############################
    matrix[2][1].push_back(5);
    matrix[2][1].push_back(12);
    
    matrix[2][5].push_back(0);
    matrix[2][5].push_back(15);
//###############################
    matrix[3][0].push_back(7);
    matrix[3][1].push_back(1);
    matrix[3][4].push_back(9);
    matrix[3][5].push_back(7);

//###############################
    matrix[4][0].push_back(13);
    matrix[4][3].push_back(7);
    matrix[4][4].push_back(6);
    matrix[4][4].push_back(10);

//###############################
    matrix[5][0].push_back(8);
    matrix[5][2].push_back(0);
    matrix[5][2].push_back(1);
    
    matrix[5][3].push_back(9);

//###############################
    std::cout << "checking matrix...";
    bool check = exoo::check_matrix(matrix, r, s, d);
    if (check) std::cout << "[ok]" << std::endl;
    else std::cout << std::endl;

    std::cout << "________________________________________" << std::endl;
    std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
    std::cout << "________________________________________" << std::endl;
    std::cout << "________________________________________" << std::endl;
    std::cout << "value: " << evaluate_matrix(matrix, r, s) << std::endl;
    std::cout << "________________________________________" << std::endl;
}


void test_move_value() {
    int r = 6, s = 16, d = 4;

//    int vertex_count = r*s;
    exoo::exoo_matrix **matrix = exoo::create_matrix(r);
    
//###############################
    matrix[0][1].push_back(8);
    matrix[0][3].push_back(9);
    matrix[0][4].push_back(3);
    matrix[0][5].push_back(8);

//###############################
    matrix[1][0].push_back(8);
    matrix[1][2].push_back(4);
    matrix[1][2].push_back(11);
    matrix[1][3].push_back(15);
    
//###############################
    matrix[2][1].push_back(5);
    matrix[2][1].push_back(12);
    
    matrix[2][5].push_back(0);
    matrix[2][5].push_back(15);
//###############################
    matrix[3][0].push_back(7);
    matrix[3][1].push_back(1);
    matrix[3][4].push_back(9);
    matrix[3][5].push_back(7);

//###############################
    matrix[4][0].push_back(13);
    matrix[4][3].push_back(7);
    matrix[4][4].push_back(6);
    matrix[4][4].push_back(10);

//###############################
    matrix[5][0].push_back(8);
    matrix[5][2].push_back(0);
    matrix[5][2].push_back(1);
    
    matrix[5][3].push_back(9);

//###############################
    std::cout << "checking matrix...";
    bool check = exoo::check_matrix(matrix, r, s, d);
    if (check) std::cout << "[ok]" << std::endl;
    else std::cout << std::endl;

    std::cout << "________________________________________" << std::endl;
    std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
    std::cout << "________________________________________" << std::endl;

    int ok = 0;
    int total = 10000;
    for (int i = 0; i < total; i++) {

        exoo_matrix** copy = copy_matrix(matrix, r);
        long before_perturb = tick();
        exoo::perturb_matrix(matrix, r, s, d);

        std::cout << "checking matrix... perturb took " << tick() - before_perturb << " ";
        check = exoo::check_matrix(matrix, r, s, d);
        if (check) {
            long before_evaluate = tick();
            double result = evaluate_matrix(matrix, r, s);
            std::cout << "[ok] cost = "  << result << " evaluation took " << tick() - before_evaluate << "ms " << std::endl;
            delete_matrix(copy, r); 
            ok++;

        } else {

            delete_matrix(matrix, r); 
            matrix = copy;
            std::cout << std::endl;
            std::cout << "________________________________________" << std::endl;
            std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
            std::cout << "________________________________________" << std::endl;

        }
    }

    cout << "ok = " << (double)ok/(double)total << endl;
}


void test_generate_random_matrix() {

    int r = 10, s = 19, d = 3;

    for (int i = 0; i < 10000; i++) {
        exoo::exoo_matrix **matrix = exoo::generate_random_matrix(r,s,d);

        bool check = exoo::check_matrix(matrix, r, s, d);
        if (!check) {
            std::cout << "________________________________________" << std::endl;
            std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
            std::cout << "________________________________________" << std::endl;
        }
        exoo::delete_matrix(matrix, r);
    }
}


void test_perturb() {
//    int r = 2, s = 5;
    int r = 10, s = 19, d = 3;

    int vertex_count = r*s;
    exoo::exoo_matrix **matrix = exoo::create_matrix(r);
    
//###############################
    matrix[0][1].push_back(5);
    matrix[0][1].push_back(10);

    matrix[0][6].push_back(2);
//###############################
    matrix[1][0].push_back(9);
    matrix[1][0].push_back(14);
    
    matrix[1][6].push_back(13);
    
//###############################
    matrix[2][7].push_back(9);
    matrix[2][7].push_back(10);
    
    matrix[2][9].push_back(8);
//###############################
    matrix[3][5].push_back(0);

    matrix[3][7].push_back(16);
    
    matrix[3][8].push_back(8);
//###############################
    matrix[4][4].push_back(8);
    matrix[4][4].push_back(11);
    
    matrix[4][8].push_back(11);
//###############################
    matrix[5][9].push_back(4);
    matrix[5][6].push_back(13);
    
    matrix[5][3].push_back(0);
//###############################
    matrix[6][0].push_back(17);
    matrix[6][1].push_back(6);
    
    matrix[6][5].push_back(6);
//###############################
    matrix[7][2].push_back(9);
    matrix[7][2].push_back(10);
    
    matrix[7][3].push_back(3);
//###############################
    matrix[8][3].push_back(11);
    matrix[8][4].push_back(8);
    
    matrix[8][9].push_back(0);
//###############################
    matrix[9][2].push_back(11);
    matrix[9][5].push_back(15);
    
    matrix[9][8].push_back(0);
//###############################

    std::cout << "checking matrix...";
    bool check = exoo::check_matrix(matrix, r, s, d);
    if (check) std::cout << "[ok]" << std::endl;
    else std::cout << std::endl;

    std::cout << "________________________________________" << std::endl;
    std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
    std::cout << "________________________________________" << std::endl;
    for (int x = 0; x < 300; x++) {
        exoo::check_matrix(matrix, r, s, d);
        std::cout << "**************perturb_mutation [" << x << "]" << std::endl;
//        exoo::change_random_value(matrix, r, s, d);
        exoo::randomize_matrix(matrix, r, s, d, exoo::get_random(r));

        std::cout << "________________________________________" << std::endl;
        std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
        std::cout << "________________________________________" << std::endl;
     
    }

    std::cout << exoo::to_string_matrix(matrix, r) << std::endl;
    std::cout << "________________________________________" << std::endl;

    exoo::exoo_graph graph = exoo::translate(matrix, r, s);

    boost::print_graph(graph);

    std::pair<int, int> diameters = exoo::compute_diameters(graph, vertex_count);

    std::cout << "diameter_size " << diameters.first << " diameter_count " << diameters.second << std::endl;

    vector<int> agents;
    for (int agent = 0; agent < r*s; agent+=s) {
        agents.push_back(agent); 
    }

    std::pair<int, int> diameters2 = exoo::compute_diameters(graph, vertex_count, agents);

    std::cout << "diameter_size2 " << diameters2.first << " diameter2_count " << diameters2.second << std::endl;
    

    exoo::delete_matrix(matrix, r);

}

