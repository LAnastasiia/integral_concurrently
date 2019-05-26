#include "additional.h"



// ~~~~~~~~~~~~~~ Return string - extension of the filename. ~~~~~~~~~~~~~~
std::string get_file_ext(const std::string &file_name){
    std::size_t dot_ind = file_name.find_last_of('.');
    return file_name.substr(dot_ind);
}


// ~~~~~~~~~~~~~~ Check if file extension is same as given one. ~~~~~~~~~~~~~~
int is_file_ext(const std::string &file_name, const std::string &ext){
    return !file_name.compare(file_name.length()-ext.length(), ext.length(), ext);
}


// ~~~~~~~~~~~~~~ Check if string can be converted to float. ~~~~~~~~~~~~~~
int is_float(const std::string &s){
    return s.find_first_of(' ') == s.find_last_of(' ');
}


// ~~~~~~~~~~~~~~ Shubert's function ~~~~~~~~~~~~~~ https://www.sfu.ca/~ssurjano/shubert.html
double shubert_func(double x1, double x2, int m){
    double x1_sum = 0, x2_sum = 0;
    for(int i=1; i <= m; i++){
        x1_sum += i * cos((i+1) * x1 + 1);
        x2_sum += i * cos((i+1) * x2 + 1);
    }
    return - x1_sum * x2_sum;
}


// ~~~~~~~~~~~~~~ Finding optimal number of steps for integration with given abs-, rel- errors. ~~~~~~~~~~~~~~
int tune_num_steps(MyConfig mc){
    int num_steps = 200;
    int max_ns = mc.max_num_steps;
    double dx_1 = fabs(mc.interval_x1[1] - mc.interval_x1[0]) / num_steps;
    double dx_2 = fabs(mc.interval_x2[1] - mc.interval_x2[0]) / num_steps;

    double prev_res = integrate_c(mc.interval_x1[0], mc.interval_x2[0],
                                  mc.interval_x1[1], mc.interval_x2[1],
                                  dx_1, dx_2,
                                  mc.parameter_m);
    num_steps *= 2;

    while (num_steps < max_ns){
        std::cout << "trying num_steps = " + std::to_string(num_steps) << std::endl;

        dx_1 = fabs(mc.interval_x1[1] - mc.interval_x1[0]) / num_steps;
        dx_2 = fabs(mc.interval_x2[1] - mc.interval_x2[0]) / num_steps;

        double curr_res = integrate_c(mc.interval_x1[0], mc.interval_x2[0],
                                      mc.interval_x1[1], mc.interval_x2[1],
                                      dx_1, dx_2,
                                      mc.parameter_m);

        double abs_err = fabs(curr_res - prev_res);
        double rel_err = fabs((curr_res - prev_res) / curr_res);

        std::cout << "res:          " + std::to_string(curr_res) << std::endl;
        std::cout << "absolute err: " + std::to_string(abs_err) << std::endl;
        std::cout << "relative err: " + std::to_string(rel_err) + "\n" << std::endl;

        if ( abs_err <= mc.absolute_accuracy || rel_err <= mc.relative_accuracy){
            return num_steps;

        } else { num_steps *= 2; prev_res = curr_res; }
    }
}
