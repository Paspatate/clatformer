#ifndef SHADER_H
#define SHADER_H

#include "glad/gl.h"
#include "vector_math.h"
 
GLuint load_program(const char* vertex_shader_path, const char* fragment_shader_path);
void set_vec2_uniform(GLuint program, const GLchar* uniform_name, const Vec2 *value);
void set_float_uniform(GLuint program, const GLchar* uniform_name, float value);
void set_int_uniform(GLuint program, const GLchar* uniform_name, int value);


#endif // SHADER_H
