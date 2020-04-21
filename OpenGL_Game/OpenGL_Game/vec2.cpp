#include "vec2.h"

vec2::vec2() : x(0.0f), y(0.0f) {

}

vec2::vec2(float a) : x(a), y(a) {

}

vec2::vec2(float a, float b) : x(a), y(b) {

}

vec2::vec2(const vec2& v)
{
	copyCounter2++;
	std::cout << "We have copied: " << copyCounter2 << " number of vec4 so far..." << std::endl;
	*this = v;
}

float vec2::dot(const vec2& v1, const vec2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float vec2::length(const vec2& v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void vec2::normalize() {
	float vectorLength = sqrt((x * x) + (y * y));
	x /= vectorLength;
	y /= vectorLength;
}

vec2 vec2::midpoint(const vec2 &a, const vec2 &b) {
	return vec2((a.x + b.x) / 2, (a.y + b.y) / 2);
}

vec2 vec2::add(const vec2& v1, const vec2& v2) {
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

vec2 vec2::subtract(const vec2& v1, const vec2& v2) {
	return vec2(v1.x - v2.x, v1.y - v2.y);
}

vec2 vec2::multiply(const vec2& v1, const vec2& v2) {
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

vec2 vec2::divide(const vec2& v1, const vec2& v2) {
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

void vec2::scale(float k) {
	x *= k;
	y *= k;
}

vec2 operator+(const vec2& left, const vec2& right) {
	return vec2::add(left, right);
}

vec2 operator-(const vec2& left, const vec2& right) {
	return vec2::subtract(left, right);
}

vec2 operator*(const vec2& left, const vec2& right) {
	return vec2::multiply(left, right);
}

vec2 operator/(const vec2& left, const vec2& right) {
	return vec2::divide(left, right);
}

std::ostream& operator<<(std::ostream& stream, const vec2& v) {
	stream << "vec2:\n(" << v.x << ", " << v.y << ")";
	return stream;
}
