
out vec4 oColor;

in vec3 color;
in vec2 uv1;

uniform sampler2D tex;

void main()
{
    oColor = texture(tex, uv1);
}