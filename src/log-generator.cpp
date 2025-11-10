#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <set>

using namespace std;
namespace fs = filesystem;

void generate_approximation_log(set<int> original_set, int target_sum, int total_original_set_sum, int found_sum, set<int> found_subset, double epsilon, double execution_time) {
    try {
        fs::path logs_dir = fs::current_path() / "logs";
        fs::create_directories(logs_dir);

        auto now = chrono::system_clock::now();
        auto millis = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

        string file_name = "apr-log-" + to_string(millis) + ".txt";
        fs::path file_path = logs_dir / file_name;
        ofstream log_file(file_path);

        if (!log_file) {
            cerr << "error while creating log file at: " << file_path << endl;
        }

        log_file << "ALGORITHM CHOICE: APPROXIMATION" << endl;
        log_file << "EPSILON: " << epsilon << endl << endl;
        log_file << "TARGET SUM: " << target_sum << endl;
        log_file << "TOTAL ORIGINAL SET SUM: " << total_original_set_sum << endl;
        log_file << "ORIGINAL SET: { ";

        for (int element : original_set) {
            log_file << element << " ";
        }
    
        log_file << "}" << endl << endl << "FOUND SUM: " << "FOUND SUBSET: { ";

        for (int element : found_subset) {
            log_file << element << " ";
        }

        log_file << "}" << endl << "EXECUTION TIME: " << execution_time << endl;

        log_file.close();
    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void generate_exact_log(set<int> original_set, int target_sum, int total_original_set_sum, int great_sum, set<int> great_subset, double execution_time) {
    try {
        fs::path logs_dir = fs::current_path() / "logs";
        fs::create_directories(logs_dir);

        auto now = chrono::system_clock::now();
        auto millis = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

        string file_name = "exc-log-" + to_string(millis) + ".txt";
        fs::path file_path = logs_dir / file_name;
        ofstream log_file(file_path);

        if (!log_file) {
            cerr << "error while creating log file at: " << file_path << endl;
        }

        log_file << "ALGORITHM CHOICE: EXACT\n" << endl;
        log_file << "TARGET SUM: " << target_sum << endl;
        log_file << "TOTAL ORIGINAL SET SUM: " << total_original_set_sum << endl;
        log_file << "ORIGINAL SET: { ";

        for (int element : original_set) {
            log_file << element << " ";
        }
    
        log_file << "}" << endl << endl << "GREAT SUM: " << great_sum << endl << "GREAT SUBSET: { ";

        for (int element : great_subset) {
            log_file << element << " ";
        }

        log_file << "}" << endl << "EXECUTION TIME: " << execution_time << endl;

        log_file.close();
    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void generate_comparative_log(set<int> original_set, int target_sum, int total_original_set_sum, int great_sum, int found_sum, double epsilon, double exact_execution_time, double approximation_execution_time) {
    try {
        fs::path logs_dir = fs::current_path() / "logs";
        fs::create_directories(logs_dir);

        auto now = chrono::system_clock::now();
        auto millis = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

        string file_name = "cmp-log-" + to_string(millis) + ".txt";
        fs::path file_path = logs_dir / file_name;
        ofstream log_file(file_path);

        if (!log_file) {
            cerr << "error while creating log file at: " << file_path << endl;
        }

        log_file << "TARGET SUM: " << target_sum << endl;
        log_file << "TOTAL ORIGINAL SET SUM: " << total_original_set_sum << endl << "ORIGINAL SET: { ";

        for (int element : original_set) {
            log_file << element << " ";
        }
    
        log_file << "}" << endl << endl << "GREAT SUM: " << great_sum << endl;
        log_file << "APPROXIMATION SUM: " << found_sum << " (EPSILON: " << epsilon << ")" << endl;
        log_file << "APPROXIMATION SUM/GREAT SUM = " << fixed << setprecision(4) << static_cast<double>(found_sum) / great_sum << endl << endl;

        log_file << "EXACT ALGORITHM EXECUTION TIME: " << exact_execution_time << endl;
        log_file << "APPROXIMATION ALGORITHM EXECUTION TIME: " << approximation_execution_time << endl;

        log_file.close();
    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}