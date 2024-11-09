#include "player.h"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "shader.h"

void player_draw(const Player* player, GLFWwindow *window, Vec2 *worldSize) {
    int win_width;
    int win_height;
    glfwGetWindowSize(window, &win_width, &win_height);
    glUseProgram(player->shader_program);
    glBindVertexArray(player->model);
    glBindTexture(GL_TEXTURE_2D, player->texture);
    set_vec2_uniform(player->shader_program, "worldPos", &player->position);
    set_vec2_uniform(player->shader_program, "size", &player->size);
    set_vec2_uniform(player->shader_program, "worldUnit", worldSize);
    set_int_uniform(player->shader_program, "win_height", win_height);
    set_int_uniform(player->shader_program, "win_width", win_width);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
