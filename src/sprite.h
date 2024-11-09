#ifndef SPRITE_H
#define SPRITE_H

#include "rect.h"
#include "vector_math.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

typedef struct {
    Rect rect;
    GLuint shader_program;
    GLuint texture_id;
    GLuint quad_id;
} Sprite;

void sprite_draw(const Sprite *sprite, GLFWwindow *window, Vec2 *world_size);

#endif

