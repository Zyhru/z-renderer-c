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
        ZLOG_ERROR("%s", "Failed to allocate memory for OpenGL context.");
        return NULL;
    }

    ZLOG_INFO("%s", "Initializing OpenGL context.");
    ctx->height = 1024;
    ctx->width  = 800;
    ctx->name   = "z-renderer";
    ctx->window_status = helper;
    ctx->gl_ver_major = 3;
    ctx->gl_ver_minor = 3;

    if(!glfwInit()) {
        //fprintf(stderr, "ERROR: failed to initialize GLFW\n");
        ZLOG_ERROR("%s", "Failed to initialize GLFW.");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ctx->gl_ver_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ctx->gl_ver_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    
    ZLOG_INFO("Using OpenGL core v%d.%d", ctx->gl_ver_major, ctx->gl_ver_minor);

    ctx->window = glfwCreateWindow(ctx->height, ctx->width, ctx->name, NULL, NULL );
    if(!ctx->window) {
        //fprintf(stderr, "ERROR: failed to create window\n");
        ZLOG_ERROR("%s", "Failed to create GLFW window.");
        return NULL;
    }

    glfwSetFramebufferSizeCallback(ctx->window, framebuffer_size_callback);
    glfwSetInputMode(ctx->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(ctx->window, input_callback);

    glfwMakeContextCurrent(ctx->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ZLOG_ERROR("%s", "Failed to load OpenGL function pointers.");
        //fprintf(stderr, "ERROR: failed to initialize glad\n");
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
    glfwDestroyWindow(ctx->window);
    ctx->window = NULL;
    free(ctx);
    glfwTerminate();
}

