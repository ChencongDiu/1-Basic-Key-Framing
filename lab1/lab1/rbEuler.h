#pragma once

//glut
#include <GL\glut.h>

#include "newVector.h"

class rbEuler {
public: 
	GLfloat roll;  //x
	GLfloat pitch; //y
	GLfloat yaw;   //z
	newVector position;

public:
	rbEuler();
	rbEuler(GLfloat x, GLfloat y, GLfloat z, GLfloat roll, GLfloat pitch, GLfloat yaw);
	rbEuler(const rbEuler& ref);
	rbEuler(newVector position, GLfloat roll, GLfloat pitch, GLfloat yaw);
	~rbEuler();
	rbEuler operator+(rbEuler euler);
	rbEuler operator-(rbEuler euler);
	rbEuler operator*(rbEuler euler);
	rbEuler operator*(GLfloat f);
	GLfloat* translateMatrix();
	GLfloat* rotateMatrix();
};
