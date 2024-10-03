#include "renderer.h"
#include "window.h"
#include "camera.h"

void update(Camera *camera, Input *input, float delta_time) {
    camera_update(camera, input, delta_time);
    window_update(input);
}


int main(void) {
    Context *ctx = window_init();
    Camera *camera = camera_init(90.0f);
    Input input = {0};
    
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

    Vertex triangle[] = {
        {{0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // Vertex 1: Position + Color
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Vertex 2: Position + Color
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}   // Vertex 3: Position + Color
    };

   Vertex cube[] = {
        // Front face
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{0.5f, -0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}}, // Bottom-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Top-left
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left

        // Back face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}}, // Bottom-right
        {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}}, // Top-left
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left

        // Left face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}, // Top-left
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Bottom-right
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left

        // Right face
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}}, // Top-left
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f, -0.5f,  0.5f},  {1.0f, 1.0f, 0.0f}}, // Bottom-right
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 0.0f}}, // Bottom-left

        // Top face
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}}, // Bottom-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Top-left
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left

        // Bottom face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}}, // Bottom-right
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Top-left
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
    };
 
    //size_t v_count = sizeof(triangle) / sizeof(triangle[0]);
    //render_add_vertices(&r, triangle, v_count);

    render_add_vertices(&r, cube, sizeof(cube) / sizeof(cube[0]));
    glEnable(GL_DEPTH_TEST);
    
    while(!should_close(ctx) && !window_closed(ctx->window)) {
        float curr_frame = glfwGetTime();
        delta_time = curr_frame - last_frame;
        last_frame = curr_frame;

        clear_color(); // TODO: pass in custom color
        update(camera, &input, delta_time);
        //camera_update_test(camera, ctx, delta_time);
       
        /* Matrices Data */
        // projection (perspective)
        mat4 projection, model;
        glm_mat4_identity(projection);
        glm_mat4_identity(camera->view);
        glm_mat4_identity(model);
        
        glm_perspective(glm_rad(camera->fov), (ctx->height / ctx->width), 0.1f, 100.0f, projection); // 0.1f near plane , 100f far plane
        
        // view (camera)
        view_matrix(camera);
       
        // model (object)
        vec3 move = {0.0f, 0.0f, -4.0f};
        vec3 axis = {1.0f, 0.3f, 0.5f};
        float angle = glm_rad(90.0f) * glfwGetTime();  // Speed of rotation

        glm_translate_z(model, -10.0f);
        glm_rotate(model, angle, axis); 
        
        render_shader(&r);
        
        int projection_loc = glGetUniformLocation(r.shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection[0]);

        int view_loc       = glGetUniformLocation(r.shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, camera->view[0]);

        int model_loc      = glGetUniformLocation(r.shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, model[0]);

        render(&r);

        poll_events();
        swap_buffers(ctx->window);
    }
    
    puts("Free'd the heap");
    window_free(ctx);
    camera_free(camera);
    render_free(r.vertices);
    
    ctx = NULL;
    r.vertices = NULL; 
    camera = NULL;

    return 0;
}
