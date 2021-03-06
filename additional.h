
#ifndef INTEGRAL_CONCURRENTLY_ADDITIONAL_H
#define INTEGRAL_CONCURRENTLY_ADDITIONAL_H

#include <cstdio>
#include <bits/stdc++.h>
#include "config.h"
#include "integrate.h"

    int is_file_ext(const std::string &file_name, const std::string &ext);
    std::string get_file_ext(const std::string &file_name);
    int is_float(const std::string &s);
    double shubert_func(double x1, double x2, int m);
    int tune_num_steps(MyConfig mc);


#endif //INTEGRAL_CONCURRENTLY_ADDITIONAL_H
