#include "camera.h"

void rotation_axis(vec3& vec, float angle, vec3 axis)
{
	mat4 rotM = rotate(mat4(1), radians(angle), axis);

	vec = vec3(rotM * vec4(vec, 1.0));
}

void rotation_axis(vec3& p, float angle, vec3 axis, vec3 x)
{
	mat4 rotM = rotate(mat4(1), radians(angle), axis);

	vec3 proj_p = p - x;

	proj_p = vec3(rotM * vec4(proj_p, 1.0));
	p = proj_p + x;
}

float module(vec3 vec)
{
	double x2, y2, z2;

	x2 = vec.x * vec.x;
	y2 = vec.y * vec.y;
	z2 = vec.z * vec.z;

	return sqrt(x2 + y2 + z2);
}