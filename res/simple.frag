#version 460 core

in vec4 fPos;

uniform sampler2D tex0;

out vec4 FragColor;

void main() {
    
    FragColor = texture(tex0, fPos.xy); 
}
