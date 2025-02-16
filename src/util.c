#include "util.h"

void z_print_vec3(Vector3 *data, int size) {
    for(int i = 0; i < size; ++i) {
        printf("{%f, %f, %f}\n", 
               data[i].x, 
               data[i].y,
               data[i].z);
    }
}

void* z_malloc(size_t size, const char *name) {
    void *ptr = malloc(size);
    if(!ptr) {
        ZMALLOC_ERROR("%s", "{%s}", "ERROR: Failed to allocate memory for", name);
        return NULL;
    }
    
    //printf("Memory allocated: [%zu] bytes for [%s]\n", size, name);
    return ptr;
}

void z_read_file(char** buffer, size_t *buffer_size, const char *path) {
    FILE *fp = fopen(path, "rb");
    if(!fp) {
        fprintf(stderr, "ERROR: Incorrect path: %s\n", path);
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    *buffer_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *buffer = malloc(*buffer_size + 1);
    if(!(*buffer)) {
        fprintf(stderr, "ERROR: failed to alloc mem for buffer");
        fclose(fp);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fread(*buffer, *buffer_size, 1, fp);
    (*buffer)[*buffer_size] = '\0';
    fclose(fp);
}

void z_free_data(void *data) {
    if(data) {
        puts("Freeing data");
        free(data);
        data = NULL;
    }
}
