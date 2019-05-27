#include "config.h"


bool MyConfig::load_abs_accuracy(const std::list<std::string> &s_values){
    std::istringstream ss (s_values.front());
        double a_ch = std::stod(s_values.front());
        if (a_ch <= 0){
            return false;
        } else { return ss >> absolute_accuracy ? true: false; }
    }


bool MyConfig::load_max_num_steps(const std::list<std::string> &s_values){
    std::istringstream ss (s_values.front());
    int ch = stoi(s_values.front());
    if ( ch > 0 ){
        return ss >> max_num_steps ? true: false;
    }
    return false;
}


bool MyConfig::load_init_num_steps(const std::list<std::string> &s_values){
    std::istringstream ss (s_values.front());
    int ch = stoi(s_values.front());
    if ( ch > 0 ){
        return ss >> init_num_steps ? true: false;
    }
    return false;
}



bool MyConfig::load_rel_accuracy(const std::list<std::string> &s_values){
    std::istringstream ss (s_values.front());
    double a_ch = std::stod(s_values.front());
    if (a_ch <= 0){
        return false;
    } else { return ss >> relative_accuracy ? true: false; }
}


bool MyConfig::load_num_threads(const std::list<std::string> &s_values){
    std::istringstream ss (s_values.front());
    int ns_ch = std::stoi(s_values.front());
    if (ns_ch <= 0){
        return false;
    } else { return ss >> number_of_threads ? true: false; }
}


bool MyConfig::load_m(const std::list<std::string> &s_values) {
    std::istringstream ss (s_values.front());
    int m_check = stoi(s_values.front());
    if ( m_check > 0 ){
        return ss >> parameter_m ? true: false;
    } else { return false; }
}


bool MyConfig::load_interval_x1(const std::list<std::string> &s_values) {
    if (s_values.size() == 2){
        auto i_beg = std::stod(s_values.front());
        auto i_end = std::stod(*std::next(s_values.begin(), 1));
        if (i_beg < i_end){
            interval_x1 = {i_beg, i_end};
            return true;
        }
    }
    return false;
}


bool MyConfig::load_interval_x2(const std::list<std::string> &s_values) {
    if (s_values.size() == 2){
        auto i_beg = std::stod(s_values.front());
        auto i_end = std::stod(*std::next(s_values.begin(), 1));
        if (i_beg < i_end){
            interval_x2 = {i_beg, i_end};
            return true;
        }
    }
    return false;
}


bool MyConfig::is_configured(){
    return check_set.empty();
}


int MyConfig::load_configs_from_file(const std::string &f_name){
    // map with key: name, val: setter method call
    std::map< std::string, std::function<bool(const std::list<std::string>&)> > cnf;
    cnf.emplace(std::make_pair("relative_accuracy", [this](const std::list<std::string> &s_values)-> bool {return load_rel_accuracy(s_values);}));
    cnf.emplace(std::make_pair("absolute_accuracy", [this](const std::list<std::string> &s_values)-> bool {return load_abs_accuracy(s_values);}));
    cnf.emplace(std::make_pair("num_of_threads", [this](const std::list<std::string> &s_values)-> bool {return load_num_threads(s_values);}));
    cnf.emplace(std::make_pair("parameter_m", [this](const std::list<std::string> &s_values)-> bool {return load_m(s_values);}));
    cnf.emplace(std::make_pair("interval_of_integration_by_x1", [this](const std::list<std::string> &s_values)-> bool {return load_interval_x1(s_values);}));
    cnf.emplace(std::make_pair("interval_of_integration_by_x2", [this](const std::list<std::string> &s_values)-> bool {return load_interval_x2(s_values);}));
    cnf.emplace(std::make_pair("max_num_steps", [this](const std::list<std::string> &s_values)-> bool {return load_max_num_steps(s_values);}));
    cnf.emplace(std::make_pair("init_num_steps", [this](const std::list<std::string> &s_values)-> bool {return load_init_num_steps(s_values);}));

    try{
        // read config-file line by line
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
                    } else { std::cout << "Error. Couldn't load " + cnf_name + "\n" << std::endl; return -3; }
                }
            }
            f.close();
            return 0;

        } else { std::cout << "File coulnd't be opened."; return -1; }
    } catch(std::string &err){ std::cout << err << std::endl; return -2; }
}


bool MyConfig::set_num_threads(int num){
    if (num > 0){
        number_of_threads = num;
        return true;
    } return false;
}
