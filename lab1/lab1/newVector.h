#pragma once

//glut
#include <GL\glut.h>

class newVector {
public:
	GLfloat x_pos;
	GLfloat y_pos;
	GLfloat z_pos;

public:
	newVector();
	newVector(GLfloat x, GLfloat y, GLfloat z);
	newVector(const newVector& ref);
	~newVector();
	newVector operator+(newVector ref);
	newVector operator-(newVector ref);
	newVector operator*(double f);
	GLfloat* translateMatrix();
};
