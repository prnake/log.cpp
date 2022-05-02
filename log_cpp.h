#ifndef LOG_LOG_CPP
#define LOG_LOG_CPP

#ifdef __cplusplus
extern "C" {
#include "log.h"
}
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class log_log_cpp {
public:
    log_log_cpp(int level, const char *file, const char *func, int line)
    {
        level_ = level;
        file_ = file;
        line_ = line;
        func_ = func;
        line_ = line;
    }

    ~log_log_cpp() {
        log_log_func(level_, file_, func_, line_, "%s", msg_.str().c_str());
    }

    std::ostream &Stream()
    {
        return msg_;
    }

private:
    int level_;
    const char *file_;
    const char *func_;
    int line_;
    std::ostringstream msg_;
};


#define log_stream(level)        \
    log_log_cpp(level, __FILE__, __FUNCTION__ ,__LINE__).Stream()
#define log_out_trace log_stream(LOG_TRACE)
#define log_out_debug log_stream(LOG_DEBUG)
#define log_out_info log_stream(LOG_INFO)
#define log_out_warn log_stream(LOG_WARN)
#define log_out_error log_stream(LOG_ERROR)
#define log_out_fatal log_stream(LOG_FATAL)

#define log_out_variable_1(n) #n << ": " << n
#define log_out_variable_2(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_1(__VA_ARGS__)
#define log_out_variable_3(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_2(__VA_ARGS__)
#define log_out_variable_4(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_3(__VA_ARGS__)
#define log_out_variable_5(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_4(__VA_ARGS__)
#define log_out_variable_6(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_5(__VA_ARGS__)
#define log_out_variable_7(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_6(__VA_ARGS__)
#define log_out_variable_8(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_7(__VA_ARGS__)
#define log_out_variable_9(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_8(__VA_ARGS__)
#define log_out_variable_10(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_9(__VA_ARGS__)
#define log_out_variable_11(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_10(__VA_ARGS__)
#define log_out_variable_12(n1,...) log_out_variable_1(n1) << ", " << log_out_variable_11(__VA_ARGS__)

#define log_out_func(n) __FUNCTION__ << '(' << n << ')'

#endif
#endif
