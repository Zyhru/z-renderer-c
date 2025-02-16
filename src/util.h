#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define GREEN "\033[0;32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

#define ZMALLOC_ERROR(...) fprintf(stderr, name, __VA_ARGS__)
#define Warning(...) fprintf(stderr,  __VA_ARGS__)

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

void    z_print_vec3(Vector3 *data, int size);
void    z_print_uint(unsigned int *data);
void    z_read_file(char **buffer, size_t *buff_size, const char* path);
void*   z_malloc(size_t size, const char *name);
void    z_free_data(void *data);

extern Paths path;
