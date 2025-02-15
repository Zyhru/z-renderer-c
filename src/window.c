#include "window.h"
#include "GLFW/glfw3.h"

bool helper = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(100, 100, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        ZLOG_INFO("%s", "Exiting ZRenderer");
        glfwDestroyWindow(window);
        //puts("Exiting renderer.");
        //glfwWindowShouldClose();
        //glfwSetWindowShouldClose(window, true);
        helper = true;
    }
}

bool window_closed(GLFWwindow *window) {
    return glfwWindowShouldClose(window);
}

bool should_close(Context *ctx) {
    ctx->window_status = helper;
    return ctx->window_status;
}

Context* window_init() {
    ZLOG_INFO("%s", "Initializing OpenGL 3.3 (core)");
    Context *ctx = malloc(sizeof(Context));
    if(!ctx) {
        ctx = NULL;
        free(ctx);
        ZLOG_ERROR("%s", "Failed to allocate memeory for OpenGL context.\n");
        //fprintf(stderr, "ERROR Failed to allocate memory for Context\n"); 
        return NULL;
    }

    ctx->height = 1024;
    ctx->width  = 800;
    ctx->name   = "Z-Renderer";
    ctx->window_status = helper;

    if(!glfwInit()) {
        ZLOG_ERROR("%s", "Failed to initialize GLFW.\n");
        //fprintf(stderr, "ERROR: failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    ctx->window = glfwCreateWindow(ctx->height, ctx->width, ctx->name, NULL, NULL );
    if(!ctx->window) {
        ZLOG_ERROR("%s", "Failed to create to window.\n");
        //fprintf(stderr, "ERROR: failed to create window\n");
        return NULL;
    }

    glfwSetFramebufferSizeCallback(ctx->window, framebuffer_size_callback);
    glfwSetInputMode(ctx->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glfwDestroyWindow(ctx->window);
    ctx->window = NULL;
    free(ctx);
    glfwTerminate();
}

