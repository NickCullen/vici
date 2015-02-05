#version 120

varying vec3 normal;
varying vec2 uv;

uniform sampler2D Diffuse;

void main()
{
	vec4 mat_amb = vec4(0.2,0.2,0.2,1);
	vec4 mat_diff = texture2D(Diffuse, uv);

	float intensity = max(0, dot(normal, vec3(0,0.8,0.2)));
	vec4 amb = mat_amb * mat_diff;
	vec4 diff = intensity * mat_diff;

   gl_FragColor = amb + diff;
}