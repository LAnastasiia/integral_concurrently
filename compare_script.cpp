#include <fstream>
#include <iostream>
//
#include "time_measure.h"
#include "additional.h"
#include "config.h"
#include "integrate.h"

int main(int argc, char *argv[]){

    if (argc < 2) { std::cout << "Too few arguments given." << std::endl; return -1; }
    int n = 1000;
    std::string in_filename, out_filename;

    std::stringstream s_n (argv[1]);
    if (s_n >> n){

        in_filename = argv[2];
        out_filename = argv[3];
        if (!in_filename.empty() || !out_filename.empty() || is_file_ext(in_filename, ".txt") || is_file_ext(out_filename, ".txt")){

            // Clear prev data from out-file.
            std::ofstream r_f(out_filename, std::ofstream::out | std::ofstream::trunc);
            r_f.close();

            MyConfig mc;
            mc.load_configs_from_file(in_filename);

            int num_steps = 102400;
            if (fabs(mc.absolute_accuracy - 0.05) > pow(10, -7)){
                num_steps = tune_num_steps(mc);
            }

            auto ex = get_current_time_fenced();
            std::vector<decltype(get_current_time_fenced()-ex)> time_results;
            std::vector<double> comp_results;

            std::ofstream f (out_filename);

            for (int i=0; i < n; i++) {
                auto st_time = get_current_time_fenced();
                double res = integrate_p(mc, num_steps);
                auto f_time = get_current_time_fenced() - st_time;
                time_results.emplace_back(f_time);
                comp_results.emplace_back(res);
                f << std::to_string(res) + "   " + std::to_string(to_us(f_time)) << std::endl;
            }

//           check results.
            int c = 0;
            for(size_t i = 1; i < comp_results.size(); i++){
                if ( fabs(comp_results[i] - comp_results[i-1]) > pow(10, -7) ){
                    c ++;
                }
            }
            if (!c){
                std::cout << "ALL results were close enogh to be considered EQUAL."
                             << " (if there was a difference between results it was less than pow(10, -7))" << std::endl;
            } else { std::cout << "NOT ALL results can be equal." << std::endl; }

//          output the min time
            std::cout << "min time: " << to_us(*std::min_element(time_results.begin(), time_results.end())) << std::endl;


        } else { std::cout << "Invalid 'in-' and 'out-' filenames specification." << std::endl; exit(0); }
    } else { std::cout << "Invalid number of experiments." << std::endl; exit(0); }

    std::cout << "\nOK\n" << std::endl;
    return 0;
}