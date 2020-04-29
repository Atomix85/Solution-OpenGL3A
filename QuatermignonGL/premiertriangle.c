#include "common.h"

GLfloat xAngle, yAngle, zAngle;
GLdouble size = 1.5;
const GLint zoom = -8;

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

    // --- CUBE ---

    // #Fee9fc color is the most beautifule pink in the world.
    glColor3f(0.99,	0.87,0.97);

    // Rotations perform on axis
    glRotatef(xAngle, 1.0, 0.0, 0.0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glRotatef(zAngle, 0.0, 0.0, 1.0);

    // scaling transfomation 
    glScalef(1.0, 1.0, 1.0);
    // draw a fucking cube.
    glutSolidCube(size);
    // Flush buffers to screen
    glFlush();

}

