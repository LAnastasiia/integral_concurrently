//
//#include "config.h"
//#include "time_measure.h"
//#include "additional.h"
//
//int main(int argc, char *argv[]){
//
//    if (argc < 2) { std::cout << "Too few arguments given." << std::endl; return -1; }
//    int n;
//    std::string in_filename, out_filename;
//
//    std::stringstream s_n (argv[1]);
//    if (s_n >> n){
//
//        in_filename = argv[2];
//        out_filename = argv[3];
//        if (!in_filename.empty() || !out_filename.empty() || is_file_ext(in_filename, ".txt") || is_file_ext(out_filename, ".txt")){
//
//            // Clear prev data from out-file.
//            std::ofstream r_f(out_filename, std::ofstream::out | std::ofstream::trunc);
//            r_f.close();
//
//            // Run n times and store results.
//            std::vector<decltype(get_current_time_fenced())> time_results;
//            std::vector<double> comp_results;
//            for (int i=0; i < n; i++){
////                auto st_time = get_current_time_fenced();
////                res = integrate(...);
////                time_results.emplace_back(get_current_time_fenced() - st_time);
//            }
//
//
//            for(const auto &ei: all_results){
//            std::cout << "min time measured: " << to_mcs(*std::min_element(ei.second.begin(), ei.second.end())) << std::endl;
//            }
//
//            // Tell if all results were equal.
//            std::ifstream res_file(out_filename);
//
//
//        } else { std::cout << "Invalid 'in-' and 'out-' filenames specification." << std::endl; exit(0); }
//    } else { std::cout << "Invalid number of experiments." << std::endl; exit(0); }
//
//    return 0;
//}