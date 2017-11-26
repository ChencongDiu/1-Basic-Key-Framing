#pragma once

#include <GL\glut.h>

#include "newVector.h"

class rbQuaternion {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
	newVector position;

public:
	rbQuaternion();
	rbQuaternion(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_q, GLfloat y_q, GLfloat z_q, GLfloat w_q);
	rbQuaternion(newVector pos, GLfloat x_q, GLfloat y_q, GLfloat z_q, GLfloat w_q);
	rbQuaternion(const rbQuaternion& ref);
	~rbQuaternion();
	rbQuaternion operator+(rbQuaternion quaternion);
	rbQuaternion operator-(rbQuaternion quaternion);
	//rbQuaternion operator*(rbQuaternion quaternion);
	rbQuaternion operator*(GLfloat f);
	GLfloat* translateMatrix();
	GLfloat* rotateMatrix();
};
