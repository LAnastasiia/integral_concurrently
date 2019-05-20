#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <string>
#include "boost/variant.hpp"

#include "additional.h"
#include "configurations.h"





int main(int argc, char *argv[])
{
    MyConfig mc;

    try{
        if (argc > 1) {
            std::string cnf_file_name = argv[1];
            std::string res_file_name = "results.txt";

            std::string ext = ".txt";
            if ( is_file_ext(cnf_file_name, ext) ){

                mc.load_configs_from_file(cnf_file_name);

                if (mc.is_configured()){
                    std::cout << "YES! Configurations loaded successfuly.\n" << std::endl;
                }


            } else { std::cout << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cout << "Too few arguments given." << std::endl; return -1; }
    } catch(std::string &unexpected_error){ std::cout << unexpected_error << std::endl; }

    std::cout << "OK\n" << std::endl;
    return 0;

}