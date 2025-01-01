#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

layout (location = 0) out vec2 texCoord;

layout (location = 2) uniform mat4 projection;
layout (location = 3) uniform mat4 model;
layout (location = 4) uniform mat4 view;

void main() {
    gl_Position = projection * model * view * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}