const char* vertexSource = R"glsl(
#version 150 core

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec2 Texcoord;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    Color = color;
    Texcoord = texcoord;
    gl_Position = view * proj * model * vec4(position, 0.0, 1.0);
}
)glsl";

const char* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
    outColor = mix(texture(tex, Texcoord), texture(tex2, Texcoord), 0.5);
})glsl";
