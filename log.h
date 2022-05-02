/*
 * Copyright (c) 2020 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 * Using environment variables LOG_LEVEL and 
 * LOG_COLOR to control the print of logs.
 */

#ifndef LOG_LOG
#define LOG_LOG
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#ifndef BEGIN_PATH
#define BEGIN_PATH "PARENT_DECTORY_NAME"
#endif

const char begin_path[] = BEGIN_PATH; 

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

static int LOG_LEVEL = 2, LOG_COLOR = 1;

// hook for libathread.so
void log_log(int level, const char *file, int line, const char *fmt, ...) {
    if (level < LOG_LEVEL) return;
    time_t t = time(NULL);
    struct tm *time = localtime(&t);
    va_list ap;
    va_start(ap, fmt);
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", time)] = '\0';
    if (LOG_COLOR) {
        printf(
            "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
            buf, level_colors[level], level_strings[level],
            strstr(file,begin_path), line);
    }
    else {
        printf(
            "%s %-5s %s:%d: ",
            buf, level_strings[level], strstr(file,begin_path), line);
    }
    printf(fmt, ap);
    printf("\n");
    va_end(ap);
}


void log_log_func(int level, const char *file, const char *func, int line, const char *fmt, ...) {
    if (level < LOG_LEVEL) return;
    time_t t = time(NULL);
    struct tm *time = localtime(&t);
    va_list ap;
    va_start(ap, fmt);
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", time)] = '\0';
    if (LOG_COLOR) {
        printf(
            "%s %s%-5s\x1b[0m \x1b[90m%s:%d<%s>:\x1b[0m ",
            buf, level_colors[level], level_strings[level],
            strstr(file,begin_path), line, func);
    } else {
        printf(
            "%s %-5s %s:%d<%s>: ",
            buf, level_strings[level], strstr(file,begin_path), line, func);
    }
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

#define log_trace(...) log_log_func(LOG_TRACE, __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)
#define log_debug(...) log_log_func(LOG_DEBUG, __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)
#define log_info(...)  log_log_func(LOG_INFO,  __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)
#define log_warn(...)  log_log_func(LOG_WARN,  __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)
#define log_error(...) log_log_func(LOG_ERROR, __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)
#define log_fatal(...) log_log_func(LOG_FATAL, __FILE__, __FUNCTION__ ,__LINE__, __VA_ARGS__)

__attribute__((constructor)) void log_prepare_env() {
    const char * log_level = getenv("LOG_LEVEL");
    const char * log_usr_color = getenv("LOG_COLOR");
    if (log_level) LOG_LEVEL = atoi(log_level);
    if (log_usr_color) LOG_COLOR = atoi(log_usr_color);
    log_debug("LOG_LEVEL=%d(%s), LOG_COLOR=%d", LOG_LEVEL, level_strings[LOG_LEVEL], LOG_COLOR);
}

#ifdef __cplusplus
}
#endif

#endif
