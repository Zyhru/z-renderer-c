/*
 * Dev: @z7hru or @zai or @zyhru
 *
 * This file is for testing purposes only.
 * Because it's easier and faster to compile instead of rebuilding my whole project
 * where things will break due to OpenGL.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
    #define OS_WINDOWS
    #include <direct.h>
#elif __linux__
    #define OS_LINUX
    #include <unistd.h>
#endif


enum {
    NO_SLASH,
    SINGLE_SLASH,
    DOUBLE_SLASH
} SlashTypes_E;

void z_concat_test() {


}

void z_absolute_path() {
    char *current_dir;
    char dir_buf[512];
    
    #ifdef OS_WINDOWS    
        current_dir = _getcwd(dir_buf, sizeof(dir_buf)); 
    #elif
        current_dir = getcwd(dir_buf, sizeof(dir_buf)); 
    #endif

    if(!current_dir) {
        perror("_getcwd");
        return;
    }
    

    char buf[128] = {0};
    char *slash = "\\";

    #if 0
    strcat(buf, dir_buf);
    strcat(buf, slash);
    strcat(buf, "assets\\penger\\penger.obj");
    #endif

    snprintf(buf, sizeof(buf), "%s%s%s", dir_buf, slash, "penger.obj");
    printf("Full path: %s\n", buf);
}

int main() {
    z_absolute_path(); 
    return 0;
}
