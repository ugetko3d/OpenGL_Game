#pragma once

#include <iostream>

class vec3
{

public:
	float x;
	float y;
	float z;

	vec3();
	vec3(float a);
	vec3(float a, float b, float c);

	static vec3 cross(const vec3& v1, const vec3& v2);

	static float dot(const vec3& v1, const vec3& v2);

	static float length(const vec3& v);

	void normalize();
	void scale(float k);

	static vec3 midpoint(const vec3& a, const vec3& b);

	static vec3 add(const vec3& v1, const vec3& v2);
	static vec3 subtract(const vec3& v1, const vec3& v2);
	static vec3 multiply(const vec3& v1, const vec3& v2);
	static vec3 divide(const vec3& v1, const vec3& v2);
	static vec3 scale(const vec3& v, float k);

	friend vec3 operator+(const vec3& left, const vec3& right);
	friend vec3 operator-(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& v, float k);
	friend vec3 operator/(const vec3& left, const vec3& right);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& v);

};