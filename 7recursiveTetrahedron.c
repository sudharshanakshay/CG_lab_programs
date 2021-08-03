#include<stdio.h>
#include<GL/glut.h>

GLfloat v[4][3]={{0.0,0.0,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.0,0.5,-0.5}};
GLfloat color[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},{0.0, 0.0, 1.0}, {0.5, 0.5, 0.0}};
int n;

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m);
void draw_tri(GLfloat *a,GLfloat *b,GLfloat *c);

void draw_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
		glColor3fv(color[0]);
		draw_tri(a,b,c);
		glColor3fv(color[1]);
		draw_tri(a,c,d);
		glColor3fv(color[2]);
		draw_tri(a,d,b);
		glColor3fv(color[3]);
		draw_tri(b,c,d);
}

void draw_tri(GLfloat *a,GLfloat *b,GLfloat *c)
{
	glBegin(GL_TRIANGLES);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
	GLfloat mid[6][3];
	int i;
	if(m>0)
	{
		for(i=0;i<3;i++)
		{
			mid[0][i]=(a[i]+b[i])/2;
			mid[1][i]=(a[i]+c[i])/2;
			mid[2][i]=(b[i]+c[i])/2;
			mid[3][i]=(d[i]+c[i])/2;
			mid[4][i]=(a[i]+d[i])/2;
			mid[5][i]=(d[i]+b[i])/2;
		}
		divide_tetra(a,mid[0],mid[1],mid[4],m-1);
		divide_tetra(mid[0],b,mid[2],mid[5],m-1);
		divide_tetra(mid[1],mid[2],c,mid[3],m-1);
		divide_tetra(mid[4],mid[5],mid[3],d,m-1);
	}
	else
		draw_tetra(a,b,c,d);		
}
void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0,1.0,-1.0,1.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	divide_tetra(v[0],v[1],v[2],v[3],n);	
	glFlush();
}
int main(int argc, char *argv[])
{
	
	printf("enter the number of divisions:");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(500,500);
	glutCreateWindow("3d Sierpinski gasket");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
}
