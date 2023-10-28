#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 myColor;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   myColor = vec3(1.0f, 0.5f, 0.0f);
}