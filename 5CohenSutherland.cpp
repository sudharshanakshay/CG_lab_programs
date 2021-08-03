#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
float xmin, ymin, xmax, ymax;
float xvmin, yvmin, xvmax, yvmax;
float x1, y1, x2, y2;
const int RIGHT = 2;
const int LEFT = 1;
const int TOP = 8;
const int BOTTOM = 4;
int computeoutcode(double x, double y);
int computeoutcode(double x, double y){
	int code = 0;
	if (y>ymax)
		code |= TOP;
	if (y<ymin)
		code |= BOTTOM;
	if (x>xmax)
		code |= RIGHT;
	else if (x<xmin)
		code |= LEFT;
	return code;
}
void cohenSutherlandLineClipAndDraw(double X1, double y1, double x2, double y2){
	int outcode1, outcode2, outcodeout;
	double x, y;
	bool accept = false, done = false;
	outcode1 = computeoutcode(x1, y1);
	outcode2 = computeoutcode(x2, y2);
	do{
		if (!(outcode1 | outcode2)){
			accept = true;
			done = true;
		}
		else if (outcode1&outcode2)
			done = true;
		else{
			outcodeout = outcode1 ? outcode1 : outcode2;
			if (outcodeout&TOP){
				x = x1 + ((x2 - x1) / (y2 - y1))*(ymax - y1);
				y = ymax;
			}
			else if (outcodeout&BOTTOM){
				x = x1 + ((x2 - x1) / (y2 - y1))*(ymin - y1);
				y = ymin;
			}
			else if (outcodeout&RIGHT){
				y = y1 + ((y2 - y1) / (x2 - x1))*(xmax - x1);
				x = xmax;
			}
			else{
				y = y1 + ((y2 - y1) / (x2 - x1))*(xmin - x1);
				x = xmin;
			}
			if (outcodeout == outcode1){
				x1 = x;
				y1 = y;
				outcode1 = computeoutcode(x1, y1);
			}
			else{
				x2 = x;
				y2 = y;
				outcode2 = computeoutcode(x2, y2);
			}

		}
	} while (!done);
	if (accept){
		float sx = (xvmax - xvmin) / (xmax - xmin);
		float sy = (yvmax - yvmin) / (ymax - ymin);

		float vx1 = xvmin + (x1 - xmin)*sx;
		float vy1 = yvmin + (y1 - ymin)*sy;
		float vx2 = xvmin + (x2 - xmin)*sx;
		float vy2 = yvmin + (y2 - ymin)*sy;
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(vx1, vy1);
		glVertex2f(vx2, vy2);
		glEnd();

	}
}

void display(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
	cohenSutherlandLineClipAndDraw(x1, y1, x2, y2);
	glFlush();
}
int main(int argc, char **argv){
	printf("enter the boundaries of window for clipping\n");
	printf("enter xmin,ymin,xmax,ymax\n");
	scanf("%f%f%f%f", &xmin, &ymin, &xmax, &ymax);

	printf("enter the boundaries of viewport\n");;
	printf("enter xvmin,yvmin,xvmax,yvmax\n");
	scanf("%f%f%f%f", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("enter vertices of 2 line(x1,y1,x2,y2):\n");
	scanf("%f%f%f%f", &x1, &y1, &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Ramyashri 4SF18CS117");
	glutDisplayFunc(display);
	glutMainLoop();
}
