
#ifndef INTEGRAL_CONCURRENTLY_CONFIG_H
#define INTEGRAL_CONCURRENTLY_CONFIG_H

    #include <tuple>
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <string>
    #include <unordered_set>
    #include <list>
    #include <functional>
    #include <map>

    class MyConfig {

        public:
            double absolute_accuracy; double relative_accuracy;
            std::tuple<double, double> interval_x1;
            std::tuple<double, double> interval_x2;
            int number_of_threads;
            int parameter_m = 5;
            int max_num_steps;

        private:
            std::unordered_set<std::string> check_set = {"absolute_accuracy", "relative_accuracy",
                                                         "num_of_threads", "parameter_m", "max_num_steps",
                                                         "interval_of_integration_by_x1", "interval_of_integration_by_x2"};
        public:
            bool set_abs_accuracy(const std::list<std::string> &s_values);
            bool set_max_num_steps(const std::list<std::string> &s_values);
            bool set_rel_accuracy(const std::list<std::string> &s_values);
            bool set_num_threads(const std::list<std::string> &s_values);
            bool set_m(const std::list<std::string> &s_values);
            bool set_interval_x1(const std::list<std::string> &s_values);
            bool set_interval_x2(const std::list<std::string> &s_values);
            bool is_configured();
            int load_configs_from_file(const std::string &f_name);

    };

#endif //INTEGRAL_CONCURRENTLY_CONFIG_H
