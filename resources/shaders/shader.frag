#version 330 core

layout(location = 0) out vec4 color;
in vec4 v_Position;
//in vec2 v_TexCoord;

uniform vec4 u_Color;
//uniform sampler2D u_Texture;

void main()
{
//    vec4 texColor = texture(u_Texture, v_TexCoord);
//    color = texColor * u_Color;
    color = u_Color /** v_Position*/;
}