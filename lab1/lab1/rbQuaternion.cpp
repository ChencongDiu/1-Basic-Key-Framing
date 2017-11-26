#include "rbQuaternion.h"
#include "math.h"

#define pi 3.1415926

rbQuaternion::rbQuaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
	position = newVector();
}

rbQuaternion::rbQuaternion(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_q, GLfloat y_q, GLfloat z_q, GLfloat w_q)
{
	x = x_q;
	y = y_q;
	z = z_q;
	w = w_q;
	position = newVector(x_pos, y_pos, z_pos);
}

rbQuaternion::rbQuaternion(newVector pos, GLfloat x_q, GLfloat y_q, GLfloat z_q, GLfloat w_q)
{
	x = x_q;
	y = y_q;
	z = z_q;
	w = w_q;
	position = pos;
}

rbQuaternion::rbQuaternion(const rbQuaternion & ref)
{
	x = ref.x;
	y = ref.y;
	z = ref.z;
	w = ref.w;
	position = ref.position;
}

rbQuaternion::~rbQuaternion()
{
}

rbQuaternion rbQuaternion::operator+(rbQuaternion quaternion)
{
	return rbQuaternion(position + quaternion.position, x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
}

rbQuaternion rbQuaternion::operator-(rbQuaternion quaternion)
{
	return rbQuaternion(position - quaternion.position, x - quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
}

rbQuaternion rbQuaternion::operator*(GLfloat f)
{
	return rbQuaternion(position * f, x * f, y * f, z * f, w * f);
}

GLfloat * rbQuaternion::translateMatrix()
{
	return position.translateMatrix();
}

GLfloat * rbQuaternion::rotateMatrix()
{
	GLfloat *m = new GLfloat[16];

	//normalization
	GLfloat sq = sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	x /= sq;
	y /= sq;
	z /= sq;
	w /= sq;

	m[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
	m[1] = 2 * x * y + 2 * w * z;
	m[2] = 2 * x * z - 2 * w * y;
	m[3] = 0.0f;
	m[4] = 2 * x * y - 2 * w * z;
	m[5] = 1 - 2 * x * x - 2 * z * z;
	m[6] = 2 * y * z + 2 * w * x;
	m[7] = 0.0f;
	m[8] = 2 * x * z + 2 * w * y;
	m[9] = 2 * y * z - 2 * w * x;
	m[10] = 1 - 2 * x * x - 2 * y * y;
	m[11] = 0.0f;
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

	return m;
}
