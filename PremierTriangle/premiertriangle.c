
#include "common.h"

void Initialize(void)
{

}

void Shutdown(void)
{

}

void Update(void)
{

}

void Render(void)
{
	glClearColor(1.f, 1.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
