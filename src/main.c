#include "renderer.h"

#include "window.h"
#include "camera.h"

#define MAJOR 0
#define MINOR 2
#define PATCH 0

#define TESTING 0

void update(Context *ctx, Camera *camera, Input *input, float delta_time) {
    double xpos, ypos;
    glfwGetCursorPos(ctx->window, &xpos, &ypos);

    camera_update(camera, input, delta_time);
    camera_look_around(camera, xpos, ypos);
    window_update(input);
}

int main(int argc, char **argv) {
    printf("Project Name: Z-Renderer\nVERSION: %d.%d.%d", MAJOR, MINOR, PATCH);
    float last_frame = 0.0f;
    float delta_time = 0.0f;
    Input input = {0};
    Renderer r;

    Context *ctx = window_init();
    if(!ctx) {
        ctx = NULL;
        return 1;
    }

    Camera *camera = camera_init(ctx, 90.0f);
    if(!camera) {
        camera = NULL;
        return 1;
    }

    context_register_callbacks(ctx, &input);


    // TODO: Pathing. Implement a relative path for passing in file paths
    // Mesh* model = import_model("C:\\Users\\zyhru\\graphics\\assets\\penger\\penger.obj");
    Mesh* model = import_model("C:\\Users\\zyhru\\graphics\\models\\test.obj");
    if(!model->vertices) {
        Warning("%s\n", "Model vertices is null");
        return 1;
    }

    if(!model->indices) {
        Warning("%s\n", "Model vertices is null");
        return 1;
    }

#if TESTING
    printf("Mode: Testing\n");
    for(int i = 0; i < model->vertices->size; ++i) {
        printf("{%f, %f, %f}\n", 
               model->vertices->data[i].v.x, 
               model->vertices->data[i].v.y,
               model->vertices->data[i].v.z);
    }

    for(int i = 0; i < model->indices->size; ++i) {
        printf("%u\n", model->indices->data[i]);
    }
#endif
    
    render_init(&r);
    render_init_shapes(&r);
    render_init_model(model);
    
    glEnable(GL_DEPTH_TEST);
    while(!should_close(ctx) && !window_closed(ctx->window)) {
        float curr_frame = glfwGetTime();
        delta_time = curr_frame - last_frame;
        last_frame = curr_frame;

        clear_color(); // TODO: pass in custom color
        update(ctx, camera, &input, delta_time);

        mat4 projection;
        glm_mat4_identity(projection);
        glm_mat4_identity(camera->view);
        glm_perspective(glm_rad(camera->fov), (ctx->height / ctx->width), 0.1f, 100.0f, projection);
        view_matrix(camera);

        /************************** 3D Cube ************************************/
        render_shader(r.shader);
        int projection_loc = glGetUniformLocation(r.shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float *)projection);

        int view_loc       = glGetUniformLocation(r.shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)camera->view);

        int model_loc = glGetUniformLocation(r.shader, "model");

        vec3 axis = {1.0f, 0.3f, 0.5f};
        vec3 cube_position = {0.0f, 0.0f, -5.0f};
        float angle = glm_rad(90.0f) * glfwGetTime();  // Speed of rotation
        mat4 cube;
        glm_mat4_identity(cube);
        glm_translate(cube, cube_position);
        glm_rotate(cube, angle, axis);

        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)cube);
        render_cube(&r);

        /************************** 2D Triangle ********************************/
        mat4 triangle;
        vec3 pos = {0.0f, 0.0f, -3.0f};
        glm_mat4_identity(triangle);
        glm_translate(triangle, pos);
        model_loc = glGetUniformLocation(r.shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)triangle);
        render_triangle(&r);

        /***************************** Model ***********************************/
        render_shader(model->shader);
        vec3 obj_pos = {0.0f, 0.0f, -10.0f};
        mat4 model_cube;
        glm_mat4_identity(model_cube);
        glm_translate(model_cube, obj_pos);

        projection_loc = glGetUniformLocation(model->shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float *)projection);

        view_loc = glGetUniformLocation(model->shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)camera->view);

        model_loc = glGetUniformLocation(model->shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model_cube);
        render_model(model);
        /***********************************************************************/
        
        poll_events();
        swap_buffers(ctx->window);
    }
   
    window_free(ctx);
    camera_free(camera);
    model_free(model);
    puts("Shutting down renderer.");
    return 0;
}
