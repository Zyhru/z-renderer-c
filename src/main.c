#include "renderer.h"
#include "window.h"

int main(void) {
    Context *ctx = window_init();
    if(!ctx) return -1;
    
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
    while(!window_closed(ctx->window)) {
        clear_color(); // TODO: pass in custom color
       
        /* Matrices Data */
        // projection (perspective)
        mat4 projection, view, model;
        glm_mat4_identity(projection);
        glm_mat4_identity(view);
        glm_mat4_identity(model);
        
        glm_perspective(glm_rad(90.0f), (ctx->height / ctx->width), 0.1f, 100.0f, projection);

        // view (camera)
        vec3 eye = {0.0f, 0.0f, 0.0f};
        vec3 up = {0.0f, 1.0f, 0.0f};
        
        vec3 pos    = {0.0f, 0.0f, 0.0f};
        vec3 front  = {0.0f, 0.0f, -1.0f};
        vec3 center = {0.0f, 0.0f, 0.0f};
        
        glm_vec3_addadd(pos, front, center);
        glm_lookat(eye, center, up, view);
       
        // model (object)
        vec3 move = {0.0f, 0.0f, -4.0f};
        vec3 axis = {1.0f, 0.3f, 0.5f};
        float angle = glm_rad(90.0f) * glfwGetTime();  // Speed of rotation

        glm_translate_z(model, -4.0f);
        glm_rotate(model, angle, axis); 
        
        render_shader(&r);
        
        int projection_loc = glGetUniformLocation(r.shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection[0]);

        int view_loc       = glGetUniformLocation(r.shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, view[0]);

        int model_loc      = glGetUniformLocation(r.shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, model[0]);

        render(&r);

        poll_events();
        swap_buffers(ctx->window);
    }
    
    window_free(ctx);
    free(r.vertices);
    return 0;
}
