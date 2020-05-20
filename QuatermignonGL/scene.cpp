#include "common.h"
#include "Quaternion.h"
#include "Camera.h"
#include <math.h>

#define M_PI 3.14159265359

/** GLOBALS **/
GLfloat yaw, pitch;
GLfloat distance = 10;
GLdouble size = 1.5;
const GLint zoom = -8;
Camera* cam = new Camera();
int isRunning = 1;

/** INPUTS MANAGER FUNCTIONS **/
void KeyboardDown(unsigned char key, int xx, int yy)
{
    switch (key)
    {
    case 'e': // Unlock Camera
        cam->locked = (cam->locked) ? 0 : 1;
        break;
    case 'z':
        cam->deltaForward = 1;
        break;
    case 's':
        cam->deltaForward = -1;
        break;
    case 'd':
        cam->deltaStrafe = -1;
        break;
    case 'q':
        cam->deltaStrafe = 1;
        break;
	case 27:
		isRunning = 0;
		break;
    }
}
void KeyboardUp(unsigned char key, int xx, int yy)
{
    switch (key)
    {
    case 'z':
    case 's':
        cam->deltaForward = 0;
        break;
    case 'q':
    case 'd':
        cam->deltaStrafe = 0;
        break;
    }
}
void SpecialDown(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        cam->deltaForward = 1;
        break;
    case GLUT_KEY_DOWN:
        cam->deltaForward = -1;
        break;
    case GLUT_KEY_RIGHT:
        cam->deltaStrafe = -1;
        break;
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 1;
        break;
    }
}

void SpecialUp(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        cam->deltaForward = 0;
        break;
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 0;
        break;
    }
}

void mouseMove(int x, int y)
{
	
    // Rentres uniquement lors du clic
    cam->orienterCam(x, y);
	pitch += (x - 350) * 0.001;
	
	 
	GLfloat yawDif = (y - 350) * 0.001f;

	if(yaw + yawDif > -M_PI/4 && yaw + yawDif < M_PI / 4)
		yaw += yawDif;
	glutWarpPointer(350, 350);
}
void mouseButton(int button, int state, int x, int y){ cam->grabCam(x, y); }

/** CAMERA MOVEMENTS **/
void computePos(int osef)
{

    cam->updatePos();
    glutTimerFunc(10, computePos, 0);
}

/** GLUT FUNCTIONS **/
void Initialize(void)
{
    glutSetCursor(GLUT_CURSOR_NONE);
	distance = 5;
	yaw = pitch = .0;

}

void Shutdown(void)
{

}

void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void Update(void)
{
	if (isRunning == 0)
		glutLeaveMainLoop();
	Render();
}

void Render(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

	gluLookAt(
		distance * cos(pitch) * cos(yaw),
		distance * cos(pitch) * sin(yaw),
		distance* sin(pitch),
		0, 
		0, 
		0, 
		0.0f,
		1.0f,
		0.0f);

	//glTranslatef(0, 0, -zoom);

    glutTimerFunc(10, computePos, 0);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);


    // #Fee9fc color is the most beautifule pink in the world.
    glColor3f(0.99, 0.87, 0.97);

    // scaling transfomation 
    glScalef(1.0, 1.0, 1.0);
    // draw a fucking cube.
    glutSolidCube(size);
    // Flush buffers to screen
    glFlush();



}

