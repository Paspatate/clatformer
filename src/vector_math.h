#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

typedef struct {
	float x;
	float y;
} Vec2;

void vec2_add(Vec2 *rhs, const Vec2 *lhs);
void vec2_mult(Vec2 *lhs, float scaler);

#endif 
