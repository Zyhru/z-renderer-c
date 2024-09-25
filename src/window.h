#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct  {
    int width;
    int height;
    const char *name;
    GLFWwindow *window;
} Context;

Context* window_init();
bool window_closed(GLFWwindow *window);
void swap_buffers(GLFWwindow *window);
void window_free(Context* ctx);
void poll_events();
