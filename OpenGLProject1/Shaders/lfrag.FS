#version 330 core

out vec4 FragColor;

uniform vec3 oColor;
uniform vec3 lColor;
uniform vec3 lPos;
uniform vec3 vPos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;




in vec3 norm;
in vec3 fPos;



void main()
{

vec3 ambstr = vec3(40.0f/255.0f, 176.0f/255.0f, 50.0f/255.0f);
vec3 matDiff = vec3(40.0f/255.0f, 176.0f/255.0f, 50.0f/255.0f);
vec3 spcstr = vec3(0.5f, 0.5f, 0.5f);

//amb
vec3 amb = ambient * vec3(0.1);

//diff
vec3 Norm = normalize(norm);
vec3 lDir = normalize(lPos - fPos);
float diff = max(dot(Norm, lDir), 0.0);
vec3 dfse = vec3(0.5) * (diff * diffuse);

//spec
vec3 vDir = normalize(vPos - fPos);
vec3 hDir = normalize(lDir + vDir);
float spec = pow(max(dot(Norm, hDir), 0.0), 64);
vec3 s =  vec3(1) * (spec * specular);



vec3 res = (amb + dfse + s) * oColor;
FragColor = vec4(res, 1.0);
}