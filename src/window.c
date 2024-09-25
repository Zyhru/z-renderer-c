#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool window_closed(GLFWwindow *window) {
    return glfwWindowShouldClose(window);
}

Context* window_init() {
    Context *ctx = (Context *)malloc(sizeof(Context));
    ctx->height = 1024;
    ctx->width  = 800;
    ctx->name   = "z-renderer";

    if(!ctx) {
        fprintf(stderr, "ERROR Failed to allocate memory for Context\n"); 
        return NULL;
    }

    if(!glfwInit()) {
        fprintf(stderr, "ERROR: failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    ctx->window = glfwCreateWindow(ctx->height, ctx->width, ctx->name, NULL, NULL );
    if(!ctx->window) {
        fprintf(stderr, "ERROR: failed to create window\n");
        return NULL;
    }

    glfwSetFramebufferSizeCallback(ctx->window, framebuffer_size_callback);
    glfwMakeContextCurrent(ctx->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "ERROR: failed to initialize glad\n");
        return NULL;
    }
    
    return ctx;
}


void swap_buffers(GLFWwindow *window) {
    glfwSwapBuffers(window);
}

void poll_events() {
    glfwPollEvents();
}

void window_free(Context* ctx) {
    free(ctx);
}
