#include "renderer.h"
#include "util.h"

void clear_color() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
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
}

void render_add_vertices(Renderer *r, Vertex *vertices, size_t v_count) {
  
    #if DEBUG
    for(size_t i = 0; i < v_count; ++i) {
        printf("{position: %f, %f, %f} \n",  vertices[i].pos[0],   vertices[i].pos[1],   vertices[i].pos[2]);
        printf("{colors:   %f, %f, %f} \n",  vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
    }
    #endif

    r->vertices_count = v_count;
    fprintf(stderr, "Vertices count: [%lld]\n", v_count);

    r->vertices = (Vertex *) malloc(sizeof(Vertex) * r->vertices_count);
    if(!r->vertices) {
        fprintf(stderr, "ERROR: failed to alloc mem for vertices");
        free(r->vertices);
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
}

void render(Renderer *r) {
    glBindVertexArray(r->vao);
    glDrawArrays(GL_TRIANGLES, 0, r->vertices_count);
    glBindVertexArray(0);
}

void render_shader(Renderer *r) {
    glUseProgram(r->shader);
}
