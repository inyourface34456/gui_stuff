const char* vertexSource = R"glsl(
#version 150 core

in vec2 position;
in vec3 color;
out vec3 Color;

void main() {
    Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

const char* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
out vec4 outColor;
void main() {
    outColor = vec4(Color, 1.0);
})glsl";
