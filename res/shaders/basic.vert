#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 texCoord;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(aPosition, 1.0);

    texCoord = aTexture;
}
