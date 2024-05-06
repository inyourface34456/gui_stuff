const char* vertexSource = R"glsl(
#version 150 core

in vec2 position;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

const char* fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
void main() {
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
})glsl";