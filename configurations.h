#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <map>
#include <functional>

using namespace std;

class MyConfig{

public:
    double absolute_accuracy;
    double relative_accuracy;
    std::tuple<double, double> interval_of_integration_by_x1;
    std::tuple<double, double> interval_of_integration_by_x2;
    int number_of_threads;
    int parameter_m = 5;

private:
    std::unordered_set<std::string> check_set = {"absolute_accuracy", "relative_accuracy",
                                                 "num_of_threads", "parameter_m",
                                                 "interval_of_integration_by_x1", "interval_of_integration_by_x2"};

public:

    bool set_abs_accuracy(const std::list<string> &s_values){
        std::istringstream ss (s_values.front());
        return ss >> absolute_accuracy ? true: false;
    }

    bool set_rel_accuracy(const std::list<string> &s_values){
        std::istringstream ss (s_values.front());
        return ss >> relative_accuracy ? true: false;
    }

    bool set_num_threads(const std::list<string> &s_values){
        std::istringstream ss (s_values.front());
        return ss >> number_of_threads? true: false;
    }

    bool set_m(const std::list<string> &s_values) {
        std::istringstream ss (s_values.front());
        return ss >> parameter_m ? true: false;
    }

    bool set_interval_x1(const std::list<string> &s_values) {
        if (s_values.size() == 2){
            auto i_beg = std::stod(s_values.front());
            auto i_end = std::stod(*std::next(s_values.begin(), 1));
            interval_of_integration_by_x1 = std::make_tuple(i_beg, i_end);
            return true;
        }
        return false;
    }

    bool set_interval_x2(const std::list<string> &s_values) {
        if (s_values.size() == 2){
            auto i_beg = std::stod(s_values.front());
            auto i_end = std::stod(*std::next(s_values.begin(), 1));
            interval_of_integration_by_x2 = std::make_tuple(i_beg, i_end);
            return true;
        }
        return false;
    }

    bool is_configured(){
        return check_set.empty();
    }

    int load_configs_from_file(const std::string &f_name){
        // map with key: name, val: setter method call
        std::map< std::string, std::function<bool(const std::list<string>&)> > cnf;
        cnf.emplace(std::make_pair("relative_accuracy", [this](const std::list<string> &s_values)-> bool {set_rel_accuracy(s_values);}));
        cnf.emplace(std::make_pair("absolute_accuracy", [this](const std::list<string> &s_values)-> bool {set_abs_accuracy(s_values);}));
        cnf.emplace(std::make_pair("num_of_threads", [this](const std::list<string> &s_values)-> bool {set_num_threads(s_values);}));
        cnf.emplace(std::make_pair("parameter_m", [this](const std::list<string> &s_values)-> bool {set_m(s_values);}));
        cnf.emplace(std::make_pair("interval_of_integration_by_x1", [this](const std::list<string> &s_values)-> bool {set_interval_x1(s_values);}));
        cnf.emplace(std::make_pair("interval_of_integration_by_x2", [this](const std::list<string> &s_values)-> bool {set_interval_x2(s_values);}));

        try{
            // read config file line by line
            std::ifstream f(f_name);
            if (f){
                std::string line;
                while (getline(f, line)){

                    // split line content [cnf name, values_str...]
                    std::list<std::string> content;
                    int c = 0;
                    for(int i = 0; i < line.length(); i++) {
                        if (isspace(line[i])){
                            if (c!= i){
                                content.emplace_back(line.substr(c, i-c));
                            }
                            c = i+1;
                        }
                    }
                    if (c != line.length()){ content.emplace_back(line.substr(c, line.length()-c)); }

                    // load values into attributes
                    std::string cnf_name = content.front();
                    content.pop_front();

                    if ( cnf.find(cnf_name) != cnf.end()){
                        if ( cnf[cnf_name](content) ){
                            check_set.erase (cnf_name);
                        } else { std::cout << "Error. Couldn't load" + cnf_name + "\n" << std::endl; return -3; }
                    }
                }
                f.close();
                return 0;

            } else { std::cout << "File coulnd't be opened."; return -1; }
        } catch(std::string &err){ std::cout << err << std::endl; return -2; }
    }

};
