#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

char* read_file(const char* path);

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

extern Paths path;
