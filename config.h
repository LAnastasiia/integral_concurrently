
#ifndef INTEGRAL_CONCURRENTLY_CONFIG_H
#define INTEGRAL_CONCURRENTLY_CONFIG_H

    #include <tuple>

    #include <array>
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
            std::array<double,2> interval_x1;
            std::array<double,2> interval_x2;
            int number_of_threads;
            int parameter_m = 5;
            int init_num_steps = 200;
            int max_num_steps = 500000;

        private:
            std::unordered_set<std::string> check_set = {"absolute_accuracy", "relative_accuracy",
                                                         "num_of_threads", "parameter_m",
                                                         "max_num_steps",
                                                         "interval_of_integration_by_x1", "interval_of_integration_by_x2"};
        public:
            bool load_abs_accuracy(const std::list<std::string> &s_values);
            bool load_max_num_steps(const std::list<std::string> &s_values);
            bool load_init_num_steps(const std::list<std::string> &s_values);
            bool load_rel_accuracy(const std::list<std::string> &s_values);
            bool load_num_threads(const std::list<std::string> &s_values);
            bool load_m(const std::list<std::string> &s_values);
            bool load_interval_x1(const std::list<std::string> &s_values);
            bool load_interval_x2(const std::list<std::string> &s_values);
            bool set_num_threads(int num);
            bool is_configured();
            int load_configs_from_file(const std::string &f_name);

    };

#endif //INTEGRAL_CONCURRENTLY_CONFIG_H
