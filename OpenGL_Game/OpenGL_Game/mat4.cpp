#include "mat4.hpp"

mat4::mat4() {
	for (int i = 0; i < 16; i++)
		data[i] = 0.0f;
}

mat4 mat4::makeIdentity() {

	mat4 result;

	result.data[0] = 1.0f;
	result.data[5] = 1.0f;
	result.data[10] = 1.0f;
	result.data[15] = 1.0f;

	return result;

}

mat4 mat4::makeScale(const vec3& scale) {

	mat4 result;

	result.data[0] = scale.x;
	result.data[5] = scale.y;
	result.data[10] = scale.z;
	result.data[15] = 1.0f;

	return result;

}

mat4 mat4::makeRotate(const float& angle, const vec3& axis) {

	float r = (float)(angle * (M_PI / 180.0f));

	mat4 result;

	float c = (float)cos((double)r);
	float s = (float)sin((double)r);
	float omc = 1.0f - c;

	vec3 v = vec3::normalize(axis);

	result.data[0] = c + omc * v.x * v.x;
	result.data[1] = omc * v.x * v.y + s * v.z;
	result.data[2] = omc * v.x * v.z - s * v.y;
		   
	result.data[4] = omc * v.y * v.x - s * v.z;
	result.data[5] = c + omc * v.y * v.y;
	result.data[6] = omc * v.y * v.z + s * v.x;
		   
	result.data[8] = omc * v.z * v.x + s * v.y;
	result.data[9] = omc * v.z * v.y - s * v.x;
	result.data[10] = c + omc * v.z * v.z;
		   
	result.data[15] = 1.0f;

	return result;

}

mat4 mat4::makeTranslate(const vec3& translation) {

	mat4 result = makeIdentity();

	result.data[12] = translation.x;
	result.data[13] = translation.y;
	result.data[14] = translation.z;

	return result;

}

mat4 mat4::makePerspective(const float& angle, const float& aspectRatio, const float& n, const float& f) {

	float a = (float)(angle * (M_PI / 180.0f));

	mat4 result;

	float t = tan(a / 2.0f) * n;
	float b = -t;
	float r = t * aspectRatio;
	float l = -t * aspectRatio;

	result.data[0] = (2.0f * n) / (r - l);
	result.data[5] = (2.0f * n) / (t - b);
	result.data[8] = (r + l) / (r - l);
	result.data[9] = (t + b) / (t - b);
	result.data[10] = -((f + n) / (f - n));
	result.data[11] = -1.0f;
	result.data[14] = -((2.0f * f * n) / (f - n));

	return result;

}

mat4 mat4::makeOrtho(const float& l, const float& r, const float& b, const float& t) {

	mat4 result;

	result.data[0] = 2.0f / (r - l);
	result.data[5] = 2.0f / (t - b);
	result.data[10] = -1.0f;
	result.data[12] = -((r + l) / (r - l));
	result.data[13] = -((t + b) / (t - b));
	result.data[15] = 1.0f;

	return result;

}

mat4 mat4::removeTranslation(const mat4& m) {
	
	mat4 result = m;

	result.data[12] = 0.0f;
	result.data[13] = 0.0f;
	result.data[14] = 0.0f;

	return result;

}

mat4 mat4::multiply(const mat4& m1, const mat4& m2) {

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

mat4 mat4::inverse(const mat4& m)
{
	double b[16], det;
	mat4 m_inv;

	b[0] =
		m.data[5] * m.data[10] * m.data[15] -
		m.data[5] * m.data[11] * m.data[14] -
		m.data[9] * m.data[6] * m.data[15] +
		m.data[9] * m.data[7] * m.data[14] +
		m.data[13] * m.data[6] * m.data[11] -
		m.data[13] * m.data[7] * m.data[10];

	b[4] =
		-m.data[4] * m.data[10] * m.data[15] +
		m.data[4] * m.data[11] * m.data[14] +
		m.data[8] * m.data[6] * m.data[15] -
		m.data[8] * m.data[7] * m.data[14] -
		m.data[12] * m.data[6] * m.data[11] +
		m.data[12] * m.data[7] * m.data[10];

	b[8] =
		m.data[4] * m.data[9] * m.data[15] -
		m.data[4] * m.data[11] * m.data[13] -
		m.data[8] * m.data[5] * m.data[15] +
		m.data[8] * m.data[7] * m.data[13] +
		m.data[12] * m.data[5] * m.data[11] -
		m.data[12] * m.data[7] * m.data[9];

	b[12] =
		-m.data[4] * m.data[9] * m.data[14] +
		m.data[4] * m.data[10] * m.data[13] +
		m.data[8] * m.data[5] * m.data[14] -
		m.data[8] * m.data[6] * m.data[13] -
		m.data[12] * m.data[5] * m.data[10] +
		m.data[12] * m.data[6] * m.data[9];

	b[1] =
		-m.data[1] * m.data[10] * m.data[15] +
		m.data[1] * m.data[11] * m.data[14] +
		m.data[9] * m.data[2] * m.data[15] -
		m.data[9] * m.data[3] * m.data[14] -
		m.data[13] * m.data[2] * m.data[11] +
		m.data[13] * m.data[3] * m.data[10];

	b[5] =
		m.data[0] * m.data[10] * m.data[15] -
		m.data[0] * m.data[11] * m.data[14] -
		m.data[8] * m.data[2] * m.data[15] +
		m.data[8] * m.data[3] * m.data[14] +
		m.data[12] * m.data[2] * m.data[11] -
		m.data[12] * m.data[3] * m.data[10];

	b[9] =
		-m.data[0] * m.data[9] * m.data[15] +
		m.data[0] * m.data[11] * m.data[13] +
		m.data[8] * m.data[1] * m.data[15] -
		m.data[8] * m.data[3] * m.data[13] -
		m.data[12] * m.data[1] * m.data[11] +
		m.data[12] * m.data[3] * m.data[9];

	b[13] =
		m.data[0] * m.data[9] * m.data[14] -
		m.data[0] * m.data[10] * m.data[13] -
		m.data[8] * m.data[1] * m.data[14] +
		m.data[8] * m.data[2] * m.data[13] +
		m.data[12] * m.data[1] * m.data[10] -
		m.data[12] * m.data[2] * m.data[9];

	b[2] =
		m.data[1] * m.data[6] * m.data[15] -
		m.data[1] * m.data[7] * m.data[14] -
		m.data[5] * m.data[2] * m.data[15] +
		m.data[5] * m.data[3] * m.data[14] +
		m.data[13] * m.data[2] * m.data[7] -
		m.data[13] * m.data[3] * m.data[6];

	b[6] =
		-m.data[0] * m.data[6] * m.data[15] +
		m.data[0] * m.data[7] * m.data[14] +
		m.data[4] * m.data[2] * m.data[15] -
		m.data[4] * m.data[3] * m.data[14] -
		m.data[12] * m.data[2] * m.data[7] +
		m.data[12] * m.data[3] * m.data[6];

	b[10] =
		m.data[0] * m.data[5] * m.data[15] -
		m.data[0] * m.data[7] * m.data[13] -
		m.data[4] * m.data[1] * m.data[15] +
		m.data[4] * m.data[3] * m.data[13] +
		m.data[12] * m.data[1] * m.data[7] -
		m.data[12] * m.data[3] * m.data[5];

	b[14] =
		-m.data[0] * m.data[5] * m.data[14] +
		m.data[0] * m.data[6] * m.data[13] +
		m.data[4] * m.data[1] * m.data[14] -
		m.data[4] * m.data[2] * m.data[13] -
		m.data[12] * m.data[1] * m.data[6] +
		m.data[12] * m.data[2] * m.data[5];

	b[3] =
		-m.data[1] * m.data[6] * m.data[11] +
		m.data[1] * m.data[7] * m.data[10] +
		m.data[5] * m.data[2] * m.data[11] -
		m.data[5] * m.data[3] * m.data[10] -
		m.data[9] * m.data[2] * m.data[7] +
		m.data[9] * m.data[3] * m.data[6];

	b[7] =
		m.data[0] * m.data[6] * m.data[11] -
		m.data[0] * m.data[7] * m.data[10] -
		m.data[4] * m.data[2] * m.data[11] +
		m.data[4] * m.data[3] * m.data[10] +
		m.data[8] * m.data[2] * m.data[7] -
		m.data[8] * m.data[3] * m.data[6];

	b[11] =
		-m.data[0] * m.data[5] * m.data[11] +
		m.data[0] * m.data[7] * m.data[9] +
		m.data[4] * m.data[1] * m.data[11] -
		m.data[4] * m.data[3] * m.data[9] -
		m.data[8] * m.data[1] * m.data[7] +
		m.data[8] * m.data[3] * m.data[5];

	b[15] =
		m.data[0] * m.data[5] * m.data[10] -
		m.data[0] * m.data[6] * m.data[9] -
		m.data[4] * m.data[1] * m.data[10] +
		m.data[4] * m.data[2] * m.data[9] +
		m.data[8] * m.data[1] * m.data[6] -
		m.data[8] * m.data[2] * m.data[5];

	det = m.data[0] * b[0] + m.data[1] * b[4] + m.data[2] * b[8] + m.data[3] * b[12];

	if (det == 0) return m_inv;

	det = 1.0 / det;

	for (int i = 0; i < 16; i++)
		m_inv.data[i] = b[i] * det;

	return m_inv;
}

mat4 operator*(const mat4& left, const mat4& right) {
	return mat4::multiply(left, right);
}

std::ostream& operator<<(std::ostream& stream, const mat4& m) {
	stream << "mat4: \n" <<
	m.data[0] << "\t" << m.data[1] << "\t" << m.data[2] << "\t" << m.data[3] << "\n" << 
	m.data[4] << "\t" << m.data[5] << "\t" << m.data[6] << "\t" << m.data[7] << "\n" <<
	m.data[8] << "\t" << m.data[9] << "\t" << m.data[10] << "\t" << m.data[11] << "\n" <<
	m.data[12] << "\t" << m.data[13] << "\t" << m.data[14] << "\t" << m.data[15];
	return stream;
}