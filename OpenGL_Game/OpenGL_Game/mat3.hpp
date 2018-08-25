#pragma once

#include <iostream>

class mat3 {

public:
	float data[9];

	mat3();

	friend std::ostream& operator<<(std::ostream& stream, const mat3& m);

};