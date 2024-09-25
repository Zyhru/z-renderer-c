#include "renderer.h"
#include "window.h"

int main(void) {
    Context *ctx = window_init();
    if(!ctx) return -1;
    
    // TODO: Impl Renderer
    Renderer r;
    render_init(&r);

    Vertex triangle[] = {
        {{0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // Vertex 1: Position + Color
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Vertex 2: Position + Color
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}   // Vertex 3: Position + Color
    };
    
    
    size_t v_count = sizeof(triangle) / sizeof(triangle[0]);
    render_add_vertices(&r, triangle, v_count);

    printf("Shader No. %u\n", r.shader);

    while(!window_closed(ctx->window)) {
        clear_color(); // TODO: pass in custom colors
        
        render_shader(&r);
        render(&r);

        poll_events();
        swap_buffers(ctx->window);
    }
    
    window_free(ctx);
    free(r.vertices);
    return 0;
}
