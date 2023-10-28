#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    vec4 temp = mix(texture(Texture0, TexCoord), texture(Texture1, vec2(1.0 - TexCoord.s, TexCoord.t)), 0.2);
    FragColor =  temp;
}