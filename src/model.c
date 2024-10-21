#include "model.h"

Mesh* MeshAlloc() {
    Mesh *m = z_malloc(sizeof(Mesh), "Mesh");
    if(!m) {
        Warning("%s\n", "Mesh pointer is null");
        exit(EXIT_FAILURE);
    }

    m->vao = 0;
    m->vbo = 0;
    m->ebo = 0;
    m->shader = 0;
    
    m->vertices = init_vertices();
    m->indices = init_indices();
    return m;
}

VertexBuffer* init_vertices() {
    VertexBuffer *vertices = z_malloc(sizeof(VertexBuffer), "VertexBuffer");
    if(!vertices) {
        Warning("%s\n", "Vertex pointer is null");
        exit(EXIT_FAILURE);
    }
    vertices->capacity = LIST_CAPACITY;
    vertices->size = 0;
    vertices->data = z_malloc(sizeof(OBJVertex) * vertices->capacity, "OBJVertex");
    if(!vertices->data) {
        Warning("%s\n", "Vertex data is null");
        free(vertices->data);
        vertices->data = NULL;
        exit(EXIT_FAILURE);
    }

    return vertices;
}

IndexBuffer* init_indices() {
    IndexBuffer *indices = z_malloc(sizeof(IndexBuffer), "IndexBuffer");
    if(!indices) {
        Warning("%s\n", "Indices pointer is null");
        exit(EXIT_FAILURE);
    }
    indices->capacity = LIST_CAPACITY;
    indices->size = 0;
    (indices->data) = z_malloc(sizeof(unsigned int) * indices->capacity, "unsigned int");
    if(!indices->data) {
        Warning("%s\n", "Indices data is null");
        free(indices->data);
        indices->data = NULL;
        exit(EXIT_FAILURE);
    }
    return indices;
}

FaceElements init_faces() {
    FaceElements faces;
    faces.capacity = LIST_CAPACITY;
    faces.size = 0;
    faces.data = malloc(sizeof(uint32_t) * faces.capacity);
    if(!faces.data) {
        fprintf(stderr, "ERROR: Failed allocate memory for {FaceList}\n");
        free(faces.data);
        exit(EXIT_FAILURE);
    }

    return faces;
}

Vector3List init_vec3_list() {
    Vector3List list;
    list.capacity = LIST_CAPACITY;      
    list.size = 0;
    list.data = malloc(sizeof(Vector3) * list.capacity);
    if(!list.data) {
        fprintf(stderr, "ERROR: Failed allocate memory for {Vec3List}\n");
        free(list.data);
        exit(EXIT_FAILURE);
    }

    return list;
}

Vector2List init_vec2_list() {
    Vector2List list;
    list.capacity = LIST_CAPACITY;    
    list.size = 0;
    list.data = malloc(sizeof(Vector2) * list.capacity);
    if(!list.data) {
        fprintf(stderr, "ERROR: Failed allocate memory for {Vec2List}\n");
        free(list.data);
        exit(EXIT_FAILURE);
    }

    return list;
}

Vector2 create_vec2(float x, float y) {
    Vector2 v2;
    v2.x = x;
    v2.y = y;
    return v2;
}

Vector3 create_vec3(float x, float y, float z) {
    Vector3 v3;
    v3.x = x;
    v3.y = y;
    v3.z = z;
    return v3;
}

// TODO: Test with textures
OBJVertex create_vertex(Vector3 pos, Vector2 uv) {
    OBJVertex ov;
    ov.v = pos;
    //ov.vt = uv;
    return ov;
}

// O(N^2)
// TODO: Implement a hashmap for faster look up -> e.g cpp way? find()
bool is_in_vbo(VertexBuffer *vbo, OBJVertex data) {
    for(int i = 0; i < vbo->size; ++i) { // 0 < 0
        if(data.v.x == vbo->data[i].v.x 
        && data.v.y == vbo->data[i].v.y
        && data.v.z == vbo->data[i].v.z) {
            return true;
        }
    }
    
    return false;
}

// 10/15/2024: Safer split version with new strtok and strcpy functions
void split(char **array, char *line, const char *delim) {
    int i = 0;
    char *context;
    char *token = strtok_s(line, delim, &context);
    while(token != NULL) {
        strcpy_s(array[i], sizeof(array[i]), token);
        token = strtok_s(NULL, delim, &context);
        ++i;
    }

}

// 10/21/2024: Issue fixed on freeing memory allocating for temp_pos. I was only using 4 bytes of memory allocation per string.
// TODO: Change memory allocation from heap to stack, since I know how much memory I need.
void destroy(char **s, char **t) {
    for(int i = 0; i < VERTEX_SIZE; ++i) {
        if(s[i]) {
            free(s[i]);
            s[i] = NULL;
        }
    }

    for(int i = 0; i < TEXTURE_SIZE; ++i) {
        if(s[i]) {
            free(t[i]);
            s[i] = NULL;
        }
    }
}


// Supporting one mesh for now
// WARNING: z_malloc
// 10/20/2024 : z_malloc was giving us our heap issues. Mistake: malloc(sizeof(size)) instead of malloc(size); (bruh)
Mesh* import_model(const char *file) {
    puts("Importing model.");
    Mesh *mesh = MeshAlloc();
    VertexBuffer *vertices = init_vertices();
    IndexBuffer *indices = init_indices(); 
    
    const char* space_delim = " ";
    char line[LINE_BUF_SIZE];
    char *temp_pos[VERTEX_SIZE] = {0};
    char *temp_tex[TEXTURE_SIZE] = {0};
    Vector3List pos = init_vec3_list(); 
    Vector2List tex = init_vec2_list(); 

    //TODO: try fopen_s
    FILE *fp = fopen(file, "rb");
    if(!fp) {
        fprintf(stderr, "ERROR: Failed to open obj file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // BUG: 10/21/2024 Fixed freeing issue. Check todo.md
    for(int i = 0; i < VERTEX_SIZE; ++i) {
        temp_pos[i] = malloc(sizeof(char) * VERTICES_CAPACITY);
        if(!temp_pos[i]) {
            fprintf(stderr, "ERROR: Cannot allocate memory for temp_pos");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < TEXTURE_SIZE; ++i) {
            temp_tex[i] = malloc(sizeof(char) * VERTICES_CAPACITY);
            if(!temp_tex[i]) {
                fprintf(stderr, "%s", "ERROR: Cannot allocate memory for temp_tex\n");
                exit(EXIT_FAILURE);
            }
    }
    
    puts("Parsing model.");
    while(fgets(line, sizeof(line), fp) != NULL) {
        if(line[0] == 'v' && line[1] == ' ') {
            split(temp_pos, line, space_delim);
            float x = atof(temp_pos[1]);
            float y = atof(temp_pos[2]);
            float z = atof(temp_pos[3]);
            z_append(pos, create_vec3(x,y,z));
        }

        if(line[0] == 'v' && line[1] == 't') {
            split(temp_tex, line, space_delim);
            float x = atof(temp_tex[1]);
            float y = atof(temp_tex[2]);
            z_append(tex, create_vec2(x,y));
        }
       
        if(line[0] == 'f') {
            FaceElements faces = init_faces();
            for(int i = 2; i < strlen(line) - 2; ++i) {
                if(line[i] != ' ') {
                    int data = line[i] - '0';
                    z_append(faces, data);
                }
            }
            
            for(int i = 0; i < faces.size; ++i) {
                OBJVertex v;
                v.v = pos.data[faces.data[i] - 1];
                if(!is_in_vbo(vertices, v)) {
                    z_append_ptr(vertices, v);
                }
            }
           
            if(faces.size == 4) { /* Triangulate */
                /* triangle 1 */
                z_append_ptr(indices, faces.data[0] - 1);
                z_append_ptr(indices, faces.data[0 + 1] - 1);
                z_append_ptr(indices, faces.data[0 + 2] - 1);

                /* triangle 2 */
                z_append_ptr(indices, faces.data[0] - 1);
                z_append_ptr(indices, faces.data[0 + 2] - 1);
                z_append_ptr(indices, faces.data[0 + 3] - 1);
            } else if(faces.size == 3) {
                // TODO: Implement regular triangles
            }
            
            free(faces.data);
        }
    }
    
    puts("Finished parsing model.");
   
    mesh->vertices = vertices;
    mesh->indices = indices;
  
    fclose(fp);
    destroy(temp_pos, temp_tex);     
    free(pos.data);
    free(tex.data);
    puts("Finished importing model.");
    return mesh;
}

void model_free(Mesh *model) {
    if (model) {
        free(model->vertices);
        free(model->indices);
		free(model);
        model = NULL;
    }
}


/*
C:\Users\zyhru\graphics\src\model.c(188,9): warning C4133: 'function': incompatible types - from 'FILE *' to 'const char *const ' [C:\Users\zyhru\graphics\build\Z-Renderer.vcxproj]
C:\Users\zyhru\graphics\src\model.c(197,13): warning C4133: 'function': incompatible types - from 'FILE *' to 'const char *const ' [C:\Users\zyhru\graphics\build\Z-Renderer.vcxproj]
C:\Users\zyhru\graphics\src\model.c(205,17): warning C4133: 'function': incompatible types - from 'FILE *' to 'const char *const ' [C:\Users\z
*/
