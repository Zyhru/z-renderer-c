#include "window.h"

bool helper = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        puts("Exiting renderer.");
        helper = true;
    }
}

bool window_closed(GLFWwindow *window) {
    return glfwWindowShouldClose(window);
}

// bad way??
bool should_close(Context *ctx) {
    ctx->window_status = helper;
    return ctx->window_status;
}

Context* window_init() {
    Context *ctx = (Context *)malloc(sizeof(Context));
    if(!ctx) {
        free(ctx);
        fprintf(stderr, "ERROR Failed to allocate memory for Context\n"); 
        return NULL;
    }

    ctx->height = 1024;
    ctx->width  = 800;
    ctx->name   = "z-renderer";
    ctx->window_status = helper;


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
    glfwSetKeyCallback(ctx->window, input_callback);

    glfwMakeContextCurrent(ctx->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "ERROR: failed to initialize glad\n");
        return NULL;
    }
    
    return ctx;
}

void context_register_callbacks(Context *ctx, Input *input) {
    glfwSetWindowUserPointer(ctx->window, input);
    glfwSetKeyCallback(ctx->window, input_callback);
}

void window_update(Input *input) {
    if(input->keys[GLFW_KEY_ESCAPE]) {
        puts("Closing renderer");
        helper = true;
    }
}

void swap_buffers(GLFWwindow *window) {
    glfwSwapBuffers(window);
}

void poll_events() {
    glfwPollEvents();
}

void window_free(Context* ctx) {
    free(ctx);
    glfwDestroyWindow(ctx->window);
    glfwTerminate();
}

