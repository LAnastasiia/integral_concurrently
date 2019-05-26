
#ifndef INTEGRAL_CONCURRENTLY_INTEGRATE_H
#define INTEGRAL_CONCURRENTLY_INTEGRATE_H

    #include "config.h"

    double integrate_c(double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double delta_x1, double delta_x2, int m);
    void safe_integrate_c(double* result, double lim_beg_1, double lim_beg_2, double lim_end_1, double lim_end_2, double dx_1, double dx_2, int m);
    double integrate_p(const MyConfig &mc, int num_steps);

#endif //INTEGRAL_CONCURRENTLY_INTEGRATE_H
