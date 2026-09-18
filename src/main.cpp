// graphics engine but i lowkey cheat using opengl and glfw cus im lazy
// be patient and sit still

// 2 lines for functions else ill go insane

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <BPAST/scene/SceneObj.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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
    glm::vec3 meowmeraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 meowmeraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 meowmeraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float myaw = -90.0f;
    float meowch = 0.0f; // (yaw n pitch for the record im just bored and this is a good way to pass time)



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
    int windowWidth = 800;
    int windowHeight = 600; // too important for dumb names

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
void chasingMice(GLFWwindow* window, double xposIN, double yposIN) {

    if (!meowsorLocked) return;

    // pos
    float meowx = static_cast<float>(xposIN); // because apparently c style casting gets you a lot of flak
    float meowy = static_cast<float>(yposIN);

    if (firstmeowse) {
        lastXmeowse = meowx;
        lastYmeowse = meowy;
        firstmeowse = false;
    }

    float meoffsetX = meowx - lastXmeowse;
    float meoffsetY = lastYmeowse - meowy; // flipped cus coords go from top to bottom

    lastXmeowse = meowx;
    lastYmeowse = meowy;

    float nonsense = 0.1f;

    meoffsetX *= nonsense;
    meoffsetY *= nonsense;

    myaw += meoffsetX;
    meowch += meoffsetY;

    // i almost forgot to clamp
    if (meowch > 89.0f) meowch = 89.0f;
    if (meowch < -89.0f) meowch = -89.0f;

    // lowkey kinda copied the spherical coordinate math from somewhere but who cares
    // cus there is NO WAY im deriving this myself lol
    glm::vec3 meowection;
    meowection.x = cos(glm::radians(myaw)) * cos(glm::radians(meowch));
    meowection.y = sin(glm::radians(meowch));
    meowection.z = sin(glm::radians(myaw)) * cos(glm::radians(meowch));

    // also almost forgot abt normalization
    meowmeraFront = glm::normalize(meowection);
}


// resize fix thing dont worry skip over this
void huh(GLFWwindow* window, int realmeowidth, int realmeowght) { // meowwwww
    glViewport(0, 0, realmeowidth, realmeowght);
    windowWidth = realmeowidth;
    windowHeight = realmeowght;
}


// make window and context and stuff
GLFWwindow* makeMyWindowsComeTrue() {
    if (!glfwInit()) {
        std::cerr << "yo glfwInit failed haha good luck" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "BPAST", nullptr, nullptr);

    if (!window) {
        std::cerr << "yo the window isnt working gang helppppp" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, chasingMice);

    glfwSetFramebufferSizeCallback(window, huh); // resize fix, ignore ts

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed, do better next time i dont hav all day" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEPTH_TEST);

    return window;
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


void toggleKeys(GLFWwindow* window) {
    static bool tabWasPressed = false;
            if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
                if (!tabWasPressed) {
                    meowsorLocked = !meowsorLocked;
                    if (meowsorLocked) {
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        firstmeowse = true;
                    } else {
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    }
                } // yay so many curly braces
                tabWasPressed = true;
            } else {
                tabWasPressed = false;
            }

            static bool fWasPressed = false;
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
                if (!fWasPressed) {
                    crashLightOn = !crashLightOn;
                }
                fWasPressed = true;
            } else {
                fWasPressed = false;
            }

}

void meowmeraMove(GLFWwindow* window, float deltaTime) {
    float meowmeraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        meowmeraSpeed *= 2.5f;


    glm::vec3 meowfix = glm::normalize(glm::vec3(meowmeraFront.x, 0.0f, meowmeraFront.z));

    // wasdwdasddwadsdsad
       if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
           meowmeraPos += meowmeraSpeed * meowfix;

       if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
           meowmeraPos -= meowmeraSpeed * meowfix;

       if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
           meowmeraPos -= glm::normalize(glm::cross(meowfix, meowmeraUp)) * meowmeraSpeed;

       if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
           meowmeraPos += glm::normalize(glm::cross(meowfix, meowmeraUp)) * meowmeraSpeed;

       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
           meowmeraPos += meowmeraSpeed * meowmeraUp;

       if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
           meowmeraPos -= meowmeraSpeed * meowmeraUp;
}


// main loop for rendering and stuff
void loopsoup(GLFWwindow* window, unsigned int shaderProgram, std::vector<MeowObject>& sceneObjects) {
    while (!glfwWindowShouldClose(window)) {
        timething();
        toggleKeys(window);
        meowmeraMove(window, deltaTime);

        glClearColor(0.15f, 0.25f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 miew = glm::lookAt(meowmeraPos, meowmeraPos + meowmeraFront, meowmeraUp);
        glm::mat4 meowjection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

        glUniformMatrix4fv(u.miew, 1, GL_FALSE, glm::value_ptr(miew));
        glUniformMatrix4fv(u.meowjection, 1, GL_FALSE, glm::value_ptr(meowjection));

        glUniform3f(u.lightPaws, meowmeraPos.x, meowmeraPos.y, meowmeraPos.z);
        glUniform3f(u.lightDir, meowmeraFront.x, meowmeraFront.y, meowmeraFront.z);
        glUniform3f(u.lightCol, 1.0f, 1.0f, 1.0f);
        glUniform3f(u.viewPaws, meowmeraPos.x, meowmeraPos.y, meowmeraPos.z);
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

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}


// "free my boy ram he aint do nun"
void cleanupcrew(std::vector<MeowObject>& sceneObjects, unsigned int shaderProgram, GLFWwindow* window) {
    for (MeowObject& obj : sceneObjects) {
        glDeleteVertexArrays(1, &obj.VAO);
    }
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    GLFWwindow* window = makeMyWindowsComeTrue();
    if (!window) return -1;

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

    cleanupcrew(sceneObjects, shaderProgram, window);
    return 0;
}

// TO DO:
// * fix up the loopsoup thing so that we dont have the entire codebase in there
// * split the codebase into smaller chunks (so like multiple files)
// * find out what other stuff i need to fix b4 adding new features to this mess
// * use less globals
// * use classes

// -common50
