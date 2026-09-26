// graphics engine but i lowkey cheat using opengl and glfw cus im lazy
// be patient and sit still

// 2 lines for functions else ill go insane


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// bpast ******
#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/core/meowmera.hpp>
#include <BPAST/core/meowindow.hpp>
// bpast ******

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
}
#endif





// shader source strings or wtv its called im still not sure how it works
// vertex shader:
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec3 meowtexColor;
out vec2 meowtexCoord;
out vec3 meowMal;
out vec3 fragPaws;
uniform mat4 meowdel;
uniform mat4 miew;
uniform mat4 meowjection;
void main() {
    gl_Position = meowjection * miew * meowdel * vec4(aPos, 1.0);
    fragPaws = vec3(meowdel * vec4(aPos, 1.0));
    meowMal = mat3(transpose(inverse(meowdel))) * aNormal;
    meowtexColor = aColor;
    meowtexCoord = aTexCoord;
}
)";

// fragment shader:
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 meowtexColor;
in vec2 meowtexCoord;
in vec3 meowMal;
in vec3 fragPaws;
out vec4 FragColor;
uniform sampler2D meowtex;
uniform bool huhTexture;
uniform vec3 lightPaws;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 viewPaws;
uniform float meownCutOff;
uniform float meowterCutOff;
uniform bool crashLightOn;

void main() {
    vec3 baseColor = huhTexture ? texture(meowtex, meowtexCoord).rgb : meowtexColor;

    vec3 ambient = 0.05 * lightCol;

    vec3 norm = normalize(meowMal);
    vec3 toLight = normalize(lightPaws - fragPaws);

    float theta = dot(toLight, normalize(-lightDir));
    float epsilon = meownCutOff - meowterCutOff;
    float spotlight = crashLightOn ? clamp((theta - meowterCutOff) / epsilon, 0.0, 1.0) : 0.0;

    float diff = max(dot(norm, toLight), 0.0);
    vec3 diffuse = diff * lightCol * spotlight;

    vec3 viewDir = normalize(viewPaws - fragPaws);
    vec3 reflectDir = reflect(-toLight, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = 0.5 * spec * lightCol * spotlight;

    FragColor = vec4((ambient + diffuse + specular) * baseColor, 1.0);
}
)";





// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX global vars n straight bars XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// TO DO: remove all this stuff and make vars not global because its bad

// i always keep it neat with the global vars cus i like to know where they are and what they do
// else ill mess up, seriously, i dont know what my problem is when i have messy globals

// functions n stuff can be all over the place idc i can handle that
// but dont mess with my global vars

    // camera stuff ----------------------------------------
    meowmera meowmera;



    // mouse stuff -----------------------------------------
    float lastXmeowse = 400.0f, lastYmeowse = 300.0f;
    bool firstmeowse = true; // was told to add this

    bool meowsorLocked = true;

    // keyboard stuff --------------------------------------
    bool crashLightOn = true;



    // frame timing stuff ---------------------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f; // couldnt come up with some corny name so just left it like this


    // window stuff ---------------------------------------
    meowindow window(800, 600, "BPAST"); // if it breaks it breaks, checked in main


    // uniforms -------------------------------------------
    struct MeowNiforms {
        int meowdel;
        int miew;
        int meowjection;
        int huhTexture; // why did i put this one here?
        int lightPaws;
        int lightCol;
        int lightDir;
        int viewPaws;
        int meownCutOff;
        int meowterCutOff;
        int crashLightOn;
    };

    MeowNiforms u;

// """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""





// mouse stuff
void meowseCB(GLFWwindow* window, double xpawsin, double ypawsin) {
    if (!meowsorLocked) return;

    float meowx = static_cast<float>(xpawsin);
    float meowy = static_cast<float>(ypawsin);

    if (firstmeowse) {
        lastXmeowse = meowx;
        lastYmeowse = meowy;
        firstmeowse = false;
    }

    float meoffsetX = meowx - lastXmeowse;
    float meoffsetY = lastYmeowse - meowy;

    lastXmeowse = meowx;
    lastYmeowse = meowy;

    meowmera.chasingMice(meoffsetX, meoffsetY);
}


// create shader program and compile shaders and whatnot
unsigned int createMeowProgram() {

    unsigned int meowtexShader = glCreateShader(GL_VERTEX_SHADER); // meowwwww
    glShaderSource(meowtexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(meowtexShader);

    int meowsess;
    char meowinfo[512];
    glGetShaderiv(meowtexShader, GL_COMPILE_STATUS, &meowsess);
    if (!meowsess) {
        glGetShaderInfoLog(meowtexShader, 512, nullptr, meowinfo);
        std::cerr << "vertex shader blew up yo: " << meowinfo << std::endl;
    }

    unsigned int meowmentShader = glCreateShader(GL_FRAGMENT_SHADER); // meowwwww
    glShaderSource(meowmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(meowmentShader);

    glGetShaderiv(meowmentShader, GL_COMPILE_STATUS, &meowsess);
    if (!meowsess) {
        glGetShaderInfoLog(meowmentShader, 512, nullptr, meowinfo);
        std::cerr << "fragment shader blew up yo: " << meowinfo << std::endl;
    }

    unsigned int meowProgram = glCreateProgram(); // meowwwww
    glAttachShader(meowProgram, meowtexShader);
    glAttachShader(meowProgram, meowmentShader);
    glLinkProgram(meowProgram);

    glGetProgramiv(meowProgram, GL_LINK_STATUS, &meowsess);
    if (!meowsess) {
        glGetProgramInfoLog(meowProgram, 512, nullptr, meowinfo);
        std::cerr << "program linking blew up yo: " << meowinfo << std::endl;
    }

    glDeleteShader(meowtexShader);
    glDeleteShader(meowmentShader);

    return meowProgram;
}


// texture loading and binding and yknow whatever other stuff related to textures
// idk what to name stuff
unsigned int textureThing(const char* path) {
    unsigned int meowxture; // meowwwww
    glGenTextures(1, &meowxture);
    glBindTexture(GL_TEXTURE_2D, meowxture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels; // i couldnt come up with anything :( same with path btw
    unsigned char* meowta = stbi_load(path, &width, &height, &nrChannels, 0);

    if (meowta) {
        std::cout << "loaded " << path << ": " << width << "x" << height << " channels=" << nrChannels << std::endl; // temporary debug print cus im stupid

        GLenum format;
        if (nrChannels == 1) {
            format = GL_RED;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 4) {
            format = GL_RGBA;
        } else {
            std::cerr << "woah wtf this is the amount of channels: " << nrChannels << " for " << path << std::endl;
            format = GL_RGB;
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, meowta);
        // couldnt have done that witout param 6
        glGenerateMipmap(GL_TEXTURE_2D); // its so easy
         stbi_image_free(meowta); // else my mem is gonna get caught leaking
    } else {
        std::cerr << "texture loading isnt loading" << path << std::endl; // only thing yall are getting is the path 4 now
        unsigned char magenta[3] = {255, 0, 255}; // is this even magenta?
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, magenta);
    }

    return meowxture;
}


void timething() {
    float purrentFrame = (float)glfwGetTime();
    deltaTime = purrentFrame - lastFrame;
    lastFrame = purrentFrame;
}


void toggleKeys(meowindow& window) {
    static bool tabWasPressed = false;
            if (window.isKeyPressed(GLFW_KEY_TAB)) {
                if (!tabWasPressed) {
                    meowsorLocked = !meowsorLocked;
                    window.setCursorLocked(meowsorLocked);
                    firstmeowse = true;
                } // yay so many curly braces
                tabWasPressed = true;
            } else {
                tabWasPressed = false;
            }

            static bool fWasPressed = false;
            if (window.isKeyPressed(GLFW_KEY_F)) {
                if (!fWasPressed) {
                    crashLightOn = !crashLightOn;
                }
                fWasPressed = true;
            } else {
                fWasPressed = false;
            }

}

void meowmeraMove(meowindow& window, float deltaTime) {
    meowmera.meowmeraMove(
        window.isKeyPressed(GLFW_KEY_W),
        window.isKeyPressed(GLFW_KEY_S),
        window.isKeyPressed(GLFW_KEY_A),
        window.isKeyPressed(GLFW_KEY_D),
        window.isKeyPressed(GLFW_KEY_SPACE),
        window.isKeyPressed(GLFW_KEY_LEFT_CONTROL),
        window.isKeyPressed(GLFW_KEY_LEFT_SHIFT),
        deltaTime
    );
}

// main loop for rendering and stuff
void loopsoup(meowindow& window, unsigned int shaderProgram, std::vector<MeowObject>& sceneObjects) {
    while (!window.shouldClose()) {
        timething();
        toggleKeys(window);
        meowmeraMove(window, deltaTime);

        glClearColor(0.15f, 0.25f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 miew = meowmera.getViewMatrix();
        glm::mat4 meowjection = glm::perspective(glm::radians(45.0f), window.aspectRatio(), 0.1f, 100.0f);

        glUniformMatrix4fv(u.miew, 1, GL_FALSE, glm::value_ptr(miew));
        glUniformMatrix4fv(u.meowjection, 1, GL_FALSE, glm::value_ptr(meowjection));

        glUniform3f(u.lightPaws, meowmera.paws.x, meowmera.paws.y, meowmera.paws.z);
        glUniform3f(u.lightDir, meowmera.front.x, meowmera.front.y, meowmera.front.z);
        glUniform3f(u.lightCol, 1.0f, 1.0f, 1.0f);
        glUniform3f(u.viewPaws, meowmera.paws.x, meowmera.paws.y, meowmera.paws.z);
        glUniform1f(u.meownCutOff, cos(glm::radians(12.5f)));
        glUniform1f(u.meowterCutOff, cos(glm::radians(17.5f)));
        glUniform1i(u.crashLightOn, crashLightOn);

        for (MeowObject& obj : sceneObjects) {
            glUniformMatrix4fv(u.meowdel, 1, GL_FALSE, glm::value_ptr(obj.modelMatrix));
            glUniform1i(u.huhTexture, obj.useTexture);
            if (obj.useTexture) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, obj.textureID);
            }
            glBindVertexArray(obj.VAO);
            glDrawElements(GL_TRIANGLES, obj.indexCount, GL_UNSIGNED_INT, 0);
        }

        window.swapBuffers();
        window.pollEvents();

        if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
            window.requestClose();
        }
    }
}


// "free my boy ram he aint do nun"
void cleanupcrew(std::vector<MeowObject>& sceneObjects, unsigned int shaderProgram) {
    for (MeowObject& obj : sceneObjects) {
        glDeleteVertexArrays(1, &obj.VAO);
    }
    glDeleteProgram(shaderProgram);
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    if (!window.isValid()) return -1;

    window.setCursorPosCallback(meowseCB);
    window.setCursorLocked(true); // mouse look starts locked like it always did

    unsigned int shaderProgram = createMeowProgram();

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "meowtex"), 0);


    u.meowdel      = glGetUniformLocation(shaderProgram, "meowdel");
    u.miew         = glGetUniformLocation(shaderProgram, "miew");
    u.meowjection  = glGetUniformLocation(shaderProgram, "meowjection");
    u.huhTexture   = glGetUniformLocation(shaderProgram, "huhTexture");
    u.lightPaws    = glGetUniformLocation(shaderProgram, "lightPaws");
    u.lightCol     = glGetUniformLocation(shaderProgram, "lightCol");
    u.viewPaws     = glGetUniformLocation(shaderProgram, "viewPaws");
    u.lightDir      = glGetUniformLocation(shaderProgram, "lightDir");
    u.meownCutOff   = glGetUniformLocation(shaderProgram, "meownCutOff");
    u.meowterCutOff = glGetUniformLocation(shaderProgram, "meowterCutOff");
    u.crashLightOn = glGetUniformLocation(shaderProgram, "crashLightOn");


    unsigned int meowndTexture = textureThing("assets/textures/garden.jpg");

    std::vector<MeowObject> sceneObjects;
    sceneObjects.push_back(loadSceneObject("assets/models/rainbowcube.obj", false, 0));
    sceneObjects.push_back(loadSceneObject("assets/models/meownd.obj", true, meowndTexture));
    sceneObjects.push_back(loadSceneObject("assets/models/mittest.obj", false, 0));

    sceneObjects[2].modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    loopsoup(window, shaderProgram, sceneObjects);

    cleanupcrew(sceneObjects, shaderProgram);
    return 0;
}

// TO DO:
// * fix up the loopsoup thing so that we dont have the entire codebase in there
// * split the codebase into smaller chunks (so like multiple files)
// * find out what other stuff i need to fix b4 adding new features to this mess
// * use less globals
// * use classes

// -common50
