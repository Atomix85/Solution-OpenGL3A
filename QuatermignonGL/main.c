// PremierTriangle.c : définit le point d'entrée pour l'application console.
//

#include "common.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Premier triangle");
	
#if defined(FREEGLUT)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	glutIdleFunc(Update);
	glutDisplayFunc(Render);

	Initialize();

	glutMainLoop();

	Shutdown();

	return 0;
}