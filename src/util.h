#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
    #define OS_WINDOWS
    #include <direct.h>
#elif __linux__
    #define OS_LINUX
    #include <unistd.h>
#endif

#define GREEN "\033[0;32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

#define PATH_BUF_SIZE 512

#define ZMALLOC_ERROR(...) fprintf(stderr, name, __VA_ARGS__) // TODO: Deprecate macro 
#define Warning(...) fprintf(stderr,  __VA_ARGS__) //TODO: Depcrecate  macro

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;

void    z_print_vec3(Vector3 *data, int size);
void    z_print_uint(unsigned int *data);
void    z_read_file(char **buffer, size_t *buff_size, const char* path);
void*   z_malloc(size_t size, const char *name);
void    z_free_data(void *data);
void    z_get_abs_path(char *buf, size_t len, char *x);
void    z_concat(char *buf, char *dir_buf, char *x);

// TODO: New logging system
