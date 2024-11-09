#include "player.h"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "config.h"
#include "sprite.h"

void player_draw(const Player* player, GLFWwindow *window, Vec2 *worldSize) {
		sprite_draw(&player->sprite, window, worldSize);
}

void player_update(Player *player, GLFWwindow *window ,float deltaTime) {
		if (glfwGetKey(window, KEY_RIGHT)) {
				player->sprite.rect.position.x += 10 * deltaTime;
		}

		if (glfwGetKey(window, KEY_LEFT)) {
				player->sprite.rect.position.x -= 10 * deltaTime;
		}

		if (glfwGetKey(window, KEY_UP)) {
				player->sprite.rect.position.y += 10 * deltaTime;
		}
		
		if (glfwGetKey(window, KEY_DOWN)) {
				player->sprite.rect.position.y -= 10 * deltaTime;
		}
}

