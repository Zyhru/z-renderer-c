# TODOs for Renderer Project

## Cross-platform support
- [ ] Fix up the cross-platform support for 
    - MSVC
    - MinGW
    - Unix? 
    - Fix MSVC bullship compiler warnings
    - Cleanup toolchain .cmake and remove GCC_EXECUTABLE logic
    - Cleanup CMakeLists.txt for proper cross-platform support.. I think? 
- [ ] Setup a system on whether to use / or \\ depending on the OS, so that we can load textures/shaders successfully based on the users system

## Logging
- [ ] Add a verbose logging system
- [ ] Add more logging information when rendering
- [ ] Look at other projects with a logging system for inspiration

## .obj importer improvements 
- [x] Fix parsing .obj file with faces for no slash
- [x] Fix parsing .obj file with faces for single slashes
- [ ] Fix parsing .obj file with faces for double slashes (not doing this right now) 
- [x] Fix the logic of sending file paths to various functions 

## General TODO
- [x] Implement camera movement (left, right, forward, backward)  
- [x] Implement camera look-around using mouse input  
- [x] Add texture support  
- [x] Refactor shader creation to be dynamic  
- [ ] Complete 3D Model Loading (.obj)  
  - [ ] Handle more advanced features (e.g., multiple meshes)  
  - [ ] Support textures and materials in .obj parsing  
- [ ] Create a custom color struct for easier window color changes  
- [ ] Implement font rendering (e.g., display FPS)  
- [x] Add a macro for `init_T_list`  
- [ ] Add ImGui -> (WORK ON THIS NEXT)
- [ ] Test cross-platform building for Linux 
- [x] Improved logging system with colors, time, function name, and line
- [ ] Render a base floor e.g -> grass, water, or concrete, street 
- [ ] Add gravity and collision
---

## Current Focus
### OBJ Importer
- [x] Parse vertices (`v`)  
- [x] Parse textures (`vt`)  
- [x] Parse normals (`vn`) (defer lighting implementation for now)  
- [x] Handle faces with slashes (e.g., `f v/vt/vn`)  
- [ ] Support textures and materials when parsing (`.mtl`)  
- [ ] Handle duplicate vertices within VBO  
- [x] Test parser with more complex models (e.g., `gravestone.obj`)  

### Textures
- [x] Load texture images using `stb_image.h`  
- [x] Configure mipmap filtering options  
- [x] Set up texture in shaders and attribute pointers  
- [x] Use `sampler2D` uniform variable for textures  
- [x] Activate texture during rendering  

---

## Debugging Progress
### Fixed Bugs
- [x] Camera movement was too fast (callback issue)  
- [x] Camera Z-axis alignment issue  
- [x] Initial camera direction offset in `camera_look_around` function  
- [x] Incorrect usage of `malloc` in `z_malloc`  
  - Fixed from `malloc(sizeof(size))` to `malloc(size)`  

### Issues to Address
- [ ] Improve `is_in_vbo` logic (current brute-force approach is inefficient)  
- [ ] Clean up shader uniform logic for various shaders  
- [ ] Implement a hashmap for faster lookups in parsing  

---

## Backlog
- [ ] Begin implementing arena allocator (for optimized memory management)  
- [x] Generate better documentation to understand code after breaks  
- [ ] Implement font rendering (e.g., FPS counter)  
- [ ] Test importer with multiple meshes and materials  

---

## Notes & Learnings
- Vector math results in new vectors; don’t modify existing ones.  
- Using `extern`: Declare, then define before use.  
- Be cautious with heap allocations and memory management when passing `Mesh` data.  
- **Progress:** Fixed heap allocation issues in `import_model` by revising custom `malloc`.  
- For better debugging, use descriptive macros and comments.  

---

### Timeline-Based TODOs
#### 11/19/2024  
- [ ] Parse .mtl file for map_Kd
- [ ] Apply textures to model

#### 11/17/2024  
- [ ] Support textures in `.obj` parsing.  
- [ ] Begin supporting models with multiple meshes.  

#### 11/10/2024  
- [x] Port testing code into main production.  
- [ ] Test rendering outline of `gravestone.obj` using vertex positions.  

#### 11/3/2024  
- [x] Integrate normals parsing.  
- [x] Review parsing logic and diagrams.  
- [ ] Improve documentation for easier onboarding after breaks.  

### 10/27/2024  
- [ ] Parse slashes in face data.  

### 10/22/2024  
- [ ] Test parser with complex objects.  
- [ ] Handle cases where `.obj` has faces with more than 6 vertices.  
- [ ] Begin parsing texture coordinates (`vt`) for `gravestone.obj`.  

### 10/21/2024  
- [x] Continue reading Ryan Fleury’s article on arena allocators.  
- [x] Debug `destroy` function (free issues).  
- [ ] Test parser with complex objects.  
- [ ] Begin parsing texture coordinates (`vt`).  

### 10/20/2024  
- [-] Read Ryan Fleury’s article on arena allocators (partial progress).  
- [x] Debug freeing model memory issues.  
- [ ] Implement arena allocator in main production code.  
- [x] Push updated code.  

### 10/19/2024  
- [ ] Debug heap error when freeing model memory.  

### 10/18/2024  
- [x] Build debug mode script.  
- [x] Debug triangle rendering in debug mode.  
- [x] Render cube from `cube.obj`.  
- [ ] Debug heap error when freeing model memory.  

### 10/16/2024  
- [x] Learn more about macros.  
- [x] Debug `glfwwindow` and importer memory issues.  
- [ ] Investigate `destroy(char **s, char **t)` (not deallocating correctly).  
- [ ] Clean up shader uniform logic.  
- [ ] Implement hashmap for faster lookups.  

### 10/15/2024  
- [ ] Log daily progress consistently.  
- [x] Clean up file structure.  
- [x] Migrate test 3D importer to main production.  
- [x] Add shader creation functions.
