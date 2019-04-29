#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int is_ext(const std::string &filename, const std::string &ext){
    return ! filename.compare(filename.length()-ext.length(), ext.length(), ext);
}



int main(int argc, char *argv[]) {

    try{

        if (argc > 1) {

            std::string cnf_file_name = argv[1];
            std::string res_file_name = "results.txt";

            if ( is_ext(cnf_file_name, ".txt") ){

                std::ifstream cnf_file(cnf_file_name);
                std::string word;
                while (cnf_file >> word){
                    std::cout << word << std::endl;
                }
                cnf_file.close();

            } else { std::cout << "Config-file must be .txt" << std::endl; return -1; }
        } else { std::cout << "Too few arguments given." << std::endl; return -1; }

    } catch(std::string &unexpected_error){
        std::cout << unexpected_error << std::endl;}

    return 0;
}



//if ( in_file.is_open() && !in_file.rdstate() ){
//std::cout << "OK" << std::endl;
//} else { std::cout << "Invalid path to Config-file." << std::endl; return -1; }