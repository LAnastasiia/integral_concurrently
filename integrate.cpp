#include <mutex>

#include "time_measure.h"
#include "config.h"
#include "additional.h"
#include "integrate.h"

std::mutex mtx;


// ~~~~~~~~~~~~~~ Integrating consistently. ~~~~~~~~~~~~~~

double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double delta_x1, double delta_x2, int m) {

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

void safe_integrate_c(double* result, double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double delta_x1, double delta_x2, int m){

    double c_res = integrate_c(lim_beg_1, lim_beg_2, lim_end_1, lim_end_2, delta_x1, delta_x2, m);
    std::lock_guard<std::mutex> lock(mtx);
    *result += c_res;
}


// ~~~~~~~~~~~~~~ Integrating in parallel way. ~~~~~~~~~~~~~~

double integrate_p(const MyConfig &mc, int num_steps){

    double lim_bg_1 = mc.interval_x1[0], lim_bg_2 = mc.interval_x2[0];
    double lim_fn_1 = mc.interval_x1[1], lim_fn_2 = mc.interval_x2[1];

    double thr_block_len = fabs(lim_fn_1 - lim_bg_1) / mc.number_of_threads;
    double delta_x1 = thr_block_len * (mc.number_of_threads + 1) / static_cast<double>(num_steps);
    double delta_x2 = fabs(lim_fn_1 - lim_bg_1) / num_steps;

    std::vector<std::thread> threads;
    double res = 0;

    auto st_time = get_current_time_fenced();
        while (lim_bg_1 < lim_fn_1){

            std::thread new_thread(safe_integrate_c,
                                       &res, lim_bg_1, lim_bg_2, lim_bg_1+thr_block_len, lim_fn_2, delta_x1, delta_x2, mc.parameter_m);

            threads.emplace_back(std::move(new_thread));
            lim_bg_1 += thr_block_len;
        }
        for (auto &curr_thread: threads){
            curr_thread.join();
        }
    auto res_time = get_current_time_fenced() - st_time;
    return res;
}


//           1 172225608
//           2 121134432
//           3  92597156
//           4  75927889
//           5  76829805
//           6  70349167
//           7  65426715
//           8  60320167
//           9 167718199
//          10  61731013
//          11  62783016
//          12  65162518
//          13  63555392
//          14  64171007
//          15  64407939
//          16  63305230
//          17  62698938
//          18  64689557
//          19  66275929
//          20  64028635
//          21  66833902
//          22  64557077
//          23 111213170