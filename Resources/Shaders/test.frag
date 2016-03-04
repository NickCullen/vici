
uniform vec3 triangleColor;

out vec4 oColor;

void main()
{
    oColor = vec4(triangleColor, 1.0);
}