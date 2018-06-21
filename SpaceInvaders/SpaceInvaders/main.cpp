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
#include "Buffer.hpp"
#include "Game.hpp"


// MARK: GLFW error handling
void errorCallback(int code, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}


// MARK: - RGB to 32 bits int
uint32_t rgbToUint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 255;
}


// MARK: - Shaders
void validate_shader(GLuint shader, const char* file = 0)
{
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length = 0;
    
    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
    
    if(length > 0)
    {
        printf("Shader %d(%s) compile error: %s\n",
               shader, (file ? file: ""), buffer);
    }
}

bool validate_program(GLuint program)
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;
    
    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
    
    if(length > 0)
    {
        printf("Program %d link error: %s\n", program, buffer);
        return false;
    }
    
    return true;
}


// MARK: - Main
int main() {
    // register GLFW error callback
    glfwSetErrorCallback(errorCallback);
    
    // Constants
    const size_t bufferWidth = 224;
    const size_t bufferHeight = 256;
    
    GLFWwindow* window;
    
    // initialize GLFW
    if (!glfwInit()) { return -1; }
    
    // tell OpenGL whih context version is wanted
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create the window
    window = glfwCreateWindow(bufferWidth, bufferHeight, "Space Invaders", NULL, NULL);
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
    
    glClearColor(1.0, 0.0, 0.0, 1.0); // setting color to red
    
    // screen buffer
    uint32_t tintColor = rgbToUint32(0, 128, 0);
    Buffer buffer;
    buffer.width = bufferWidth;
    buffer.height = bufferHeight;
    buffer.pixels = new uint32_t[buffer.width * buffer.height];
    buffer.tint(tintColor);
    
    
    // create texture
    GLuint buffer_texture;
    glGenTextures(1, &buffer_texture);
    glBindTexture(GL_TEXTURE_2D, buffer_texture);
    glTexImage2D(
                 GL_TEXTURE_2D, 0, GL_RGB8,
                 buffer.width, buffer.height, 0,
                 GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer.pixels
                 );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // openGL shaders
    static const char* fragment_shader =
    "\n"
    "#version 330\n"
    "\n"
    "uniform sampler2D buffer;\n"
    "noperspective in vec2 TexCoord;\n"
    "\n"
    "out vec3 outColor;\n"
    "\n"
    "void main(void){\n"
    "    outColor = texture(buffer, TexCoord).rgb;\n"
    "}\n";
    
    const char* vertex_shader =
    "\n"
    "#version 330\n"
    "\n"
    "noperspective out vec2 TexCoord;\n"
    "\n"
    "void main(void){\n"
    "\n"
    "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
    "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
    "    \n"
    "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
    "}\n";
    
    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);
    glBindVertexArray(fullscreen_triangle_vao);
    
    GLuint shader_id = glCreateProgram();
    
    //Create vertex shader
    {
        GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);
        
        glShaderSource(shader_vp, 1, &vertex_shader, 0);
        glCompileShader(shader_vp);
        validate_shader(shader_vp, vertex_shader);
        glAttachShader(shader_id, shader_vp);
        
        glDeleteShader(shader_vp);
    }
    
    //Create fragment shader
    {
        GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(shader_fp, 1, &fragment_shader, 0);
        glCompileShader(shader_fp);
        validate_shader(shader_fp, fragment_shader);
        glAttachShader(shader_id, shader_fp);
        
        glDeleteShader(shader_fp);
    }
    
    glLinkProgram(shader_id);
    
    if(!validate_program(shader_id))
    {
        fprintf(stderr, "Error while validating shader.\n");
        glfwTerminate();
        glDeleteVertexArrays(1, &fullscreen_triangle_vao);
        delete[] buffer.pixels;
        return -1;
    }
    
    glUseProgram(shader_id);
    
    GLint location = glGetUniformLocation(shader_id, "buffer");
    glUniform1i(location, 0);
    
    //OpenGL setup
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(fullscreen_triangle_vao);
    
    
    // Alien Sprites
    Sprite alienSprite;
    alienSprite.width = 11;
    alienSprite.height = 8;
    alienSprite.data = new uint8_t[11 * 8]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
        0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
        0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
        0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
    };
    
    Sprite alienSprite2;
    alienSprite2.width = 11;
    alienSprite2.height = 8;
    alienSprite2.data = new uint8_t[88]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        1,0,0,1,0,0,0,1,0,0,1, // @..@...@..@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,1,1,0,1,1,1,0,1,1,1, // @@@.@@@.@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,1,0,0,0,0,0,0,0,1,0  // .@.......@.
    };
    
    
    // Alien animation
    SpriteAnimation* alienAnimation = new SpriteAnimation;
    
    alienAnimation->loop = true;
    alienAnimation->numFrames = 2;
    alienAnimation->frameDuration = 10;
    alienAnimation->time = 0;
    
    alienAnimation->frames = new Sprite*[2];
    alienAnimation->frames[0] = &alienSprite;
    alienAnimation->frames[1] = &alienSprite2;
    
    
    // Player Sprite
    Sprite playerSprite;
    playerSprite.height = 7;
    playerSprite.width = 11;
    playerSprite.data = new uint8_t[77]
    {
        0,0,0,0,0,1,0,0,0,0,0, // .....@.....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
    };
    
    
    // Game struct
    Game game;
    game.height = buffer.height;
    game.width = buffer.width;
    game.numAliens = 55;
    game.aliens = new Alien[game.numAliens];
    
    game.player.x = 112 - 5;
    game.player.y = 32;
    game.player.life = 3;
    
    
    // adding aliens
    for(size_t yi = 0; yi < 5; ++yi) {
        for(size_t xi = 0; xi < 11; ++xi) {
            game.aliens[yi * 11 + xi].x = 16 * xi + 20;
            game.aliens[yi * 11 + xi].y = 17 * yi + 128;
        }
    }
    
    // V-sync
    glfwSwapInterval(1);
    
    int player_move_dir = 1;
    
    
    // game loop
    while (!glfwWindowShouldClose(window)) {
        buffer.tint(tintColor);
        
        // drawing aliens
        for(size_t ai = 0; ai < game.numAliens; ++ai) {
            const Alien& alien = game.aliens[ai];
            buffer.drawSprite(alienSprite, alien.x, alien.y, rgbToUint32(128, 0, 0));
        }
        
        buffer.drawSprite(playerSprite, game.player.x, game.player.y, rgbToUint32(128, 0, 0));
        
        // animate aliens
        ++alienAnimation->time;
        if(alienAnimation->time == alienAnimation->numFrames * alienAnimation->frameDuration) {
            if(alienAnimation->loop) alienAnimation->time = 0;
            else {
                delete alienAnimation;
                alienAnimation = nullptr;
            }
        }
        
        for(size_t ai = 0; ai < game.numAliens; ++ai) {
            const Alien& alien = game.aliens[ai];
            size_t currentFrame = alienAnimation->time / alienAnimation->frameDuration;
            const Sprite& sprite = *alienAnimation->frames[currentFrame];
            buffer.drawSprite(sprite, alien.x, alien.y, rgbToUint32(128, 0, 0));
        }
        
        if(game.player.x + playerSprite.width + player_move_dir >= game.width - 1) {
            game.player.x = game.width - playerSprite.width - player_move_dir - 1;
            player_move_dir *= -1;
        
        }else if((int)game.player.x + player_move_dir <= 0) {
            game.player.x = 0;
            player_move_dir *= -1;
        
        }else game.player.x += player_move_dir;
        
        glTexSubImage2D(
                        GL_TEXTURE_2D, 0, 0, 0,
                        buffer.width, buffer.height,
                        GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
                        buffer.pixels
                        );
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    // closing program
    glfwDestroyWindow(window);
    glfwTerminate();
    
    glDeleteVertexArrays(1, &fullscreen_triangle_vao);
    
    delete[] alienSprite.data;
    delete[] buffer.pixels;
    
    return 0;
}
