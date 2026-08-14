// graphics engine but i lowkey cheat using opengl and glfw cus im lazy 
// be patient and sit still

// 2 lines for functions else ill go insane

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <obj-pawrser.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>



// cluttering my code just for you because i have nothing better to do





// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX verticies n stuff XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// spinning colored cube thing object whatever it is
// 3 pos, 3 color and 2 texcoord values for each n every lil vertex
float vertices[] = {
// pos                  color              normal
// back (-z)
-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
// front (+z)
-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
// left (-x)
-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
// right (+x)
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
// bottom (-y)
-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
// top (+y)
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
// its so hard to keep track of this stuff
};

// indecies n stuff
// so basically saying draw the triangles like *this*
unsigned int indices[] = {
    0, 1, 2,    2, 3, 0,
    4, 5, 6,    6, 7, 4,
    8, 9, 10,   10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20

};

// YOUR HORIZON IS MY GARDEN BUT WHO WATERS IT? 
float meowndVertices[] = {
    //   pos                     color              normal              texcoord
    -10.0f, -1.0f, -10.0f,   0.2f, 0.2f, 0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
     10.0f, -1.0f, -10.0f,   0.2f, 0.2f, 0.25f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
     10.0f, -1.0f,  10.0f,   0.2f, 0.2f, 0.25f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -10.0f, -1.0f,  10.0f,   0.2f, 0.2f, 0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f
};

unsigned int meowndIndices[] = {
    0, 1, 2,
    2, 3, 0
};

// """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""





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

    float nonsense = 0.1f; // sensitivity for the record

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
        std::cerr << "yo glfwInit failed haha good luck" << std::endl; // cus ppl always get angry at me if i dont do err handling
        return nullptr; // should i make this 0 haha
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "BPAST", nullptr, nullptr);
    // same reason as above, i should probably do err handling here too
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
    // vertex part
    unsigned int meowtexShader = glCreateShader(GL_VERTEX_SHADER); // meowwwww
    glShaderSource(meowtexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(meowtexShader);

    // err handling part 1
    int meowsess;  
    char meowinfo[512];
    glGetShaderiv(meowtexShader, GL_COMPILE_STATUS, &meowsess);
    if (!meowsess) {
        glGetShaderInfoLog(meowtexShader, 512, nullptr, meowinfo);
        std::cerr << "vertex shader blew up yo: " << meowinfo << std::endl;
    }

    // fragment part
    unsigned int meowmentShader = glCreateShader(GL_FRAGMENT_SHADER); // meowwwww
    glShaderSource(meowmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(meowmentShader);

    // err handling part 2 (omg so excited)
    glGetShaderiv(meowmentShader, GL_COMPILE_STATUS, &meowsess);
    if (!meowsess) {
        glGetShaderInfoLog(meowmentShader, 512, nullptr, meowinfo);
        std::cerr << "fragment shader blew up yo: " << meowinfo << std::endl;
    }

    // program part
    unsigned int meowProgram = glCreateProgram(); // meowwwww
    glAttachShader(meowProgram, meowtexShader);
    glAttachShader(meowProgram, meowmentShader);
    glLinkProgram(meowProgram);

    // err handling part 3 (last part i promise)
    glGetProgramiv(meowProgram, GL_LINK_STATUS, &meowsess);
    if (!meowsess) {
        glGetProgramInfoLog(meowProgram, 512, nullptr, meowinfo);
        std::cerr << "program linking blew up yo: " << meowinfo << std::endl;
    }

    // cleanup part
    glDeleteShader(meowtexShader);
    glDeleteShader(meowmentShader);
    // there HAS to be someone out there that got stuck cus they deleted the program aswell

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


// platform thing 
void platformbs(unsigned int& meowndVAO, unsigned int& meowndVBO, unsigned int& meowndEBO) { // bs and buffer setup at the same time
    glGenVertexArrays(1, &meowndVAO);
    glGenBuffers(1, &meowndVBO);
    glGenBuffers(1, &meowndEBO);

    glBindVertexArray(meowndVAO);
    glBindBuffer(GL_ARRAY_BUFFER, meowndVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(meowndVertices), meowndVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meowndEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meowndIndices), meowndIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
}


// mess with gpu buffers and vertex arrays
void GPUseless(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {
    // VAO n VBO n EBO part and some texture stuff too i guess
    // was gonna name em sum stupid like meowVAO n meowVBO 
    // but maybe not they seem too important to be named like that
    glGenVertexArrays(1, &VAO); // 1 vao pls
    glGenBuffers(1, &VBO); // 1 vbo pls
    glGenBuffers(1, &EBO); // 1 ebo pls

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
}


// main loop for rendering and stuff
void loopsoup(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO, unsigned int meowndVAO, unsigned int meowndTexture) {
    while (!glfwWindowShouldClose(window)) { // who named this dawg
        float purrentFrame = (float)glfwGetTime();
        deltaTime = purrentFrame - lastFrame;
        lastFrame = purrentFrame;
        
        glClearColor(0.15f, 0.25f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 meowdel = glm::mat4(1.0f);

        meowdel = glm::rotate(meowdel, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 miew = glm::lookAt(meowmeraPos, meowmeraPos + meowmeraFront, meowmeraUp);

        glm::mat4 meowjection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

        glUniformMatrix4fv(u.meowdel, 1, GL_FALSE, glm::value_ptr(meowdel));
        glUniformMatrix4fv(u.miew, 1, GL_FALSE, glm::value_ptr(miew));
        glUniformMatrix4fv(u.meowjection, 1, GL_FALSE, glm::value_ptr(meowjection));

        glUniform3f(u.lightPaws, meowmeraPos.x, meowmeraPos.y, meowmeraPos.z);
        glUniform3f(u.lightDir, meowmeraFront.x, meowmeraFront.y, meowmeraFront.z);
        glUniform3f(u.lightCol, 1.0f, 1.0f, 1.0f);
        glUniform3f(u.viewPaws, meowmeraPos.x, meowmeraPos.y, meowmeraPos.z);
        glUniform1f(u.meownCutOff, cos(glm::radians(12.5f)));
        glUniform1f(u.meowterCutOff, cos(glm::radians(17.5f))); // standard angles cus im unoriginal

        glUniform1i(u.huhTexture, false);

        glUniform1i(u.crashLightOn, crashLightOn);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glm::mat4 meowndModel = glm::mat4(1.0f);

        glUniformMatrix4fv(u.meowdel, 1, GL_FALSE, glm::value_ptr(meowndModel));

        glUniform1i(u.huhTexture, true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, meowndTexture);

        glBindVertexArray(meowndVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

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

        float meowmeraSpeed = 2.5f * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            meowmeraSpeed *= 2.5f;

        glm::vec3 movefix = glm::normalize(glm::vec3(meowmeraFront.x, 0.0f, meowmeraFront.z));

        // wasdwdasddwadsdsad
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            meowmeraPos += meowmeraSpeed * movefix;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            meowmeraPos -= meowmeraSpeed * movefix;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            meowmeraPos -= glm::normalize(glm::cross(movefix, meowmeraUp)) * meowmeraSpeed;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            meowmeraPos += glm::normalize(glm::cross(movefix, meowmeraUp)) * meowmeraSpeed;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            meowmeraPos += meowmeraSpeed * meowmeraUp;

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            meowmeraPos -= meowmeraSpeed * meowmeraUp;
    }
}


// "free my boy ram he aint do nun"
void cleanupcrew(unsigned int VAO, unsigned int VBO, unsigned int EBO, unsigned int shaderProgram, GLFWwindow* window) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}





// i remember when i first actually started doing error handling
// i thought i was doing it correctly but i just put something dumb like 
// "if (!window) return -1;" and i thought that was good enough
// then i started thinking hmm wait i dont actually know exactly WHERE the error was
// so i also started putting a print statement saying "glfwInit lowkey failed" or "window creation got messed up"
// and i thought that was good enough

// we all know it was not

// i only started realising this after a having lot of errors and thinking to myself:
// "so i know its broken here but i dont know WHY"
// and then i discovered that i could actually make it say what the error was
// like in line 83 with meowinfo
// (line 83 in as of this commit, might change in the future if i add more stuff)
// and i thought to myself: "wow this is actually really useful"
// and thats how we got here





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


    unsigned int VAO, VBO, EBO;
    GPUseless(VAO, VBO, EBO);

    unsigned int meowndVAO, meowndVBO, meowndEBO;
    platformbs(meowndVAO, meowndVBO, meowndEBO);

    unsigned int meowndTexture = textureThing("assets/textures/garden.jpg");

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    // pawrser test
    Meowdel testModel = loadObj("assets/models/mittest.obj");

    loopsoup(window, shaderProgram, VAO, meowndVAO, meowndTexture);

    cleanupcrew(VAO, VBO, EBO, shaderProgram, window);
    return 0;
}

// notes 2 self ignore this pls its embarrassing lowk
// k so vertex = points in 3d space n fragment = color
// vao n vbo = gpu memory stuff
// ebo holds indecies

// -common50