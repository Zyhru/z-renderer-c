#include "window.h"
#include "renderer.h"
#include "util.h"
#include "camera.h"

#define MAJOR 0
#define MINOR 2
#define PATCH 1

#define TESTING 0

static char penger_path[PATH_BUF_SIZE];
static char ball_path[PATH_BUF_SIZE];

void update(Context *ctx, Camera *camera, Input *input, float delta_time) {
    double xpos, ypos;
    glfwGetCursorPos(ctx->window, &xpos, &ypos);

    camera_update(camera, input, delta_time);
    camera_look_around(camera, xpos, ypos);
    window_update(input);
}

int main(int argc, char **argv) {
    //printf("Project Name: Z-Renderer\nVERSION: %d.%d.%d\n", MAJOR, MINOR, PATCH);
    printf("\n\n");
    ZLOG_INFO("Loading Z-Renderer: %d.%d.%d", MAJOR, MINOR, PATCH);
    float last_frame = 0.0f;
    float delta_time = 0.0f;
    Input input = {0};
    Renderer r;
    
    z_get_abs_path(penger_path, sizeof(penger_path), "assets\\penger\\penger.obj");
    z_get_abs_path(ball_path, sizeof(ball_path), "models\\ball.obj");

    Context *ctx = window_init();
    if(!ctx) {
        exit(EXIT_FAILURE);
    }
    ZLOG_INFO("%s", "Successfully initialized OpenGL context");

    Camera *camera = camera_init(ctx, 90.0f);
    if(!camera) {
        exit(EXIT_FAILURE);
    }
    ZLOG_INFO("%s", "Successfully initialized the camera.");

    context_register_callbacks(ctx, &input);

    Mesh* penger_model = import_model(penger_path);
    Mesh* ball_model = import_model(ball_path);

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
    
    render_init_model(penger_model, "penger");
    render_init_model(ball_model, "ball");
    
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
        float angle = glm_rad(90.0f) * glfwGetTime();
        mat4 cube;
        glm_mat4_identity(cube);
        glm_translate(cube, cube_position);
        glm_rotate(cube, angle, axis);

        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)cube);
        render_cube(&r);

        /************************** 2D Triangle ********************************/
        #if 0
        mat4 triangle;
        vec3 pos = {0.0f, 0.0f, -3.0f};
        glm_mat4_identity(triangle);
        glm_translate(triangle, pos);
        model_loc = glGetUniformLocation(r.shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)triangle);
        render_triangle(&r);
        #endif

        /***************************** Model ***********************************/
        render_shader(penger_model->shader);
        vec3 penger_pos = {0.0f, 0.0f, -10.0f};
        //vec3 ball_pos   = {0.0f, 0.0f, -8.0f};
        
        mat4 penger_mat;
        mat4 ball_mat;
        glm_mat4_identity(penger_mat);
        glm_translate(penger_mat, penger_pos);
        
        //glm_mat4_identity(ball_mat);
        //glm_translate(ball_mat, ball_pos);

        projection_loc = glGetUniformLocation(penger_model->shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float *)projection);

        view_loc = glGetUniformLocation(penger_model->shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float *)camera->view);

        model_loc = glGetUniformLocation(penger_model->shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)penger_mat);

        //int ball_loc = glGetUniformLocation(penger_model->shader, "model");
        //glUniformMatrix4fv(ball_loc, 1, GL_FALSE, (float*)ball_pos);
        
        render_model(penger_model);
        //render_model(ball_model);
        /***********************************************************************/
        
        poll_events();
        swap_buffers(ctx->window);
    }
   
    window_free(ctx);
    camera_free(camera);
    model_free(penger_model);
    model_free(ball_model);
    ZLOG_INFO("%s", "Application closed successfully");
    return 0;
}
