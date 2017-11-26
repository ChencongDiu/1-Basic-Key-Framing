//#include "stdafx.h"0

// standard
#include <assert.h>
#include <math.h>
#include <iostream>


// glut
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

#include "newVector.h"
#include "rbEuler.h"
#include "rbQuaternion.h"

using namespace std;
#define pi 3.1415926

//================================
// global variables
//================================
// screen size
int g_screenWidth = 0;
int g_screenHeight = 0;

// frame index
int g_frameIndex = 0;

// angle for rotation
int g_angle = 0;
double g_xdistance = 0.0;
double g_ydistance = 0.0;

// initial value of interpolation and time
int index = 0;
GLfloat time = 0.0f;

// counter for spacebar
int counter = 0;

//================================
// 6 key framing in Euler and Quaternion
//================================
rbEuler euler_p0(-5.0f, -3.0f, -10.0f, 0.0f, 0.0f, 0.0f);
rbEuler euler_p1(-3.0f, -1.0f, -10.0f, 90.0f, 0.0f, 0.0f);
rbEuler euler_p2(-1.0f, 1.0f, -10.0f, 0.0f, 0.0f, 90.0f);
rbEuler euler_p3(1.0f, -1.0f, -10.0f, 90.0f, 90.0f, 0.0f);
rbEuler euler_p4(3.0f, -2.0f, -10.0f, 0.0f, 0.0f, 90.0f);
rbEuler euler_p5(5.0f, -3.0f, -10.0f, 0.0f, 0.0f, 0.0f);

rbQuaternion quaternion_p0(-5.0f, -3.0f, -10.0f, 0.0f, 0.0f, 0.0f, 90.0f);
rbQuaternion quaternion_p1(-3.0f, -1.0f, -10.0f, 90.0f, 0.0f, 0.0f, 0.0f);
rbQuaternion quaternion_p2(-1.0f, 1.0f, -10.0f, 0.0f, 90.0f, 0.0f, 90.0f);
rbQuaternion quaternion_p3(1.0f, -1.0f, -10.0f, 0.0f, 0.0f, 0.0f, 180.0f);
rbQuaternion quaternion_p4(3.0f, -2.0f, -10.0f, 0.0f, 0.0f, 90.0f, 90.0f);
rbQuaternion quaternion_p5(5.0f, -3.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f);

rbEuler euler_points[6] = {
	euler_p0, euler_p1, euler_p2, euler_p3, euler_p4, euler_p5
};

rbQuaternion quaternion_points[6] = {
	quaternion_p0, quaternion_p1, quaternion_p2, quaternion_p3, quaternion_p4, quaternion_p5
};

//================================
// Catmull-Rom Function for Euler
//================================
rbEuler catmull_rom_euler(rbEuler p0, rbEuler p1, rbEuler p2, rbEuler p3, GLfloat t) {
	GLfloat a = 0.5f;
	rbEuler row1 = p0 * (-a) + p1 * (2 - a) + p2 * (a - 2) + p3 * a;
	rbEuler row2 = p0 * 2 * a + p1 * (a - 3) + p2 * (3 - 2 * a) + p3 * (-a);
	rbEuler row3 = p0 * (-a) + p1 * 0 + p2 * a + p3 * 0;
	rbEuler row4 = p0 * 0 + p1 * 1 + p2 * 0 + p3 * 0;
	return row1 * t * t * t + row2 * t * t + row3 * t + row4;
}

//================================
// Catmull-Rom Function for Quaternion
//================================
rbQuaternion catmull_rom_quaternion(rbQuaternion p0, rbQuaternion p1, rbQuaternion p2, rbQuaternion p3, GLfloat t) {
	GLfloat a = 0.5f;
	rbQuaternion row1 = p0 * (-a) + p1 * (2 - a) + p2 * (a - 2) + p3 * a;
	rbQuaternion row2 = p0 * 2 * a + p1 * (a - 3) + p2 * (3 - 2 * a) + p3 * (-a);
	rbQuaternion row3 = p0 * (-a) + p1 * 0 + p2 * a + p3 * 0;
	rbQuaternion row4 = p0 * 0 + p1 * 1 + p2 * 0 + p3 * 0;
	return row1 * t * t * t + row2 * t * t + row3 * t + row4;
}

//================================
// B-Splines Function for Euler
//================================
rbEuler b_splines_euler(rbEuler p0, rbEuler p1, rbEuler p2, rbEuler p3, GLfloat t) {
	GLfloat coe = 1.0f / 6.0f;
	rbEuler row1 = (p0 * -1.0f + p1 * 3.0f + p2 * -3.0f + p3 * 1.0f) * coe;
	rbEuler row2 = (p0 * 3.0f + p1 * -6.0f + p2 * 3.0f + p3 * 0.0f) * coe;
	rbEuler row3 = (p0 * -3.0f + p1 * 0.0f + p2 * 3.0f + p3 * 0.0f) * coe;
	rbEuler row4 = (p0 * 1.0f + p1 * 4.0f + p2 * 1.0f + p3 * 0.0f) * coe;
	return row1 * t * t * t + row2 * t * t + row3 * t + row4;
}

//================================
// B-Splines Function for Quaternion
//================================
rbQuaternion b_splines_quaternion(rbQuaternion p0, rbQuaternion p1, rbQuaternion p2, rbQuaternion p3, GLfloat t) {
	GLfloat coe = 1.0f / 6.0f;
	rbQuaternion row1 = (p0 * -1.0f + p1 * 3.0f + p2 * -3.0f + p3 * 1.0f) * coe;
	rbQuaternion row2 = (p0 * 3.0f + p1 * -6.0f + p2 * 3.0f + p3 * 0.0f) * coe;
	rbQuaternion row3 = (p0 * -3.0f + p1 * 0.0f + p2 * 3.0f + p3 * 0.0f) * coe;
	rbQuaternion row4 = (p0 * 1.0f + p1 * 4.0f + p2 * 1.0f + p3 * 0.0f) * coe;
	return row1 * t * t * t + row2 * t * t + row3 * t + row4;
}

//================================
// Print String on Screen
//================================
void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

//================================
// init
//================================
void init(void) {
	// init something before main loop...
}

//================================
// update
//================================
void update(void) {
	// do something before rendering...
	
	// rotation angle
	g_angle = (g_angle + 5) % 360;

	//g_xdistance = g_xdistance + 0.01;
	//g_ydistance = g_ydistance - 0.01;
}


//================================
// render
//================================
void render(void) {
	// clear buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render state
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	//helper and 6 points
	drawBitmapText("Press Spacebar to Next Mode", -3.5, 1.8, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(-5.0f, -3.0f, -10.0f);
	glVertex3f(-3.0f, -1.0f, -10.0f);
	glVertex3f(-1.0f, 1.0f, -10.0f);
	glVertex3f(1.0f, -1.0f, -10.0f);
	glVertex3f(3.0f, -2.0f, -10.0f);
	glVertex3f(5.0f, -3.0f, -10.0f);
	glEnd();

	//switch mode according to counter's value
	switch (counter) {
	case 0:
	{
		//catmull_rom_euler
		drawBitmapText("Mode: Catmull-Rom Spline for Euler Angle", -3.5, 1.5, 0.0);
		rbEuler teaport = catmull_rom_euler(euler_points[index], euler_points[index + 1], euler_points[index + 2], euler_points[index + 3], time/100.0f);
		//rbEuler teaport = catmull_rom_euler(euler_points[2], euler_points[2], euler_points[2], euler_points[2], time / 100.0f);

		glMultMatrixf(teaport.translateMatrix());
		GLfloat* m = teaport.rotateMatrix();
		glMultMatrixf(m);
		delete []m;
		break;
	}
	case 1:
	{
		//catmull_rom_quaternion
		drawBitmapText("Mode: Catmull-Rom Spline for Quaternion Angle", -3.5, 1.5, 0.0);
		rbQuaternion teaport = catmull_rom_quaternion(quaternion_points[index], quaternion_points[index + 1], quaternion_points[index + 2], quaternion_points[index + 3], time / 100.0f);
		glMultMatrixf(teaport.translateMatrix());
		GLfloat* m = teaport.rotateMatrix();
		glMultMatrixf(m);
		delete[]m;
		break;
	}
	case 2:
	{	
		//b_splines_euler
		drawBitmapText("Mode: B-Spline for Euler Angle", -3.5, 1.5, 0.0);
		rbEuler teaport = b_splines_euler(euler_points[index], euler_points[index + 1], euler_points[index + 2], euler_points[index + 3], time / 100.0f);
		glMultMatrixf(teaport.translateMatrix());
		GLfloat* m = teaport.rotateMatrix();
		glMultMatrixf(m);
		delete[]m;
		break;
	
	}
	case 3:
	{
		//b_splines_quaternion
		drawBitmapText("Mode: B-Spline for Quaternion Angle", -3.5, 1.5, 0.0);
		rbQuaternion teaport = b_splines_quaternion(quaternion_points[index], quaternion_points[index + 1], quaternion_points[index + 2], quaternion_points[index + 3], time / 100.0f);
		glMultMatrixf(teaport.translateMatrix());
		GLfloat* m = teaport.rotateMatrix();
		glMultMatrixf(m);
		delete[]m;
	}
	default:
		break;
	}

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// light source attributes
	GLfloat LightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightDiffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat LightSpecular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// surface material attributes
	GLfloat material_Ka[] = { 0.11f, 0.06f, 0.11f, 1.0f };
	GLfloat material_Kd[] = { 0.43f, 0.47f, 0.54f, 1.0f };
	GLfloat material_Ks[] = { 0.33f, 0.33f, 0.52f, 1.0f };
	GLfloat material_Ke[] = { 0.1f , 0.0f , 0.1f , 1.0f };
	GLfloat material_Se = 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	// render objects
	glutSolidTeapot(1.0);

	//index++
	if (time == 100.0f) {
		++index;
		if (index > 2) index = 0;
	}

	// disable lighting
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// swap back and front buffers
	glutSwapBuffers();
}

//================================
// keyboard input
//================================
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		counter = (counter + 1) % 4;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//================================
// reshape : update viewport and projection matrix when the window is resized
//================================
void reshape(int w, int h) {
	// screen size
	g_screenWidth = w;
	g_screenHeight = h;

	// viewport
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 2000.0);
}

//================================
// timer : triggered every 16ms ( about 60 frames per second )
//================================
void timer(int value) {
	// increase frame index
	g_frameIndex++;

	// time++
	time += 1.0f;
	if (time > 100.0f) time = 0.0f;

	//update();

	// render
	glutPostRedisplay();

	// reset timer
	// 16 ms per frame ( about 60 frames per second )
	glutTimerFunc(16, timer, 0);
}

//================================
// main
//================================
int main(int argc, char** argv) {
	// create opengL window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Lab1");

	// init
	init();

	// set callback functions
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(16, timer, 0);

	// main loop
	glutMainLoop();

	return 0;
}