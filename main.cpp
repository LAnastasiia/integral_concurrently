#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <string>

#include "boost/variant.hpp"
#include "configurations.h"

using namespace std;



//std::unordered_set<std::string> check_set ({"abs_accuracy", "rel_accuracy", "interval_of_integration_by_x1",
//                                            "interval_of_integration_by_x2", "num_of_threads", "parameter_m"});

//int load_configs(const std::string &cnf_file_name){
//    try{
//        std::ifstream cnf_file(cnf_file_name);       // open file
//        if (cnf_file){
//
//            std::string line;                         // read line by line
//            while (getline(cnf_file, line)){
//                std::cout << line << std::endl;
//
//            }
//            cnf_file.close();                        // close file
//
//            return 0;
//
//        } else { std::cout << "File coulnd't be opened."; return -1;}
//    } catch(std::string &err){ std::cout << err << std::endl; return -2; }
//}



int main(int argc, char *argv[])
{
    try{
        if (argc > 1) {
            std::string cnf_file_name = argv[1];
            std::string res_file_name = "results.txt";

            std::string ext = ".txt";
            if ( !cnf_file_name.compare(cnf_file_name.length()-ext.length(), ext.length(), ext) ){      // check if file has .txt extension
                MyConfig mc;
                mc.load_configs(cnf_file_name);

            } else { std::cout << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cout << "Too few arguments given." << std::endl; return -1; }
    } catch(std::string &unexpected_error){ std::cout << unexpected_error << std::endl; }

    return 0;

}