#version 400

layout (location = 0) in vec2 position;
out vec2 coord;

void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
    coord.x = position.x;
    coord.y = position.y;
}