#include <GL/glew.h>
#include <GL/freeglut.h>


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void Resize(int w, int h)
{

}

void Init()
{
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	
	glutInitWindowPosition(35, 35);
	glutInitWindowSize(1024, 800);
	glutCreateWindow("OpenGL");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);

	glutMainLoop();

	return 0;
}