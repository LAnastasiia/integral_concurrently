#include <mutex>

#include "time_measure.h"
#include "config.h"
#include "additional.h"
#include "integrate.h"

std::mutex mtx;


// ~~~~~~~~~~~~~~ Integrating consistently. ~~~~~~~~~~~~~~

double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m) {

    double delta_x1 = (lim_end_1 - lim_beg_1) / num_steps;
    double delta_x2 = (lim_end_2 - lim_beg_2) / num_steps;

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
    }
    return res;
}


// ~~~~~~~~~~~~~~ Wrap integrate_c function with mutex. ~~~~~~~~~~~~~~

void safe_integrate_c(double* result, double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m){

    double c_res = integrate_c(lim_beg_1, lim_beg_2, lim_end_1, lim_end_2, num_steps, m);  // compute using integrate_c

    std::lock_guard<std::mutex> lock(mtx);
    {*result += c_res;}
}


// ~~~~~~~~~~~~~~ Integrating in parallel way. ~~~~~~~~~~~~~~

double integrate_p(const MyConfig &mc, int num_steps){

    double lim_bg_1 = std::get<0>(mc.interval_x1), lim_bg_2 = std::get<0>(mc.interval_x2);
    double lim_fn_1 = std::get<1>(mc.interval_x1), lim_fn_2 = std::get<1>(mc.interval_x2);
    double row_step = fabs(lim_fn_1 - lim_bg_1) / mc.number_of_threads;
    int th_num_steps = num_steps / mc.number_of_threads + 1;

    std::vector<std::thread> threads;
    double res = 0;

    while (lim_bg_1 < lim_fn_1){

        std::thread new_thread(safe_integrate_c, &res, lim_bg_1, lim_bg_2, lim_bg_1+row_step, lim_fn_2, th_num_steps, mc.parameter_m);

        threads.emplace_back(std::move(new_thread));
        lim_bg_1 += row_step;
    }

    auto st_time = get_current_time_fenced();
    for (auto &curr_thread: threads){
        curr_thread.join();
    }
    auto res_time = get_current_time_fenced() - st_time;
    return res;
}