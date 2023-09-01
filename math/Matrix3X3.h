#pragma once


namespace owen
{
namespace math
{

class Matrix3X3
{
public:
	Matrix3X3();

public:
	union
	{
		float v[9];
		struct {
			float r0c0; float r1c0; float r2c0;
			float r0c1; float r1c1; float r2c1;
			float r0c2; float r1c2; float r2c2;
		};
		struct
		{
			float c0r0; float c0r1; float c0r2;
			float c1r0; float c1r1; float c1r2;
			float c2r0; float c2r1; float c2r2;
		};
	};
};
}
}


