#ifndef PLAYER_H
#define PLAYER_H

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "vector_math.h"
#include "sprite.h"

typedef struct {
		Sprite sprite;

} Player;

void player_draw(const Player *player, GLFWwindow *window, Vec2 *world_size);
void player_update(Player *player, GLFWwindow *window, float deltaTime);

#endif
