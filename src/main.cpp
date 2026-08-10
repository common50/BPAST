// graphics engine but i lowkey cheat using opengl and glfw cus im lazy 
// be patient and sit still

// 2 lines for functions else ill go insane

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



// clutter comment slop just for you because i have nothing better to do and some ppl like it

// verticies n stuff
// 3 pos and 3 color values for each n every lil vertex
float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

// shader source strings or wtv its called im still not sure how it works
// vertex shader:
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 meowtexColor;
void main() {
    gl_Position = vec4(aPos, 1.0);
    meowtexColor = aColor;
}
)";

// fragment shader:
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 meowtexColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(meowtexColor, 1.0);

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


// mess with gpu buffers and vertex arrays
void GPUseless(unsigned int& VAO, unsigned int& VBO) {
    // VAO n VBO part
    // was gonna name em sum stupid like meowVAO n meowVBO 
    // but maybe not they seem too important to be named like that
    glGenVertexArrays(1, &VAO); // 1 vao pls
    glGenBuffers(1, &VBO); // 1 vbo pls

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


// main loop for rendering and stuff
void loopsoup(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO) {
    while (!glfwWindowShouldClose(window)) { // who named this dawg
        glClearColor(0.15f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}


// "free my boy ram he aint do nun"
void cleanupcrew(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram, GLFWwindow* window) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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

    unsigned int VAO, VBO;
    GPUseless(VAO, VBO);

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    loopsoup(window, shaderProgram, VAO);

    cleanupcrew(VAO, VBO, shaderProgram, window);
    return 0;
}

// notes 2 self ignore this pls its embarrassing lowk
// k so vertex = points in 3d space n fragment = color
// vao n vbo = gpu memory stuff