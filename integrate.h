
#ifndef INTEGRAL_CONCURRENTLY_INTEGRATE_H
#define INTEGRAL_CONCURRENTLY_INTEGRATE_H

    #include "config.h"

    double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m);
    void safe_integrate_c(double* result, double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double num_steps, int m);
    double integrate_p(const MyConfig &mc, int num_steps);

#endif //INTEGRAL_CONCURRENTLY_INTEGRATE_H
