#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>   /* for inline */
#include "cglm/cam.h"
#include "cglm/mat4.h"
#include "cglm/vec3.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// TODO: install stb_image.h

// #define MAX_VERTICES 1024
#define STATUS_LOG_SIZE 512 

#define DEBUG 0

typedef struct {
    vec3 pos;
    vec3 color;
} Vertex;

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int shader;

    Vertex *vertices;
    size_t vertices_count;

} Renderer;

void clear_color();
void render_init(Renderer *r);
void render_add_vertices(Renderer *r, Vertex *vertices, size_t v_count);
void render_shader(Renderer *r);
void render(Renderer *r);
void render_free(Vertex *vertices);
