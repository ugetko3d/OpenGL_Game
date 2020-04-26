#include "mat4.h"
#include "vec4.h"

vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {

}

vec4::vec4(float a) : x(a), y(a), z(a), w(1.0f) {

}

vec4::vec4(float a, float b, float c) : x(a), y(b), z(c), w(1.0f) {

}

vec4::vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {

}

vec4 vec4::multiply(const mat4& m, const vec4& v) {
	return vec4(m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z + m.data[12] * v.w,
				m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z + m.data[13] * v.w,
				m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z + m.data[14] * v.w,
				m.data[3] * v.x + m.data[7] * v.y + m.data[11] * v.z + m.data[15] * v.w);
}

vec4 vec4::cross(const vec4& v1, const vec4& v2) {
	return vec4((v1.y * v2.z) - (v2.y * v1.z), -((v1.x * v2.z) - (v2.x * v1.z)), (v1.x * v2.y) - (v2.x * v1.y));
}

float vec4::dot(const vec4& v1, const vec4& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

void vec4::normalize() {
	float vectorLength = sqrt((x * x) + (y * y) + (z * z));
	x /= vectorLength;
	y /= vectorLength;
	z /= vectorLength;
	w = 1.0f;
}

void vec4::scale(float k)
{
	x *= k;
	y *= k;
	z *= k;
}

vec4 vec4::add(const vec4& v1, const vec4& v2) {
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, 1.0f);
}

vec4 vec4::subtract(const vec4& v1, const vec4& v2) {
	return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, 1.0f);
}

vec4 vec4::multiply(const vec4& v1, const vec4& v2) {
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, 1.0f);
}

vec4 vec4::divide(const vec4& v1, const vec4& v2) {
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, 1.0f);
}

vec4 vec4::scale(const vec4& v, float k) {
	return vec4(v.x * k, v.y * k, v.z * k, 1.0f);
}

vec4 operator+(const vec4& left, const vec4& right) {
	return vec4::add(left, right);
}

vec4 operator-(const vec4& left, const vec4& right) {
	return vec4::subtract(left, right);
}

vec4 operator*(const vec4& left, const vec4& right) {
	return vec4::multiply(left, right);
}

vec4 operator*(const vec4& v, float k) {
	return vec4::scale(v, k);
}

vec4 operator/(const vec4& left, const vec4& right) {
	return vec4::divide(left, right);
}

std::ostream& operator<<(std::ostream& stream, const vec4& v) {
	stream << "vec4:\n(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return stream;
}
