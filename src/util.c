#include "util.h"

void z_log_msg(const char *level, const char *file, int line, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);
    
    printf("[%s] [%s] %s:%d - ", time_str, level, file, line);
    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}

void* z_malloc(size_t size, const char *name) {
    void *ptr = malloc(size);
    if(!ptr) {
        ZMALLOC_ERROR("%s", "{%s}", "ERROR: Failed to allocate memory for", name);
        return NULL;
    }
    
    printf("Memory allocated: [%zu] bytes for [%s]\n", size, name);
    return ptr;
}

char* read_file(const char* path) {
    FILE *fp = fopen(path, "rb");
    if(!fp) {
        fprintf(stderr, "ERROR: could not open file: [%s\n]", path);
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if(!buffer) {
        fprintf(stderr, "ERROR: failed to alloc mem for buffer");
        fclose(fp);
        free(buffer);
        return NULL;
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);
    buffer[file_size] = '\0';

    return buffer;
}

void read_file_t(char** buffer, size_t *buffer_size, const char *path) {
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

void free_data(void *data) {
    if(data) {
        puts("Freeing data");
        free(data);
        data = NULL;
    }
}
