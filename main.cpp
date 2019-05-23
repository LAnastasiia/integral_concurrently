#include <mutex>
#include <thread>

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <list>
#include <functional>
#include <map>

#include "time_measure.h"
#include "config.h"
#include "additional.h"
#include "integrate.h"


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
                    std::cout << "Configurations loaded successfully.\n" << std::endl;

                    // tune
                    int num_steps = tune_num_steps(mc); // дуже довго тюнить; вдала к-сть при abs=0.05 : min 102400

                    // time
                    auto st_time_p = get_current_time_fenced();
                        double res_p = integrate_p(mc, num_steps);

                    auto res_time_p = get_current_time_fenced() - st_time_p;

                    // output

                    std::cout << "\nresult -->  " + std::to_string(res_p) << std::endl;
                    std::cout << "\ntime  ...   " + std::to_string(to_us(res_time_p)) << std::endl;

                } else {std::cerr << " Error. Not all configurations were loaded properly."; return -1; }

            } else { std::cerr << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cerr << "Too few arguments given." << std::endl; return -1; }

    } catch(std::string &unexpected_error)
        {std::cerr << unexpected_error + "\n Sorry, unpredicted error. We will fix it in the next version." << std::endl;
        return -2;}

    std::cout << "\nOK\n" << std::endl;
    return 0;

}


// -8.192345 -- 1600
// -6.571375-- 3200
// -5.794479 -- 6400
// -5.416354 -- 12800
// -5.230115
// -5.137731
// -5.091727 -- 102400 -- 0.00195312

// acc: 0.05, 0.01
// result: -5.085075, time: 5029265082, absolute err: 0.052528, relative err: 0.010303

// double res_p = integrate_c(std::get<0>(mc.interval_x1), std::get<0>(mc.interval_x2),
//                            std::get<1>(mc.interval_x2), std::get<1>(mc.interval_x1), num_steps, mc.parameter_m);