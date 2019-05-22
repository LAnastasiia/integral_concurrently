#include <mutex>

#include "time_measure.h"
#include "additional.h"
#include "config.h"

std::mutex mutex;

// Integrating consistently.
double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m) {

    double delta_x1 = (lim_end_1 - lim_beg_1) / num_steps;
    double delta_x2 = (lim_end_2 - lim_beg_2) / num_steps;

    std::cout << "###########";
    std::cout << delta_x1 << std::endl;
    std::cout << delta_x2 << std::endl;
    std::cout << "###########";

    double res = 0;
    int i, j;

    i = 0;
    while (lim_beg_1 + i*delta_x1 < lim_end_1) {

        j = 0;
        while (lim_beg_2 + j*delta_x2 < lim_end_2) {
            res += shubert_func(lim_beg_1 + i*delta_x1, lim_beg_2 + j*delta_x2, m) * delta_x1 * delta_x2;
            j++;
        }
        i++;
        std::cout << "i: " + std::to_string(i) + "    j: " + std::to_string(j) << std::endl;
    }
    std::cout << "~~~~~~~~~~~~";
    std::cout << res << std::endl;
    return res;
}


// Finding optimal number of steps for integration with given abs-, rel- errors.
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

        double abs_err = fabs(curr_res - prev_res);
        double rel_err = fabs((curr_res - prev_res) / curr_res);

        if ( abs_err <= mc.absolute_accuracy || rel_err <= mc.relative_accuracy){

            std::cout << std::to_string(fabs(curr_res - prev_res)) << std::endl;
            std::cout << std::to_string(fabs(curr_res - prev_res / curr_res)) << std::endl;
            std::cout << "%%%%%" << std::endl;
            return num_steps;

        } else { num_steps *= 2; }
    }

}


void safe_integrate_c(double* result, double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m){
    double c_res = integrate_c(lim_beg_1, lim_beg_2, lim_end_1, lim_end_2, num_steps, m);
    mutex.lock();
    *result += c_res;
    mutex.unlock();
}


double integrate_p(const MyConfig &mc, int num_steps){
    double lim_bg_1 = std::get<0>(mc.interval_x1), lim_bg_2 = std::get<0>(mc.interval_x2);
    double lim_fn_1 = std::get<1>(mc.interval_x1), lim_fn_2 = std::get<1>(mc.interval_x2);
    double row_step = fabs(lim_fn_1 - lim_bg_1) / mc.number_of_threads;

    std::vector<std::thread> threads;
    double res = 0;

    while (lim_bg_1 < lim_fn_1){
        std::thread new_thread(safe_integrate_c, &res, lim_bg_1, lim_bg_2, lim_bg_1+row_step, lim_fn_2, num_steps, mc.parameter_m);

        threads.push_back(std::move(new_thread));
        lim_bg_1 += row_step;
    }

    auto st_time = get_current_time_fenced();
    for (auto &curr_thread: threads){
        curr_thread.join();
    }
    auto res_time = get_current_time_fenced() - st_time;
    return res;
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
                    std::cout << "YES! Configurations loaded successfully.\n" << std::endl;

                    int num_steps = 1600;  // num_steps = tune_num_steps(mc); // дуже довго тюнить, норм к-сть кроків при abs=0.01 -- 102400

                    double res_p = integrate_p(mc, num_steps);

                    std::cout << "absolute err: " + std::to_string(mc.absolute_accuracy) << std::endl;
                    std::cout << "relative err: " + std::to_string(mc.relative_accuracy) << std::endl;
                    std::cout << "\nresult --> " + std::to_string(res_p) << std::endl;
                    std::cout << "\ntime ..." << std::endl;

                } else {std::cerr << " Error. Not all configurations were loaded properly."; return -1; }

            } else { std::cerr << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cerr << "Too few arguments given." << std::endl; return -1; }

    } catch(std::string &unexpected_error){
        std::cout << unexpected_error + "\n Sorry, unpredicted error. Will fix in the next version." << std::endl;
        return -2;
    }

//    auto time_to_calculate = get_current_time_fenced() - before;

    std::cout << "\nOK\n" << std::endl;
    return 0;

}

//-12.859964
//-30.528103



// -8.192345 -- 1600
// -6.571375-- 3200
// -5.794479 -- 6400
// -5.416354 -- 12800
// -5.230115
// -5.137731
// -5.091727 -- 102400 -- 0.00195312

// F: -5.045849736

// acc: 0.05, 0.01


//double res_c = integrate_c(std::get<0>(mc.interval_x1), std::get<0>(mc.interval_x2),
//                           std::get<1>(mc.interval_x2), std::get<1>(mc.interval_x1),
//                           num_steps, mc.parameter_m);