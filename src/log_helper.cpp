#include <memory>

#include "log_helper.hpp"
#include "log_helper.h"

unsigned long int set_max_errors_iter(unsigned long int max_errors) {
    return log_helper::set_max_errors_iter(max_errors);
}

unsigned long int set_max_infos_iter(unsigned long int max_infos) {
    return log_helper::set_max_infos_iter(max_infos);
}

int set_iter_interval_print(int interval) {
    return log_helper::set_iter_interval_print(interval);
}

void disable_double_error_kill() {
    log_helper::disable_double_error_kill();
}

int start_log_file(const char *benchmark_name, const char *test_info) {
    std::string bench_name_str = benchmark_name;
    std::string test_info_str = test_info;
    return log_helper::start_log_file(bench_name_str, test_info_str);
}

int end_log_file() {
    return log_helper::end_log_file();
}

int start_iteration() {
    return log_helper::start_iteration();
}

int end_iteration() {
    return log_helper::end_iteration();
}

int log_error_count(unsigned long int kernel_errors) {
    return log_helper::log_error_count(kernel_errors);
}

int log_info_count(unsigned long int info_count) {
    return log_helper::log_info_count(info_count);
}

int log_error_detail(const char *error_detail) {
    std::string error_detail_str = error_detail;
    return log_helper::log_error_detail(error_detail_str);
}

int log_info_detail(const char *info_detail) {
    std::string info_detail_str = info_detail;
    return log_helper::log_info_detail(info_detail_str);
}

void update_timestamp() {
    log_helper::update_timestamp();
}

void get_log_file_name(char *log_file_name) {
    std::copy(log_helper::file_writer_ptr->get_file_path().begin(),
              log_helper::file_writer_ptr->get_file_path().end(),
              log_file_name);
}
