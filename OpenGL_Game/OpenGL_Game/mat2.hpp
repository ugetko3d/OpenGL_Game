#pragma once

class mat2 {

public:
	float data[4];

	mat2();

	friend std::ostream& operator<<(std::ostream& stream, const mat2& m);

};