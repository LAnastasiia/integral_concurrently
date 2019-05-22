#include "additional.h"


// Return string - extention of the filename.
std::string get_file_ext(const std::string &file_name){
    std::size_t dot_ind = file_name.find_last_of('.');
    return file_name.substr(dot_ind);
}


// Check
int is_file_ext(const std::string &file_name, const std::string &ext){
    return !file_name.compare(file_name.length()-ext.length(), ext.length(), ext);
}


// Check if string can be converted to float.
int is_float(const std::string &s){
    return s.find_first_of(' ') == s.find_last_of(' ');
}

// Shubert's function https://www.sfu.ca/~ssurjano/shubert.html, http://benchmarkfcns.xyz/benchmarkfcns/shubertfcn.html
double shubert_func(double x1, double x2, int m){
    double x1_sum = 0, x2_sum = 0;
    for(int i=1; i <= m; i++){
        x1_sum += i * cos((i+1) * x1 + 1);
        x2_sum += i * cos((i+1) * x2 + 1);
    }
    return - x1_sum * x2_sum;
}


