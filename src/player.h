#ifndef PLAYER_H
#define PLAYER_H

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "vector_math.h"

typedef struct {
	GLuint texture;
	GLuint shader_program;
	GLuint model;
	Vec2 position;
} Player;

void player_draw(const Player *player, GLFWwindow *window);

#endif
