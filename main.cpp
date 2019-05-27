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
                    int num_steps = 25600;            // вдала к-сть при abs=0.05 rel=0.01
                    num_steps = tune_num_steps(mc);   // трохи довго тюнить;

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
