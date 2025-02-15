/*
* Input Class: Manages the state of the input
* 
* Used to specify the key_input callback
*/ 

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>

#include "util.h"

#define KEY_COUNT 257

typedef struct {
    int keys[KEY_COUNT];
} Input;

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void input_update(Input *input, int key, int action);
