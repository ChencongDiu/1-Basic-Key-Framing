#include "newVector.h"

newVector::newVector()
{
	x_pos = 0.0f;
	y_pos = 0.0f;
	z_pos = 0.0f;
}

newVector::newVector(GLfloat x, GLfloat y, GLfloat z)
{
	x_pos = x;
	y_pos = y;
	z_pos = z;
}

newVector::newVector(const newVector& ref)
{
	x_pos = ref.x_pos;
	y_pos = ref.y_pos;
	z_pos = ref.z_pos;
}

newVector::~newVector()
{
}

newVector newVector::operator+(newVector ref)
{
	return newVector(x_pos + ref.x_pos, y_pos + ref.y_pos, z_pos + ref.z_pos);
}

newVector newVector::operator-(newVector ref)
{
	return newVector(x_pos - ref.x_pos, y_pos - ref.y_pos, z_pos - ref.z_pos);
}

newVector newVector::operator*(double f)
{
	return newVector(f * x_pos, f * y_pos, f * z_pos);
}

GLfloat* newVector::translateMatrix()
{
	GLfloat m[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x_pos, y_pos, z_pos, 1.0f
	};
	return m;
}
