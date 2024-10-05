#include "input.h"

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input *input = (Input *)glfwGetWindowUserPointer(window);
    if(!input) {
        fprintf(stderr, "ERROR: Window pointer is invalid\n");
        return;
    }

    input_update(input, key, action);
}

void input_update(Input *input, int key, int action) {
    if(key >= 0 && key <= KEY_COUNT) {
        input->keys[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
    }
}
