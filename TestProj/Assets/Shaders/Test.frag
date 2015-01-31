#version 120

varying vec3 normal;

void main()
{
	//constant vals
	vec4 mat_amb = vec4(0.2,0.2,0.2,1);
	vec4 mat_diff = vec4(0.8,0.8,0.8,1);

	float intensity = max(0, dot(normal, vec3(0,0.8,0.2)));
	vec4 amb = mat_amb * mat_diff;
	vec4 diff = intensity * mat_diff;

   gl_FragColor = amb + diff;
}