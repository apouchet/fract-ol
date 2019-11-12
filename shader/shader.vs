#version 400

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 posTexture;

out vec2 coord;
out vec2 textCoor;

void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
    coord.x = position.x;
    coord.y = -position.y;
    textCoor.x = posTexture.x;
    textCoor.y = -posTexture.y;
}