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
    float x; // 0
    float y; // 4
    float z; // 8
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;


extern Paths path;
