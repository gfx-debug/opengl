

#include <GL/freeglut.h>

int width = 0;
int height = 0;

void DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0);
	glVertex3f(0.5f, -0.5f, 0);
	glVertex3f(0.5f, 0.5f, 0);
	glEnd();
}
void Draw()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width / 2, height / 2);
	DrawTriangle();
	glViewport(width/2, 0, width/2, height/2);
	DrawTriangle();
	glViewport(0, height/2, width / 2, height / 2);
	DrawTriangle();
	glViewport(width / 2, height / 2, width / 2, height / 2);
	DrawTriangle();

	glutSwapBuffers();
}

void ReSize(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);	
	glMatrixMode(GL_MODELVIEW);	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(1024, 800);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("OpenGL");

	glutDisplayFunc(Draw);
	glutReshapeFunc(ReSize);
	glutMainLoop();
	return 0;
}