#include "renderer.h"
#include "window.h"
#include "camera.h"

void update(Context *ctx, Camera *camera, Input *input, float delta_time) {
    double xpos, ypos;
    glfwGetCursorPos(ctx->window, &xpos, &ypos);
    
    camera_update(camera, input, delta_time);
    camera_look_around(camera, xpos, ypos);
    window_update(input);
}

int main(int argc, char **argv) {
    Input input = {0};
    Context *ctx = window_init();
    Camera *camera = camera_init(ctx, 90.0f);
    
    float last_frame = 0.0f;
    float delta_time = 0.0f;
    
    if(!ctx || !camera) {
        camera = NULL;
        ctx = NULL;
        exit(EXIT_FAILURE);
    }
    
    context_register_callbacks(ctx, &input);

    Renderer r;
    render_init(&r);
    render_init_shapes(&r);

    Vector3 cube_pos[] = {  
        {5.0f, 0.0f, -7.0f},
        {3.0f, 0.0f, -7.0f},
        {1.0f, 0.0f, -7.0f},
        {-1.0f, 0.0f, -7.0f},
        {-3.0f, 0.0f, -7.0f},
    };

    glEnable(GL_DEPTH_TEST);

    while(!should_close(ctx) && !window_closed(ctx->window)) {
        float curr_frame = glfwGetTime();
        delta_time = curr_frame - last_frame;
        last_frame = curr_frame;

        clear_color(); // TODO: pass in custom color
        update(ctx, camera, &input, delta_time);
       
        /* Matrices Data */
        mat4 projection;
        glm_mat4_identity(projection);
        glm_mat4_identity(camera->view);
        
        glm_perspective(glm_rad(camera->fov), (ctx->height / ctx->width), 0.1f, 100.0f, projection); // 0.1f near plane , 100f far plane
        
        // view (camera)
        view_matrix(camera);

        render_shader(&r);
        
        int projection_loc = glGetUniformLocation(r.shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float *)projection);

        int view_loc       = glGetUniformLocation(r.shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)camera->view);
        
        vec3 axis = {1.0f, 0.3f, 0.5f};
        float angle = glm_rad(90.0f) * glfwGetTime();  // Speed of rotation
        for(int i = 0; i < 5; ++i) {
            // model (object)
            mat4 model;
            glm_mat4_identity(model);
            
            glm_translate_x(model, cube_pos[i].x);
            glm_translate_y(model, cube_pos[i].y);
            glm_translate_z(model, cube_pos[i].z);
            glm_rotate(model, angle, axis); 
            
            int model_loc = glGetUniformLocation(r.shader, "model");
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);
            render_cube(&r);
        }

        /* Triangle */
        mat4 model_triangle;
        vec3 pos = {0.0f, 0.0f, -3.0f};
        glm_mat4_identity(model_triangle);
        glm_translate(model_triangle, pos);
        int model_loc = glGetUniformLocation(r.shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model_triangle);
        render_triangle(&r);

        poll_events();
        swap_buffers(ctx->window);
    }
    
    window_free(ctx);
    camera_free(camera);
    
    ctx = NULL;
    camera = NULL;
    puts("Free'd the heap");
    return 0;
}
