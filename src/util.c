#include "util.h"

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
