#include "model.h"

typedef enum {
    INITIAL,
    NO_SLASH,
    SINGLE_SLASH,
    DOUBLE_SLASH
} SlashTypes_E;

static void parse_no_slash(String *sb, IndexBuffer *indices) {
    puts("TESTING NEW FUNCTION");
    int zero = atoi(sb->data[1]) - 1;
    int one = atoi(sb->data[2]) - 1;
    int two = atoi(sb->data[3]) - 1;
    int three = atoi(sb->data[4]) - 1;

    //printf("New Face: {%d, %d, %d, %d}\n", zero, one, two, three);

    // first triangle
    z_append_ptr(indices, zero);
    z_append_ptr(indices, one);
    z_append_ptr(indices, two);

    // second triangle
    z_append_ptr(indices, zero);
    z_append_ptr(indices, two);
    z_append_ptr(indices, three);

}

static void parse_single_slash() {
    Warning("%s", "Parsing face with single slashes.");
}

// WARNING: Probably will not be implementing this.
static void parse_double_slash() {
    Warning("%s", "Parsing face with double slashes.");

}

String* usplit(char *line, const char *delim) {
    String *sb = init_string();
    char *context;
    char *token = strtok_s(line, delim, &context);
    int i = 0;

    // append each token to string list
    while(token != NULL) {
        append_string(sb, token);
        token = strtok_s(NULL, delim, &context);
        ++i;
    }
    
    return sb;
}

void read_mtl_file(MTLLib *mat) {
    FILE *fp = fopen(mat->file_path, "rb");
    if(!fp) {
        Warning("Unable to open file %s\n", mat->file_path);
        exit(EXIT_FAILURE);
    }

    char line[LINE_BUF_SIZE];
    puts("Reading MTL file..");
    while(fgets(line, sizeof(line), fp)) {
        
        // TODO: Save texture image (map_Kd)
        // split each line, if first token is equal to map_Kd, grab the second token
        if(strcmp(line, "map_Kd") == 0) {
            printf("Texture image: %s", line); 
        }

    }
}

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

String* init_string() {
    String *s = malloc(sizeof(String));
    s->cap = LIST_CAPACITY;
    s->size = 0;
    s->data = malloc(sizeof(char *) * s->cap); // essentially 50 char pointers

    if(!s->data) {
        Warning("%s\n", "ERROR: Failed to allocate memory for string list"); 
        exit(EXIT_FAILURE);
    }

    // now we need to allocate mem for each potential string
    // allocating 30 bytes of space for each string, which is good because our strings wont really have alot of bytes
    for(int i = 0; i < LIST_CAPACITY; ++i) {
        s->data[i] = malloc(sizeof(char) * VERTICES_CAPACITY);
        if(!s->data[i]) {
            Warning("ERROR: Cannot allocate memory for string");
            for(int j = 0; j < VERTICES_CAPACITY; ++j) {
                free(s->data[j]);
            }

            free(s->data);
            exit(EXIT_FAILURE);
        }
    }

    return s;    
}

void append_string(String *s, char *item) {
    // if the size exceeds the count limit, reallocate memory for more pointers and string data
    if(s->size >= s->cap)  {
        // reallocate memory
        size_t new_cap = s->cap * 2;
        char **temp = realloc(s->data, sizeof(char *) * new_cap);
        if(!temp) {
            Warning("%s\n", "ERROR: Unable to reallocate memory for string.\n");
            free(temp);
            exit(EXIT_FAILURE);
        }
        
        s->cap = new_cap;
        s->data = temp;
    }

    s->data[s->size++] = item;
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
OBJVertex create_obj_vertex(Vector3 pos, Vector2 uv, Vector3 vn) {
    OBJVertex ov;
    ov.v = pos;
    ov.vt = uv;
    ov.vn = vn;
    return ov;
}

void print_vertex(OBJVertex v) {
    printf("Pos: (%f, %f, %f)\n", v.v.x, v.v.y, v.v.z);
    printf("Tex: (%f, %f)\n", v.vt.x, v.vt.y);
    printf("Norm: (%f, %f, %f)\n", v.vn.x, v.vn.y, v.vn.z);
    printf("\n");
}

// O(N^2)
// TODO: Implement a hashmap for faster look up -> e.g cpp way? find()
bool is_in_vbo(VertexBuffer *vbo, OBJVertex *data) {
    //print_vertex(data);
    for(int i = 0; i < vbo->size; ++i) { // 0 < 0
        // WARNING: Refactor very sloppy. (if it works its works though?) lol

             /* Positions */
        if(data->v.x == vbo->data[i].v.x 
        && data->v.y == vbo->data[i].v.y
        && data->v.z == vbo->data[i].v.z
        
             /* Textures */
        && data->vt.x == vbo->data[i].vt.x
        && data->vt.y == vbo->data[i].vt.y
        
            /* Normals */
        && data->vn.x == vbo->data[i].vn.x 
        && data->vn.y == vbo->data[i].vn.y
        && data->vn.z == vbo->data[i].vn.z) {
            //print_vertex(data);
            //print_vertex(vbo->data[i]);
            return true;
        }
    }
    
    //printf("Unique!\n");
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


// Supporting one mesh for now
Mesh* import_model(const char *file) {
    puts("Importing model.");
    const char* space_delim = " ";
    const char* slash_delim = "/";
   
    // TODO: Fix absolute pathing, shit is ass
    char prepend[LINE_BUF_SIZE] = "C:\\Users\\zyhru\\graphics\\assets\\penger\\";
    char line[LINE_BUF_SIZE];
    
    Mesh *mesh = MeshAlloc();
    VertexBuffer *vertices = init_vertices();
    IndexBuffer *indices = init_indices(); 
    String *positions = NULL;
    String *textures = NULL;
    String *normals = NULL;
    Vector3List pos = init_vec3_list(); 
    Vector2List tex = init_vec2_list(); 
    Vector3List norm = init_vec3_list(); 
    MTLLib material;
    SlashTypes_E slash_type = INITIAL;


    VertexBuffer *ns_vertices = init_vertices();

    FILE *fp = fopen(file, "rb");
    if(!fp) {
        fprintf(stderr, "ERROR: Failed to open obj file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    
    printf("Parsing model: %s\n", file);
    int vertex_index = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        
        if(line[0] == 'm') {
            size_t mtlfile_len = (strlen(line) - 1) - MATERIAL_FILE_OFFSET;
            char *material_file = malloc(mtlfile_len + 1);
            if(!material_file) {
                Warning("%s\n", "Could not allocate memory for the material file.");
                exit(EXIT_FAILURE);
            }

            for(int i = MATERIAL_FILE_OFFSET, c = 0; i < strlen(line); ++i, c++) {
                material_file[c] = line[i];
            }
            
            material_file[mtlfile_len] = '\0';
            
            for(int i = 0; i < strlen(material_file); ++i) {
                printf("test: %d\n", (int)material_file[i]);
            }
            
            printf("line Length: %zu\n", strlen(line));
            printf("mtlfile Length: %zu\n", mtlfile_len);
            printf("material_file Length: %zu\n", strlen(material_file));

            snprintf(material.file_path, sizeof(material.file_path), "%s%s", prepend, material_file);
            //printf("MTL file path: %s\n", material.file_path);
            read_mtl_file(&material);
            //return mesh;
        }

        if(line[0] == 'v' && line[1] == ' ') {
            //puts("Parsing vertices");
            positions = usplit(line, space_delim);
            if(!positions) {
                Warning("%s\n", "Generating positions has failed. (null)");
                exit(EXIT_FAILURE);
            }
            float x = atof(positions->data[1]);
            float y = atof(positions->data[2]);
            float z = atof(positions->data[3]);
            //printf("Positions: %f, %f, %f\n", x,y,z);
            z_append(pos, create_vec3(x,y,z));
        }

        if(line[0] == 'v' && line[1] == 't') {
            textures = usplit(line, space_delim);
            if(!textures) {
                Warning("%s\n", "Generating textures has failed. (null)");
                exit(EXIT_FAILURE);
            }
            float x = atof(textures->data[1]);
            float y = atof(textures->data[2]);
            //printf("Textures: %f, %f,\n", x,y);
            z_append(tex, create_vec2(x,y));
        }

        if(line[0] == 'v' && line[1] == 'n') {
            normals = usplit(line, space_delim);
            if(!normals) {
                Warning("%s\n", "Generating normals has failed. (null)");
                exit(EXIT_FAILURE);
            }

            float x = atof(normals->data[1]);
            float y = atof(normals->data[2]);
            float z = atof(normals->data[3]);
            //printf("Normals: %f, %f, %f\n", x,y,z);
            z_append(norm, create_vec3(x,y,z));
        }
      
        // TODO: Parse no slash [DONE]
        // TODO: Parse single slash
        // TODO: Parse double slash
        if(line[0] == 'f') {
            String *sb = usplit(line, space_delim);
            char *res = strchr(line, space_delim[0]);
            if(!res) {
                puts("Parsing face with no slashes.\n");
                slash_type = NO_SLASH;
            } else {
                long long position = res - line;
                if(line[position + 1] == '/') {
                    slash_type = DOUBLE_SLASH;
                } else { 
                    slash_type = SINGLE_SLASH;
                }
            }
            
            #if 0
            for(int i = 1; i < sb->size; ++i) {
                // TODO: If there is a slash then do this [ ]
                // TODO: If there is a double slash then do this
                // TODO: If there is a not a slash then do this
                String *faces = usplit(sb->data[i], slash_delim); // 11 1 2

                OBJVertex v;
                int pos_index = atoi(faces->data[0]) - 1; 
                int tex_index = atoi(faces->data[1]) - 1;
                int norm_index = atoi(faces->data[2]) - 1;
               
                v.v = pos.data[pos_index];
                v.vt = tex.data[tex_index];
                v.vn = norm.data[norm_index];
               
                #if 0 
                for(int i = 0; i < pos.size; ++i) {
                    printf("Pos %d: (%f, %f, %f)\n", i, pos.data[i].x, pos.data[i].y, pos.data[i].z);
                }
                printf("Pos Index: %d\n", pos_index); 
                printf("Tex Index: %d\n", tex_index); 

                //printf("Pos %d: (%f, %f, %f)\n", i, v.v.x, v.v.y, v.v.z);
                //printf("UV %d: (%f, %f)\n", i, v.vt.x, v.vt.y);
                #endif

                // ignoring duplicate vertices
                z_append_ptr(vertices, v);
                free(faces);
            }
            #endif

            //printf("Vertices Size: [%zu]\n", vertices->size);
            if(sb->size == 4) {
                puts("No need for triangluation.");
                z_append_ptr(indices, vertices->size - 3);
                z_append_ptr(indices, vertices->size - 2);
                z_append_ptr(indices, vertices->size - 1);
            } else if(sb->size  == 5) {
                puts("Triangulating face with a size of 4.");
                if(slash_type == NO_SLASH) {
                    parse_no_slash(sb, indices);
                } else {
                    // first triangle
                    z_append_ptr(indices, vertices->size - 4);
                    z_append_ptr(indices, vertices->size - 3);
                    z_append_ptr(indices, vertices->size - 2);
                    
                    // second triangle
                    z_append_ptr(indices, vertices->size - 4);
                    z_append_ptr(indices, vertices->size - 2);
                    z_append_ptr(indices, vertices->size - 1);
                }
               
            } else if(sb->size == 7) {
                puts("Triangulating face with a size of 6.");
                for(int i = vertices->size - 6; i < vertices->size; ++i) {
                    z_append_ptr(indices, i);
                }
            }
            
            free(sb);
        }
    }

    if(slash_type == NO_SLASH) {
        puts("MAJOR MINOR PATCH Setting positions to vertices.");
        for(int i = 0; i < pos.size; ++i) {
            // add the positions to the vbo
            OBJVertex obj_vertex;
            obj_vertex.v = pos.data[i];
            z_append_ptr(vertices, obj_vertex);
            //printf("{%f, %f, %f}\n", obj_vertex.v.x, obj_vertex.v.y, obj_vertex.v.z);
        }
    }
   
    mesh->vertices = vertices;
    mesh->indices = indices;
  
    fclose(fp);
    free(positions);
    free(textures);
    free(normals);
    free(pos.data);
    free(norm.data);
    free(tex.data);
    puts("Finished parsing model.");
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
