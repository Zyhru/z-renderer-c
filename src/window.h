#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input.h"
#include "util.h"

typedef struct  {
    float width;
    float height;
    const char *name;
    GLFWwindow *window;
    bool window_status;
    int gl_ver_major;
    int gl_ver_minor;
} Context;

Context* window_init();
bool window_closed(GLFWwindow *window);
void window_free(Context* ctx);
void context_register_callbacks(Context *ctx, Input *input);
void window_update(Input *input);
bool should_close(Context *ctx);
void swap_buffers(GLFWwindow *window);
void poll_events();
