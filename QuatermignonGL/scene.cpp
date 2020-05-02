#include "common.h"
#include "Quaternion.h"
#include "Camera.h"

GLfloat xAngle, yAngle, zAngle;
GLdouble size = 1.5;
const GLint zoom = -8;
Camera* cam = new Camera();

/** FONCTIONS DE GESTION CLAVIER **/
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

/** FONCTIONS DE GESTION SOURIS (ORIENTATION CAMERA) **/
void mouseMove(int x, int y)
{
    // Rentres uniquement lors du clic
    cam->orienterCam(x, y);
}
void mouseButton(int button, int state, int x, int y)
{
    // Gestion camera en fonction du clic souris
    if (button == GLUT_LEFT_BUTTON)
    {
        // Relacher la camera
        if (state == GLUT_UP)
        {
            cam->releaseCam();
        }
        // Mise à jour origine du clic
        else
        {
            cam->grabCam(x, y);
        }
    }
}

/** GESTION DEPLACEMENT CAMERA **/
void computePos(int inutile)
{
    cam->updatePos();
    glutTimerFunc(10, computePos, 0);
}

void Initialize(void)
{
    xAngle = yAngle = zAngle = 30.0;
    xAngle = 43;
    yAngle = 50;
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
    xAngle += 0.01;
    yAngle += 0.01;
    zAngle += 0.01;
    Render();
}

void Render(void)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // translate the draw on z to zoom.
    glTranslatef(0.0, 0.0, zoom);
    gluLookAt(cam->posx, cam->posy, cam->posz,
        cam->posx + cam->dirx, cam->posy + cam->diry, cam->posz + cam->dirz,
        0.0f, 1.0f, 0.0f
    );

    glutTimerFunc(10, computePos, 0);

    /** GESTION CLAVIER **/
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    /** GESTION SOURIS **/
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);


    // --- CUBE ---

    // #Fee9fc color is the most beautifule pink in the world.
    glColor3f(0.99, 0.87, 0.97);
    Quaternion q(xAngle, 1.0, 0.0, 0.0); // just to test if quaternion can be called here.
    // Rotations perform on axis
    glRotatef(q.a(),q.b(),q.c(),q.d());
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);

    // scaling transfomation 
    glScalef(1.0, 1.0, 1.0);
    // draw a fucking cube.
    glutSolidCube(size);
    // Flush buffers to screen
    glFlush();



}

