
#include "additional.h"
#include "config.h"
#include "time_measure.h"


// Integrating consistently.
double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m) {

    double delta_x1 = (lim_end_1 - lim_beg_1) / num_steps;
    double delta_x2 = (lim_end_2 - lim_beg_2) / num_steps;

    std::cout << delta_x1 << std::endl;
    std::cout << delta_x2 << std::endl;

    double res = 0;
    int i, j;

    i = 0;
    while (lim_beg_1 + i*delta_x1 <= lim_end_1) {

        j = 0;
        while (lim_beg_2 + j*delta_x2 <= lim_end_2) {
            res += shubert_func(lim_beg_1 + i*delta_x1, lim_beg_2 + j*delta_x2, m) * delta_x1 * delta_x2;
            j++;
        }
        i++;
        std::cout << "i: " + std::to_string(i) + "    j: " + std::to_string(j) << std::endl;
    }

    std::cout << res << std::endl;
    return res;
}


int tune_num_steps(MyConfig mc){
    int num_steps = 200;
    int max_ns = mc.max_num_steps;
    double prev_res = integrate_c(std::get<0>(mc.interval_x1), std::get<0>(mc.interval_x2),
                                  std::get<1>(mc.interval_x1), std::get<1>(mc.interval_x2),
                                  num_steps, mc.parameter_m);
    num_steps *= 2;

    while (num_steps < max_ns){
        double curr_res = integrate_c(std::get<0>(mc.interval_x1), std::get<0>(mc.interval_x2),
                                      std::get<1>(mc.interval_x1), std::get<1>(mc.interval_x2),
                                      num_steps, mc.parameter_m);
        if (fabs(curr_res - prev_res) <= mc.absolute_accuracy || fabs((curr_res - prev_res) / curr_res) <= mc.relative_accuracy){
            return num_steps;

        } else { num_steps *= 2; }
    }

}


int main(int argc, char *argv[])
{
    MyConfig mc;

    try{
        if (argc > 1) {
            std::string cnf_file_name = argv[1];
            std::string res_file_name = "results.txt";

            std::string ext = ".txt";
            if ( is_file_ext(cnf_file_name, ext) ){

                // config
                mc.load_configs_from_file(cnf_file_name);
                if (mc.is_configured()) {
                    std::cout << "YES! Configurations loaded successfuly.\n" << std::endl;


                    // tune the number of steps
                    double num_steps = 102400;


                    // integrate consistently
                    double res_c = integrate_c(std::get<0>(mc.interval_x1), std::get<0>(mc.interval_x2),
                                               std::get<1>(mc.interval_x2), std::get<1>(mc.interval_x1),
                                               num_steps, mc.parameter_m);


                    std::cout << "absolute err: " + std::to_string(mc.absolute_accuracy) << std::endl;
                    std::cout << "relative err: " + std::to_string(mc.relative_accuracy) << std::endl;
                    std::cout << "\nresult --> " + std::to_string(res_c) << std::endl;
                    std::cout << "\ntime ..." << std::endl;

                } else {std::cerr << " Error. Not all configurations were loaded properly."; return -1; }

            } else { std::cerr << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cerr << "Too few arguments given." << std::endl; return -1; }

    } catch(std::string &unexpected_error){
        std::cout << unexpected_error + "\n Sorry, unpredicted error. Will fix in the next version." << std::endl;
        return -2;
    }

//    auto time_to_calculate = get_current_time_fenced() - before;

    std::cout << "OK\n" << std::endl;
    return 0;

}

// -8.192345 -- 1600
// -6.571375-- 3200
// -5.794479 -- 6400
// -5.416354 -- 12800
// -5.230115
// -5.137731
// -5.091727 -- 102400 -- 0.00195312

// F: -5.045849736

// 0.05, 0.01