#include "game_conf.h"
#include "player.h"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "config.h"
#include "sprite.h"
#include "vector_math.h"

GLboolean player_on_ground(const Player *player) {
		return player->sprite.rect.position.y < 1;
}

void player_draw(const Player* player, GLFWwindow *window, Vec2 *worldSize) {
		sprite_draw(&player->sprite, window, worldSize);
}

void player_update(Player *player, GLFWwindow *window ,float deltaTime) {
		if (glfwGetKey(window, KEY_RIGHT)) {
				player->velocity.x += player->speed * deltaTime;
		}

		if (glfwGetKey(window, KEY_LEFT)) {
				player->velocity.x -= player->speed * deltaTime;
		}

		if (glfwGetKey(window, KEY_JUMP)) {
				if (player_on_ground(player)) {
				player->velocity.y += player->jump_force * deltaTime;
				}
		}

		player->velocity.y -= GRAVITY * deltaTime;
		
		vec2_add(&player->sprite.rect.position, &player->velocity);
		vec2_mult(&player->velocity, DRAG_COEF);

		if (player->sprite.rect.position.y <= 0) {
				player->sprite.rect.position.y = 0;
		}
}

