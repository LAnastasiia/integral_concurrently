#include <fstream>
#include <iostream>

#include "time_measure.h"
#include "additional.h"
#include "config.h"
#include "integrate.h"


int main(int argc, char *argv[]){

    if (argc < 2)
        { std::cout << "Too few arguments given." << std::endl; return -1; }

    int n = 10;
    std::string in_filename, out_filename;
    std::stringstream s_n (argv[1]);
    if (s_n >> n){
        in_filename = argv[2];
        out_filename = argv[3];
        if (!in_filename.empty() && !out_filename.empty() && is_file_ext(in_filename, ".txt") && is_file_ext(out_filename, ".txt")){

            // Clear prev data from out-file.
            std::ofstream r_f(out_filename, std::ofstream::out | std::ofstream::trunc);
            r_f.close();

            // config
            MyConfig mc;
            mc.load_configs_from_file(in_filename);


            int num_steps = 25600;
//            num_steps = tune_num_steps(mc);

            auto example = get_current_time_fenced();
            std::vector<decltype(get_current_time_fenced()-example)> all_time_results;
            std::vector<double> all_comp_results;

            std::ofstream f (out_filename);
            for (int t=16; t < 30; t++) {
                mc.set_num_threads(t);

                std::vector<decltype(get_current_time_fenced()-example)> time_results;
                std::vector<double> comp_results;

                for (int i = 0; i < n; i++) {
                    auto st_time = get_current_time_fenced();              // measure the time of integrating_p
                    double res = integrate_p(mc, num_steps);
                    auto f_time = get_current_time_fenced() - st_time;

                    // save results
                    std::cout << "~~~~~~~~~~~~~" << std::endl;
                    time_results.emplace_back(f_time);
                    comp_results.emplace_back(res);
                    f << std::to_string(res) + "   " + std::to_string(to_us(f_time)) << std::endl;
                }
                all_comp_results.push_back(*comp_results.end());

                // output the min time
                std::cout << "min time: " << to_us(*std::min_element(time_results.begin(), time_results.end())) << std::endl;
            }


            // check results.
            double c = 0;
            for (size_t i = 1; i < all_comp_results.size(); i++) {
                if (fabs(all_comp_results[i] - all_comp_results[i - 1]) > pow(10, -7)) {
                    c += std::max(c, fabs(all_comp_results[i] - all_comp_results[i - 1]));
                }
            }

            // output check results
            if (c > 0){
                std::cout << "ALL results were close enogh to be considered EQUAL."
                             << " (if there was a difference between results it was less than pow(10, -7))" << std::endl;
            } else {
                std::cout << "NOT ALL results can be equal." << std::endl << "Max deviation = " << c << std::endl;
            }


        } else { std::cout << "Invalid 'in-' and 'out-' filenames specification." << std::endl; exit(0); }
    } else { std::cout << "Invalid number of experiments." << std::endl; exit(0); }

    std::cout << "\nOK\n" << std::endl;
    return 0;
}