// PremierTriangle.c : définit le point d'entrée pour l'application console.
//
/*
#include "common.h"
void Reshape(int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(350, 350);
	glutCreateWindow("Rotating Cube #Fee9fc");
	
#if defined(FREEGLUT)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);

	Initialize();

	glutMainLoop();

	Shutdown();

	return 0;
}*/