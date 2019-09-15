#include <iostream>

#include "mat2.h"

mat2::mat2() {
	for (int i = 0; i < 4; i++)
		data[i] = 0.0f;
}

std::ostream& operator<<(std::ostream& stream, const mat2& m) {
	stream << "mat2: \n" <<
		m.data[0] << "\t" << m.data[1] << "\n" <<
		m.data[2] << "\t" << m.data[3];
	return stream;
}