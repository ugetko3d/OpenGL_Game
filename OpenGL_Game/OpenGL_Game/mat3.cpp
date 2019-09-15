#include "mat3.h"

mat3::mat3() {
	for (int i = 0; i < 9; i++)
		data[i] = 0.0f;
}

std::ostream& operator<<(std::ostream& stream, const mat3& m) {
	stream << "mat3: \n" <<
		m.data[0] << "\t" << m.data[1] << "\t" << m.data[2] << "\n" <<
		m.data[3] << "\t" << m.data[4] << "\t" << m.data[5] << "\n" <<
		m.data[6] << "\t" << m.data[7] << "\t" << m.data[8];
	return stream;
}