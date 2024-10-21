#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#define LINE_BUF_SIZE 256
#define LIST_CAPACITY 50
#define VERTICES_CAPACITY 30
#define VERTEX_SIZE 4
#define TEXTURE_SIZE 3

#define z_append_ptr(l, i)\
    do {\
        if(l->size >= l->capacity) {\
            l->capacity *= 2;\
            void *data = realloc(l->data, sizeof(*l->data) * l->capacity);\
            if(!data) {\
                puts("Could not reallocate memory for list.");\
                free(data);\
                exit(EXIT_FAILURE);\
            }\
            l->data = data;\
        }\
        l->data[l->size++] = i;\
    } while(0)\

#define z_append(l, i)\
    do {\
        if(l.size >= l.capacity) {\
            l.capacity *= 2;\
            void *data = realloc(l.data, sizeof(*l.data) * l.capacity);\
            if(!data) {\
                puts("Could not reallocate memory for list.");\
                free(data);\
                exit(EXIT_FAILURE);\
            }\
            l.data = data;\
        }\
        l.data[l.size++] = i;\
    } while(0)\

typedef struct {
    Vector3 v;
    //Vector2 vt;
} OBJVertex;

typedef struct {
    size_t capacity; // 0
    size_t size; // 8
    unsigned int *data; // 12
} IndexBuffer;

typedef struct {
    size_t capacity; // 0
    size_t size; // 16
    OBJVertex *data; // 24
} VertexBuffer;

typedef struct {
    size_t capacity;
    size_t size;
    Vector3 *data;
} Vector3List;

typedef struct {
    size_t capacity;
    size_t size;
    Vector2 *data;
} Vector2List;

typedef struct {
    size_t capacity; 
    size_t size;
    uint32_t *data;
} FaceElements;

typedef struct {
    unsigned int shader; // 0
    unsigned int vao; // 4
    unsigned int vbo; // 8
    unsigned int ebo; // 12 
    IndexBuffer *indices; // 24
    VertexBuffer *vertices; // 36
} Mesh;

Mesh* import_model(const char* file);
Mesh* MeshAlloc();
VertexBuffer* init_vertices();
IndexBuffer* init_indices();
FaceElements init_faces();
Vector3List      init_vec3_list();
Vector2List      init_vec2_list();
Vector2 create_vec2(float x, float y);
Vector3 create_vec3(float x, float y, float z);
OBJVertex create_vertex(Vector3 pos, Vector2 uv);
bool is_in_vbo(VertexBuffer *vbo, OBJVertex data);
void split(char **array, char *line, const char *delim);
void model_free(Mesh *mesh);
void destroy(char *s[], char *t[]);
