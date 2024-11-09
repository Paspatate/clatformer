#include "vector_math.h"
#include "shader.h"
#include "image.h"
#include "model.h"
#include "player.h"
#include "sprite.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void window_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLFWwindow *init_opengl_window() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "game", NULL, NULL);
    if (!window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        printf("ERROR: could not create window");
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    return window;
}

int main(int argc, char const *argv[]) {
    if(!glfwInit()) return -1;
    
    GLFWwindow *window = init_opengl_window();

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    float square[] = {-1.0,  1.0, 0.0, 1.0,
                       1.0,  1.0, 1.0, 1.0, 
                       1.0, -1.0, 1.0, 0.0,
                      -1.0, -1.0, 0.0, 0.0};
    
    int indice[] = {0, 1, 2, 0, 2, 3};

    GLuint shader_prog = load_program("./res/simple.vert", "./res/simple.frag");
    GLuint texture = load_texture("res/untitled.png");

    Vec2 position = {0.0, 0.0}; 
    Vec2 size = {5, 5};
    Vec2 world_unit = {20, 20};
    
    GLuint square_vao = load_vao(square, sizeof(square), indice, sizeof(indice));
    Sprite s = {{{0.0, 0.0}, {3.0, 3.0}}, shader_prog, texture ,square_vao};
    Player player = {s};

    double start_time = 0.0;
    float delta_time = 0.0;

    while (!glfwWindowShouldClose(window)) {
        start_time = glfwGetTime();

        glfwPollEvents();

        player_update(&player, window, delta_time);

        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        player_draw(&player, window, &world_unit);
        sprite_draw(&s, window, &world_unit);

        glfwSwapBuffers(window);
        delta_time = (float)(glfwGetTime() - start_time);
    }

    glDeleteProgram(shader_prog);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
