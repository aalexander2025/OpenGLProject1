#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
uniform mat4 transMat;
uniform mat4 view;
uniform mat4 pro;


void main()
{
   gl_Position = pro * view * (transMat * vec4(aPos, 1.0f));
	vertexColor = vec3(1.0f, 0.5f, 0.0f);
}