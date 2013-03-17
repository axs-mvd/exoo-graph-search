#include "exoo_tabu_search.hh"



void exoo::search(History *tabu, 
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
                            ostream &history_stream) { 

    int t = max_t;
    int loops_without_change = 0;
    long int loop_count = 0;

    if (!exoo::check_matrix(v, r, s, d)) {
        cout << "[" << __FILE__ << ":" << __LINE__ << "] v matrix fail!!" << endl;
    }

    vector<pair<double, exoo_matrix**> > pi;
    double v_value = evaluate_matrix(v, r, s);
    double best_v_value = v_value;

    int jumps = 0;

    while (true) {

        if (history_enabled) 
            history_stream << exoo::to_string_matrix(v, r);

        loop_count++;
        cout << "[" << __FILE__ << ":" << __LINE__ << "] loop_count: " 
             << loop_count << " loop without change " << loops_without_change 
             << " t " << t 
             << " value " << v_value  
             << " best_value " << best_v_value  
             << " jumps " << jumps 
             << endl;


        tabu->append(matrix_signature(v, r)); 

        for (int i = 0; i < k; i++) {
           exoo_matrix** copy = copy_matrix(v, r);

//            if (!exoo::check_matrix(copy, r, s, d)) {
//                cout << "[" << __FILE__ << ":" << __LINE__ << "] copy matrix fail!!" << endl;
//            }

            if (!use_interlaced) exoo::perturb_matrix(copy, r, s, d);
            else exoo::perturb_matrix_interlaced(copy, r, s, d);

            if (exoo::check_matrix(copy, r, s, d) && 
                !tabu->exists(matrix_signature(copy, r))) { 

                double value = evaluate_matrix(copy, r, s);
                if (value < 1000) {
                    pi.push_back(make_pair(value, copy)); 
                    
                    if ((int)value <= (int)value_threshold) {
                        cout << "________________________________________" << endl;
                        cout << "value: " << value << endl;
                        cout << exoo::to_string_matrix(copy, r) << endl;
                        cout << "________________________________________" << endl;
                    }

               } else delete_matrix(copy,r);

            } else delete_matrix(copy,r);
        }

        if (!pi.empty()) {
            
            sort(pi.begin(), pi.end(), exoo::compare);

            int better_count = 0;
            for (int i = 0; i < (int) pi.size(); i++) 
                if (v_value > pi[i].first) better_count++;

            cout << endl; 
            cout << "|pi| = " << (int)pi.size() << " neighborghood best: " << pi[0].first << " there are " << better_count << " better neighborgs" << endl;

            int max_t_pi;

            if ((int)pi.size() > t) max_t_pi = t;
            else max_t_pi = pi.size();


            int selected_idx = get_random(max_t_pi);
            cout << "max_t_pi " << max_t_pi << " selected_idx " << selected_idx << endl;


            delete_matrix(v, r);
            v = pi[selected_idx].second;
            v_value = pi[selected_idx].first;

            if (best_v_value > v_value) {
                
                loops_without_change = 0;
                best_v_value = v_value;

            } else if (t == 1) loops_without_change++;

            for (int i = 0; i < (int) pi.size(); i++) 
                if (i != selected_idx) delete_matrix(pi[i].second, r);

            pi.clear();


            if (loop_count % change_t_interval == 0) {
                t--;
                if (t == 0) {
                    t = 1;
                    if (loops_without_change > loops_without_change_max) {
                        t = max_t;
                        loops_without_change = 0;
                        jumps++;
                         
                        cout << "[" << __FILE__ << ":" << __LINE__ << "] v matrix :" << endl;
                        cout << to_string_matrix(v, r) << endl;
                        //creating a new matrix
                        delete_matrix(v, r);
                        while (true) {
                            v= generate_random_matrix(r, s, d);
                            if (evaluate_matrix(v, r, s) < 1000) {
                                break;
                            } else delete_matrix(v, r);
                        }

                        cout << "[" << __FILE__ << ":" << __LINE__ << "] jump to :" << endl;
                        cout << to_string_matrix(v, r) << endl;
 
                    }
                }
            }

        } else {
            loops_without_change++;
        
            if (loops_without_change > loops_without_change_max) {
                t = max_t;
                loops_without_change = 0;
            }
        }
    }

    delete_matrix(v, r); 
}

bool exoo::compare(pair<double, exoo_matrix**> a, pair<double, exoo_matrix**> b) {
    return a.first < b.first;
}

