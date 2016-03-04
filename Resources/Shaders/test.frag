
out vec4 oColor;

in vec3 color;

void main()
{
    oColor = vec4(color, 1.0);
}