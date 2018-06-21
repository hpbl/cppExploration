//
//  main.cpp
//  SpaceInvaders
//
//  Created by Hilton Pintor Bezerra Leite on 20/06/2018.
//

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>


// MARK: GLFW error handling
void errorCallback(int code, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}


// MARK: - Buffer (screen representation)
struct Buffer {
    size_t width, height;
    
};


// MARK: - RGB to 32 bits int
uint32_t rgbToUint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 255;
}


// MARK: - Main
int main() {
    // register GLFW error callback
    glfwSetErrorCallback(errorCallback);
    
    GLFWwindow* window;
    
    // initialize GLFW
    if (!glfwInit()) { return -1; }
    
    // tell OpenGL whih context version is wanted
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create the window
    window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // initialize GLEW
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return -1;
    }
    
    // checking the current OpenGL version
    int glVersion[2] = { -1, -1 };
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    printf("Using OpenGL: %d.%d\n", glVersion[0], glVersion[1]);
    
    // game loop
    glClearColor(1.0, 0.0, 0.0, 1.0); // setting color to red
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // closing program
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
