#version 120

varying vec3 tangent;
varying vec3 binormal;

void main()
{
	vec3 normal = normalize(tangent);
	gl_FragColor = normalize(vec4((normal + vec3(1.0, 1.0, 1.0)) / 2.0, 1.0));
}