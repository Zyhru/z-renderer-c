#include "../src/renderer.h"
#include "../src/window.h"

#define VERSION "v.0.1.2"
#define PROJECT "DVD Logo"

void update(Input *input) {
    window_update(input);
}

void check_gl_errors() { 
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        printf("Error: %d\n", err);
    }
}

void GLAPIENTRY opengl_debug(GLenum source, GLenum type, GLuint id,
                             GLenum severity, GLsizei length, const GLchar *msg,
                             const void* userParam) {

    printf("OpenGL Debug Messages [%d] %s\n", id, msg);
    if(severity == GL_DEBUG_SEVERITY_HIGH) {
        printf("CRITICAL\n");
    } else if(severity == GL_DEBUG_SEVERITY_MEDIUM) {
        printf("WARNING error\n");
    } else if(severity == GL_DEBUG_SEVERITY_LOW) {
        printf("INFO error\n");
    }
}

int main(void) {
    Renderer r;
    Input input;
    char *dvd_logo_path_abs = "dvd_logo.png";
    Image img = {dvd_logo_path_abs, PNG};

    Context *ctx = window_init();
    if(!ctx) {
        return 1;
    }
    
    //glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    context_register_callbacks(ctx, &input);
    render_init_test(&r, &img);
    render_init_shapes(&r);
    
    while(!window_closed(ctx->window)) {
        clear_color(0.4f, 0.5f, 0.0f);
        //update(&input);

        // ortho projection (2D)
        // DVD Logo Model -> vertex shader -> frag shader -> screen
        #if 0
        mat4 projection;
        mat4 view;
        mat4 model;
        glm_mat4_identity(projection);
        glm_mat4_identity(view);
        glm_mat4_identity(model);

        /* View matrix initialization */ 
        vec3 eye = {0.0f, 0.0f, 0.0f}; 
        vec3 dir = {0.0f, 0.0f, 0.0f};
        vec3 up  = {0.0f, 1.0f, 0.0f};
        
        glm_ortho(0.0f, (float)ctx->width, (float)ctx->height, 0.0f, -1.0f, 1.0f, projection);
        glm_lookat(eye, dir, up, view);
        //render_set_uniform4fv(r.shader, "projection", projection);
        //render_set_uniform4fv(r.shader, "view", view);
        //render_set_uniform4fv(r.shader, "model", model);
        #endif
     
        /* Rendering DVD Logo */
        check_gl_errors();
        render_shader(&r);
        render_img(&r);
        
        poll_events();
        swap_buffers(ctx->window);
    }
    
    window_free(ctx);
    ZLOG_INFO("%s", "Shutting down renderer.");
    return 0;
}
