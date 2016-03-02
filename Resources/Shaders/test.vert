uniform mat4 uModelMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;

in vec3 position;

void main(void)
{
	gl_Position = vec4(position,1.0) * uModelViewProjectionMatrix;
}