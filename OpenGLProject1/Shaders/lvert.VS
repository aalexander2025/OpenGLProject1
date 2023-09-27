#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 pro;

out vec3 norm;
out vec3 fPos;


void main()
{
   
   fPos = vec3(trans * vec4(aPos, 1.0));
   norm = mat3(transpose(inverse(trans))) * (aNorm);

   gl_Position = pro * view * vec4(fPos, 1.0);
}