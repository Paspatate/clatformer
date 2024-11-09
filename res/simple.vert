#version 460 core

layout (location = 0) in vec2 modelPos;

out vec4 fPos;

uniform vec2 worldPos;
uniform vec2 worldUnit;
uniform vec2 size;
uniform int win_height;
uniform int win_width;

void main() {
    float ratio_x = worldUnit.x / win_width;
    float ratio_y = worldUnit.y / win_height;

    float scaled_model_x = modelPos.x * size.x * ratio_x;
    float scaled_model_y = modelPos.y * size.y * ratio_y;

    float render_x = worldPos.x * ratio_x + scaled_model_x;
    float render_y = worldPos.y * ratio_y + scaled_model_y;

    gl_Position = vec4(render_x, render_y, 1.0, 1.0);

    fPos = vec4(modelPos.x, modelPos.y, 1.0, 1.0);
}
