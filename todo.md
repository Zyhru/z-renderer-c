## General TODO
- [x] Implement moving camera left, right, forward and backwards
- [x] Implement camera look around based on the mouse position
- [x] Textures 
- [x] Refactor to make creating a shader dynamic
- [ ] 3D Model Loading (.obj) (more than partially done)
- [ ] Custom color struct to pass easily change the window color
- [ ] Font rendering (to add FPS)
- [ ] create a macro for init_T_list

## Bugs
- camera movement is being registered to fast due to the callback. [fixed]
- Camera z axis is fucked still [fixed]
- With the addition of the camera_look_around function, the initial camera direction is offsetted by alot. (need to fix: nothing major though)
- Implementation of z_malloc was incorrect. I was doing void *data = malloc(sizeof(size))
instead of void *data = malloc(size);

sizeof(size) is always going to return the size of the **size_t size** parameter which is 8, since size_t is 8 bytes

## Textures TODO [done]
- Load in the texture image with stb_image.h
- Set mip map filtering options
- Set up texture in shader and attribpointer
- set up texture sampler2D uniform var
- activate the texture when rendering

## 10/21/24 TODO: 
- [x] Continue reading Ryan Fleurys article on Arena Allocators 
- [x] Debug destroy function (within model.c) (free issues) (fixed 10/21/24)
- [ ] Test our obj parser on more complex objects
- [ ] Begin testing parsing vt (vertices for textures (uv's)) for our final model (gravestone)

## 10/20/24 TODO: 
- [-] Read Ryan Fluerys article on Arena Allocator (https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator) (read a little bit)
- [x] Keep on debugging -> freeing model issue.
- [ ] Implement an arena allocator to migrate to main prod code for the renderer
- [x] Push updated code

## 10/19/24 TODO: 
- [ ] Figure out why freeing the model gives me a heap error

## 10/18/24 TODO: 
- [x] Build a debug mode script for debugging purposes
- [x] Triangle not being rendered in debug mode
- [x] Render cube from cube.obj :)
- [ ] Figure out why freeing the model gives me a heap error

## 10/16/24 TODO: 
- [x] Read more on macros
- [x] Debug more on the importer and glfwwindow not freeing (debug mode)
- [ ] Investigate *destroy(char **s, char **t)* function. Not de-allocating correctly
- [ ] Clean up shader uniform logic for various shaders
- [ ] Implement a hashmap for faster lookup times 

## 10/15/24 (Tomorrow) TODO: 
- [ ] Jot down what I've completed each day. e.g (10/15/24) -> Tasks Completed: - [ ] printed hello world (some shit like that))
- [x] Clean up file structure
- [x] Migrate my test 3D importer to main production 
- [x] Shader function to create different shader id's


## Importer TODO
- [x] Read each line, revise and test (almost done)
- [x] handle various faces (just focus on making one thing work and work on this later)
- [x] dynamic array for v,vt and normals
- [x] parse vertices
- [x] parse textures
- [ ] parse normals (save for later, once I feel like adding lighting)
- Apply testing code into main production code

## Issues 
- When using extern Paths path, you must use the same name. I was using
Paths paths (in renderer.c oops..) which != Paths path

- Had some trouble passing the Mesh data back locally. Involves heap allocation and that crazy magic. Need to look into macros with
dynamic memory allocation

- Finally got over the heap allocation hump that involved import_model (Mesh *). I created a custom malloc function and the internals was incorrect,
see WARNING code above import_model

- Fixed: Destroy function was having issues with freeing my temp arrays for parsing the v and vt. I was allocating only 4 bytes for each v position. (To small)

## Notes:
- When doing any type of Vector Math, the result will always be a new vector.
- When using **extern** you must first declare, then define it wherever you want to use it.
- Made some progress, need to figure out a way of passing mesh info from heap back to main
- z_malloc logic was incorrect
