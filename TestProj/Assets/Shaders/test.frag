#version 120

#include common

void main()
{
	vec4 my_col = vec4(1,0,0,1);

	GetMyColour(my_col);

	gl_FragColor = my_col;
}