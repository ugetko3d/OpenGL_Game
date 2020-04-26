#include "mat4.h"
#include <iostream>

mat4::mat4() : data{ 0.0f }
{

}

void mat4::reset()
{
	*data = { 0 };
}

void mat4::identity()
{

	reset();

	data[0] = 1.0f;
	data[5] = 1.0f;
	data[10] = 1.0f;
	data[15] = 1.0f;

}

void mat4::scale(const vec3& scale)
{

	reset();

	data[0] = scale.x;
	data[5] = scale.y;
	data[10] = scale.z;
	data[15] = 1.0f;

}

void mat4::rotate(float angle, vec3 v)
{

	float r = (float)(angle * (M_PI / 180.0f));

	float c = (float)cos((double)r);
	float s = (float)sin((double)r);
	float omc = 1.0f - c;

	v.normalize();

	reset();

	data[0] = c + omc * v.x * v.x;
	data[1] = omc * v.x * v.y + s * v.z;
	data[2] = omc * v.x * v.z - s * v.y;

	data[4] = omc * v.y * v.x - s * v.z;
	data[5] = c + omc * v.y * v.y;
	data[6] = omc * v.y * v.z + s * v.x;

	data[8] = omc * v.z * v.x + s * v.y;
	data[9] = omc * v.z * v.y - s * v.x;
	data[10] = c + omc * v.z * v.z;

	data[15] = 1.0f;
}

void mat4::translate(const vec3& translation)
{

	identity();

	data[12] = translation.x;
	data[13] = translation.y;
	data[14] = translation.z;

}

void mat4::makeView(const vec3& position, const vec3& front, const vec3& up)
{
	vec3 center = position + front;

	vec3 f = center - position;
	f.normalize();
	vec3 s = vec3::cross(f, up);
	s.normalize();

	vec3 u = vec3::cross(s, f);

	reset();

	data[0] = s.x;
	data[4] = s.y;
	data[8] = s.z;
	data[1] = u.x;
	data[5] = u.y;
	data[9] = u.z;
	data[2] = -f.x;
	data[6] = -f.y;
	data[10] = -f.z;
	data[12] = -vec3::dot(s, position);
	data[13] = -vec3::dot(u, position);
	data[14] = vec3::dot(f, position);
	data[15] = 1.0f;
}

void mat4::makePerspective(float angle, float aspectRatio, float n, float f)
{

	float a = (float)(angle * (M_PI / 180.0f));

	float t = tan(a / 2.0f) * n;
	float b = -t;
	float r = t * aspectRatio;
	float l = -t * aspectRatio;

	reset();

	data[0] = (2.0f * n) / (r - l);
	data[5] = (2.0f * n) / (t - b);
	data[8] = (r + l) / (r - l);
	data[9] = (t + b) / (t - b);
	data[10] = -((f + n) / (f - n));
	data[11] = -1.0f;
	data[14] = -((2.0f * f * n) / (f - n));
}

void mat4::makeOrtho(float l, float r, float b, float t)
{

	reset();

	data[0] = 2.0f / (r - l);
	data[5] = 2.0f / (t - b);
	data[10] = -1.0f;
	data[12] = -((r + l) / (r - l));
	data[13] = -((t + b) / (t - b));
	data[15] = 1.0f;

}

void mat4::removeTranslation()
{

	data[12] = 0.0f;
	data[13] = 0.0f;
	data[14] = 0.0f;

}

mat4 mat4::multiply(const mat4& m1, const mat4& m2)
{

	mat4 result;

	result.data[0] = m1.data[0] * m2.data[0] + m1.data[4] * m2.data[1] + m1.data[8] * m2.data[2] + m1.data[12] * m2.data[3];
	result.data[4] = m1.data[0] * m2.data[4] + m1.data[4] * m2.data[5] + m1.data[8] * m2.data[6] + m1.data[12] * m2.data[7];
	result.data[8] = m1.data[0] * m2.data[8] + m1.data[4] * m2.data[9] + m1.data[8] * m2.data[10] + m1.data[12] * m2.data[11];
	result.data[12] = m1.data[0] * m2.data[12] + m1.data[4] * m2.data[13] + m1.data[8] * m2.data[14] + m1.data[12] * m2.data[15];
	result.data[1] = m1.data[1] * m2.data[0] + m1.data[5] * m2.data[1] + m1.data[9] * m2.data[2] + m1.data[13] * m2.data[3];
	result.data[5] = m1.data[1] * m2.data[4] + m1.data[5] * m2.data[5] + m1.data[9] * m2.data[6] + m1.data[13] * m2.data[7];
	result.data[9] = m1.data[1] * m2.data[8] + m1.data[5] * m2.data[9] + m1.data[9] * m2.data[10] + m1.data[13] * m2.data[11];
	result.data[13] = m1.data[1] * m2.data[12] + m1.data[5] * m2.data[13] + m1.data[9] * m2.data[14] + m1.data[13] * m2.data[15];
	result.data[2] = m1.data[2] * m2.data[0] + m1.data[6] * m2.data[1] + m1.data[10] * m2.data[2] + m1.data[14] * m2.data[3];
	result.data[6] = m1.data[2] * m2.data[4] + m1.data[6] * m2.data[5] + m1.data[10] * m2.data[6] + m1.data[14] * m2.data[7];
	result.data[10] = m1.data[2] * m2.data[8] + m1.data[6] * m2.data[9] + m1.data[10] * m2.data[10] + m1.data[14] * m2.data[11];
	result.data[14] = m1.data[2] * m2.data[12] + m1.data[6] * m2.data[13] + m1.data[10] * m2.data[14] + m1.data[14] * m2.data[15];
	result.data[3] = m1.data[3] * m2.data[0] + m1.data[7] * m2.data[1] + m1.data[11] * m2.data[2] + m1.data[15] * m2.data[3];
	result.data[7] = m1.data[3] * m2.data[4] + m1.data[7] * m2.data[5] + m1.data[11] * m2.data[6] + m1.data[15] * m2.data[7];
	result.data[11] = m1.data[3] * m2.data[8] + m1.data[7] * m2.data[9] + m1.data[11] * m2.data[10] + m1.data[15] * m2.data[11];
	result.data[15] = m1.data[2] * m2.data[12] + m1.data[7] * m2.data[13] + m1.data[11] * m2.data[14] + m1.data[15] * m2.data[15];

	return result;
}

void mat4::inverse()
{
	float b[16], det;

	b[0] =
		data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	b[4] =
		-data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	b[8] =
		data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	b[12] =
		-data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	b[1] =
		-data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	b[5] =
		data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	b[9] =
		-data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	b[13] =
		data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	b[2] =
		data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	b[6] =
		-data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	b[10] =
		data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	b[14] =
		-data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	b[3] =
		-data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	b[7] =
		data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	b[11] =
		-data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	b[15] =
		data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	det = data[0] * b[0] + data[1] * b[4] + data[2] * b[8] + data[3] * b[12];

	if (det != 0.0f)
		det = 1.0f / det;

	for (int i = 0; i < 16; i++)
		data[i] = b[i] * det;
}

mat4 operator*(const mat4& left, const mat4& right)
{
	return mat4::multiply(left, right);
}

std::ostream& operator<<(std::ostream& stream, const mat4& m)
{
	stream << "mat4: \n" <<
		m.data[0] << "\t" << m.data[1] << "\t" << m.data[2] << "\t" << m.data[3] << "\n" <<
		m.data[4] << "\t" << m.data[5] << "\t" << m.data[6] << "\t" << m.data[7] << "\n" <<
		m.data[8] << "\t" << m.data[9] << "\t" << m.data[10] << "\t" << m.data[11] << "\n" <<
		m.data[12] << "\t" << m.data[13] << "\t" << m.data[14] << "\t" << m.data[15];
	return stream;
}