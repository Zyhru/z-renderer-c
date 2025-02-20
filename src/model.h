#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#define MATERIAL_FILE_OFFSET 7
#define LINE_BUF_SIZE 256
#define LIST_CAPACITY 50
#define VERTICES_CAPACITY 30
#define VERTEX_SIZE 4
#define TEXTURE_SIZE 3

#define REGULAR_TRIANGULATION 4
#define QUAD_TRIANGULATION 5

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

typedef enum {
    INITIAL,
    NO_SLASH,
    SINGLE_SLASH,
    DOUBLE_SLASH
} SlashTypes_E;

typedef struct {
    size_t cap;
    size_t size;
    char **data;
} String;

typedef struct {
    Vector3 v;
    Vector2 vt;
    Vector3 vn;
} OBJVertex;

typedef struct {
    size_t capacity;
    size_t size;
    unsigned int *data;
} IndexBuffer;

typedef struct {
    size_t capacity;
    size_t size;
    OBJVertex *data;
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
    char *texture_image;
    char file_path[LINE_BUF_SIZE];
} MTLLib;

typedef struct {
    unsigned int shader;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    IndexBuffer *indices;
    VertexBuffer *vertices;
} Mesh;

Mesh* import_model(const char *file);
Mesh* MeshAlloc();

VertexBuffer* init_vertices();
IndexBuffer* init_indices();
FaceElements init_faces();

Vector3List init_vec3_list();
Vector2List init_vec2_list();
String* init_string();
String* usplit(char *line, const char *delim);

Vector2 create_vec2(float x, float y);
Vector3 create_vec3(float x, float y, float z);
OBJVertex create_obj_vertex(Vector3 pos, Vector2 uv, Vector3 vn);

void split(char **array, char *line, const char *delim);
void model_free(Mesh *mesh);
void read_mtl_file(MTLLib *mat);
void append_string(String *s, char *item);
