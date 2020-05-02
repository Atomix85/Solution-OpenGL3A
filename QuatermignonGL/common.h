#pragma once

#ifndef OPENGL_INITIATION_COMMON_H
#define OPENGL_INITIATION_COMMON_H

// comme on link avec glew32s.lib (en static)
// il faut forcer les bonnes declarations egalement
// note: les binaires precompiles pour mingw sont ici http://www.grhmedia.com/glew.html
#define GLEW_STATIC 1
#include <GL/glew.h>

// Utilise-t-on le compilateur de microsoft ?
// si oui on peut inserer programmatiquement le nom
// de la lib a linker via une directive du compilateur
#ifdef _MSC_VER
#pragma comment(lib, "glew32s.lib")
#endif

// S'agit-il d'un compilateur pour plateforme Apple ?
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef FREEGLUT
#include <GL/freeglut_ext.h>
#endif

extern void Update(void);
extern void Render(void);
extern void Initialize(void);
extern void Shutdown(void);
extern void Reshape(int x, int y);
extern void KeyboardDown(unsigned char key, int xx, int yy);
extern void KeyboardUp(unsigned char key, int xx, int yy);
extern void SpecialDown(int key, int xx, int yy);
extern void SpecialUp(int key, int xx, int yy);
extern void mouseMove(int x, int y);
extern void computePos(int inutile);


#endif // OPENGL_INITIATION_COMMON_H
