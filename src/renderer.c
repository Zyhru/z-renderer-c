#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

// TODO: Refactor this, i dont know why i did this?
Paths path = {
    .vertex_path   =  "C:\\Users\\zyhru\\graphics\\shaders\\vertex.vert",
    .fragment_path = "C:\\Users\\zyhru\\graphics\\shaders\\fragment.frag",
    .texture =  {
        "C:\\Users\\zyhru\\graphics\\assets\\minecraft_grass.jpg",
        "C:\\Users\\zyhru\\graphics\\assets\\wall.jpg",
        "C:\\Users\\zyhru\\graphics\\assets\\penger\\penger.png",
    }
};

void clear_color(float x, float y, float z) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(x, y, z, 1.0f);
}

bool is_image_supported(Image *image) {
    char *img_fmt;
    switch(image->img_f) {
        case PNG:
            img_fmt = ".png";
            break;
        case JPEG:
            img_fmt = ".jpeg";
            break;
        default:
            Warning("%s\n", "Image format not supported\n"); 
            break;
    }
    

    // TODO: Use usplit
    char *context;
    char *delim = ".";
    char *token = strtok_s(image->image_path, delim, &context);
    while(token != NULL) {
            
        token = strtok_s(NULL, delim, &context);
    }

    return true;
}

void render_init_test(Renderer* r, Image *img) {
    ZLOG_INFO("%s", "Initializing renderer");
    // TODO: Add support for certain image formats
    #if 0 
    if(!image || !is_image_supported(image)) {
        
    }
    #endif

    int pos = strcspn(img->image_path, ".");
    strncpy(r->texture_uniform, img->image_path, pos);
    r->texture_uniform[pos] = '\0';

    //printf("Image relative path: %s\n", img->image_path);  
    //printf("Texture Uniform: %s\n", r->texture_uniform);
    //printf("Texture Uniform length %zu\n", strlen(r->texture_uniform));

    Primitive shapes[] = {
        {
            .vertices = NULL,
            .vertices_count = 0,
            .shape = CUBE,

        },
        {
            .vertices = NULL,
            .vertices_count = 0,
            .shape = TRIANGLE
        },
        {
            .vertices = NULL,
            .vertices_count = 0,
            .shape = IMAGE 
        },
        
    };
    
    memcpy(r->shapes, shapes, sizeof(shapes));
    r->shader = generate_shader(path.vertex_path, path.fragment_path);
    
    //puts("Initialing textures.");
    ZLOG_INFO("%s", "Initializing texures");
    glGenTextures(1, &r->texture_id);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    char root_dir[STATUS_LOG_SIZE] = "C:\\Users\\zyhru\\graphics\\assets\\"; // TODO: Grab root dir instead of hardcoding this path
    size_t len = strlen(root_dir);
    snprintf(root_dir + len, sizeof(root_dir), "%s", img->image_path);
    //printf("Image absolute path %s\n", root_dir);

    Texture texture = load_image(root_dir); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture.x, texture.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture.image_data);
    //puts("Finished textures.");
}

void render_init(Renderer *r) {
    Primitive shapes[] = {
        {
            .vertices = NULL,
            .vertices_count = 0,
            .shape = CUBE,

        },
        {
            .vertices = NULL,
            .vertices_count = 0,
            .shape = TRIANGLE
        },
    };
    
    memcpy(r->shapes, shapes, sizeof(shapes));

    r->shader = generate_shader(path.vertex_path, path.fragment_path);

    puts("Initialing textures.");
    glGenTextures(1, &r->texture_id);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Texture texture = load_image(path.texture[0]); // hard-coded? why did I do this?
    glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.x, texture.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture.image_data);
    puts("Finished textures.");
}

void render_init_model(Mesh *mesh) {
    puts("Initializing model.");
    mesh->shader = generate_shader("C:\\Users\\zyhru\\graphics\\shaders\\modelvert.vert", "C:\\Users\\zyhru\\graphics\\shaders\\modelfrag.frag");

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);
    
    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(OBJVertex) * mesh->vertices->size, mesh->vertices->data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->indices->size, mesh->indices->data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void *)offsetof(OBJVertex, v));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void *)offsetof(OBJVertex, vt));
    glEnableVertexAttribArray(1);

    free_data(mesh->vertices->data);
    free_data(mesh->indices->data);
    
    puts("Finished init model.");
}

void render_init_shapes(Renderer *r) {
    ZLOG_INFO("%s", "Initializing vertex buffer");
    Vertex triangle[] = {
        {{-0.5f,  -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f},   {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.0f, 0.5f, 0.0f},    {0.0f, 0.0f, 1.0f}, {0.5f, 0.0f}}
    };


    Vertex image[] = {
        {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f},   {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

        {{0.5f,  -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    };

    // TODO: EBO for faster rendering
    Vertex cube[] = {
         // Front face
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left
        {{0.5f, -0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // Top-left
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left

        // Back face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-left
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-right
        {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Top-left
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-left

        // Left face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-left
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Top-left
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // Top-right
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-right
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-left

        // Right face
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // Top-left
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // Top-right
        {{0.5f, -0.5f,  0.5f},  {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-right
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left

        // Top face
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // Bottom-left
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Bottom-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // Top-right
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Top-left
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // Bottom-left

        // Bottom face
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // Bottom-left
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // Bottom-right
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // Top-right
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // Top-right
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Top-left
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}  // Bottom-left
    };
    
    render_add_vertices(r, cube, sizeof(cube) / sizeof(cube[0]), CUBE);
    render_add_vertices(r, triangle, sizeof(triangle) / sizeof(triangle[0]), TRIANGLE);
    render_add_vertices(r, image, sizeof(image)/ sizeof(image[0]), IMAGE);
    
    ZLOG_INFO("%s", "Vertex buffer setup complete.");
}

void render_add_vertices(Renderer *r, Vertex *vertices, size_t v_count, int pos) {
    r->shapes[pos].vertices_count = v_count;
    
    #if DEBUG
    for(size_t i = 0; i < v_count; ++i) {
        printf("{position: %f, %f, %f} \n",  vertices[i].pos[0],   vertices[i].pos[1],   vertices[i].pos[2]);
        printf("{colors:   %f, %f, %f} \n",  vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
        printf("{uv:   %f, %f} \n",  vertices[i].uv[0], vertices[i].uv[1]);   
    }
    fprintf(stderr, "Vertices count: [%lld]\n", v_count);
    #endif

    r->shapes[pos].vertices = malloc(sizeof(Vertex) * r->shapes[pos].vertices_count);
    if(!r->shapes[pos].vertices) {
        //fprintf(stderr, "ERROR: failed to alloc mem for vertices");
        ZLOG_INFO("%s", "Failed to allocate memory for vertices");
        free(r->shapes[pos].vertices);
        r->shapes[pos].vertices = NULL;
        return;
    }
   
    memcpy(r->shapes[pos].vertices, vertices, sizeof(Vertex) * r->shapes[pos].vertices_count);

    glGenVertexArrays(1, &r->shapes[pos].vao);
    glGenBuffers(1, &r->shapes[pos].vbo);
    glBindVertexArray(r->shapes[pos].vao);
    glBindBuffer(GL_ARRAY_BUFFER, r->shapes[pos].vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * r->shapes[pos].vertices_count, r->shapes[pos].vertices, GL_STATIC_DRAW);

    /* Position */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    /* Color */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    /* Tex Coord */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    
    free(r->shapes[pos].vertices);
    r->shapes[pos].vertices = NULL;
}

void render_model(Mesh *mesh) {
    // bind the textures here
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, r->texture_id);
    // glUniform1i(glGetUniformLocation(r->shader, "minecraft_grass"), 0);

    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->indices->size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void render_img(Renderer *r) {
    //ZLOG_INFO("%s", "Rendering..");
    #if 1
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);

    GLuint location = glGetUniformLocation(r->shader, "dvd_logo");
    if(location == -1) {
        Warning("%s\n", "dvd_logo uniform not found in shader");
    }
    
    glUniform1i(location, 0);
    #endif
    //glUniform1i(glGetUniformLocation(r->shader, "dvd_logo"),  0);

    glBindVertexArray(r->shapes[IMAGE].vao);
    glDrawArrays(GL_TRIANGLES, 0, r->shapes[IMAGE].vertices_count);
    glBindVertexArray(0);
}

void render_cube(Renderer *r) {
    
    // internally parse texture path to grab the name
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    glUniform1i(glGetUniformLocation(r->shader, r->texture_uniform), 0);

    glBindVertexArray(r->shapes[CUBE].vao);
    glDrawArrays(GL_TRIANGLES, 0, r->shapes[CUBE].vertices_count);
    glBindVertexArray(0);
}

void render_triangle(Renderer *r) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    glUniform1i(glGetUniformLocation(r->shader, "minecraft_grass"), 0); // ?

    glBindVertexArray(r->shapes[TRIANGLE].vao);
    glDrawArrays(GL_TRIANGLES, 0, r->shapes[TRIANGLE].vertices_count);
    glBindVertexArray(0);
}

void render_shader(Renderer *r) {
    //ZLOG_INFO("%s", "Using shaders.");
    glUseProgram(r->shader);
}

#if 1
// need this for later (shapes & models)
void render_shader_dynamic(unsigned int shader) {
    glUseProgram(shader);
}
#endif

void render_free(Vertex *vertices) {
    free(vertices);
}

Texture load_image(char *file_name) {
    Texture texture = {0};
    stbi_set_flip_vertically_on_load(true);
   
    unsigned char *image_data = stbi_load(file_name, &texture.x, &texture.y, &texture.channels, STBI_rgb_alpha);
    if(!image_data)  {
        //fprintf(stderr, "ERROR: Failed to load texture\n");
        ZLOG_ERROR("Failed to load %s", file_name);
        stbi_image_free(image_data);
        exit(EXIT_FAILURE);
    }

    ZLOG_INFO("Successfully loaded: %s (%dx%d)", file_name, texture.x, texture.y);

    texture.image_data = image_data;
    if(texture.channels == 3) {
        ZLOG_INFO("%s", "Format: RGB");
        texture.format = GL_RGB;
    } else if(texture.channels == 4) {
        ZLOG_INFO("%s", "Format: RGBA");
        texture.format = GL_RGBA;
    } else if(texture.channels == 0) {
        ZLOG_INFO("%s", "Format: Greyscale");
        texture.format = GL_LUMINANCE;
    } else {
        ZLOG_ERROR("%s", "Invalid channel format");
        //fprintf(stderr, "ERROR: Invalid channel format\n");
        stbi_image_free(image_data);
        exit(EXIT_FAILURE);
    }

    //printf("Image Data: W: %d | H: %d\nFormat: %d\n", texture.x, texture.y, texture.format);
    return texture;
}

unsigned int generate_shader(const char *v, const char* f) {
    //printf("Reading shader files: [%s] | [%s]\n", v, f);


    unsigned int shader_id;
    char *vertex_buffer, *fragment_buffer;
    size_t vbuff_size, fbuff_size;
    read_file_t(&vertex_buffer, &vbuff_size, v);
    read_file_t(&fragment_buffer, &fbuff_size, f);

    if(vbuff_size == 0 || fbuff_size == 0) {
        fprintf(stderr, "ERROR: Shader file size is 0!\n");
        exit(EXIT_FAILURE);
    }

    //puts("Compiling vertex shader.");
    ZLOG_INFO("Compiling vertex shader [%s]", v);
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (char const * const *)&vertex_buffer, NULL);
    glCompileShader(vertex_shader);

    int status;
    char status_log[STATUS_LOG_SIZE];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(vertex_shader, sizeof(status_log), NULL, status_log);
        //fprintf(stderr, "ERROR: Vertex Shader Compilation: %s\n", status_log);
        ZLOG_ERROR("Failed to compile vertex shader [%s]: %s\n", v, status_log);
        exit(EXIT_FAILURE);
    }

    //puts("Compiling fragments shader.");
    ZLOG_INFO("Compiling fragment shader [%s]", f);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (char const * const *)&fragment_buffer, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(fragment_shader, sizeof(status_log), NULL, status_log);
        //fprintf(stderr, "ERROR: Fragment Shader Compilation: %s\n", status_log);
        ZLOG_ERROR("Failed to compile fragment shader [%s]: %s\n", f, status_log);
        exit(EXIT_FAILURE);
    }
    
    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex_shader);
    glAttachShader(shader_id, fragment_shader);
    glLinkProgram(shader_id);

    glGetShaderiv(shader_id, GL_LINK_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(shader_id, sizeof(status_log), NULL, status_log);
        fprintf(stderr, "ERROR: Shader could not link: %s\n", status_log);
        ZLOG_ERROR("Failed to link shaders %s\n", status_log);
        exit(EXIT_FAILURE);
    }

    free(vertex_buffer);
    free(fragment_buffer);
    //puts("Finished shaders.");
    return shader_id;
}

void render_set_uniform4fv(int shader, char *name, mat4 matrix) {
    int loc = glGetUniformLocation(shader, name);
    printf("Location value is %d\n", loc);

    if(loc < 0) {
        Warning("Could not find uniform variable: %s\n", name);
        exit(EXIT_FAILURE);
    }

    glUniformMatrix4fv(loc, 1, GL_FALSE, (float *)matrix);
}
