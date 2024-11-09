#include "shader.h"
#include "vector_math.h"
#include "glad/gl.h"
#include <stdio.h>
#include <stdlib.h>

GLuint create_program_from_source(char **vert_source, char **frag_source) {
    int success;
    char buf[512];

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vert_source, NULL);
    glCompileShader(vertex_shader);
    
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, buf);
        printf("ERROR: Can't compile vertex shader. \n%s", buf);
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, frag_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, buf);
        printf("ERROR: Can't compile fragment shader. \n%s", buf);
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetShaderiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader_program, 512, NULL, buf);
        printf("ERROR: Can't link program. \n%s", buf);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}

GLuint load_program(const char* vertex_shader_path, const char* fragment_shader_path) {
    FILE *vertex_shader_fd = fopen(vertex_shader_path, "r");
    FILE *frag_shader_fd = fopen(fragment_shader_path, "r");

    if (!vertex_shader_fd) {
        printf("ERROR: can't open the file \"%s\"\n", vertex_shader_path);
        exit(1);
    }

    if (!frag_shader_fd) {
        printf("ERROR: can't open the file \"%s\"\n", fragment_shader_path);
        exit(1);
    }

    char *vert_src;
    fseek(vertex_shader_fd, 0, SEEK_END); // met le pointeur a la fin du fichier
    long vert_src_len = ftell(vertex_shader_fd); // lit la position du pointeur de lecture (fin du fichier ici)
    vert_src = malloc(vert_src_len * sizeof(char) + 1); // add 1 to add a null byte at the end
    vert_src[vert_src_len] = '\0';

    fseek(vertex_shader_fd, 0, SEEK_SET);

    if (vert_src) {
        fread(vert_src, sizeof(GLchar), vert_src_len, vertex_shader_fd);
    }

    char *frag_src;
    fseek(frag_shader_fd, 0, SEEK_END);
    long frag_src_len = ftell(frag_shader_fd);
    frag_src = malloc(frag_src_len * sizeof(char) + 1); 
    frag_src[frag_src_len] = '\0';

    fseek(frag_shader_fd, 0, SEEK_SET);

    if (frag_src) {
        fread(frag_src, sizeof(GLchar), frag_src_len, frag_shader_fd);
    }
    GLuint shader_program = create_program_from_source(&vert_src, &frag_src);

    free(frag_src);
    free(vert_src);
    fclose(vertex_shader_fd);
    fclose(frag_shader_fd);

    return shader_program;
}

void set_vec2_uniform(GLuint program, const GLchar* uniform_name, const Vec2 *value){
    int uniform_location = glGetUniformLocation(program, uniform_name);
    glUseProgram(program);
    glUniform2f(uniform_location, value->x, value->y);
}

void set_int_uniform(GLuint program, const GLchar* uniform_name, int value){
    int uniform_location = glGetUniformLocation(program, uniform_name);
    glUseProgram(program);
    glUniform1i(uniform_location, value);
}

void set_float_uniform(GLuint program, const GLchar* uniform_name, float value){
    int uniform_location = glGetUniformLocation(program, uniform_name);
    glUseProgram(program);
    glUniform1f(uniform_location, value);
}
