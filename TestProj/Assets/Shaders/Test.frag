#version 120

varying in vec3 normal;

void main()
{
   gl_FragColor = vec4(normal,1);
}