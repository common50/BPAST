// graphics engine but i lowkey cheat using opengl and glfw cus im lazy 
// be patient and sit still

// 2 lines for functions else ill go insane

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



// clutter comment slop just for you because i have nothing better to do and some ppl like it

// verticies n stuff
// 3 pos, 3 color and 2 texcoord values for each n every lil vertex
float vertices[] = {
//  pos                   color               texcoord
    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f
};

// indecies n stuff
// so basically saying draw the triangles like *this*
unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

// shader source strings or wtv its called im still not sure how it works
// vertex shader:
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 meowtexColor;
out vec2 meowtexCoord;
void main() {
    gl_Position = vec4(aPos, 1.0);
    meowtexColor = aColor;
    meowtexCoord = aTexCoord;
}
)";

// fragment shader:
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 meowtexColor;
in vec2 meowtexCoord;
out vec4 FragColor;
uniform sampler2D meowtex;
void main() {
    FragColor = texture(meowtex, meowtexCoord);
}
)";


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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed, do better next time i dont hav all day" << std::endl;
        return nullptr;
    }

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

        GLenum format;
        if (nrChannels == 4) {
            format = GL_RGBA;
        } else{
            format = GL_RGB;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, meowta);
        // couldnt have done that witout param 6
        glGenerateMipmap(GL_TEXTURE_2D); // its so easy
    } else {
        std::cerr << "texture loading isnt loading" << path << std::endl; // only thing yall are getting is the path 4 now
    }
    stbi_image_free(meowta); // else my ram is gonna get caught leaking

    return meowxture;
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}


// main loop for rendering and stuff
void loopsoup(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO, unsigned int meowxture) {
    while (!glfwWindowShouldClose(window)) { // who named this dawg
        glClearColor(0.15f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, meowxture);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
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




// lets pollute my code

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

    unsigned int VAO, VBO, EBO;
    GPUseless(VAO, VBO, EBO);

    unsigned int meowxture = textureThing("assets/textures/lavatory.jpg");

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    loopsoup(window, shaderProgram, VAO , meowxture);

    cleanupcrew(VAO, VBO, EBO, shaderProgram, window);
    return 0;
}

// notes 2 self ignore this pls its embarrassing lowk
// k so vertex = points in 3d space n fragment = color
// vao n vbo = gpu memory stuff
// ebo holds indecies