#include "camera.h"
#include "cglm/vec3.h"

Camera* camera_init(Context *ctx, float fov) {
    Camera *camera = (Camera *) malloc(sizeof(Camera));
    if(!camera) {
        fprintf(stderr, "ERROR: failed to allocate mem for camera");
        free(camera);
        return NULL;
    }
    
    camera->fov = fov;
    camera->pitch = -90.0f;
    camera->yaw = 0.0f;
    camera->sens = 0.1f;
    camera->x = -(ctx->width / 2);
    camera->y = -(ctx->height / 2);

    printf("Initial X,Y: (%f, %f)\n", camera->x, camera->y);
    
    camera->pos[0] = 0.0f; // x
    camera->pos[1] = 0.0f; // y
    camera->pos[2] = 0.0f; // z
   
    camera->up[0] = 0.0f; // x 
    camera->up[1] = 1.0f; // y
    camera->up[2] = 0.0f; // z
   
    camera->front[0] = 0.0f;  // x 
    camera->front[1] = 0.0f;  // y
    camera->front[2] = -1.0f; // z
    return camera;
}

void view_matrix(Camera *cam) {
    vec3 front_t = {0.0f, 0.0f, 0.0f};
    glm_vec3_add(cam->pos, cam->front, front_t);
    glm_lookat(cam->pos, front_t, cam->up, cam->view);
}

void camera_free(Camera *cam) {
    free(cam);
    cam = NULL;
}

void camera_update(Camera *camera, Input *input, float delta_time) {
    float velocity = 1.5f * delta_time;
    if(input->keys[GLFW_KEY_W] == GLFW_PRESS) {
        vec3 temp = {0.0f, 0.0f, 0.0f};
        glm_vec3_scale(camera->front, velocity, temp);
        glm_vec3_add(camera->pos, temp, camera->pos);
        //printf("Cam Position (%f, %f, %f)\n", camera->pos[0], camera->pos[1], camera->pos[2]);
    }

    if(input->keys[GLFW_KEY_S] == GLFW_PRESS) {
        vec3 temp = {0.0f, 0.0f, 0.0f};
        glm_vec3_scale(camera->front, velocity, temp);
        glm_vec3_sub(camera->pos, temp, camera->pos);
        //printf("Cam Position (%f, %f, %f)\n", camera->pos[0], camera->pos[1], camera->pos[2]);
    }

    if(input->keys[GLFW_KEY_D] == GLFW_PRESS) {
        vec3 right = {0.0f, 0.0f, 0.0f};
        glm_cross(camera->front, camera->up, right);
        glm_normalize(right);
        //printf("(Positive X): %f, %f, %f\n", right[0], right[1], right[2]);
        
        right[0] *= velocity;
        right[1] *= velocity;
        right[2] *= velocity;
        
        camera->pos[0] += right[0]; 
        camera->pos[1] += right[1];
        camera->pos[2] += right[2];

    }

    if(input->keys[GLFW_KEY_A] == GLFW_PRESS) {
        vec3 right = {0.0f, 0.0f, 0.0f};
        //printf("(Negative X) Vector: %f, %f, %f\n", right[0], right[1], right[2]);
        glm_cross(camera->front, camera->up, right);
        glm_normalize(right);
        
        right[0] *= velocity;
        right[1] *= velocity;
        right[2] *= velocity;
        
        camera->pos[0] -= right[0]; 
        camera->pos[1] -= right[1];
        camera->pos[2] -= right[2];
    }
}

void camera_look_around(Camera* camera, float xpos, float ypos) {
    // calculate x,y mouse offset and apply it to the pitch and yaw angles
    float x_offset = xpos - camera->x;
    float y_offset = camera->y - ypos;

    camera->x = xpos;
    camera->y = ypos;
        
    x_offset *= camera->sens;
    y_offset *= camera->sens;

    camera->yaw += x_offset;
    camera->pitch += y_offset;

    // clamp camera flipping 
    if(camera->pitch > 89.0f) camera->pitch = 89.0f;
    if(camera->pitch < -89.0f) camera->pitch = -89.0f;

    // calculuate the direction of the camera based
    // on the yaw and pitch values
    vec3 dir = {0.0f, 0.0f, 0.0f};
    dir[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch)); // x
    dir[1] = sin(glm_rad(camera->pitch)); // y
    dir[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch)); // z
    glm_normalize(dir);    

    camera->front[0] = dir[0];
    camera->front[1] = dir[1];
    camera->front[2] = dir[2];
    //glm_normalize_to(dir, camera->front);
}
