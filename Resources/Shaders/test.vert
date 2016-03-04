in vec3 vPosition;
in vec3 vColor;
in vec2 vUV1;

out vec3 color;
out vec2 uv1;

void main(void)
{
	color = vec3(vUV1, 0.0);
	uv1 = vUV1;
	gl_Position = vec4(vPosition,1.0);
}