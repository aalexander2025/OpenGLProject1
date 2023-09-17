#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 transMat;
uniform mat4 view;
uniform mat4 pro;


void main()
{
   gl_Position = pro * view * (transMat * vec4(aPos, 1.0f));
}