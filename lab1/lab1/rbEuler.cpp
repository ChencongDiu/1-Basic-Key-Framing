#include <iostream>
#include "rbEuler.h"
#include "math.h"

using namespace std;

#define pi 3.1415926f

rbEuler::rbEuler()
{
	roll = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	position = newVector();
}

rbEuler::rbEuler(GLfloat x, GLfloat y, GLfloat z, GLfloat roll, GLfloat pitch, GLfloat yaw)
{
	position = newVector(x, y, z);
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

rbEuler::rbEuler(const rbEuler & ref)
{
	roll = ref.roll;
	pitch = ref.pitch;
	yaw = ref.yaw;
	position = ref.position;
}

rbEuler::rbEuler(newVector position, GLfloat roll, GLfloat pitch, GLfloat yaw)
{
	this->position = position;
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

rbEuler::~rbEuler()
{
}

rbEuler rbEuler::operator+(rbEuler euler)
{
	return rbEuler(position + euler.position, roll + euler.roll, pitch + euler.pitch, yaw + euler.yaw);
}

rbEuler rbEuler::operator-(rbEuler euler)
{
	return rbEuler(position - euler.position, roll - euler.roll, pitch - euler.pitch, yaw - euler.yaw);
}

rbEuler rbEuler::operator*(rbEuler euler)
{
	return rbEuler();
}

rbEuler rbEuler::operator*(GLfloat f)
{
	return rbEuler(position * f, f * roll, f * pitch, f * yaw);
}

GLfloat * rbEuler::translateMatrix()
{
	return position.translateMatrix();
}

GLfloat* rbEuler::rotateMatrix()
{
	//GLfloat m[16];
	GLfloat *m = new GLfloat[16];
	GLfloat a = roll * pi / 180.0f;
	GLfloat b = pitch * pi / 180.0f;
	GLfloat c = yaw * pi / 180.0f;

	//z * y * x
	m[0] = cos(b) * cos(c);
	m[1] = cos(a) * sin(c) + sin(a) * sin(b) * cos(c);
	m[2] = sin(a) * sin(c) - cos(a) * sin(b) * cos(c);
	m[3] = 0.0f;
	m[4] = -(cos(b) * sin(c));
	m[5] = cos(a) * cos(c) - sin(a) * sin(b) * sin(c);
	m[6] = sin(a) * cos(c) + cos(a) * sin(b) * sin(c);
	m[7] = 0.0f;
	m[8] = sin(b);
	m[9] = -(sin(a) * cos(b));
	m[10] = cos(a) * cos(b);
	m[11] = 0.0f;
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;
	/* for (int i = 1; i <= 16; ++i) {
		cout << m[i - 1] << " ";
		if (i % 4 == 0) cout << endl;
	}
	cout << endl; */
	return m;
}
