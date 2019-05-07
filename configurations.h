#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>

using namespace std;

class MyConfig{

private:
    std::string abs_accuracy;
    std::string rel_accuracy;
    std::tuple<double > interval_of_integration_by_x1;
    std::tuple<double> interval_of_integration_by_x2;
    int num_of_threads;
    int parameter_m;

    std::unordered_set<std::string> check_set;

public:

    int load_configs(const std::string &f_name){

        try{
            std::ifstream f(f_name);
            if (f){
                std::string line;
                while (getline(f, line)){
//                    std::cout << line << std::endl;

                    std::vector<std::string> line_words;
                    int c = 0;

                    for(int i = 0; i < line.length(); i++) {
                        if (isspace(line[i])){
                            if (c!= i)
                                { line_words.emplace_back(line.substr(c, i-c)); }
                            c = i+1;
                        }
                    }
                    if (c != line.length()){ line_words.emplace_back(line.substr(c, line.length()-c)); }

                    std::cout << "~~~~~~~~~~~~" << std::endl;
                    for (std::string s : line_words) {
                        std::cout << "S:" + s << std::endl;
                    }
                }

                f.close();
                return 0;

            } else { std::cout << "File coulnd't be opened."; return -1; }
        } catch(std::string &err){ std::cout << err << std::endl; return -2; }
    }



};
