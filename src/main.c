#include "vector_math.h"
#include "shader.h"
#include "image.h"
#include "model.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLFWwindow *init_opengl_window() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

    float square[] = {-1.0,  1.0,
                       1.0,  1.0, 
                       1.0, -1.0, 
                      -1.0, -1.0};
    
    int indice[] = {0, 1, 2, 0, 2, 3};

    GLuint shader_prog = load_program("./res/simple.vert", "./res/simple.frag");
    GLuint texture = load_texture("res/untitled.png");
    Vec2 position = {0.0, 0.0}; 
    Vec2 size = {1, 1};
    Vec2 world_unit = {50, 50};
    GLuint square_vao = load_vao(square, sizeof(square), indice, sizeof(indice));

    double start_time = 0.0;
    float delta_time = 0.0;

    while (!glfwWindowShouldClose(window)) {
        start_time = glfwGetTime();

        glfwPollEvents();

        position.x += 1 * delta_time;

        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_prog);
        glBindVertexArray(square_vao);
        glBindTexture(GL_TEXTURE_2D, texture);
        set_vec2_uniform(shader_prog, "worldPos", &position);
        set_vec2_uniform(shader_prog, "worldUnit", &world_unit);
        set_vec2_uniform(shader_prog, "size", &size);
        set_int_uniform(shader_prog, "win_height", WIN_HEIGHT);
        set_int_uniform(shader_prog, "win_width", WIN_WIDTH);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        delta_time = (float)(glfwGetTime() - start_time);
    }

    glDeleteProgram(shader_prog);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
