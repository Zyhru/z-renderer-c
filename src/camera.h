#pragma once 

#include <stdio.h>
#include <stdlib.h>

#include "cglm/mat4.h"
#include <cglm/cglm.h>   /* for inline */

#include "window.h"

typedef struct  {
    // cam xyz
    vec3 pos;
    vec3 up;
    vec3 front;
    
    // cam attributes
    float fov;
    float pitch;
    float yaw;
    float x;
    float y;
    float sens;

    mat4 view;    
} Camera;

Camera* camera_init(Context* ctx, float fov);
void camera_update(Camera *camera, Input *input, float delta_time);
void camera_look_around(Camera *camera, float xpos, float ypos);
void camera_free(Camera *camera);
void view_matrix(Camera *camera);
