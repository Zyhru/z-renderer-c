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
        //puts("Freeing data");
        free(data);
        data = NULL;
    }
}

/*
    *
    * @param: buf -> this buffer will be used to set the full path of
    * whatever needs to be used in the renderer
    *
    * @param: x (will change var name later)
    * x -> this will be the rest of the path that will be passed in
    * by the user
    *
    * e.g 
    *
    * "assets\\penger\\penger.obj"
    *
    */

void z_get_abs_path(char *buf, size_t len, char *x) {
    char dir_buf[50];
    char *res;

    #ifdef OS_WINDOWS    
        res = _getcwd(dir_buf, sizeof(dir_buf));
    #elif
        /* Linux specific */
        res = getcwd(dir_buf, sizeof(dir_buf));
    #endif

    if(!res) {
        puts("Failed to grab current working directory");
        return;
        //perror();
    }
    
    //printf("%s\n", dir_buf);
    //printf("%s\n", x);
    //printf("%zu\n", len);
    
    int offset = 0;
    offset += snprintf(buf + offset, len - offset, "%s", dir_buf);
    offset += snprintf(buf + offset, len - offset, "%s", "\\");
    offset += snprintf(buf + offset, len - offset, "%s", x);
}

#if 0
void z_concat(char *buf, char *dir_buf, char *msg) {
    printf("CWD Path: %s\n", dir_buf);
    printf("Rest of path %s\n", msg);

    char *win_slash = "\\";
    strcat_s(buf, sizeof(buf), dir_buf);
    strcat_s(buf, sizeof(buf), win_slash);
    strcat_s(buf, sizeof(buf), msg);


    //snprintf(buf, sizeof(buf), "%s%s", dir_buf, msg);

}
#endif
