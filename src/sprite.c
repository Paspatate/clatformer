#include "sprite.h"
#include "vector_math.h"
#include "shader.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

void sprite_draw(const Sprite *sprite, GLFWwindow *window, Vec2 *world_size) {
    int win_width, win_height;

    glfwGetWindowSize(window, &win_width, &win_height);

    glUseProgram(sprite->shader_program);
    glBindTexture(GL_TEXTURE_2D, sprite->texture_id);
    glBindVertexArray(sprite->quad_id);

    set_vec2_uniform(sprite->shader_program, "worldPos", &sprite->rect.position);
    set_vec2_uniform(sprite->shader_program, "size", &sprite->rect.size);
    set_vec2_uniform(sprite->shader_program, "worldUnit", world_size);
    set_int_uniform(sprite->shader_program, "win_height", win_height);
    set_int_uniform(sprite->shader_program, "win_width", win_width);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
