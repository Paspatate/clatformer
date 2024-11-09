#include "vector_math.h"

void vec2_add(Vec2 *lhs, const Vec2 *rhs) {
	lhs->x += rhs->x;
	lhs->y += rhs->y;
}

void vec2_mult(Vec2 *lhs, float scaler) {
	lhs->x *= scaler;
	lhs->y *= scaler;
}

