#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec2 TexCoord2;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    //vec4 temp = texture(Texture0, TexCoord) * vec4 (ourColor, 1.0);
    vec4 temp = mix(texture(Texture0, TexCoord), texture(Texture1, vec2(TexCoord2.s, TexCoord2.t)), 0.2);
    FragColor =  temp;
}