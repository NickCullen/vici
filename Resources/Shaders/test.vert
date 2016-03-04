in vec2 vPosition;
in vec3 vColor;

out vec3 color;

void main(void)
{
	color = vColor;
	gl_Position = vec4(vPosition,0.0,1.0);
}