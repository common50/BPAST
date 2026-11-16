// example 1
// kinda crazy how this file went from the entire graphics engine to just an example

// i really hope that you know how to use these...
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ... since i'll only be explaining this one:
#include <BPAST/bpast.hpp>

// -------------------- do this to force discrete instead of intergrated --------------------
#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
}
#endif
// -------------------------------------------------------------------------------------------

int main() {

    // k so first do Engine and put
    // window width, window height, window title,
    // and then the .vert and .frag shader paths or wtv they're called i dont remember
    bpast::Engine engine(800, 600, "BPAST", "assets/shaders/mttns.vert", "assets/shaders/mttns.frag");
    //and then check for error
    if (!engine.isValid()) return -1;

    // versioj print for easier debug
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    // this loads garden.jpg into a gpu texture, cooltexture.id would now be the raw GL texture handle
    bpast::Texture cooltexture("assets/textures/garden.jpg");

    // set the camera world-space position
    // (i'll fix the "paws" thing later)
    engine.camera.paws = glm::vec3(0.0f, 0.0f, 3.0f);

    // this takes an .obj, shoves it thru my parser, and uploads it to the GPU (VAO, VBO, EBO)
    // and then appends it to the scene
    engine.scene.add("assets/models/rainbowcube.obj");

    // same as above, but here you give it a texture with the second parameter (true),
    // and set the texture (cooltexture.id, which we created with bpast::meowxture previously)
    engine.scene.add("assets/models/meownd.obj", true, cooltexture.id);

    // another .obj, but this one we push to the side using glm
    int mitts = engine.scene.add("assets/models/mittest.obj");
    engine.scene.get(mitts).modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

    // IMPORTANT: don't hold a get() reference across more add() calls
    // the underlying std::vector can reallocate and invalidate it
    // so don't do that (unless you want that, which i doubt)

    // true once the window's close flag is set (either ESC or the lil X in the top corner usually)
    while (!engine.shouldClose()) {

        // polls input, advances delta time, and handles input
        engine.update();

        // clears, sets view/projection and light uniforms, draws every scene object, swaps buffers
        engine.draw();
    }

    return 0; // wish i got to see this more often
}

// alr lmk if smth is not clear just message me and ill TRY and help

// -common50
