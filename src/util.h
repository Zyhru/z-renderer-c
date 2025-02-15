#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>

#define GREEN "\033[0;32m"
#define RED   "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

#define ZMALLOC_ERROR(...) fprintf(stderr, name, __VA_ARGS__)
#define Warning(...) fprintf(stderr,  __VA_ARGS__)

#define ZLOG_INFO(fmt, ...) z_log_msg(GREEN"INFO"RESET, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define ZLOG_WARN(fmt, ...) z_log_msg(YELLOW"WARN"RESET, __FILE__, __LINE__, fmt, __VA_ARGS__)
#define ZLOG_ERROR(fmt, ...) z_log_msg(RED"ERROR"RESET, __FILE__, __LINE__, fmt, __VA_ARGS__)

void z_log_msg(const char *level, const char *file, int line, const char *fmt, ...);
char* read_file(const char* path);
void  read_file_t(char **buffer, size_t *buff_size, const char* path);
void* z_malloc(size_t size, const char *name);
void free_data(void *data);

typedef struct {
    const char *vertex_path;
    const char *fragment_path;
    char *texture[];  
} Paths;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;

extern Paths path;
