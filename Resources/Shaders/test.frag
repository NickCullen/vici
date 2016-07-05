#version 150

out vec4 oColor;

in vec3 color;
in vec2 uv1;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    oColor = mix(texture2D(tex1, uv1), texture2D(tex2, uv1), (sin(500.0) + 1.0) * 0.5);
}