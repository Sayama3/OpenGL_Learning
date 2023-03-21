#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 texCoord;
out vec4 v_Position;
//out vec2 v_TexCoord;

uniform mat4 u_MVP; // Model View Projection matrix

void main()
{
    vec4 projectedPosition = u_MVP * position;

    gl_Position = projectedPosition;
    v_Position = projectedPosition;
//    v_TexCoord = texCoord;
}