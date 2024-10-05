#include "renderer.h"
#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void clear_color() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void render_init(Renderer *r) {
    r->vertices = NULL; 
    puts("Reading shader files.");
    const char *vertex_glsl = read_file("C:\\Users\\zyhru\\graphics\\vertex.vert");
    const char *fragment_glsl = read_file("C:\\Users\\zyhru\\graphics\\fragment.frag");

    if(!vertex_glsl || !fragment_glsl) {
        fprintf(stderr, "ERROR: Could not read shaders");
    }

    puts("Compiling vertex shader.");
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_glsl, NULL);
    glCompileShader(vertex_shader);

    int status;
    char status_log[STATUS_LOG_SIZE];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(vertex_shader, sizeof(status_log), NULL, status_log);
        fprintf(stderr, "ERROR: Vertex Shader Compilation: %s\n", status_log);
        return;
    }

    puts("Compiling fragments shader.");
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_glsl, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(fragment_shader, sizeof(status_log), NULL, status_log);
        fprintf(stderr, "ERROR: Fragment Shader Compilation: %s\n", status_log);
        return;
    }
   
    // Link shaders
    r->shader = glCreateProgram();
    glAttachShader(r->shader, vertex_shader);
    glAttachShader(r->shader, fragment_shader);
    glLinkProgram(r->shader);

    free((char *)vertex_glsl);
    free((char *)fragment_glsl);
    
    puts("Finished shaders.");

    puts("Initialing textures.");
    glGenTextures(1, &r->texture_id);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Texture texture = load_image("C:\\Users\\zyhru\\graphics\\minecraft_grass.jpg");
    printf("Image Data: W: %d | H: %d\nFormat: %d\n", texture.x, texture.y, texture.format);
    puts("Finished textures.");
}

void render_add_vertices(Renderer *r, Vertex *vertices, size_t v_count) {
    r->vertices_count = v_count;
    #if DEBUG
    for(size_t i = 0; i < v_count; ++i) {
        printf("{position: %f, %f, %f} \n",  vertices[i].pos[0],   vertices[i].pos[1],   vertices[i].pos[2]);
        printf("{colors:   %f, %f, %f} \n",  vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
        printf("{uv:   %f, %f} \n",  vertices[i].uv[0], vertices[i].uv[1]);   
    }
    fprintf(stderr, "Vertices count: [%lld]\n", v_count);
    #endif

    r->vertices = (Vertex *) malloc(sizeof(Vertex) * r->vertices_count);
    if(!r->vertices) {
        fprintf(stderr, "ERROR: failed to alloc mem for vertices");
        free(r->vertices);
        r->vertices = NULL;
        return;
    }
   
    memcpy(r->vertices, vertices, sizeof(Vertex) * r->vertices_count);
    
    glGenVertexArrays(1, &r->vao);
    glGenBuffers(1, &r->vbo);
    
    glBindVertexArray(r->vao);
    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * r->vertices_count, r->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
}

void render(Renderer *r) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, r->texture_id);
    glUniform1i(glGetUniformLocation(r->shader, "minecraft_grass"), 0);

    glBindVertexArray(r->vao);
    glDrawArrays(GL_TRIANGLES, 0, r->vertices_count);
    glBindVertexArray(0);
}

void render_shader(Renderer *r) {
    glUseProgram(r->shader);
}

void render_free(Vertex *vertices) {
    free(vertices);
}

 Texture load_image(const char *file_name) {
    Texture texture = {0};
    unsigned char *image_data = stbi_load(file_name, &texture.x, &texture.y, &texture.channels, STBI_rgb_alpha);
    if(!image_data)  {
        fprintf(stderr, "ERROR: Failed to load texture\n");
        stbi_image_free(image_data);
        exit(EXIT_FAILURE);
    }

    texture.image_data = image_data;

    if(texture.channels == 3) {
        puts("Format: RGB");
        texture.format = GL_RGB;
    } else if(texture.channels == 4) {
        puts("Format: RGBA");
        texture.format = GL_RGBA;
    } else if(texture.channels == 0) {
        puts("Format: Greyscale");
        texture.format = GL_LUMINANCE;
    } else {
        fprintf(stderr, "ERROR: Invalid channel format\n");
        stbi_image_free(image_data);
        exit(EXIT_FAILURE);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.x, texture.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture.image_data);
    return texture;
}
