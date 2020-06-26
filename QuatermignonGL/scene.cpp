#include "common.h"
#include "Quaternion.h"
#include "Camera.h"
#include <math.h>
#include "Cube.h"

#define M_PI 3.14159265359

/** GLOBALS **/
GLfloat yaw, pitch;
GLfloat theta = 0;
GLfloat distance = 20;
GLdouble size = 1.5;
const GLint zoom = -8;
Camera* cam = new Camera();
int isRunning = 1;
int oldTimeSinceStart = 0;
const int sizeObjects = 5;
Cube* objects[sizeObjects];


Quaternion rot(deg2Rad(theta), 0.0, 1.0, 0);
Cube* cube, *skybox;

GLuint texture1;

GLfloat deg2Rad(GLfloat angle) {
    return angle/ 180 * M_PI;
}

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
	yaw += (x - 350) * 0.005;
	
	 
	GLfloat pitchDif = (y - 350) * 0.005f;

	if(pitch + pitchDif >= -M_PI/2 && pitch + pitchDif < M_PI / 2)
		pitch += pitchDif;
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
	distance = 30;
	yaw = pitch = .0;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);
    //(Cube**)malloc(sizeof(Cube*) * 2);

    objects[0] = new Cube(0, 0, 0, 1, 0, 1, 1, 2, Quaternion(deg2Rad(0), 1, 0, 1), "Suntex.bmp", "tex", "sphere.obj");
    /*objects[1] = new Cube(0, 1, 1, 1, 0, 1, 0.7f, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "sphere.obj");
    objects[2] = new Cube(1, 0, 1, 0, 0, 1, 0.5f, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "sphere.obj");
    objects[3] = new Cube(3, 3, 3, 1, 1, 1, 0, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "");
    objects[4] = new Cube(4, 4, 4, 1, 0, 1, 1, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "sphere.obj");
    objects[5] = new Cube(2, 0, 2, 1, 0, 1, 1, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "");
    objects[6] = new Cube(0, 2, 2, 1, 0, 1, 1, Quaternion(deg2Rad(0), 1, 0, 1), "Explosif.bmp", "tex", "sphere.obj");*/
    objects[1] = new Cube(12, 0, 0, 0, 1, 0, -4, 0.5f, Quaternion(deg2Rad(0), 0, 1, 0),  "Explosif.bmp", "tex", "");
    //objects[2] = new Cube(1, 2, 3, 1, 0, 1, 4, 2, Quaternion(deg2Rad(0), 1, 0, 1), "moontext.bmp", "tex", "planet.obj");
    objects[2] = new Cube(5, 0, 0, 0, 0, 1, 3, 1, Quaternion(deg2Rad(0), 1, 0, 1), "", "color", "mengerCube.obj");
    objects[3] = new Cube(7, 0, 1, 0, 1, 0, 3, 0.4f, Quaternion(deg2Rad(0), 1, 0, 1), "moontext.bmp", "tex", "sphere.obj");
    objects[4] = new Cube(10, 0, 5, 1, 1, 0, 5, 1, Quaternion(deg2Rad(0), 0, 1, 0), "Explosif.bmp", "tex", "");


	//cube = new Cube(1, 1, 1, 0.5f, rot, "Explosif.bmp", "tex", "sphere.obj");
	skybox = new Cube(0, 0, 0, 0, 0, 0, 0, 50.0f, rot, "", "skybox", "");
}

void Shutdown(void)
{
	delete cube, skybox;
}

void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 210.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void Update(void)
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;


    theta += 0.0001 * deltaTime;
    for (int i = 0; i < sizeObjects; i++)
    {
		if (objects[i] != NULL) {
			objects[i]->rotate(Quaternion(deg2Rad(theta / objects[i]->thetha()), objects[i]->rotb(), objects[i]->rotc(), objects[i]->rotd()));

		}
            
            //objects[i]->rotate(Quaternion(deg2Rad(theta), objects[i]->rotb(), objects[i]->rotc(), objects[i]->rotd()));
            //objects[i]->rotate(Quaternion(deg2Rad(theta), 1, 0, 1));
    }
    //cube->rotate(Quaternion(deg2Rad(theta), cube->rotation.b, cube->rotation.c, cube->rotation.d));

	if (isRunning == 0)
		glutLeaveMainLoop();
	Render();
}

void drawRepere(int size) {

	glColor3f(0.5f, 0.0, 0.0);
	for (int i = -size; i <= size; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, -size - 1);
		glVertex3f(i, 0, size + 1);
		glEnd();
	}

	glColor3f(0.0f, 0.5, 0.0);
	for (int i = -size; i <= size; i++) {
		glBegin(GL_LINES);
		glVertex3f(-size - 1, 0, i);
		glVertex3f(size + 1, 0, i);
		glEnd();
	}

}

void Render(void)
{
    glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	gluLookAt(
		distance * cos(pitch) * cos(yaw),
		distance * sin(pitch),
		distance * cos(pitch) * sin(yaw),
		0, 
		1, 
		0, 
		0.0f,
		1.0f,
		0.0f);


	

    glutTimerFunc(10, computePos, 0);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);

	glPushMatrix();

	drawRepere(10);
   // cube->rotation *= Quaternion(deg2Rad(theta), 0.0, 1.0, 0);
	glTranslatef(0, 1, 0);

    // #Fee9fc color is the most beautiful pink in the world.
    //glColor3f(0.99, 0.87, 0.97);

    // scaling transfomation 
    glScalef(1.0, 1.0, 1.0);

    for (int i = 0; i < sizeObjects; i++)
    {
        if(objects[i] != NULL)
            objects[i]->draw(1);
    }
	skybox->draw(0);



	glPopMatrix();

    // Flush buffers to screen
    glFlush();



}


