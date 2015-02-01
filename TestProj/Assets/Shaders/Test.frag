#version 120

varying vec3 normal;
varying vec2 uv;

uniform sampler2D SimpleTexture;
uniform sampler2D RedTexture;

uniform float time;

void main()
{
	//constant vals
	float t = ( sin(time) + 1) * 0.5;

	vec4 mat_amb = vec4(0.2,0.2,0.2,1);
	vec4 mat_diff = ( t * texture2D(RedTexture, uv)) + ( (1-t) * texture2D( SimpleTexture, uv ));

	float intensity = max(0, dot(normal, vec3(0,0.8,0.2)));
	vec4 amb = mat_amb * mat_diff;
	vec4 diff = intensity * mat_diff;

   gl_FragColor = amb + diff;
}