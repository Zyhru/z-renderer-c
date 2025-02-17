#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <cglm/cglm.h>
#include "cglm/cam.h"
#include "cglm/mat4.h"
#include "cglm/vec3.h"

#include "model.h"
#include "util.h"

#define PRIMITIVE_SIZE 2
#define STATUS_LOG_SIZE 512 
#define DEBUG 0

typedef enum {
    CUBE,
    TRIANGLE,
} Shapes_E;

typedef struct {
    vec3 pos;
    vec3 color;
    vec2 uv;
} Vertex;

typedef struct {
    unsigned char *image_data;
    int x;
    int y;
    int channels;
    GLenum format;
} Texture;

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    Vertex *vertices;
    size_t vertices_count;
    Shapes_E shape;
} Primitive;

typedef struct {
    unsigned int shader;
    unsigned int texture_id;
    Primitive shapes[PRIMITIVE_SIZE];
} Renderer;

/* rendering funcs */
void render_init(Renderer *r);
void render_init_shapes(Renderer *r);
void render_init_model(Mesh *mesh);
void render_add_vertices(Renderer *r, Vertex *vertices, size_t v_count, int pos);
void render_shader(unsigned int shd);
void render_free(Vertex *vertices);
void render_cube(Renderer *r);
void render_triangle(Renderer *r);
void render_model(Mesh *mesh);

/* shader funcs */
unsigned int generate_shader_id(const char *v, const char *f);

/* texture funcs */
Texture load_image(const char *file_name);

void clear_color();
