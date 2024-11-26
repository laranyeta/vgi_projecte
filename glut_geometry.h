//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MONOFINESTRA amb OpenGL 4.3, interf�cie GLFW, ImGui i llibreries GLM
//******** Enric Mart� G�dia (Setembre 2024)
// glut_geometry.h: interface de de glut_geometry.cpp.

/*
 * glut_geometry.h
 *
 * Freeglut geometry rendering methods.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 3 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//#include <GL/freeglut.h>
//#include "freeglut_internal.h"
#include "constants.h"
#include <vector>
#include <string>

/*
 * TODO BEFORE THE STABLE RELEASE:
 *
 * Following functions have been contributed by Andreas Umbach, updated by Enric Mart� to VBO.
 *
 *      glutSolidCube()          -- looks OK, VAO functions separated (*_VAO(), draw*(), deleteVBO(GL*)
 *      glutSolidCubeRGB()       -- looks OK, VAO functions separated (*_VAO(), draw*(), deleteVBO(GL*)
 *
 *  The Following functions have been updated by Nigel Stewart, based
 *  on FreeGLUT 2.0.0 implementations, updated by Enric Mart� to VBO:
 *
 *      glutSolidSphere()       -- looks OK
 *      glutSolidCone()         -- looks OK
 *      glutSolidCylinder()     -- looks OK
 *
 * Those functions have been implemented by John Fay, updated by Enric Mart� to VBO..
 *
 *      glutSolidTorus()				-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      glutSolidDodecahedron()			-- looks OK
 *      glutSolidOctahedron()			-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      glutSolidTetrahedron()			-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      glutSolidIcosahedron()			-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      glutSolidRhombicDodecahedron()  -- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      glutSolidSierpinskiSponge()		-- looks OK
 *      glutSolidTeapot()				-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *
 *  The Following functions have been updated by Enric Mart�, based
 *  on GLU 9.0.0 implementations (include texture coordinates) to VBO:
 *
 *      gluCylinder()			-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      gluDisk()				-- looks OK
 *      gluPartialDisk()		-- looks OK
 *      gluSphere()				-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      draw_Lemniscata2D()		-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      draw_Lemniscata3D()		-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      draw_BSpline_Curve()	-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 *      draw_Bezier_Curve()		-- looks OK, VBO functions separated (*_VBO(), draw*(), deleteVBO(GL*)
 */

#ifndef  GLET_GEOMETRY_H /* GLET_GEOMETRY_H */
#define  GLET_GEOMETRY_H

 /* -- INTERFACE CONSTANTS -------------------------------------------------- */

//--------------- VGI: M�xim tamany vector vaoList
#define MAX_SIZE_VAOID 50

//--------------- VGI: Apuntadors a l'estructura VAOList per primitives
#define CUBE_SKYBOX 0
#define GLUT_CUBE 1
#define GLUT_CUBE_RGB 2
#define GLUT_SPHERE 3
#define GLUT_CONE 4
#define GLUT_CYLINDER 5
#define GLUT_TORUS 6
#define GLUT_DODECAHEDRON 7
#define GLUT_OCTAHEDRON 8
#define GLUT_TETRAHEDRON 9
#define GLUT_ICOSAHEDRON 10
#define GLUT_RHOMBICDODECAHEDRON 11
#define GLUT_SIERPINSKISPONGE 12
#define GLUT_TEAPOT 13
#define GLU_CYLINDER 14
#define GLU_DISK 15
#define GLU_PARTIALDISK 16
#define GLU_SPHERE 17
#define CRV_POLYLINE 18
#define CRV_LEMNISCATA2D 19
#define CRV_LEMNISCATA3D 20
#define CRV_BSPLINE 21
#define CRV_BEZIER 22
#define CRV_HERMITTE 23
#define CRV_CATMULL_ROM 24
#define SUP_BSPLINE 25
#define SUP_BEZIER 26
#define GLUT_LINES 27
#define GLUT_TRIANGLES 28
#define GLU_CILINDRE_SENCER 29
#define GLU_CILINDRE_ARESTA 30
#define GLUT_SQUARE 31
#define MAR_FRACTAL_VAO 32
#define O_FRACTAL_VAO 33
#define FIT_OBJ 34
#define FIT_OBJ2 35
#define FIT_OBJ3 36
#define FIT_OBJ4 37
#define GRID_XY 38
#define GRID_XZ 39
#define GRID_YZ 40
#define GRID_XYZ 41
#define GLUT_USER1 42
#define GLUT_USER2 43
#define GLUT_USER3 44
#define GLUT_USER4 45
#define GLUT_USER5 46
#define GLUT_USER6 47
#define GLUT_USER7 48
#define GLUT_USER8 49
#define GLUT_USER9 50

// ------------------------ INTERFACE FUNCTIONS ---------------------------------

//--------------- SETS (o PUTS)
void SetColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
void Set_VAOList(GLint k, CVAO auxVAO);
void Set_vaoId(GLuint k, GLuint vaoId);
void Set_vboId(GLuint k, GLuint vboId);
void Set_eboId(GLuint k, GLuint eboId);
void Set_nVertexs(GLuint k, GLint nvertexs);

//--------------- GETS
CVAO Get_VAOList(GLint k);
GLuint Get_VAOId(GLint k);

//--------------- INITS i DELETES
void initVAOList();
void netejaVAOList();
void deleteVAOList(GLint k);

//--------------- DRAWS (DIBUIX DE VAO's i EBO's
void draw_TriVAO_Object(GLint k);
void draw_LinVAO_Object(GLint k);
void draw_TriEBO_Object(GLint k);
void draw_LinEBO_Object(GLint k);

// ---------- CUBE -----------------------------------------------------------
void glutSolidCube(GLdouble dSize);		// Generates solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
CVAO loadglutSolidCube_VAO(GLdouble dSize);
CVAO loadglutSolidCube_EBO(GLdouble dSize);
// ISMAEL ASTEROIDES
CVAO loadIcosahedron_EBO(GLdouble radius, int subdivisions);
// ---------- CUBE RGB--------------------------------------------------------
void glutSolidCubeRGB(GLdouble dSize);// Draws a solid cube coloured by RGB with VAO. Code contributed by Enric Marti <enric.marti@uab.cat>
CVAO loadglutSolidCubeRGB_VAO(GLdouble dSize);// Draws a solid cube coloured by RGB with VAO. Code contributed by Enric Marti <enric.marti@uab.cat>
CVAO loadglutSolidCubeRGB_EBO(GLdouble dSize);

// ---------- CUBE SKYBOX -----------------------------------------------------
void CubeSkybox(GLdouble dSize);
CVAO loadCubeSkybox_VAO();
void drawCubeSkybox();

// ---------- SPHERE ----------------------------------------------------------
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks); // Draws a solid sphere
CVAO loadglutSolidSphere_VAO(GLdouble radius, GLint slices, GLint stacks); // Loads a solid sphere as VAO
CVAO loadglutSolidSphere_EBO(GLdouble radius, GLint slices, GLint stacks); // Loads a solid sphere as EBO
void fghCircleTable(double **sint, double **cost, const int n);

// ---------- CONE ------------------------------------------------------------
void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks); // Draws a solid cone
CVAO loadglutSolidCone_VAO(GLdouble base, GLdouble height, GLint slices, GLint stacks); // Loads a solid cone as VAO
CVAO loadglutSolidCone_EBO(GLdouble base, GLdouble height, GLint slices, GLint stacks); // LOads a solid cone as EBO

// ---------- CYLINDER --------------------------------------------------------
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks); // Draws a solid cylinder
CVAO loadglutSolidCylinder_VAO(GLdouble radius, GLdouble height, GLint slices, GLint stacks); // Loads a solid cylinder as VAO
CVAO loadglutSolidCylinder_EBO(GLdouble radius, GLdouble height, GLint slices, GLint stacks); // Loads a solid cylinder as EBO

// ---------- TORUS -----------------------------------------------------------
void glutSolidTorus(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings); // Draws a solid torus
CVAO loadglutSolidTorus_VAO(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings); // Loads a solid torus as VAO
CVAO loadglutSolidTorus_EBO(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings); // Loads a solid torus as EBO

// ---------- DODECAHEDRON -----------------------------------------------------
void glutSolidDodecahedron(void);			// Draws a solid dodecahedron
CVAO loadglutSolidDodecahedron_VAO(void);	// Loads a solid dodecahedron as VAO
CVAO loadglutSolidDodecahedron_EBO(void);	// Loads a solid dodecahedron as ebo

// ---------- OCTAHEDRON -----------------------------------------------------
void glutSolidOctahedron(void);			// Draws a solid octahedron
CVAO loadglutSolidOctahedron_VAO(void); // Loads a solid octahedron as VAO
CVAO loadglutSolidOctahedron_EBO(void); // Loads a solid octahedron as EBO

// ---------- TETRAHEDRON -----------------------------------------------------

#define NUM_TETR_FACES     4

static GLdouble tet_r[4][3] = { { 1.0, 0.0, 0.0 },
{ -0.333333333333, 0.942809041582, 0.0 },
{ -0.333333333333, -0.471404520791, 0.816496580928 },
{ -0.333333333333, -0.471404520791, -0.816496580928 } };

static GLint tet_i[4][3] =  /* Vertex indices */
{
	{ 1, 3, 2 }, { 0, 2, 3 }, { 0, 3, 1 }, { 0, 1, 2 }
};

void glutSolidTetrahedron(void);			// Draws a solid tetrahedron
CVAO loadglutSolidTetrahedron_VAO(void);	// Loads a solid tetrahedron as VAO
CVAO loadglutSolidTetrahedron_EBO(void);	// Loads a solid tetrahedron as EBO

// ---------- ICOSAHEDRON -----------------------------------------------------
static GLdouble icos_r[12][3] = {
    {  1.0,             0.0,             0.0            },
    {  0.447213595500,  0.894427191000,  0.0            },
    {  0.447213595500,  0.276393202252,  0.850650808354 },
    {  0.447213595500, -0.723606797748,  0.525731112119 },
    {  0.447213595500, -0.723606797748, -0.525731112119 },
    {  0.447213595500,  0.276393202252, -0.850650808354 },
    { -0.447213595500, -0.894427191000,  0.0 },
    { -0.447213595500, -0.276393202252,  0.850650808354 },
    { -0.447213595500,  0.723606797748,  0.525731112119 },
    { -0.447213595500,  0.723606797748, -0.525731112119 },
    { -0.447213595500, -0.276393202252, -0.850650808354 },
    { -1.0,             0.0,             0.0            }
};

static int icos_v [20][3] = {
    {  0,  1,  2 },
    {  0,  2,  3 },
    {  0,  3,  4 },
    {  0,  4,  5 },
    {  0,  5,  1 },
    {  1,  8,  2 },
    {  2,  7,  3 },
    {  3,  6,  4 },
    {  4, 10,  5 },
    {  5,  9,  1 },
    {  1,  9,  8 },
    {  2,  8,  7 },
    {  3,  7,  6 },
    {  4,  6, 10 },
    {  5, 10,  9 },
    { 11,  9, 10 },
    { 11,  8,  9 },
    { 11,  7,  8 },
    { 11,  6,  7 },
    { 11, 10,  6 }
};

void glutSolidIcosahedron(void);			// Draws a solid icosahedron
CVAO loadglutSolidIcosahedron_VAO(void);	// Draws a solid icosahedron in VAO
CVAO loadglutSolidIcosahedron_EBO(void);	// Draws a solid icosahedron in EBO

// ---------- RHOMBIC DODECAHEDRON ---------------------------------------------

static GLdouble rdod_r[14][3] = {
    {  0.0,             0.0,             1.0 },
    {  0.707106781187,  0.000000000000,  0.5 },
    {  0.000000000000,  0.707106781187,  0.5 },
    { -0.707106781187,  0.000000000000,  0.5 },
    {  0.000000000000, -0.707106781187,  0.5 },
    {  0.707106781187,  0.707106781187,  0.0 },
    { -0.707106781187,  0.707106781187,  0.0 },
    { -0.707106781187, -0.707106781187,  0.0 },
    {  0.707106781187, -0.707106781187,  0.0 },
    {  0.707106781187,  0.000000000000, -0.5 },
    {  0.000000000000,  0.707106781187, -0.5 },
    { -0.707106781187,  0.000000000000, -0.5 },
    {  0.000000000000, -0.707106781187, -0.5 },
    {  0.0,             0.0,            -1.0 }
} ;

static int rdod_v [12][4] = {
    { 0,  1,  5,  2 },
    { 0,  2,  6,  3 },
    { 0,  3,  7,  4 },
    { 0,  4,  8,  1 },
    { 5, 10,  6,  2 },
    { 6, 11,  7,  3 },
    { 7, 12,  8,  4 },
    { 8,  9,  5,  1 },
    { 5,  9, 13, 10 },
    { 6, 10, 13, 11 },
    { 7, 11, 13, 12 },
    { 8, 12, 13,  9 }
};

static GLdouble rdod_n[12][3] = {
    {  0.353553390594,  0.353553390594,  0.5 },
    { -0.353553390594,  0.353553390594,  0.5 },
    { -0.353553390594, -0.353553390594,  0.5 },
    {  0.353553390594, -0.353553390594,  0.5 },
    {  0.000000000000,  1.000000000000,  0.0 },
    { -1.000000000000,  0.000000000000,  0.0 },
    {  0.000000000000, -1.000000000000,  0.0 },
    {  1.000000000000,  0.000000000000,  0.0 },
    {  0.353553390594,  0.353553390594, -0.5 },
    { -0.353553390594,  0.353553390594, -0.5 },
    { -0.353553390594, -0.353553390594, -0.5 },
    {  0.353553390594, -0.353553390594, -0.5 }
};

void glutSolidRhombicDodecahedron(void);			// Draws a solid Rhombic Dodecahedron
CVAO loadglutSolidRhombicDodecahedron_VAO(void);	// Loads a solid Rhombic Dodecahedron in VAO
CVAO loadglutSolidRhombicDodecahedron_EBO(void);	// Loads a solid Rhombic Dodecahedron in EBO

// ---------- SIERPINSKI SPONGE --------------------------------------------- 
void glutSolidSierpinskiSponge(int num_levels, GLdouble offset[3], GLdouble scale);				// Draws a Sierspinski Sponge
CVAO loadglutSolidSierpinskiSponge_VAO(int num_levels, GLdouble offset[3], GLdouble scale);		// Loads a Sierspinski Sponge in VAO
CVAO loadglutSolidSierpinskiSponge_EBO(int num_levels, GLdouble offset[3], GLdouble scale);		// Loads a Sierspinski Sponge in EBO
void glutSolidSierpinskiSpongeR(int num_levels, GLdouble offset[3], GLdouble scale, std::vector <double>& vertices, std::vector <double>& normals,
	std::vector <double>& colors, std::vector <double>& textures, std::vector <uint>& indices, GLuint& apunt);

// ---------- TEAPOT_DATA --------------------------------------------------- 
// Submitted through the kind offices of Daniel Wagner (daniel@ims.tuwien.ac.at)

// 530 vertices
const int numVertices = 530;
const float Vertices[530][3] = {
	2.1f, 3.6f, 0.0f,
	2.071f, 3.711f, 0.0f,
	2.105f, 3.748f, 0.0f,
	2.174f, 3.711f, 0.0f,
	2.25f, 3.6f, 0.0f,
	1.937f, 3.6f, 0.8242f,
	1.91f, 3.711f, 0.8128f,
	1.942f, 3.748f, 0.8261f,
	2.005f, 3.711f, 0.8532f,
	2.076f, 3.6f, 0.8831f,
	1.491f, 3.6f, 1.491f,
	1.47f, 3.711f, 1.47f,
	1.494f, 3.748f, 1.494f,
	1.543f, 3.711f, 1.543f,
	1.597f, 3.6f, 1.597f,
	0.8242f, 3.6f, 1.937f,
	0.8128f, 3.711f, 1.91f,
	0.8261f, 3.748f, 1.942f,
	0.8532f, 3.711f, 2.005f,
	0.8831f, 3.6f, 2.076f,
	0.0f, 3.6f, 2.1f,
	0.0f, 3.711f, 2.071f,
	0.0f, 3.748f, 2.105f,
	0.0f, 3.711f, 2.174f,
	0.0f, 3.6f, 2.25f,
	-0.8812f, 3.6f, 1.937f,
	-0.8368f, 3.711f, 1.91f,
	-0.8332f, 3.748f, 1.942f,
	-0.8541f, 3.711f, 2.005f,
	-0.8831f, 3.6f, 2.076f,
	-1.542f, 3.6f, 1.491f,
	-1.492f, 3.711f, 1.47f,
	-1.501f, 3.748f, 1.494f,
	-1.544f, 3.711f, 1.543f,
	-1.597f, 3.6f, 1.597f,
	-1.956f, 3.6f, 0.8242f,
	-1.918f, 3.711f, 0.8128f,
	-1.944f, 3.748f, 0.8261f,
	-2.006f, 3.711f, 0.8532f,
	-2.076f, 3.6f, 0.8831f,
	-2.1f, 3.6f, 0.0f,
	-2.071f, 3.711f, 0.0f,
	-2.105f, 3.748f, 0.0f,
	-2.174f, 3.711f, 0.0f,
	-2.25f, 3.6f, 0.0f,
	-1.937f, 3.6f, -0.8242f,
	-1.91f, 3.711f, -0.8128f,
	-1.942f, 3.748f, -0.8261f,
	-2.005f, 3.711f, -0.8532f,
	-2.076f, 3.6f, -0.8831f,
	-1.491f, 3.6f, -1.491f,
	-1.47f, 3.711f, -1.47f,
	-1.494f, 3.748f, -1.494f,
	-1.543f, 3.711f, -1.543f,
	-1.597f, 3.6f, -1.597f,
	-0.8242f, 3.6f, -1.937f,
	-0.8128f, 3.711f, -1.91f,
	-0.8261f, 3.748f, -1.942f,
	-0.8532f, 3.711f, -2.005f,
	-0.8831f, 3.6f, -2.076f,
	0.0f, 3.6f, -2.1f,
	0.0f, 3.711f, -2.071f,
	0.0f, 3.748f, -2.105f,
	0.0f, 3.711f, -2.174f,
	0.0f, 3.6f, -2.25f,
	0.8242f, 3.6f, -1.937f,
	0.8128f, 3.711f, -1.91f,
	0.8261f, 3.748f, -1.942f,
	0.8532f, 3.711f, -2.005f,
	0.8831f, 3.6f, -2.076f,
	1.491f, 3.6f, -1.491f,
	1.47f, 3.711f, -1.47f,
	1.494f, 3.748f, -1.494f,
	1.543f, 3.711f, -1.543f,
	1.597f, 3.6f, -1.597f,
	1.937f, 3.6f, -0.8242f,
	1.91f, 3.711f, -0.8128f,
	1.942f, 3.748f, -0.8261f,
	2.005f, 3.711f, -0.8532f,
	2.076f, 3.6f, -0.8831f,
	2.525f, 3.011f, 0.0f,
	2.766f, 2.433f, 0.0f,
	2.936f, 1.876f, 0.0f,
	3.0f, 1.35f, 0.0f,
	2.33f, 3.011f, 0.9912f,
	2.551f, 2.433f, 1.086f,
	2.708f, 1.876f, 1.152f,
	2.767f, 1.35f, 1.178f,
	1.793f, 3.011f, 1.793f,
	1.964f, 2.433f, 1.964f,
	2.084f, 1.876f, 2.084f,
	2.13f, 1.35f, 2.13f,
	0.9912f, 3.011f, 2.33f,
	1.086f, 2.433f, 2.551f,
	1.152f, 1.876f, 2.708f,
	1.178f, 1.35f, 2.767f,
	0.0f, 3.011f, 2.525f,
	0.0f, 2.433f, 2.766f,
	0.0f, 1.876f, 2.936f,
	0.0f, 1.35f, 3.0f,
	-0.9912f, 3.011f, 2.33f,
	-1.086f, 2.433f, 2.551f,
	-1.152f, 1.876f, 2.708f,
	-1.178f, 1.35f, 2.767f,
	-1.793f, 3.011f, 1.793f,
	-1.964f, 2.433f, 1.964f,
	-2.084f, 1.876f, 2.084f,
	-2.13f, 1.35f, 2.13f,
	-2.33f, 3.011f, 0.9912f,
	-2.551f, 2.433f, 1.086f,
	-2.708f, 1.876f, 1.152f,
	-2.767f, 1.35f, 1.178f,
	-2.525f, 3.011f, 0.0f,
	-2.766f, 2.433f, 0.0f,
	-2.936f, 1.876f, 0.0f,
	-3.0f, 1.35f, 0.0f,
	-2.33f, 3.011f, -0.9912f,
	-2.551f, 2.433f, -1.086f,
	-2.708f, 1.876f, -1.152f,
	-2.767f, 1.35f, -1.178f,
	-1.793f, 3.011f, -1.793f,
	-1.964f, 2.433f, -1.964f,
	-2.084f, 1.876f, -2.084f,
	-2.13f, 1.35f, -2.13f,
	-0.9912f, 3.011f, -2.33f,
	-1.086f, 2.433f, -2.551f,
	-1.152f, 1.876f, -2.708f,
	-1.178f, 1.35f, -2.767f,
	0.0f, 3.011f, -2.525f,
	0.0f, 2.433f, -2.766f,
	0.0f, 1.876f, -2.936f,
	0.0f, 1.35f, -3.0f,
	0.9912f, 3.011f, -2.33f,
	1.086f, 2.433f, -2.551f,
	1.152f, 1.876f, -2.708f,
	1.178f, 1.35f, -2.767f,
	1.793f, 3.011f, -1.793f,
	1.964f, 2.433f, -1.964f,
	2.084f, 1.876f, -2.084f,
	2.13f, 1.35f, -2.13f,
	2.33f, 3.011f, -0.9912f,
	2.551f, 2.433f, -1.086f,
	2.708f, 1.876f, -1.152f,
	2.767f, 1.35f, -1.178f,
	2.883f, 0.9053f, 0.0f,
	2.625f, 0.5766f, 0.0f,
	2.367f, 0.3533f, 0.0f,
	2.25f, 0.225f, 0.0f,
	2.659f, 0.9053f, 1.132f,
	2.422f, 0.5766f, 1.03f,
	2.184f, 0.3533f, 0.9291f,
	2.076f, 0.225f, 0.8831f,
	2.047f, 0.9053f, 2.047f,
	1.864f, 0.5766f, 1.864f,
	1.681f, 0.3533f, 1.681f,
	1.597f, 0.225f, 1.597f,
	1.132f, 0.9053f, 2.659f,
	1.03f, 0.5766f, 2.422f,
	0.9291f, 0.3533f, 2.184f,
	0.8831f, 0.225f, 2.076f,
	0.0f, 0.9053f, 2.883f,
	0.0f, 0.5766f, 2.625f,
	0.0f, 0.3533f, 2.367f,
	0.0f, 0.225f, 2.25f,
	-1.132f, 0.9053f, 2.659f,
	-1.03f, 0.5766f, 2.422f,
	-0.9291f, 0.3533f, 2.184f,
	-0.8831f, 0.225f, 2.076f,
	-2.047f, 0.9053f, 2.047f,
	-1.864f, 0.5766f, 1.864f,
	-1.681f, 0.3533f, 1.681f,
	-1.597f, 0.225f, 1.597f,
	-2.659f, 0.9053f, 1.132f,
	-2.422f, 0.5766f, 1.03f,
	-2.184f, 0.3533f, 0.9291f,
	-2.076f, 0.225f, 0.8831f,
	-2.883f, 0.9053f, 0.0f,
	-2.625f, 0.5766f, 0.0f,
	-2.367f, 0.3533f, 0.0f,
	-2.25f, 0.225f, 0.0f,
	-2.659f, 0.9053f, -1.132f,
	-2.422f, 0.5766f, -1.03f,
	-2.184f, 0.3533f, -0.9291f,
	-2.076f, 0.225f, -0.8831f,
	-2.047f, 0.9053f, -2.047f,
	-1.864f, 0.5766f, -1.864f,
	-1.681f, 0.3533f, -1.681f,
	-1.597f, 0.225f, -1.597f,
	-1.132f, 0.9053f, -2.659f,
	-1.03f, 0.5766f, -2.422f,
	-0.9291f, 0.3533f, -2.184f,
	-0.8831f, 0.225f, -2.076f,
	0.0f, 0.9053f, -2.883f,
	0.0f, 0.5766f, -2.625f,
	0.0f, 0.3533f, -2.367f,
	0.0f, 0.225f, -2.25f,
	1.132f, 0.9053f, -2.659f,
	1.03f, 0.5766f, -2.422f,
	0.9291f, 0.3533f, -2.184f,
	0.8831f, 0.225f, -2.076f,
	2.047f, 0.9053f, -2.047f,
	1.864f, 0.5766f, -1.864f,
	1.681f, 0.3533f, -1.681f,
	1.597f, 0.225f, -1.597f,
	2.659f, 0.9053f, -1.132f,
	2.422f, 0.5766f, -1.03f,
	2.184f, 0.3533f, -0.9291f,
	2.076f, 0.225f, -0.8831f,
	2.199f, 0.1424f, 0.0f,
	1.927f, 0.07031f, 0.0f,
	1.253f, 0.01934f, 0.0f,
	0.0f, 0.0f, 0.0f,
	2.029f, 0.1424f, 0.8631f,
	1.777f, 0.07031f, 0.7562f,
	1.156f, 0.01934f, 0.4919f,
	1.561f, 0.1424f, 1.561f,
	1.368f, 0.07031f, 1.368f,
	0.8899f, 0.01934f, 0.8899f,
	0.8631f, 0.1424f, 2.029f,
	0.7562f, 0.07031f, 1.777f,
	0.4919f, 0.01934f, 1.156f,
	0.0f, 0.1424f, 2.199f,
	0.0f, 0.07031f, 1.927f,
	0.0f, 0.01934f, 1.253f,
	-0.8631f, 0.1424f, 2.029f,
	-0.7562f, 0.07031f, 1.777f,
	-0.4919f, 0.01934f, 1.156f,
	-1.561f, 0.1424f, 1.561f,
	-1.368f, 0.07031f, 1.368f,
	-0.8899f, 0.01934f, 0.8899f,
	-2.029f, 0.1424f, 0.8631f,
	-1.777f, 0.07031f, 0.7562f,
	-1.156f, 0.01934f, 0.4919f,
	-2.199f, 0.1424f, 0.0f,
	-1.927f, 0.07031f, 0.0f,
	-1.253f, 0.01934f, 0.0f,
	-2.029f, 0.1424f, -0.8631f,
	-1.777f, 0.07031f, -0.7562f,
	-1.156f, 0.01934f, -0.4919f,
	-1.561f, 0.1424f, -1.561f,
	-1.368f, 0.07031f, -1.368f,
	-0.8899f, 0.01934f, -0.8899f,
	-0.8631f, 0.1424f, -2.029f,
	-0.7562f, 0.07031f, -1.777f,
	-0.4919f, 0.01934f, -1.156f,
	0.0f, 0.1424f, -2.199f,
	0.0f, 0.07031f, -1.927f,
	0.0f, 0.01934f, -1.253f,
	0.8631f, 0.1424f, -2.029f,
	0.7562f, 0.07031f, -1.777f,
	0.4919f, 0.01934f, -1.156f,
	1.561f, 0.1424f, -1.561f,
	1.368f, 0.07031f, -1.368f,
	0.8899f, 0.01934f, -0.8899f,
	2.029f, 0.1424f, -0.8631f,
	1.777f, 0.07031f, -0.7562f,
	1.156f, 0.01934f, -0.4919f,
	-2.4f, 3.038f, 0.0f,
	-3.101f, 3.032f, 0.0f,
	-3.619f, 2.995f, 0.0f,
	-3.94f, 2.895f, 0.0f,
	-4.05f, 2.7f, 0.0f,
	-2.377f, 3.09f, 0.2531f,
	-3.122f, 3.084f, 0.2531f,
	-3.669f, 3.041f, 0.2531f,
	-4.005f, 2.926f, 0.2531f,
	-4.12f, 2.7f, 0.2531f,
	-2.325f, 3.206f, 0.3375f,
	-3.168f, 3.198f, 0.3375f,
	-3.778f, 3.143f, 0.3375f,
	-4.15f, 2.993f, 0.3375f,
	-4.275f, 2.7f, 0.3375f,
	-2.273f, 3.322f, 0.2531f,
	-3.214f, 3.313f, 0.2531f,
	-3.888f, 3.244f, 0.2531f,
	-4.294f, 3.06f, 0.2531f,
	-4.43f, 2.7f, 0.2531f,
	-2.25f, 3.375f, 0.0f,
	-3.234f, 3.364f, 0.0f,
	-3.938f, 3.291f, 0.0f,
	-4.359f, 3.09f, 0.0f,
	-4.5f, 2.7f, 0.0f,
	-2.273f, 3.322f, -0.2531f,
	-3.214f, 3.313f, -0.2531f,
	-3.888f, 3.244f, -0.2531f,
	-4.294f, 3.06f, -0.2531f,
	-4.43f, 2.7f, -0.2531f,
	-2.325f, 3.206f, -0.3375f,
	-3.168f, 3.198f, -0.3375f,
	-3.778f, 3.143f, -0.3375f,
	-4.15f, 2.993f, -0.3375f,
	-4.275f, 2.7f, -0.3375f,
	-2.377f, 3.09f, -0.2531f,
	-3.122f, 3.084f, -0.2531f,
	-3.669f, 3.041f, -0.2531f,
	-4.005f, 2.926f, -0.2531f,
	-4.12f, 2.7f, -0.2531f,
	-3.991f, 2.394f, 0.0f,
	-3.806f, 2.025f, 0.0f,
	-3.48f, 1.656f, 0.0f,
	-3.0f, 1.35f, 0.0f,
	-4.055f, 2.365f, 0.2531f,
	-3.852f, 1.98f, 0.2531f,
	-3.496f, 1.6f, 0.2531f,
	-2.977f, 1.28f, 0.2531f,
	-4.196f, 2.3f, 0.3375f,
	-3.952f, 1.881f, 0.3375f,
	-3.531f, 1.478f, 0.3375f,
	-2.925f, 1.125f, 0.3375f,
	-4.336f, 2.235f, 0.2531f,
	-4.051f, 1.782f, 0.2531f,
	-3.566f, 1.356f, 0.2531f,
	-2.873f, 0.9703f, 0.2531f,
	-4.4f, 2.205f, 0.0f,
	-4.097f, 1.737f, 0.0f,
	-3.582f, 1.3f, 0.0f,
	-2.85f, 0.9f, 0.0f,
	-4.336f, 2.235f, -0.2531f,
	-4.051f, 1.782f, -0.2531f,
	-3.566f, 1.356f, -0.2531f,
	-2.873f, 0.9703f, -0.2531f,
	-4.196f, 2.3f, -0.3375f,
	-3.952f, 1.881f, -0.3375f,
	-3.531f, 1.478f, -0.3375f,
	-2.925f, 1.125f, -0.3375f,
	-4.055f, 2.365f, -0.2531f,
	-3.852f, 1.98f, -0.2531f,
	-3.496f, 1.6f, -0.2531f,
	-2.977f, 1.28f, -0.2531f,
	2.55f, 2.137f, 0.0f,
	3.27f, 2.303f, 0.0f,
	3.581f, 2.7f, 0.0f,
	3.752f, 3.182f, 0.0f,
	4.05f, 3.6f, 0.0f,
	2.55f, 1.944f, 0.5569f,
	3.324f, 2.159f, 0.5028f,
	3.652f, 2.617f, 0.3839f,
	3.838f, 3.151f, 0.265f,
	4.191f, 3.6f, 0.2109f,
	2.55f, 1.519f, 0.7425f,
	3.445f, 1.844f, 0.6704f,
	3.806f, 2.433f, 0.5119f,
	4.027f, 3.085f, 0.3533f,
	4.5f, 3.6f, 0.2813f,
	2.55f, 1.093f, 0.5569f,
	3.566f, 1.529f, 0.5028f,
	3.961f, 2.249f, 0.3839f,
	4.215f, 3.018f, 0.265f,
	4.809f, 3.6f, 0.2109f,
	2.55f, 0.9f, 0.0f,
	3.621f, 1.385f, 0.0f,
	4.031f, 2.166f, 0.0f,
	4.301f, 2.988f, 0.0f,
	4.95f, 3.6f, 0.0f,
	2.55f, 1.093f, -0.5569f,
	3.566f, 1.529f, -0.5028f,
	3.961f, 2.249f, -0.3839f,
	4.215f, 3.018f, -0.265f,
	4.809f, 3.6f, -0.2109f,
	2.55f, 1.519f, -0.7425f,
	3.445f, 1.844f, -0.6704f,
	3.806f, 2.433f, -0.5119f,
	4.027f, 3.085f, -0.3533f,
	4.5f, 3.6f, -0.2813f,
	2.55f, 1.944f, -0.5569f,
	3.324f, 2.159f, -0.5028f,
	3.652f, 2.617f, -0.3839f,
	3.838f, 3.151f, -0.265f,
	4.191f, 3.6f, -0.2109f,
	4.158f, 3.663f, 0.0f,
	4.238f, 3.684f, 0.0f,
	4.261f, 3.663f, 0.0f,
	4.2f, 3.6f, 0.0f,
	4.308f, 3.666f, 0.1978f,
	4.379f, 3.689f, 0.1687f,
	4.381f, 3.668f, 0.1397f,
	4.294f, 3.6f, 0.1266f,
	4.64f, 3.673f, 0.2637f,
	4.69f, 3.7f, 0.225f,
	4.645f, 3.677f, 0.1863f,
	4.5f, 3.6f, 0.1688f,
	4.971f, 3.68f, 0.1978f,
	5.001f, 3.711f, 0.1687f,
	4.909f, 3.687f, 0.1397f,
	4.706f, 3.6f, 0.1266f,
	5.122f, 3.683f, 0.0f,
	5.142f, 3.716f, 0.0f,
	5.029f, 3.691f, 0.0f,
	4.8f, 3.6f, 0.0f,
	4.971f, 3.68f, -0.1978f,
	5.001f, 3.711f, -0.1687f,
	4.909f, 3.687f, -0.1397f,
	4.706f, 3.6f, -0.1266f,
	4.64f, 3.673f, -0.2637f,
	4.69f, 3.7f, -0.225f,
	4.645f, 3.677f, -0.1863f,
	4.5f, 3.6f, -0.1688f,
	4.308f, 3.666f, -0.1978f,
	4.379f, 3.689f, -0.1687f,
	4.381f, 3.668f, -0.1397f,
	4.294f, 3.6f, -0.1266f,
	0.0f, 4.725f, 0.0f,
	0.5109f, 4.651f, 0.0f,
	0.4875f, 4.472f, 0.0f,
	0.2953f, 4.25f, 0.0f,
	0.3f, 4.05f, 0.0f,
	0.4715f, 4.651f, 0.2011f,
	0.4499f, 4.472f, 0.1918f,
	0.2725f, 4.25f, 0.1161f,
	0.2768f, 4.05f, 0.1178f,
	0.3632f, 4.651f, 0.3632f,
	0.3465f, 4.472f, 0.3465f,
	0.2098f, 4.25f, 0.2098f,
	0.213f, 4.05f, 0.213f,
	0.2011f, 4.651f, 0.4715f,
	0.1918f, 4.472f, 0.4499f,
	0.1161f, 4.25f, 0.2725f,
	0.1178f, 4.05f, 0.2768f,
	0.0f, 4.651f, 0.5109f,
	0.0f, 4.472f, 0.4875f,
	0.0f, 4.25f, 0.2953f,
	0.0f, 4.05f, 0.3f,
	-0.2011f, 4.651f, 0.4715f,
	-0.1918f, 4.472f, 0.4499f,
	-0.1161f, 4.25f, 0.2725f,
	-0.1178f, 4.05f, 0.2768f,
	-0.3632f, 4.651f, 0.3632f,
	-0.3465f, 4.472f, 0.3465f,
	-0.2098f, 4.25f, 0.2098f,
	-0.213f, 4.05f, 0.213f,
	-0.4715f, 4.651f, 0.2011f,
	-0.4499f, 4.472f, 0.1918f,
	-0.2725f, 4.25f, 0.1161f,
	-0.2768f, 4.05f, 0.1178f,
	-0.5109f, 4.651f, 0.0f,
	-0.4875f, 4.472f, 0.0f,
	-0.2953f, 4.25f, 0.0f,
	-0.3f, 4.05f, 0.0f,
	-0.4715f, 4.651f, -0.2011f,
	-0.4499f, 4.472f, -0.1918f,
	-0.2725f, 4.25f, -0.1161f,
	-0.2768f, 4.05f, -0.1178f,
	-0.3632f, 4.651f, -0.3632f,
	-0.3465f, 4.472f, -0.3465f,
	-0.2098f, 4.25f, -0.2098f,
	-0.213f, 4.05f, -0.213f,
	-0.2011f, 4.651f, -0.4715f,
	-0.1918f, 4.472f, -0.4499f,
	-0.1161f, 4.25f, -0.2725f,
	-0.1178f, 4.05f, -0.2768f,
	0.0f, 4.651f, -0.5109f,
	0.0f, 4.472f, -0.4875f,
	0.0f, 4.25f, -0.2953f,
	0.0f, 4.05f, -0.3f,
	0.2011f, 4.651f, -0.4715f,
	0.1918f, 4.472f, -0.4499f,
	0.1161f, 4.25f, -0.2725f,
	0.1178f, 4.05f, -0.2768f,
	0.3632f, 4.651f, -0.3632f,
	0.3465f, 4.472f, -0.3465f,
	0.2098f, 4.25f, -0.2098f,
	0.213f, 4.05f, -0.213f,
	0.4715f, 4.651f, -0.2011f,
	0.4499f, 4.472f, -0.1918f,
	0.2725f, 4.25f, -0.1161f,
	0.2768f, 4.05f, -0.1178f,
	0.6844f, 3.916f, 0.0f,
	1.237f, 3.825f, 0.0f,
	1.734f, 3.734f, 0.0f,
	1.95f, 3.6f, 0.0f,
	0.6313f, 3.916f, 0.2686f,
	1.142f, 3.825f, 0.4857f,
	1.6f, 3.734f, 0.6807f,
	1.799f, 3.6f, 0.7654f,
	0.4859f, 3.916f, 0.4859f,
	0.8786f, 3.825f, 0.8786f,
	1.231f, 3.734f, 1.231f,
	1.385f, 3.6f, 1.385f,
	0.2686f, 3.916f, 0.6313f,
	0.4857f, 3.825f, 1.142f,
	0.6807f, 3.734f, 1.6f,
	0.7654f, 3.6f, 1.799f,
	0.0f, 3.916f, 0.6844f,
	0.0f, 3.825f, 1.237f,
	0.0f, 3.734f, 1.734f,
	0.0f, 3.6f, 1.95f,
	-0.2686f, 3.916f, 0.6313f,
	-0.4857f, 3.825f, 1.142f,
	-0.6807f, 3.734f, 1.6f,
	-0.7654f, 3.6f, 1.799f,
	-0.4859f, 3.916f, 0.4859f,
	-0.8786f, 3.825f, 0.8786f,
	-1.231f, 3.734f, 1.231f,
	-1.385f, 3.6f, 1.385f,
	-0.6313f, 3.916f, 0.2686f,
	-1.142f, 3.825f, 0.4857f,
	-1.6f, 3.734f, 0.6807f,
	-1.799f, 3.6f, 0.7654f,
	-0.6844f, 3.916f, 0.0f,
	-1.237f, 3.825f, 0.0f,
	-1.734f, 3.734f, 0.0f,
	-1.95f, 3.6f, 0.0f,
	-0.6313f, 3.916f, -0.2686f,
	-1.142f, 3.825f, -0.4857f,
	-1.6f, 3.734f, -0.6807f,
	-1.799f, 3.6f, -0.7654f,
	-0.4859f, 3.916f, -0.4859f,
	-0.8786f, 3.825f, -0.8786f,
	-1.231f, 3.734f, -1.231f,
	-1.385f, 3.6f, -1.385f,
	-0.2686f, 3.916f, -0.6313f,
	-0.4857f, 3.825f, -1.142f,
	-0.6807f, 3.734f, -1.6f,
	-0.7654f, 3.6f, -1.799f,
	0.0f, 3.916f, -0.6844f,
	0.0f, 3.825f, -1.237f,
	0.0f, 3.734f, -1.734f,
	0.0f, 3.6f, -1.95f,
	0.2686f, 3.916f, -0.6313f,
	0.4857f, 3.825f, -1.142f,
	0.6807f, 3.734f, -1.6f,
	0.7654f, 3.6f, -1.799f,
	0.4859f, 3.916f, -0.4859f,
	0.8786f, 3.825f, -0.8786f,
	1.231f, 3.734f, -1.231f,
	1.385f, 3.6f, -1.385f,
	0.6313f, 3.916f, -0.2686f,
	1.142f, 3.825f, -0.4857f,
	1.6f, 3.734f, -0.6807f,
	1.799f, 3.6f, -0.7654f
};


/* 530 normals */
const int numNormals = 530;
const float Normals[530][3] = {
	0.0486f, -0.9986f, 0.0168f,
	0.9976f, -0.0678f, -0.0008f,
	-0.233f, 0.8502f, -0.4719f,
	-0.2299f, 0.9679f, 0.1004f,
	-0.1648f, 0.985f, 0.0501f,
	-0.0117f, 0.7461f, 0.6656f,
	-0.0888f, 0.9692f, 0.2294f,
	0.6449f, -0.7172f, -0.2637f,
	-0.066f, 0.9851f, 0.1583f,
	-0.6585f, -0.342f, -0.6703f,
	-0.293f, 0.9558f, 0.0209f,
	0.179f, 0.9825f, -0.0513f,
	-0.0094f, 0.903f, 0.4295f,
	-0.0059f, -0.986f, -0.1662f,
	-0.7355f, 0.6774f, -0.0026f,
	-0.997f, 0.0763f, 0.0019f,
	-0.1478f, 0.9333f, 0.3271f,
	-0.3014f, -0.6034f, -0.7382f,
	-0.7048f, -0.0681f, 0.706f,
	-0.3361f, 0.9332f, 0.1263f,
	0.3709f, 0.1524f, -0.916f,
	-0.3399f, -0.4121f, 0.8453f,
	0.1921f, 0.9724f, -0.1316f,
	-0.2671f, 0.7429f, 0.6137f,
	0.0888f, 0.9692f, -0.2294f,
	0.066f, 0.9851f, -0.1583f,
	0.9411f, 0.338f, 0.001f,
	0.8666f, -0.2559f, 0.4282f,
	-0.8029f, 0.4968f, 0.3293f,
	-0.0008f, -0.0678f, -0.9976f,
	-0.8453f, -0.4121f, -0.3399f,
	-0.4801f, -0.8741f, 0.0733f,
	0.6355f, -0.772f, 0.0006f,
	-0.9215f, -0.0678f, 0.3822f,
	-0.6698f, -0.6907f, -0.2723f,
	0.3734f, 0.876f, -0.3051f,
	0.3548f, -0.4118f, 0.8393f,
	-0.3629f, 0.2429f, 0.8995f,
	0.9033f, 0.2079f, 0.375f,
	-0.2824f, 0.5939f, 0.7532f,
	0.8938f, 0.4452f, 0.0532f,
	0.1478f, 0.9333f, -0.3271f,
	0.0085f, -0.0031f, -0.9999f,
	0.3595f, 0.933f, 0.0115f,
	0.8995f, 0.2429f, 0.3629f,
	0.7048f, -0.0681f, -0.706f,
	-0.6428f, -0.7172f, -0.2688f,
	0.6366f, -0.447f, 0.6283f,
	-0.1213f, -0.9861f, -0.1128f,
	0.8003f, 0.4978f, 0.334f,
	0.3361f, 0.9332f, -0.1263f,
	0.3399f, -0.4121f, -0.8453f,
	-0.3909f, 0.4452f, 0.8055f,
	0.0117f, 0.7462f, -0.6655f,
	0.9215f, -0.0678f, -0.3822f,
	0.3582f, -0.7656f, 0.5343f,
	-0.9782f, 0.2075f, -0.0011f,
	0.2824f, 0.5939f, -0.7532f,
	0.035f, -0.8413f, 0.5393f,
	-0.8044f, 0.5934f, 0.0262f,
	-0.1128f, -0.9861f, 0.1213f,
	0.13f, -0.1396f, 0.9816f,
	0.6644f, 0.3392f, 0.6659f,
	-0.0042f, -0.6898f, -0.7239f,
	-0.1587f, 0.9851f, 0.065f,
	-0.8719f, -0.3415f, 0.3508f,
	0.6486f, 0.4756f, -0.5941f,
	-0.4991f, 0.8499f, -0.1684f,
	-0.3969f, 0.6342f, -0.6634f,
	0.7041f, -0.3863f, -0.5956f,
	0.3909f, 0.4452f, -0.8055f,
	-0.0391f, -0.0113f, 0.9991f,
	-0.3321f, 0.5936f, -0.733f,
	0.8523f, -0.5219f, -0.0338f,
	0.329f, 0.4978f, 0.8023f,
	0.8044f, 0.5934f, -0.0262f,
	0.1128f, -0.9861f, -0.1213f,
	0.0178f, 0.9861f, -0.1651f,
	0.3491f, 0.4045f, 0.8452f,
	-0.2727f, 0.8505f, 0.4496f,
	0.065f, 0.9851f, 0.1587f,
	-0.0005f, 0.4037f, 0.9148f,
	-0.0077f, -0.4109f, -0.9116f,
	0.5609f, -0.604f, 0.5661f,
	0.8236f, 0.5668f, -0.0138f,
	0.1587f, 0.9851f, -0.065f,
	0.8719f, -0.3415f, -0.3508f,
	-0.7382f, -0.6034f, 0.3014f,
	0.0346f, 0.8495f, 0.5263f,
	-0.4373f, -0.7921f, -0.4257f,
	-0.0532f, 0.4452f, 0.8938f,
	0.0689f, -0.9861f, 0.1509f,
	-0.1509f, -0.9861f, 0.0689f,
	0.7706f, -0.2424f, -0.5893f,
	-0.7543f, -0.6564f, 0.0105f,
	0.0005f, 0.4037f, -0.9148f,
	-0.9116f, -0.4109f, 0.0077f,
	0.0058f, -0.0438f, 0.999f,
	0.1719f, 0.985f, 0.0005f,
	-0.1697f, 0.9693f, 0.1774f,
	0.5874f, -0.5124f, 0.6263f,
	0.7382f, -0.6034f, -0.3014f,
	-0.1518f, 0.985f, -0.081f,
	0.646f, 0.4051f, 0.6468f,
	0.334f, 0.4978f, -0.8003f,
	-0.7354f, -0.6034f, -0.3082f,
	-0.6919f, 0.2428f, -0.6798f,
	0.0532f, 0.4452f, -0.8938f,
	0.3547f, -0.3173f, 0.8794f,
	0.9879f, -0.1547f, -0.0033f,
	-0.0462f, -0.9986f, 0.0223f,
	-0.6088f, 0.4806f, 0.6311f,
	-0.109f, -0.1969f, -0.9743f,
	0.1509f, -0.9861f, -0.0689f,
	-0.0568f, 0.9983f, 0.0009f,
	0.9074f, -0.3096f, -0.2839f,
	0.8677f, 0.4969f, 0.0026f,
	-0.2723f, -0.6907f, 0.6698f,
	-0.4734f, -0.6798f, 0.5599f,
	0.9116f, -0.4109f, -0.0077f,
	0.1697f, 0.9693f, -0.1774f,
	0.5875f, 0.5937f, 0.5497f,
	-0.3232f, 0.6846f, 0.6533f,
	-0.5078f, -0.6913f, 0.5139f,
	-0.4612f, 0.7474f, -0.478f,
	-0.2071f, -0.8049f, 0.556f,
	-0.6976f, -0.7164f, -0.0027f,
	-0.8697f, 0.3388f, 0.3587f,
	0.0462f, -0.9986f, -0.0223f,
	0.2723f, -0.6907f, -0.6698f,
	-0.829f, -0.4466f, -0.3365f,
	0.9148f, 0.4037f, 0.0005f,
	-0.1583f, 0.9851f, -0.066f,
	0.148f, 0.9838f, 0.1002f,
	-0.1717f, 0.985f, -0.0162f,
	-0.4282f, -0.2559f, 0.8666f,
	0.3094f, -0.2556f, 0.9159f,
	0.2803f, -0.6907f, 0.6665f,
	-0.6154f, 0.497f, 0.6117f,
	-0.0262f, 0.5934f, -0.8044f,
	0.0286f, 0.1639f, -0.986f,
	-0.6924f, 0.2083f, 0.6907f,
	-0.0105f, 0.9975f, -0.0685f,
	0.5078f, -0.6913f, -0.5139f,
	0.2071f, -0.8049f, -0.556f,
	-0.4903f, -0.7178f, -0.4942f,
	-0.2637f, -0.7172f, -0.6449f,
	-0.3822f, -0.0678f, -0.9215f,
	0.8697f, 0.3388f, -0.3587f,
	0.2461f, -0.805f, 0.5397f,
	-0.2615f, 0.9334f, 0.2452f,
	0.6187f, 0.747f, -0.243f,
	0.0375f, -0.8401f, -0.5411f,
	0.0054f, 0.9691f, 0.2464f,
	0.3587f, 0.3388f, 0.8697f,
	0.3993f, 0.6582f, -0.6381f,
	-0.3476f, -0.4464f, -0.8245f,
	0.099f, 0.9692f, 0.2251f,
	-0.3666f, -0.3412f, 0.8655f,
	0.0396f, 0.153f, -0.9874f,
	0.0349f, 0.9969f, -0.0698f,
	0.1096f, 0.985f, 0.1324f,
	-0.0578f, -0.9861f, 0.1556f,
	0.4479f, -0.5145f, -0.7311f,
	0.6924f, 0.2083f, -0.6907f,
	0.6096f, 0.747f, 0.265f,
	-0.3508f, -0.3415f, -0.8719f,
	-0.6215f, 0.4454f, -0.6443f,
	-0.4942f, -0.7178f, 0.4903f,
	-0.9402f, -0.3403f, -0.0085f,
	0.0056f, -0.0358f, 0.9993f,
	0.2615f, 0.9334f, -0.2452f,
	-0.0024f, 0.0291f, -0.9995f,
	-0.2667f, 0.9637f, -0.001f,
	0.0569f, -0.2712f, -0.9608f,
	0.7463f, 0.254f, 0.615f,
	0.5153f, 0.6516f, -0.5564f,
	0.0223f, -0.9986f, 0.0462f,
	0.3666f, -0.3412f, -0.8655f,
	0.0578f, -0.9861f, -0.1556f,
	0.6111f, 0.4984f, 0.6148f,
	-0.243f, 0.747f, -0.6187f,
	-0.0092f, 0.2338f, -0.9722f,
	0.478f, 0.7474f, -0.4612f,
	-0.0058f, -0.4457f, -0.8951f,
	-0.4856f, -0.6774f, -0.5524f,
	0.54f, 0.6414f, 0.5448f,
	-0.3365f, -0.4466f, 0.829f,
	-0.2257f, 0.795f, 0.5629f,
	0.8055f, 0.4452f, 0.3909f,
	0.3729f, 0.208f, 0.9042f,
	-0.727f, -0.2562f, 0.6369f,
	-0.0514f, -0.9986f, 0.0029f,
	0.9159f, 0.1555f, -0.3699f,
	0.0019f, -0.2377f, -0.9713f,
	0.4942f, -0.7178f, -0.4903f,
	0.6497f, -0.4127f, 0.6383f,
	0.0089f, 0.0486f, -0.9987f,
	-0.0213f, 0.6301f, -0.7761f,
	-0.9269f, -0.3751f, 0.0038f,
	-0.1215f, 0.9852f, 0.1207f,
	-0.5856f, 0.5198f, 0.6218f,
	0.8655f, -0.3412f, 0.3666f,
	-0.2464f, 0.9691f, 0.0054f,
	0.0123f, 0.1386f, 0.9902f,
	0.0179f, -0.0369f, 0.9991f,
	-0.1207f, 0.9852f, -0.1215f,
	-0.0081f, 0.5671f, 0.8235f,
	-0.8689f, 0.3387f, -0.3607f,
	0.0062f, 0.0309f, -0.9995f,
	0.3365f, -0.4466f, -0.829f,
	-0.3787f, 0.2424f, -0.8931f,
	-0.2904f, 0.4454f, -0.8468f,
	-0.8707f, 0.4915f, 0.0133f,
	0.163f, -0.8182f, 0.5512f,
	0.4337f, -0.8052f, 0.4041f,
	0.0514f, -0.9986f, -0.0029f,
	-0.0084f, 0.1303f, 0.9914f,
	-0.706f, -0.0681f, -0.7048f,
	-0.556f, -0.8049f, -0.2071f,
	0.8448f, 0.4045f, 0.3501f,
	0.4259f, -0.5474f, 0.7203f,
	-0.6907f, 0.2083f, -0.6924f,
	0.1215f, 0.9852f, -0.1207f,
	-0.1263f, 0.9332f, -0.3361f,
	0.7711f, -0.0741f, -0.6323f,
	0.2464f, 0.9691f, -0.0054f,
	0.1774f, 0.9693f, 0.1697f,
	-0.9042f, 0.208f, 0.3729f,
	-0.8393f, -0.4118f, 0.3548f,
	0.6888f, -0.7219f, -0.0648f,
	0.1556f, -0.9861f, 0.0578f,
	0.3271f, 0.9333f, 0.1478f,
	-0.0024f, 0.2379f, 0.9712f,
	-0.0026f, 0.4969f, 0.8677f,
	0.0f, 1.0f, 0.0f,
	0.1912f, -0.9815f, -0.0025f,
	-0.3762f, -0.6681f, 0.6418f,
	-0.7759f, 0.0432f, 0.6292f,
	-0.0208f, -0.8044f, -0.5936f,
	-0.2274f, 0.8822f, -0.4122f,
	0.7532f, 0.5939f, 0.2824f,
	-0.9221f, -0.0681f, -0.3807f,
	-0.2198f, 0.8494f, 0.4796f,
	0.0065f, -0.7656f, 0.6431f,
	-0.5876f, 0.4472f, -0.6742f,
	0.7981f, -0.6024f, 0.0036f,
	-0.0383f, -0.9986f, -0.0341f,
	-0.6369f, -0.2562f, -0.727f,
	-0.5497f, 0.5937f, 0.5875f,
	0.1084f, 0.9431f, 0.314f,
	0.9042f, 0.208f, -0.3729f,
	-0.6659f, 0.3392f, 0.6644f,
	0.8393f, -0.4118f, -0.3548f,
	0.0029f, -0.9986f, 0.0514f,
	-0.9647f, -0.2552f, -0.0635f,
	-0.2294f, 0.9692f, -0.0888f,
	0.0026f, 0.4969f, -0.8677f,
	0.2452f, 0.9334f, 0.2615f,
	0.5171f, -0.4876f, -0.7033f,
	-0.8951f, -0.4457f, 0.0058f,
	-0.5936f, -0.8044f, 0.0208f,
	0.5642f, -0.5426f, -0.6222f,
	0.5938f, 0.4451f, 0.6702f,
	0.5497f, 0.5937f, -0.5875f,
	0.6657f, 0.4653f, 0.5832f,
	0.4857f, -0.6243f, 0.6117f,
	-0.0486f, -0.9986f, -0.0168f,
	-0.6468f, 0.4051f, 0.646f,
	0.6659f, 0.3392f, -0.6644f,
	0.1833f, 0.9735f, -0.1365f,
	0.3955f, 0.8505f, 0.3465f,
	0.5139f, -0.6913f, 0.5078f,
	0.8023f, 0.4978f, -0.329f,
	-0.001f, 0.338f, 0.9411f,
	-0.2496f, 0.8321f, -0.4951f,
	0.8951f, -0.4457f, -0.0058f,
	0.233f, 0.8502f, 0.4719f,
	-0.0168f, -0.9986f, 0.0486f,
	0.5936f, -0.8044f, -0.0208f,
	-0.05f, 0.3155f, 0.9475f,
	0.6585f, -0.342f, 0.6703f,
	0.4909f, -0.1864f, -0.8509f,
	-0.37f, 0.9238f, -0.0973f,
	0.6468f, 0.4051f, -0.646f,
	0.0059f, -0.986f, 0.1662f,
	-0.3724f, 0.9278f, -0.0202f,
	-0.3501f, 0.4045f, 0.8448f,
	-0.0425f, 0.8398f, -0.5411f,
	-0.1684f, 0.8499f, 0.4991f,
	-0.6665f, -0.6907f, 0.2803f,
	-0.2251f, 0.9692f, 0.099f,
	0.9241f, -0.3816f, -0.0169f,
	0.001f, 0.338f, -0.9411f,
	-0.9411f, 0.338f, -0.001f,
	-0.8666f, -0.2559f, -0.4282f,
	0.0262f, 0.5183f, -0.8547f,
	0.3014f, -0.6034f, 0.7382f,
	0.0168f, -0.9986f, -0.0486f,
	-0.3548f, -0.4118f, -0.8393f,
	-0.6023f, -0.5297f, 0.5971f,
	-0.9033f, 0.2079f, -0.375f,
	-0.8938f, 0.4452f, -0.0532f,
	0.6044f, 0.7397f, 0.2957f,
	0.0008f, -0.0678f, 0.9976f,
	0.7058f, 0.0906f, -0.7025f,
	0.8453f, -0.4121f, 0.3399f,
	-0.3595f, 0.933f, -0.0115f,
	0.6698f, -0.6907f, 0.2723f,
	-0.8995f, 0.2429f, -0.3629f,
	-0.6366f, -0.447f, -0.6283f,
	0.3501f, 0.4045f, -0.8448f,
	-0.01f, -0.0605f, 0.9981f,
	-0.8003f, 0.4978f, -0.334f,
	0.1684f, 0.8499f, -0.4991f,
	0.6665f, -0.6907f, -0.2803f,
	0.2251f, 0.9692f, -0.099f,
	-0.0036f, -0.6024f, 0.7981f,
	0.6637f, -0.2967f, -0.6865f,
	-0.081f, 0.985f, 0.1518f,
	0.0084f, 0.2423f, 0.9701f,
	0.0071f, -0.9029f, -0.4296f,
	-0.8679f, 0.4966f, -0.0026f,
	0.0123f, 0.5735f, 0.819f,
	-0.0005f, 0.985f, 0.1719f,
	0.6428f, -0.7172f, 0.2688f,
	0.6588f, -0.3366f, 0.6727f,
	0.1213f, -0.9861f, 0.1128f,
	-0.8931f, 0.2424f, 0.3787f,
	-0.1662f, -0.986f, 0.0059f,
	0.9994f, 0.0313f, 0.0095f,
	0.762f, -0.146f, 0.6308f,
	-0.7731f, 0.0861f, -0.6283f,
	-0.6644f, 0.3392f, -0.6659f,
	-0.0027f, -0.7164f, 0.6976f,
	0.0036f, -0.6024f, -0.7981f,
	0.9782f, 0.2075f, 0.0011f,
	0.0405f, -0.9991f, -0.0018f,
	0.6882f, -0.703f, 0.179f,
	-0.0115f, 0.933f, 0.3595f,
	0.0911f, 0.0518f, -0.9944f,
	0.0005f, 0.985f, -0.1719f,
	0.5337f, -0.5852f, -0.6104f,
	0.0042f, -0.6898f, 0.7239f,
	0.4863f, 0.2366f, 0.8411f,
	0.4991f, 0.8499f, 0.1684f,
	-0.6543f, 0.7561f, 0.0071f,
	0.265f, 0.747f, -0.6096f,
	-0.329f, 0.4978f, -0.8023f,
	0.1662f, -0.986f, -0.0059f,
	-0.3491f, 0.4045f, -0.8452f,
	0.3321f, 0.5936f, 0.733f,
	-0.065f, 0.9851f, -0.1587f,
	-0.6283f, -0.447f, 0.6366f,
	0.0027f, -0.7164f, -0.6976f,
	-0.1316f, 0.6339f, 0.762f,
	-0.5609f, -0.604f, -0.5661f,
	-0.8452f, 0.4045f, 0.3491f,
	-0.5263f, 0.8495f, 0.0346f,
	0.0115f, 0.933f, -0.3595f,
	-0.0346f, 0.8495f, -0.5263f,
	0.0077f, -0.4109f, 0.9116f,
	0.5758f, -0.8175f, -0.0017f,
	-0.0011f, 0.2075f, 0.9782f,
	-0.0689f, -0.9861f, -0.1509f,
	0.2934f, -0.5928f, -0.7499f,
	0.0724f, 0.1198f, -0.9901f,
	-0.7367f, -0.275f, -0.6176f,
	-0.3131f, 0.8154f, 0.4868f,
	-0.0114f, 0.0022f, 0.9999f,
	0.6283f, -0.447f, -0.6366f,
	0.8452f, 0.4045f, -0.3491f,
	0.5263f, 0.8495f, -0.0346f,
	-0.6383f, -0.4127f, 0.6497f,
	-0.1719f, 0.985f, -0.0005f,
	-0.6703f, -0.342f, 0.6585f,
	-0.0085f, -0.3403f, 0.9402f,
	-0.646f, 0.4051f, -0.6468f,
	0.0011f, 0.2075f, -0.9782f,
	-0.7216f, -0.3071f, 0.6204f,
	0.0282f, 0.0023f, -0.9995f,
	-0.2483f, 0.6806f, -0.6892f,
	0.1518f, 0.985f, 0.081f,
	0.047f, 0.0466f, -0.9978f,
	0.7354f, -0.6034f, 0.3082f,
	0.6919f, 0.2428f, 0.6798f,
	0.4086f, -0.3626f, -0.8375f,
	0.6383f, -0.4127f, -0.6497f,
	-0.5875f, 0.5937f, -0.5497f,
	0.6703f, -0.342f, -0.6585f,
	-0.8245f, -0.4464f, 0.3476f,
	0.0085f, -0.3403f, -0.9402f,
	-0.0591f, -0.0663f, 0.996f,
	0.0f, -1.0f, 0.0f,
	0.4612f, 0.7474f, 0.478f,
	0.6976f, -0.7164f, 0.0027f,
	-0.9148f, 0.4037f, -0.0005f,
	0.173f, -0.8158f, -0.5518f,
	-0.3607f, 0.3387f, 0.8689f,
	0.7836f, -0.2411f, 0.5724f,
	-0.1985f, 0.8026f, -0.5623f,
	-0.3094f, -0.2556f, -0.9159f,
	-0.2803f, -0.6907f, -0.6665f,
	0.8245f, -0.4464f, -0.3476f,
	0.829f, -0.4466f, 0.3365f,
	-0.4848f, 0.7385f, 0.4683f,
	0.1583f, 0.9851f, 0.066f,
	-0.0077f, 0.7656f, -0.6432f,
	-0.0162f, 0.985f, 0.1717f,
	0.1717f, 0.985f, 0.0162f,
	0.0244f, 0.9805f, -0.1949f,
	-0.2461f, -0.805f, -0.5397f,
	0.0262f, 0.5934f, 0.8044f,
	0.142f, 0.1881f, 0.9718f,
	0.1846f, 0.1002f, 0.9776f,
	0.4903f, -0.7178f, 0.4942f,
	0.2637f, -0.7172f, 0.6449f,
	0.3822f, -0.0678f, 0.9215f,
	-0.0054f, 0.9691f, -0.2464f,
	0.3607f, 0.3387f, -0.8689f,
	-0.3587f, 0.3388f, -0.8697f,
	-0.5694f, -0.8219f, 0.0081f,
	-0.1324f, 0.985f, 0.1096f,
	-0.099f, 0.9692f, -0.2251f,
	-0.6702f, 0.4451f, 0.5938f,
	0.0077f, -0.9976f, 0.0684f,
	-0.5661f, -0.604f, 0.5609f,
	-0.1096f, 0.985f, -0.1324f,
	-0.6096f, 0.747f, -0.265f,
	-0.0015f, 0.0295f, -0.9995f,
	0.3476f, -0.4464f, 0.8245f,
	-0.0635f, -0.2552f, 0.9647f,
	-0.8468f, 0.4454f, 0.2904f,
	-0.4719f, 0.8502f, 0.233f,
	-0.0502f, 0.8385f, 0.5425f,
	-0.6671f, 0.7448f, -0.0116f,
	0.3508f, -0.3415f, 0.8719f,
	-0.4119f, 0.6135f, -0.6736f,
	-0.2688f, -0.7172f, 0.6428f,
	-0.4041f, -0.8052f, 0.4337f,
	-0.375f, 0.2079f, 0.9033f,
	-0.0223f, -0.9986f, -0.0462f,
	0.6702f, 0.4451f, -0.5938f,
	0.9402f, -0.3403f, 0.0085f,
	0.5661f, -0.604f, -0.5609f,
	-0.6252f, 0.7406f, 0.246f,
	-0.0341f, -0.9986f, 0.0383f,
	-0.6111f, 0.4984f, -0.6148f,
	0.6655f, 0.7462f, 0.0117f,
	0.1233f, 0.199f, 0.9722f,
	0.8468f, 0.4454f, -0.2904f,
	0.7383f, 0.2702f, -0.6179f,
	-0.8055f, 0.4452f, -0.3909f,
	-0.3729f, 0.208f, -0.9042f,
	0.4719f, 0.8502f, -0.233f,
	0.243f, 0.747f, 0.6187f,
	-0.6497f, -0.4127f, -0.6383f,
	-0.5406f, 0.5651f, -0.623f,
	0.0058f, -0.4457f, 0.8951f,
	-0.3082f, -0.6034f, 0.7354f,
	-0.8655f, -0.3412f, -0.3666f,
	0.2688f, -0.7172f, -0.6428f,
	0.4041f, -0.8052f, -0.4337f,
	0.375f, 0.2079f, -0.9033f,
	0.0341f, -0.9986f, -0.0383f,
	-0.9701f, 0.2423f, 0.0084f,
	-0.3807f, -0.0681f, 0.9221f,
	0.9643f, -0.2551f, 0.0705f,
	-0.8758f, 0.4808f, 0.0415f,
	0.1207f, 0.9852f, 0.1215f,
	0.4821f, 0.7724f, 0.4133f,
	-0.0522f, 0.9982f, 0.0278f,
	-0.4337f, -0.8052f, -0.4041f,
	-0.6164f, 0.4198f, 0.6661f,
	-0.8448f, 0.4045f, -0.3501f,
	0.3082f, -0.6034f, -0.7354f,
	0.8689f, 0.3387f, 0.3607f,
	0.6894f, -0.7242f, 0.0091f,
	0.3787f, 0.2424f, 0.8931f,
	0.2904f, 0.4454f, 0.8468f,
	0.6148f, 0.4984f, -0.6111f,
	0.0501f, 0.985f, 0.1648f,
	-0.5397f, -0.805f, 0.2461f,
	-0.9159f, -0.2556f, 0.3094f,
	0.706f, -0.0681f, 0.7048f,
	-0.3341f, 0.4972f, 0.8006f,
	0.556f, -0.8049f, 0.2071f,
	-0.1774f, 0.9693f, -0.1697f,
	0.6907f, 0.2083f, 0.6924f,
	0.1263f, 0.9332f, 0.3361f,
	0.3807f, -0.0681f, -0.9221f,
	-0.1556f, -0.9861f, -0.0578f,
	-0.3271f, 0.9333f, -0.1478f,
	-0.3465f, 0.8505f, 0.3955f,
	0.5315f, 0.8438f, -0.0735f,
	0.9737f, 0.2276f, -0.0003f,
	0.6441f, 0.7648f, -0.0112f,
	-0.7239f, -0.6898f, 0.0042f,
	-0.7532f, 0.5939f, -0.2824f,
	0.1093f, 0.1415f, -0.9838f,
	0.5397f, -0.805f, -0.2461f,
	-0.7981f, -0.6024f, -0.0036f,
	0.9456f, 0.3251f, -0.0052f,
	0.1278f, 0.9696f, -0.2085f,
	0.0208f, -0.8044f, 0.5936f,
	0.1635f, 0.1348f, -0.9772f,
	-0.733f, 0.5936f, 0.3321f,
	-0.0505f, 0.9852f, -0.1635f,
	0.4089f, -0.9069f, -0.1015f,
	-0.0029f, -0.9986f, -0.0514f,
	-0.1796f, 0.814f, -0.5522f,
	0.9221f, -0.0681f, 0.3807f,
	0.0383f, -0.9986f, 0.0341f,
	0.6369f, -0.2562f, 0.727f,
	0.3465f, 0.8505f, -0.3955f,
	-0.2452f, 0.9334f, -0.2615f,
	0.4921f, -0.247f, 0.8346f,
	-0.9976f, -0.0678f, 0.0008f,
	-0.5396f, 0.8418f, -0.0094f,
	0.2294f, 0.9692f, 0.0888f,
	0.7239f, -0.6898f, -0.0042f,
	-0.4472f, 0.5952f, 0.6675f,
	-0.6449f, -0.7172f, 0.2637f,
	0.4543f, 0.2732f, -0.8478f,
	-0.6798f, 0.2428f, 0.6919f,
	-0.5938f, 0.4451f, -0.6702f,
	0.733f, 0.5936f, -0.3321f,
	-0.3955f, 0.8505f, -0.3465f,
	-0.5139f, -0.6913f, -0.5078f,
	-0.623f, -0.5156f, -0.5881f
};

/* 1 color   */
/*255 255 0  */

/* 1024 faces */
/* numIdx fidx0 fidx1 fidx2 nidx0 nidx1 nidx2 coloridx */

const int numFaces = 1024;
const int faces[1024][8] = {
	3, 0, 5, 6, 255, 295, 309, 0,
	3, 6, 1, 0, 309, 465, 255, 0,
	3, 1, 6, 7, 465, 309, 134, 0,
	3, 7, 2, 1, 134, 4, 465, 0,
	3, 2, 7, 8, 4, 134, 165, 0,
	3, 8, 3, 2, 165, 448, 4, 0,
	3, 3, 8, 9, 448, 165, 49, 0,
	3, 9, 4, 3, 49, 116, 448, 0,
	3, 5, 10, 11, 295, 248, 106, 0,
	3, 11, 6, 5, 106, 309, 295, 0,
	3, 6, 11, 12, 309, 106, 102, 0,
	3, 12, 7, 6, 102, 134, 309, 0,
	3, 7, 12, 13, 134, 102, 394, 0,
	3, 13, 8, 7, 394, 165, 134, 0,
	3, 8, 13, 14, 165, 394, 180, 0,
	3, 14, 9, 8, 180, 49, 165, 0,
	3, 10, 15, 16, 248, 401, 211, 0,
	3, 16, 11, 10, 211, 106, 248, 0,
	3, 11, 16, 17, 106, 211, 427, 0,
	3, 17, 12, 11, 427, 102, 106, 0,
	3, 12, 17, 18, 102, 427, 455, 0,
	3, 18, 13, 12, 455, 394, 102, 0,
	3, 13, 18, 19, 394, 455, 74, 0,
	3, 19, 14, 13, 74, 180, 394, 0,
	3, 15, 20, 21, 401, 174, 182, 0,
	3, 21, 16, 15, 182, 211, 401, 0,
	3, 16, 21, 22, 211, 182, 507, 0,
	3, 22, 17, 16, 507, 427, 211, 0,
	3, 17, 22, 23, 427, 507, 5, 0,
	3, 23, 18, 17, 5, 455, 427, 0,
	3, 18, 23, 24, 455, 5, 234, 0,
	3, 24, 19, 18, 234, 74, 455, 0,
	3, 20, 25, 26, 174, 386, 20, 0,
	3, 26, 21, 20, 20, 182, 174, 0,
	3, 21, 26, 27, 182, 20, 410, 0,
	3, 27, 22, 21, 410, 507, 182, 0,
	3, 22, 27, 28, 507, 410, 23, 0,
	3, 28, 23, 22, 23, 5, 507, 0,
	3, 23, 28, 29, 5, 23, 485, 0,
	3, 29, 24, 23, 485, 234, 5, 0,
	3, 25, 30, 31, 386, 69, 305, 0,
	3, 31, 26, 25, 305, 20, 386, 0,
	3, 26, 31, 32, 20, 305, 503, 0,
	3, 32, 27, 26, 503, 410, 20, 0,
	3, 27, 32, 33, 410, 503, 405, 0,
	3, 33, 28, 27, 405, 23, 410, 0,
	3, 28, 33, 34, 23, 405, 138, 0,
	3, 34, 29, 28, 138, 485, 23, 0,
	3, 30, 35, 36, 69, 115, 193, 0,
	3, 36, 31, 30, 193, 305, 69, 0,
	3, 31, 36, 37, 305, 193, 270, 0,
	3, 37, 32, 31, 270, 503, 305, 0,
	3, 32, 37, 38, 503, 270, 445, 0,
	3, 38, 33, 32, 445, 405, 503, 0,
	3, 33, 38, 39, 405, 445, 28, 0,
	3, 39, 34, 33, 28, 138, 405, 0,
	3, 35, 40, 41, 115, 467, 495, 0,
	3, 41, 36, 35, 495, 193, 115, 0,
	3, 36, 41, 42, 193, 495, 11, 0,
	3, 42, 37, 36, 11, 270, 193, 0,
	3, 37, 42, 43, 270, 11, 435, 0,
	3, 43, 38, 37, 435, 445, 270, 0,
	3, 38, 43, 44, 445, 435, 322, 0,
	3, 44, 39, 38, 322, 28, 445, 0,
	3, 40, 45, 46, 467, 27, 44, 0,
	3, 46, 41, 40, 44, 495, 467, 0,
	3, 41, 46, 47, 495, 44, 409, 0,
	3, 47, 42, 41, 409, 11, 495, 0,
	3, 42, 47, 48, 11, 409, 428, 0,
	3, 48, 43, 42, 428, 435, 11, 0,
	3, 43, 48, 49, 435, 428, 313, 0,
	3, 49, 44, 43, 313, 322, 435, 0,
	3, 45, 50, 51, 27, 513, 385, 0,
	3, 51, 46, 45, 385, 44, 27, 0,
	3, 46, 51, 52, 44, 385, 382, 0,
	3, 52, 47, 46, 382, 409, 44, 0,
	3, 47, 52, 53, 409, 382, 124, 0,
	3, 53, 48, 47, 124, 428, 409, 0,
	3, 48, 53, 54, 428, 124, 447, 0,
	3, 54, 49, 48, 447, 313, 428, 0,
	3, 50, 55, 56, 513, 136, 478, 0,
	3, 56, 51, 50, 478, 385, 513, 0,
	3, 51, 56, 57, 385, 478, 161, 0,
	3, 57, 52, 51, 161, 382, 385, 0,
	3, 52, 57, 58, 382, 161, 181, 0,
	3, 58, 53, 52, 181, 124, 382, 0,
	3, 53, 58, 59, 124, 181, 348, 0,
	3, 59, 54, 53, 348, 447, 124, 0,
	3, 55, 60, 61, 136, 431, 320, 0,
	3, 61, 56, 55, 320, 478, 136, 0,
	3, 56, 61, 62, 478, 320, 481, 0,
	3, 62, 57, 56, 481, 161, 478, 0,
	3, 57, 62, 63, 161, 481, 53, 0,
	3, 63, 58, 57, 53, 181, 161, 0,
	3, 58, 63, 64, 181, 53, 257, 0,
	3, 64, 59, 58, 257, 348, 181, 0,
	3, 60, 65, 66, 431, 135, 37, 0,
	3, 66, 61, 60, 37, 320, 431, 0,
	3, 61, 66, 67, 320, 37, 408, 0,
	3, 67, 62, 61, 408, 481, 320, 0,
	3, 62, 67, 68, 481, 408, 347, 0,
	3, 68, 63, 62, 347, 53, 481, 0,
	3, 63, 68, 69, 53, 347, 104, 0,
	3, 69, 64, 63, 104, 257, 53, 0,
	3, 65, 70, 71, 135, 191, 524, 0,
	3, 71, 66, 65, 524, 37, 135, 0,
	3, 66, 71, 72, 37, 524, 319, 0,
	3, 72, 67, 66, 319, 408, 37, 0,
	3, 67, 72, 73, 408, 319, 183, 0,
	3, 73, 68, 67, 183, 347, 408, 0,
	3, 68, 73, 74, 347, 183, 480, 0,
	3, 74, 69, 68, 480, 104, 347, 0,
	3, 70, 75, 76, 191, 483, 328, 0,
	3, 76, 71, 70, 328, 524, 191, 0,
	3, 71, 76, 77, 524, 328, 422, 0,
	3, 77, 72, 71, 422, 319, 524, 0,
	3, 72, 77, 78, 319, 422, 151, 0,
	3, 78, 73, 72, 151, 183, 319, 0,
	3, 73, 78, 79, 183, 151, 273, 0,
	3, 79, 74, 73, 273, 480, 183, 0,
	3, 75, 0, 1, 483, 255, 465, 0,
	3, 1, 76, 75, 465, 328, 483, 0,
	3, 76, 1, 2, 328, 465, 4, 0,
	3, 2, 77, 76, 4, 422, 328, 0,
	3, 77, 2, 3, 422, 4, 448, 0,
	3, 3, 78, 77, 448, 151, 422, 0,
	3, 78, 3, 4, 151, 448, 116, 0,
	3, 4, 79, 78, 116, 273, 151, 0,
	3, 4, 9, 84, 116, 49, 220, 0,
	3, 84, 80, 4, 220, 131, 116, 0,
	3, 80, 84, 85, 131, 220, 476, 0,
	3, 85, 81, 80, 476, 26, 131, 0,
	3, 81, 85, 86, 26, 476, 38, 0,
	3, 86, 82, 81, 38, 336, 26, 0,
	3, 82, 86, 87, 336, 38, 511, 0,
	3, 87, 83, 82, 511, 1, 336, 0,
	3, 9, 14, 88, 49, 180, 103, 0,
	3, 88, 84, 9, 103, 220, 49, 0,
	3, 84, 88, 89, 220, 103, 62, 0,
	3, 89, 85, 84, 62, 476, 220, 0,
	3, 85, 89, 90, 476, 62, 488, 0,
	3, 90, 86, 85, 488, 38, 476, 0,
	3, 86, 90, 91, 38, 488, 484, 0,
	3, 91, 87, 86, 484, 511, 38, 0,
	3, 14, 19, 92, 180, 74, 78, 0,
	3, 92, 88, 14, 78, 103, 180, 0,
	3, 88, 92, 93, 103, 78, 154, 0,
	3, 93, 89, 88, 154, 62, 103, 0,
	3, 89, 93, 94, 62, 154, 190, 0,
	3, 94, 90, 89, 190, 488, 62, 0,
	3, 90, 94, 95, 488, 190, 417, 0,
	3, 95, 91, 90, 417, 484, 488, 0,
	3, 19, 24, 96, 74, 234, 81, 0,
	3, 96, 92, 19, 81, 78, 74, 0,
	3, 92, 96, 97, 78, 81, 274, 0,
	3, 97, 93, 92, 274, 154, 78, 0,
	3, 93, 97, 98, 154, 274, 363, 0,
	3, 98, 94, 93, 363, 190, 154, 0,
	3, 94, 98, 99, 190, 363, 304, 0,
	3, 99, 95, 94, 304, 417, 190, 0,
	3, 24, 29, 100, 234, 485, 287, 0,
	3, 100, 96, 24, 287, 81, 234, 0,
	3, 96, 100, 101, 81, 287, 398, 0,
	3, 101, 97, 96, 398, 274, 81, 0,
	3, 97, 101, 102, 274, 398, 440, 0,
	3, 102, 98, 97, 440, 363, 274, 0,
	3, 98, 102, 103, 363, 440, 466, 0,
	3, 103, 99, 98, 466, 304, 363, 0,
	3, 29, 34, 104, 485, 138, 268, 0,
	3, 104, 100, 29, 268, 287, 485, 0,
	3, 100, 104, 105, 287, 268, 252, 0,
	3, 105, 101, 100, 252, 398, 287, 0,
	3, 101, 105, 106, 398, 252, 141, 0,
	3, 106, 102, 101, 141, 440, 398, 0,
	3, 102, 106, 107, 440, 141, 18, 0,
	3, 107, 103, 102, 18, 466, 440, 0,
	3, 34, 39, 108, 138, 28, 357, 0,
	3, 108, 104, 34, 357, 268, 138, 0,
	3, 104, 108, 109, 268, 357, 127, 0,
	3, 109, 105, 104, 127, 252, 268, 0,
	3, 105, 109, 110, 252, 127, 228, 0,
	3, 110, 106, 105, 228, 141, 252, 0,
	3, 106, 110, 111, 141, 228, 33, 0,
	3, 111, 107, 106, 33, 18, 141, 0,
	3, 39, 44, 112, 28, 322, 396, 0,
	3, 112, 108, 39, 396, 357, 28, 0,
	3, 108, 112, 113, 357, 396, 294, 0,
	3, 113, 109, 108, 294, 127, 357, 0,
	3, 109, 113, 114, 127, 294, 56, 0,
	3, 114, 110, 109, 56, 228, 127, 0,
	3, 110, 114, 115, 228, 56, 517, 0,
	3, 115, 111, 110, 517, 33, 228, 0,
	3, 44, 49, 116, 322, 313, 474, 0,
	3, 116, 112, 44, 474, 396, 322, 0,
	3, 112, 116, 117, 396, 474, 208, 0,
	3, 117, 113, 112, 208, 294, 396, 0,
	3, 113, 117, 118, 294, 208, 301, 0,
	3, 118, 114, 113, 301, 56, 294, 0,
	3, 114, 118, 119, 56, 301, 242, 0,
	3, 119, 115, 114, 242, 517, 56, 0,
	3, 49, 54, 120, 313, 447, 377, 0,
	3, 120, 116, 49, 377, 474, 313, 0,
	3, 116, 120, 121, 474, 377, 333, 0,
	3, 121, 117, 116, 333, 208, 474, 0,
	3, 117, 121, 122, 208, 333, 222, 0,
	3, 122, 118, 117, 222, 301, 208, 0,
	3, 118, 122, 123, 301, 222, 218, 0,
	3, 123, 119, 118, 218, 242, 301, 0,
	3, 54, 59, 124, 447, 348, 350, 0,
	3, 124, 120, 54, 350, 377, 447, 0,
	3, 120, 124, 125, 377, 350, 420, 0,
	3, 125, 121, 120, 420, 333, 377, 0,
	3, 121, 125, 126, 333, 420, 453, 0,
	3, 126, 122, 121, 453, 222, 333, 0,
	3, 122, 126, 127, 222, 453, 147, 0,
	3, 127, 123, 122, 147, 218, 222, 0,
	3, 59, 64, 128, 348, 257, 95, 0,
	3, 128, 124, 59, 95, 350, 348, 0,
	3, 124, 128, 129, 350, 95, 293, 0,
	3, 129, 125, 124, 293, 420, 350, 0,
	3, 125, 129, 130, 420, 293, 378, 0,
	3, 130, 126, 125, 378, 453, 420, 0,
	3, 126, 130, 131, 453, 378, 29, 0,
	3, 131, 127, 126, 29, 147, 453, 0,
	3, 64, 69, 132, 257, 104, 311, 0,
	3, 132, 128, 64, 311, 95, 257, 0,
	3, 128, 132, 133, 95, 311, 419, 0,
	3, 133, 129, 128, 419, 293, 95, 0,
	3, 129, 133, 134, 293, 419, 463, 0,
	3, 134, 130, 129, 463, 378, 293, 0,
	3, 130, 134, 135, 378, 463, 490, 0,
	3, 135, 131, 130, 490, 29, 378, 0,
	3, 69, 74, 136, 104, 480, 284, 0,
	3, 136, 132, 69, 284, 311, 104, 0,
	3, 132, 136, 137, 311, 284, 269, 0,
	3, 137, 133, 132, 269, 419, 311, 0,
	3, 133, 137, 138, 419, 269, 164, 0,
	3, 138, 134, 133, 164, 463, 419, 0,
	3, 134, 138, 139, 463, 164, 45, 0,
	3, 139, 135, 134, 45, 490, 463, 0,
	3, 74, 79, 140, 480, 273, 371, 0,
	3, 140, 136, 74, 371, 284, 480, 0,
	3, 136, 140, 141, 284, 371, 148, 0,
	3, 141, 137, 136, 148, 269, 284, 0,
	3, 137, 141, 142, 269, 148, 251, 0,
	3, 142, 138, 137, 251, 164, 269, 0,
	3, 138, 142, 143, 164, 251, 54, 0,
	3, 143, 139, 138, 54, 45, 164, 0,
	3, 79, 4, 80, 273, 116, 131, 0,
	3, 80, 140, 79, 131, 371, 273, 0,
	3, 140, 80, 81, 371, 131, 26, 0,
	3, 81, 141, 140, 26, 148, 371, 0,
	3, 141, 81, 82, 148, 26, 336, 0,
	3, 82, 142, 141, 336, 251, 148, 0,
	3, 142, 82, 83, 251, 336, 1, 0,
	3, 83, 143, 142, 1, 54, 251, 0,
	3, 83, 87, 148, 1, 511, 404, 0,
	3, 148, 144, 83, 404, 276, 1, 0,
	3, 144, 148, 149, 276, 404, 308, 0,
	3, 149, 145, 144, 308, 520, 276, 0,
	3, 145, 149, 150, 520, 308, 325, 0,
	3, 150, 146, 145, 325, 395, 520, 0,
	3, 146, 150, 151, 395, 325, 384, 0,
	3, 151, 147, 146, 384, 246, 395, 0,
	3, 87, 91, 152, 511, 484, 47, 0,
	3, 152, 148, 87, 47, 404, 511, 0,
	3, 148, 152, 153, 404, 47, 272, 0,
	3, 153, 149, 148, 272, 308, 404, 0,
	3, 149, 153, 154, 308, 272, 415, 0,
	3, 154, 150, 149, 415, 325, 308, 0,
	3, 150, 154, 155, 325, 415, 83, 0,
	3, 155, 151, 150, 83, 384, 325, 0,
	3, 91, 95, 156, 484, 417, 430, 0,
	3, 156, 152, 91, 430, 47, 484, 0,
	3, 152, 156, 157, 47, 430, 137, 0,
	3, 157, 153, 152, 137, 272, 47, 0,
	3, 153, 157, 158, 272, 137, 416, 0,
	3, 158, 154, 153, 416, 415, 272, 0,
	3, 154, 158, 159, 415, 416, 297, 0,
	3, 159, 155, 154, 297, 83, 415, 0,
	3, 95, 99, 160, 417, 304, 458, 0,
	3, 160, 156, 95, 458, 430, 417, 0,
	3, 156, 160, 161, 430, 458, 343, 0,
	3, 161, 157, 156, 343, 137, 430, 0,
	3, 157, 161, 162, 137, 343, 334, 0,
	3, 162, 158, 157, 334, 416, 137, 0,
	3, 158, 162, 163, 416, 334, 317, 0,
	3, 163, 159, 158, 317, 297, 416, 0,
	3, 99, 103, 164, 304, 466, 187, 0,
	3, 164, 160, 99, 187, 458, 304, 0,
	3, 160, 164, 165, 458, 187, 117, 0,
	3, 165, 161, 160, 117, 343, 458, 0,
	3, 161, 165, 166, 343, 117, 438, 0,
	3, 166, 162, 161, 438, 334, 343, 0,
	3, 162, 166, 167, 334, 438, 459, 0,
	3, 167, 163, 162, 459, 317, 334, 0,
	3, 103, 107, 168, 466, 18, 353, 0,
	3, 168, 164, 103, 353, 187, 466, 0,
	3, 164, 168, 169, 187, 353, 123, 0,
	3, 169, 165, 164, 123, 117, 187, 0,
	3, 165, 169, 170, 117, 123, 168, 0,
	3, 170, 166, 165, 168, 438, 117, 0,
	3, 166, 170, 171, 438, 168, 426, 0,
	3, 171, 167, 166, 426, 459, 438, 0,
	3, 107, 111, 172, 18, 33, 390, 0,
	3, 172, 168, 107, 390, 353, 18, 0,
	3, 168, 172, 173, 353, 390, 290, 0,
	3, 173, 169, 168, 290, 123, 353, 0,
	3, 169, 173, 174, 123, 290, 522, 0,
	3, 174, 170, 169, 522, 168, 123, 0,
	3, 170, 174, 175, 168, 522, 87, 0,
	3, 175, 171, 170, 87, 426, 168, 0,
	3, 111, 115, 176, 33, 517, 260, 0,
	3, 176, 172, 111, 260, 390, 33, 0,
	3, 172, 176, 177, 390, 260, 497, 0,
	3, 177, 173, 172, 497, 290, 390, 0,
	3, 173, 177, 178, 290, 497, 126, 0,
	3, 178, 174, 173, 126, 522, 290, 0,
	3, 174, 178, 179, 522, 126, 501, 0,
	3, 179, 175, 174, 501, 87, 522, 0,
	3, 115, 119, 180, 517, 242, 130, 0,
	3, 180, 176, 115, 130, 260, 517, 0,
	3, 176, 180, 181, 260, 130, 34, 0,
	3, 181, 177, 176, 34, 497, 260, 0,
	3, 177, 181, 182, 497, 34, 46, 0,
	3, 182, 178, 177, 46, 126, 497, 0,
	3, 178, 182, 183, 126, 46, 105, 0,
	3, 183, 179, 178, 105, 501, 126, 0,
	3, 119, 123, 184, 242, 218, 310, 0,
	3, 184, 180, 119, 310, 130, 242, 0,
	3, 180, 184, 185, 130, 310, 528, 0,
	3, 185, 181, 180, 528, 34, 130, 0,
	3, 181, 185, 186, 34, 528, 145, 0,
	3, 186, 182, 181, 145, 46, 34, 0,
	3, 182, 186, 187, 46, 145, 356, 0,
	3, 187, 183, 182, 356, 105, 46, 0,
	3, 123, 127, 188, 218, 147, 156, 0,
	3, 188, 184, 123, 156, 310, 218, 0,
	3, 184, 188, 189, 310, 156, 402, 0,
	3, 189, 185, 184, 402, 528, 310, 0,
	3, 185, 189, 190, 528, 402, 146, 0,
	3, 190, 186, 185, 146, 145, 528, 0,
	3, 186, 190, 191, 145, 146, 17, 0,
	3, 191, 187, 186, 17, 356, 145, 0,
	3, 127, 131, 192, 147, 29, 184, 0,
	3, 192, 188, 127, 184, 156, 147, 0,
	3, 188, 192, 193, 156, 184, 63, 0,
	3, 193, 189, 188, 63, 402, 156, 0,
	3, 189, 193, 194, 402, 63, 354, 0,
	3, 194, 190, 189, 354, 146, 402, 0,
	3, 190, 194, 195, 146, 354, 335, 0,
	3, 195, 191, 190, 335, 17, 146, 0,
	3, 131, 135, 196, 29, 490, 210, 0,
	3, 196, 192, 131, 210, 184, 29, 0,
	3, 192, 196, 197, 184, 210, 129, 0,
	3, 197, 193, 192, 129, 63, 184, 0,
	3, 193, 197, 198, 63, 129, 461, 0,
	3, 198, 194, 193, 461, 354, 63, 0,
	3, 194, 198, 199, 354, 461, 475, 0,
	3, 199, 195, 194, 475, 335, 354, 0,
	3, 135, 139, 200, 490, 45, 370, 0,
	3, 200, 196, 135, 370, 210, 490, 0,
	3, 196, 200, 201, 210, 370, 143, 0,
	3, 201, 197, 196, 143, 129, 210, 0,
	3, 197, 201, 202, 129, 143, 195, 0,
	3, 202, 198, 197, 195, 461, 129, 0,
	3, 198, 202, 203, 461, 195, 444, 0,
	3, 203, 199, 198, 444, 475, 461, 0,
	3, 139, 143, 204, 45, 54, 403, 0,
	3, 204, 200, 139, 403, 370, 45, 0,
	3, 200, 204, 205, 370, 403, 315, 0,
	3, 205, 201, 200, 315, 143, 370, 0,
	3, 201, 205, 206, 143, 315, 7, 0,
	3, 206, 202, 201, 7, 195, 143, 0,
	3, 202, 206, 207, 195, 7, 101, 0,
	3, 207, 203, 202, 101, 444, 195, 0,
	3, 143, 83, 144, 54, 1, 276, 0,
	3, 144, 204, 143, 276, 403, 54, 0,
	3, 204, 144, 145, 403, 276, 520, 0,
	3, 145, 205, 204, 520, 315, 403, 0,
	3, 205, 145, 146, 315, 520, 395, 0,
	3, 146, 206, 205, 395, 7, 315, 0,
	3, 206, 146, 147, 7, 395, 246, 0,
	3, 147, 207, 206, 246, 101, 7, 0,
	3, 147, 151, 212, 246, 384, 486, 0,
	3, 212, 208, 147, 486, 279, 246, 0,
	3, 208, 212, 213, 279, 486, 231, 0,
	3, 213, 209, 208, 231, 349, 279, 0,
	3, 209, 213, 214, 349, 231, 0, 0,
	3, 214, 210, 209, 0, 216, 349, 0,
	3, 210, 214, 211, 216, 0, 393, 0,
	3, 211, 211, 210, 393, 393, 216, 0,
	3, 151, 155, 215, 384, 83, 215, 0,
	3, 215, 212, 151, 215, 486, 384, 0,
	3, 212, 215, 216, 486, 215, 327, 0,
	3, 216, 213, 212, 327, 231, 486, 0,
	3, 213, 216, 217, 231, 327, 512, 0,
	3, 217, 214, 213, 512, 0, 231, 0,
	3, 214, 217, 211, 0, 512, 393, 0,
	3, 211, 211, 214, 393, 393, 0, 0,
	3, 155, 159, 218, 83, 297, 149, 0,
	3, 218, 215, 155, 149, 215, 83, 0,
	3, 215, 218, 219, 215, 149, 91, 0,
	3, 219, 216, 215, 91, 327, 215, 0,
	3, 216, 219, 220, 327, 91, 177, 0,
	3, 220, 217, 216, 177, 512, 327, 0,
	3, 217, 220, 211, 512, 177, 393, 0,
	3, 211, 211, 217, 393, 393, 512, 0,
	3, 159, 163, 221, 297, 317, 504, 0,
	3, 221, 218, 159, 504, 149, 297, 0,
	3, 218, 221, 222, 149, 504, 285, 0,
	3, 222, 219, 218, 285, 91, 149, 0,
	3, 219, 222, 223, 91, 285, 254, 0,
	3, 223, 220, 219, 254, 177, 91, 0,
	3, 220, 223, 211, 177, 254, 393, 0,
	3, 211, 211, 220, 393, 393, 177, 0,
	3, 163, 167, 224, 317, 459, 125, 0,
	3, 224, 221, 163, 125, 504, 317, 0,
	3, 221, 224, 225, 504, 125, 162, 0,
	3, 225, 222, 221, 162, 285, 504, 0,
	3, 222, 225, 226, 285, 162, 278, 0,
	3, 226, 223, 222, 278, 254, 285, 0,
	3, 223, 226, 211, 254, 278, 393, 0,
	3, 211, 211, 223, 393, 393, 254, 0,
	3, 167, 171, 227, 459, 426, 439, 0,
	3, 227, 224, 167, 439, 125, 459, 0,
	3, 224, 227, 228, 125, 439, 60, 0,
	3, 228, 225, 224, 60, 162, 125, 0,
	3, 225, 228, 229, 162, 60, 446, 0,
	3, 229, 226, 225, 446, 278, 162, 0,
	3, 226, 229, 211, 278, 446, 393, 0,
	3, 211, 211, 226, 393, 393, 278, 0,
	3, 171, 175, 230, 426, 87, 482, 0,
	3, 230, 227, 171, 482, 439, 426, 0,
	3, 227, 230, 231, 439, 482, 92, 0,
	3, 231, 228, 227, 92, 60, 439, 0,
	3, 228, 231, 232, 60, 92, 110, 0,
	3, 232, 229, 228, 110, 446, 60, 0,
	3, 229, 232, 211, 446, 110, 393, 0,
	3, 211, 211, 229, 393, 393, 446, 0,
	3, 175, 179, 233, 87, 501, 261, 0,
	3, 233, 230, 175, 261, 482, 87, 0,
	3, 230, 233, 234, 482, 261, 329, 0,
	3, 234, 231, 230, 329, 92, 482, 0,
	3, 231, 234, 235, 92, 329, 192, 0,
	3, 235, 232, 231, 192, 110, 92, 0,
	3, 232, 235, 211, 110, 192, 393, 0,
	3, 211, 211, 232, 393, 393, 110, 0,
	3, 179, 183, 236, 501, 105, 219, 0,
	3, 236, 233, 179, 219, 261, 501, 0,
	3, 233, 236, 237, 261, 219, 491, 0,
	3, 237, 234, 233, 491, 329, 261, 0,
	3, 234, 237, 238, 329, 491, 267, 0,
	3, 238, 235, 234, 267, 192, 329, 0,
	3, 235, 238, 211, 192, 267, 393, 0,
	3, 211, 211, 235, 393, 393, 192, 0,
	3, 183, 187, 239, 105, 356, 472, 0,
	3, 239, 236, 183, 472, 219, 105, 0,
	3, 236, 239, 240, 219, 472, 48, 0,
	3, 240, 237, 236, 48, 491, 219, 0,
	3, 237, 240, 241, 491, 48, 247, 0,
	3, 241, 238, 237, 247, 267, 491, 0,
	3, 238, 241, 211, 267, 247, 393, 0,
	3, 211, 211, 238, 393, 393, 267, 0,
	3, 187, 191, 242, 356, 17, 411, 0,
	3, 242, 239, 187, 411, 472, 356, 0,
	3, 239, 242, 243, 472, 411, 364, 0,
	3, 243, 240, 239, 364, 48, 472, 0,
	3, 240, 243, 244, 48, 364, 441, 0,
	3, 244, 241, 240, 441, 247, 48, 0,
	3, 241, 244, 211, 247, 441, 393, 0,
	3, 211, 211, 241, 393, 393, 247, 0,
	3, 191, 195, 245, 17, 335, 239, 0,
	3, 245, 242, 191, 239, 411, 17, 0,
	3, 242, 245, 246, 411, 239, 13, 0,
	3, 246, 243, 242, 13, 364, 411, 0,
	3, 243, 246, 247, 364, 13, 509, 0,
	3, 247, 244, 243, 509, 441, 364, 0,
	3, 244, 247, 211, 441, 509, 393, 0,
	3, 211, 211, 244, 393, 393, 441, 0,
	3, 195, 199, 248, 335, 475, 144, 0,
	3, 248, 245, 195, 144, 239, 335, 0,
	3, 245, 248, 249, 239, 144, 179, 0,
	3, 249, 246, 245, 179, 13, 239, 0,
	3, 246, 249, 250, 13, 179, 298, 0,
	3, 250, 247, 246, 298, 509, 13, 0,
	3, 247, 250, 211, 509, 298, 393, 0,
	3, 211, 211, 247, 393, 393, 509, 0,
	3, 199, 203, 251, 475, 444, 462, 0,
	3, 251, 248, 199, 462, 144, 475, 0,
	3, 248, 251, 252, 144, 462, 76, 0,
	3, 252, 249, 248, 76, 179, 144, 0,
	3, 249, 252, 253, 179, 76, 464, 0,
	3, 253, 250, 249, 464, 298, 179, 0,
	3, 250, 253, 211, 298, 464, 393, 0,
	3, 211, 211, 250, 393, 393, 298, 0,
	3, 203, 207, 254, 444, 101, 500, 0,
	3, 254, 251, 203, 500, 462, 444, 0,
	3, 251, 254, 255, 462, 500, 113, 0,
	3, 255, 252, 251, 113, 76, 462, 0,
	3, 252, 255, 256, 76, 113, 128, 0,
	3, 256, 253, 252, 128, 464, 76, 0,
	3, 253, 256, 211, 464, 128, 393, 0,
	3, 211, 211, 253, 393, 393, 464, 0,
	3, 207, 147, 208, 101, 246, 279, 0,
	3, 208, 254, 207, 279, 500, 101, 0,
	3, 254, 208, 209, 500, 279, 349, 0,
	3, 209, 255, 254, 349, 113, 500, 0,
	3, 255, 209, 210, 113, 349, 216, 0,
	3, 210, 256, 255, 216, 128, 113, 0,
	3, 256, 210, 211, 128, 216, 393, 0,
	3, 211, 211, 256, 393, 393, 128, 0,
	3, 257, 262, 263, 425, 244, 58, 0,
	3, 263, 258, 257, 58, 337, 425, 0,
	3, 258, 263, 264, 337, 58, 214, 0,
	3, 264, 259, 258, 214, 236, 337, 0,
	3, 259, 264, 265, 236, 214, 266, 0,
	3, 265, 260, 259, 266, 32, 236, 0,
	3, 260, 265, 266, 32, 266, 331, 0,
	3, 266, 261, 260, 331, 109, 32, 0,
	3, 262, 267, 268, 244, 233, 369, 0,
	3, 268, 263, 262, 369, 58, 244, 0,
	3, 263, 268, 269, 58, 369, 71, 0,
	3, 269, 264, 263, 71, 214, 58, 0,
	3, 264, 269, 270, 214, 71, 392, 0,
	3, 270, 265, 264, 392, 266, 214, 0,
	3, 265, 270, 271, 266, 392, 312, 0,
	3, 271, 266, 265, 312, 331, 266, 0,
	3, 267, 272, 273, 233, 12, 434, 0,
	3, 273, 268, 267, 434, 369, 233, 0,
	3, 268, 273, 274, 369, 434, 188, 0,
	3, 274, 269, 268, 188, 71, 369, 0,
	3, 269, 274, 275, 71, 188, 201, 0,
	3, 275, 270, 269, 201, 392, 71, 0,
	3, 270, 275, 276, 392, 201, 238, 0,
	3, 276, 271, 270, 238, 312, 392, 0,
	3, 272, 277, 278, 12, 142, 114, 0,
	3, 278, 273, 272, 114, 434, 12, 0,
	3, 273, 278, 279, 434, 114, 173, 0,
	3, 279, 274, 273, 173, 188, 434, 0,
	3, 274, 279, 280, 188, 173, 14, 0,
	3, 280, 275, 274, 14, 201, 188, 0,
	3, 275, 280, 281, 201, 14, 15, 0,
	3, 281, 276, 275, 15, 238, 201, 0,
	3, 277, 282, 283, 142, 407, 288, 0,
	3, 283, 278, 277, 288, 114, 142, 0,
	3, 278, 283, 284, 114, 288, 400, 0,
	3, 284, 279, 278, 400, 173, 114, 0,
	3, 279, 284, 285, 173, 400, 457, 0,
	3, 285, 280, 279, 457, 14, 173, 0,
	3, 280, 285, 286, 14, 457, 332, 0,
	3, 286, 281, 280, 332, 15, 14, 0,
	3, 282, 287, 288, 407, 194, 42, 0,
	3, 288, 283, 282, 42, 288, 407, 0,
	3, 283, 288, 289, 288, 42, 380, 0,
	3, 289, 284, 283, 380, 400, 288, 0,
	3, 284, 289, 290, 400, 380, 383, 0,
	3, 290, 285, 284, 383, 457, 400, 0,
	3, 285, 290, 291, 457, 383, 197, 0,
	3, 291, 286, 285, 197, 332, 457, 0,
	3, 287, 292, 293, 194, 321, 152, 0,
	3, 293, 288, 287, 152, 42, 194, 0,
	3, 288, 293, 294, 42, 152, 397, 0,
	3, 294, 289, 288, 397, 380, 42, 0,
	3, 289, 294, 295, 380, 397, 342, 0,
	3, 295, 290, 289, 342, 383, 380, 0,
	3, 290, 295, 296, 383, 342, 225, 0,
	3, 296, 291, 290, 225, 197, 383, 0,
	3, 292, 257, 258, 321, 425, 337, 0,
	3, 258, 293, 292, 337, 152, 321, 0,
	3, 293, 258, 259, 152, 337, 236, 0,
	3, 259, 294, 293, 236, 397, 152, 0,
	3, 294, 259, 260, 397, 236, 32, 0,
	3, 260, 295, 294, 32, 342, 397, 0,
	3, 295, 260, 261, 342, 32, 109, 0,
	3, 261, 296, 295, 109, 225, 342, 0,
	3, 261, 266, 301, 109, 331, 175, 0,
	3, 301, 297, 261, 175, 502, 109, 0,
	3, 297, 301, 302, 502, 175, 265, 0,
	3, 302, 298, 297, 265, 84, 502, 0,
	3, 298, 302, 303, 84, 265, 186, 0,
	3, 303, 299, 298, 186, 496, 84, 0,
	3, 299, 303, 304, 496, 186, 470, 0,
	3, 304, 300, 299, 470, 494, 496, 0,
	3, 266, 271, 305, 331, 312, 170, 0,
	3, 305, 301, 266, 170, 175, 331, 0,
	3, 301, 305, 306, 175, 170, 97, 0,
	3, 306, 302, 301, 97, 265, 175, 0,
	3, 302, 306, 307, 265, 97, 205, 0,
	3, 307, 303, 302, 205, 186, 265, 0,
	3, 303, 307, 308, 186, 205, 449, 0,
	3, 308, 304, 303, 449, 470, 186, 0,
	3, 271, 276, 309, 312, 238, 379, 0,
	3, 309, 305, 271, 379, 170, 312, 0,
	3, 305, 309, 310, 170, 379, 300, 0,
	3, 310, 306, 305, 300, 97, 170, 0,
	3, 306, 310, 311, 97, 300, 118, 0,
	3, 311, 307, 306, 118, 205, 97, 0,
	3, 307, 311, 312, 205, 118, 237, 0,
	3, 312, 308, 307, 237, 449, 205, 0,
	3, 276, 281, 313, 238, 15, 199, 0,
	3, 313, 309, 276, 199, 379, 238, 0,
	3, 309, 313, 314, 379, 199, 94, 0,
	3, 314, 310, 309, 94, 300, 379, 0,
	3, 310, 314, 315, 300, 94, 421, 0,
	3, 315, 311, 310, 421, 118, 300, 0,
	3, 311, 315, 316, 118, 421, 31, 0,
	3, 316, 312, 311, 31, 237, 118, 0,
	3, 281, 286, 317, 15, 332, 367, 0,
	3, 317, 313, 281, 367, 199, 15, 0,
	3, 313, 317, 318, 199, 367, 529, 0,
	3, 318, 314, 313, 529, 94, 199, 0,
	3, 314, 318, 319, 94, 529, 185, 0,
	3, 319, 315, 314, 185, 421, 94, 0,
	3, 315, 319, 320, 421, 185, 89, 0,
	3, 320, 316, 315, 89, 31, 421, 0,
	3, 286, 291, 321, 332, 197, 172, 0,
	3, 321, 317, 286, 172, 367, 332, 0,
	3, 317, 321, 322, 367, 172, 209, 0,
	3, 322, 318, 317, 209, 529, 367, 0,
	3, 318, 322, 323, 529, 209, 429, 0,
	3, 323, 319, 318, 429, 185, 529, 0,
	3, 319, 323, 324, 185, 429, 112, 0,
	3, 324, 320, 319, 112, 89, 185, 0,
	3, 291, 296, 325, 197, 225, 451, 0,
	3, 325, 321, 291, 451, 172, 197, 0,
	3, 321, 325, 326, 172, 451, 66, 0,
	3, 326, 322, 321, 66, 209, 172, 0,
	3, 322, 326, 327, 209, 66, 176, 0,
	3, 327, 323, 322, 176, 429, 209, 0,
	3, 323, 327, 328, 429, 176, 155, 0,
	3, 328, 324, 323, 155, 112, 429, 0,
	3, 296, 261, 297, 225, 109, 502, 0,
	3, 297, 325, 296, 502, 451, 225, 0,
	3, 325, 297, 298, 451, 502, 84, 0,
	3, 298, 326, 325, 84, 66, 451, 0,
	3, 326, 298, 299, 66, 84, 496, 0,
	3, 299, 327, 326, 496, 176, 66, 0,
	3, 327, 299, 300, 176, 496, 494, 0,
	3, 300, 328, 327, 494, 155, 176, 0,
	3, 329, 334, 335, 3, 355, 122, 0,
	3, 335, 330, 329, 122, 518, 3, 0,
	3, 330, 335, 336, 518, 122, 111, 0,
	3, 336, 331, 330, 111, 213, 518, 0,
	3, 331, 336, 337, 213, 111, 473, 0,
	3, 337, 332, 331, 473, 468, 213, 0,
	3, 332, 337, 338, 468, 473, 521, 0,
	3, 338, 333, 332, 521, 346, 468, 0,
	3, 334, 339, 340, 355, 61, 414, 0,
	3, 340, 335, 334, 414, 122, 355, 0,
	3, 335, 340, 341, 122, 414, 413, 0,
	3, 341, 336, 335, 413, 111, 122, 0,
	3, 336, 341, 342, 111, 413, 204, 0,
	3, 342, 337, 336, 204, 473, 111, 0,
	3, 337, 342, 343, 473, 204, 217, 0,
	3, 343, 338, 337, 217, 521, 473, 0,
	3, 339, 344, 345, 61, 55, 100, 0,
	3, 345, 340, 339, 100, 414, 61, 0,
	3, 340, 345, 346, 414, 100, 399, 0,
	3, 346, 341, 340, 399, 413, 414, 0,
	3, 341, 346, 347, 413, 399, 326, 0,
	3, 347, 342, 341, 326, 204, 413, 0,
	3, 342, 347, 348, 204, 326, 221, 0,
	3, 348, 343, 342, 221, 217, 204, 0,
	3, 344, 349, 350, 55, 508, 477, 0,
	3, 350, 345, 344, 477, 100, 55, 0,
	3, 345, 350, 351, 100, 477, 292, 0,
	3, 351, 346, 345, 292, 399, 100, 0,
	3, 346, 351, 352, 399, 292, 73, 0,
	3, 352, 347, 346, 73, 326, 399, 0,
	3, 347, 352, 353, 326, 73, 362, 0,
	3, 353, 348, 347, 362, 221, 326, 0,
	3, 349, 354, 355, 508, 365, 262, 0,
	3, 355, 350, 349, 262, 477, 508, 0,
	3, 350, 355, 356, 477, 262, 93, 0,
	3, 356, 351, 350, 93, 292, 477, 0,
	3, 351, 356, 357, 292, 93, 318, 0,
	3, 357, 352, 351, 318, 73, 292, 0,
	3, 352, 357, 358, 73, 318, 163, 0,
	3, 358, 353, 352, 163, 362, 73, 0,
	3, 354, 359, 360, 365, 140, 340, 0,
	3, 360, 355, 354, 340, 262, 365, 0,
	3, 355, 360, 361, 262, 340, 505, 0,
	3, 361, 356, 355, 505, 93, 262, 0,
	3, 356, 361, 362, 93, 505, 499, 0,
	3, 362, 357, 356, 499, 318, 93, 0,
	3, 357, 362, 363, 318, 499, 159, 0,
	3, 363, 358, 357, 159, 163, 318, 0,
	3, 359, 364, 365, 140, 510, 68, 0,
	3, 365, 360, 359, 68, 340, 140, 0,
	3, 360, 365, 366, 340, 68, 167, 0,
	3, 366, 361, 360, 167, 505, 340, 0,
	3, 361, 366, 367, 505, 167, 245, 0,
	3, 367, 362, 361, 245, 499, 505, 0,
	3, 362, 367, 368, 499, 245, 437, 0,
	3, 368, 363, 362, 437, 159, 499, 0,
	3, 364, 329, 330, 510, 3, 518, 0,
	3, 330, 365, 364, 518, 68, 510, 0,
	3, 365, 330, 331, 68, 518, 213, 0,
	3, 331, 366, 365, 213, 167, 68, 0,
	3, 366, 331, 332, 167, 213, 468, 0,
	3, 332, 367, 366, 468, 245, 167, 0,
	3, 367, 332, 333, 245, 468, 346, 0,
	3, 333, 368, 367, 346, 437, 245, 0,
	3, 333, 338, 373, 346, 521, 79, 0,
	3, 373, 369, 333, 79, 286, 346, 0,
	3, 369, 373, 374, 286, 79, 77, 0,
	3, 374, 370, 369, 77, 22, 286, 0,
	3, 370, 374, 375, 22, 77, 523, 0,
	3, 375, 371, 370, 523, 330, 22, 0,
	3, 371, 375, 376, 330, 523, 259, 0,
	3, 376, 372, 371, 259, 338, 330, 0,
	3, 338, 343, 377, 521, 217, 207, 0,
	3, 377, 373, 338, 207, 79, 521, 0,
	3, 373, 377, 378, 79, 207, 471, 0,
	3, 378, 374, 373, 471, 77, 79, 0,
	3, 374, 378, 379, 77, 471, 198, 0,
	3, 379, 375, 374, 198, 523, 77, 0,
	3, 375, 379, 380, 523, 198, 366, 0,
	3, 380, 376, 375, 366, 259, 523, 0,
	3, 343, 348, 381, 217, 221, 516, 0,
	3, 381, 377, 343, 516, 207, 217, 0,
	3, 377, 381, 382, 207, 516, 250, 0,
	3, 382, 378, 377, 250, 471, 207, 0,
	3, 378, 382, 383, 471, 250, 240, 0,
	3, 383, 379, 378, 240, 198, 471, 0,
	3, 379, 383, 384, 198, 240, 381, 0,
	3, 384, 380, 379, 381, 366, 198, 0,
	3, 348, 353, 385, 221, 362, 230, 0,
	3, 385, 381, 348, 230, 516, 221, 0,
	3, 381, 385, 386, 516, 230, 303, 0,
	3, 386, 382, 381, 303, 250, 516, 0,
	3, 382, 386, 387, 250, 303, 10, 0,
	3, 387, 383, 382, 10, 240, 250, 0,
	3, 383, 387, 388, 240, 10, 283, 0,
	3, 388, 384, 383, 283, 381, 240, 0,
	3, 353, 358, 389, 362, 163, 282, 0,
	3, 389, 385, 353, 282, 230, 362, 0,
	3, 385, 389, 390, 230, 282, 35, 0,
	3, 390, 386, 385, 35, 303, 230, 0,
	3, 386, 390, 391, 303, 35, 243, 0,
	3, 391, 387, 386, 243, 10, 303, 0,
	3, 387, 391, 392, 10, 243, 368, 0,
	3, 392, 388, 387, 368, 283, 10, 0,
	3, 358, 363, 393, 163, 159, 296, 0,
	3, 393, 389, 358, 296, 282, 163, 0,
	3, 389, 393, 394, 282, 296, 160, 0,
	3, 394, 390, 389, 160, 35, 282, 0,
	3, 390, 394, 395, 35, 160, 323, 0,
	3, 395, 391, 390, 323, 243, 35, 0,
	3, 391, 395, 396, 243, 323, 280, 0,
	3, 396, 392, 391, 280, 368, 243, 0,
	3, 363, 368, 397, 159, 437, 275, 0,
	3, 397, 393, 363, 275, 296, 159, 0,
	3, 393, 397, 398, 296, 275, 133, 0,
	3, 398, 394, 393, 133, 160, 296, 0,
	3, 394, 398, 399, 160, 133, 344, 0,
	3, 399, 395, 394, 344, 323, 160, 0,
	3, 395, 399, 400, 323, 344, 108, 0,
	3, 400, 396, 395, 108, 280, 323, 0,
	3, 368, 333, 369, 437, 346, 286, 0,
	3, 369, 397, 368, 286, 275, 437, 0,
	3, 397, 369, 370, 275, 286, 22, 0,
	3, 370, 398, 397, 22, 133, 275, 0,
	3, 398, 370, 371, 133, 22, 330, 0,
	3, 371, 399, 398, 330, 344, 133, 0,
	3, 399, 371, 372, 344, 330, 338, 0,
	3, 372, 400, 399, 338, 108, 344, 0,
	3, 401, 401, 406, 235, 235, 189, 0,
	3, 406, 402, 401, 189, 40, 235, 0,
	3, 402, 406, 407, 40, 189, 306, 0,
	3, 407, 403, 402, 306, 119, 40, 0,
	3, 403, 407, 408, 119, 306, 202, 0,
	3, 408, 404, 403, 202, 443, 119, 0,
	3, 404, 408, 409, 443, 202, 241, 0,
	3, 409, 405, 404, 241, 75, 443, 0,
	3, 401, 401, 410, 235, 235, 263, 0,
	3, 410, 406, 401, 263, 189, 235, 0,
	3, 406, 410, 411, 189, 263, 196, 0,
	3, 411, 407, 406, 196, 306, 189, 0,
	3, 407, 411, 412, 306, 196, 281, 0,
	3, 412, 408, 407, 281, 202, 306, 0,
	3, 408, 412, 413, 202, 281, 121, 0,
	3, 413, 409, 408, 121, 241, 202, 0,
	3, 401, 401, 414, 235, 235, 479, 0,
	3, 414, 410, 401, 479, 263, 235, 0,
	3, 410, 414, 415, 263, 479, 36, 0,
	3, 415, 411, 410, 36, 196, 263, 0,
	3, 411, 415, 416, 196, 36, 436, 0,
	3, 416, 412, 411, 436, 281, 196, 0,
	3, 412, 416, 417, 281, 436, 351, 0,
	3, 417, 413, 412, 351, 121, 281, 0,
	3, 401, 401, 418, 235, 235, 90, 0,
	3, 418, 414, 401, 90, 479, 235, 0,
	3, 414, 418, 419, 479, 90, 361, 0,
	3, 419, 415, 414, 361, 36, 479, 0,
	3, 415, 419, 420, 36, 361, 376, 0,
	3, 420, 416, 415, 376, 436, 36, 0,
	3, 416, 420, 421, 436, 376, 412, 0,
	3, 421, 417, 416, 412, 351, 436, 0,
	3, 401, 401, 422, 235, 235, 52, 0,
	3, 422, 418, 401, 52, 90, 235, 0,
	3, 418, 422, 423, 90, 52, 21, 0,
	3, 423, 419, 418, 21, 361, 90, 0,
	3, 419, 423, 424, 361, 21, 158, 0,
	3, 424, 420, 419, 158, 376, 361, 0,
	3, 420, 424, 425, 376, 158, 39, 0,
	3, 425, 421, 420, 39, 412, 376, 0,
	3, 401, 401, 426, 235, 235, 424, 0,
	3, 426, 422, 401, 424, 52, 235, 0,
	3, 422, 426, 427, 52, 424, 373, 0,
	3, 427, 423, 422, 373, 21, 52, 0,
	3, 423, 427, 428, 21, 373, 375, 0,
	3, 428, 424, 423, 375, 158, 21, 0,
	3, 424, 428, 429, 158, 375, 249, 0,
	3, 429, 425, 424, 249, 39, 158, 0,
	3, 401, 401, 430, 235, 235, 432, 0,
	3, 430, 426, 401, 432, 424, 235, 0,
	3, 426, 430, 431, 424, 432, 229, 0,
	3, 431, 427, 426, 229, 373, 424, 0,
	3, 427, 431, 432, 373, 229, 65, 0,
	3, 432, 428, 427, 65, 375, 373, 0,
	3, 428, 432, 433, 375, 65, 506, 0,
	3, 433, 429, 428, 506, 249, 375, 0,
	3, 401, 401, 434, 235, 235, 302, 0,
	3, 434, 430, 401, 302, 432, 235, 0,
	3, 430, 434, 435, 432, 302, 96, 0,
	3, 435, 431, 430, 96, 229, 432, 0,
	3, 431, 435, 436, 229, 96, 169, 0,
	3, 436, 432, 431, 169, 65, 229, 0,
	3, 432, 436, 437, 65, 169, 59, 0,
	3, 437, 433, 432, 59, 506, 65, 0,
	3, 401, 401, 438, 235, 235, 452, 0,
	3, 438, 434, 401, 452, 302, 235, 0,
	3, 434, 438, 439, 302, 452, 30, 0,
	3, 439, 435, 434, 30, 96, 302, 0,
	3, 435, 439, 440, 96, 30, 460, 0,
	3, 440, 436, 435, 460, 169, 96, 0,
	3, 436, 440, 441, 169, 460, 498, 0,
	3, 441, 437, 436, 498, 59, 169, 0,
	3, 401, 401, 442, 235, 235, 525, 0,
	3, 442, 438, 401, 525, 452, 235, 0,
	3, 438, 442, 443, 452, 525, 456, 0,
	3, 443, 439, 438, 456, 30, 452, 0,
	3, 439, 443, 444, 30, 456, 9, 0,
	3, 444, 440, 439, 9, 460, 30, 0,
	3, 440, 444, 445, 460, 9, 388, 0,
	3, 445, 441, 440, 388, 498, 460, 0,
	3, 401, 401, 446, 235, 235, 212, 0,
	3, 446, 442, 401, 212, 525, 235, 0,
	3, 442, 446, 447, 525, 212, 299, 0,
	3, 447, 443, 442, 299, 456, 525, 0,
	3, 443, 447, 448, 456, 299, 166, 0,
	3, 448, 444, 443, 166, 9, 456, 0,
	3, 444, 448, 449, 9, 166, 72, 0,
	3, 449, 445, 444, 72, 388, 9, 0,
	3, 401, 401, 450, 235, 235, 107, 0,
	3, 450, 446, 401, 107, 212, 235, 0,
	3, 446, 450, 451, 212, 107, 82, 0,
	3, 451, 447, 446, 82, 299, 212, 0,
	3, 447, 451, 452, 299, 82, 391, 0,
	3, 452, 448, 447, 391, 166, 299, 0,
	3, 448, 452, 453, 166, 391, 139, 0,
	3, 453, 449, 448, 139, 72, 166, 0,
	3, 401, 401, 454, 235, 235, 70, 0,
	3, 454, 450, 401, 70, 107, 235, 0,
	3, 450, 454, 455, 107, 70, 51, 0,
	3, 455, 451, 450, 51, 82, 107, 0,
	3, 451, 455, 456, 82, 51, 178, 0,
	3, 456, 452, 451, 178, 391, 82, 0,
	3, 452, 456, 457, 391, 178, 57, 0,
	3, 457, 453, 452, 57, 139, 391, 0,
	3, 401, 401, 458, 235, 235, 442, 0,
	3, 458, 454, 401, 442, 70, 235, 0,
	3, 454, 458, 459, 70, 442, 387, 0,
	3, 459, 455, 454, 387, 51, 70, 0,
	3, 455, 459, 460, 51, 387, 389, 0,
	3, 460, 456, 455, 389, 178, 51, 0,
	3, 456, 460, 461, 178, 389, 264, 0,
	3, 461, 457, 456, 264, 57, 178, 0,
	3, 401, 401, 462, 235, 235, 450, 0,
	3, 462, 458, 401, 450, 442, 235, 0,
	3, 458, 462, 463, 442, 450, 253, 0,
	3, 463, 459, 458, 253, 387, 442, 0,
	3, 459, 463, 464, 387, 253, 86, 0,
	3, 464, 460, 459, 86, 389, 387, 0,
	3, 460, 464, 465, 389, 86, 526, 0,
	3, 465, 461, 460, 526, 264, 389, 0,
	3, 401, 401, 402, 235, 235, 40, 0,
	3, 402, 462, 401, 40, 450, 235, 0,
	3, 462, 402, 403, 450, 40, 119, 0,
	3, 403, 463, 462, 119, 253, 450, 0,
	3, 463, 403, 404, 253, 119, 443, 0,
	3, 404, 464, 463, 443, 86, 253, 0,
	3, 464, 404, 405, 86, 443, 75, 0,
	3, 405, 465, 464, 75, 526, 86, 0,
	3, 405, 409, 470, 75, 241, 519, 0,
	3, 470, 466, 405, 519, 226, 75, 0,
	3, 466, 470, 471, 226, 519, 406, 0,
	3, 471, 467, 466, 406, 98, 226, 0,
	3, 467, 471, 472, 98, 406, 232, 0,
	3, 472, 468, 467, 232, 43, 98, 0,
	3, 468, 472, 473, 43, 232, 345, 0,
	3, 473, 469, 468, 345, 372, 43, 0,
	3, 409, 413, 474, 241, 121, 227, 0,
	3, 474, 470, 409, 227, 519, 241, 0,
	3, 470, 474, 475, 519, 227, 469, 0,
	3, 475, 471, 470, 469, 406, 519, 0,
	3, 471, 475, 476, 406, 469, 258, 0,
	3, 476, 472, 471, 258, 232, 406, 0,
	3, 472, 476, 477, 232, 258, 271, 0,
	3, 477, 473, 472, 271, 345, 232, 0,
	3, 413, 417, 478, 121, 351, 157, 0,
	3, 478, 474, 413, 157, 227, 121, 0,
	3, 474, 478, 479, 227, 157, 80, 0,
	3, 479, 475, 474, 80, 469, 227, 0,
	3, 475, 479, 480, 469, 80, 489, 0,
	3, 480, 476, 475, 489, 258, 469, 0,
	3, 476, 480, 481, 258, 489, 277, 0,
	3, 481, 477, 476, 277, 271, 258, 0,
	3, 417, 421, 482, 351, 412, 153, 0,
	3, 482, 478, 417, 153, 157, 351, 0,
	3, 478, 482, 483, 157, 153, 324, 0,
	3, 483, 479, 478, 324, 80, 157, 0,
	3, 479, 483, 484, 80, 324, 339, 0,
	3, 484, 480, 479, 339, 489, 80, 0,
	3, 480, 484, 485, 489, 339, 88, 0,
	3, 485, 481, 480, 88, 277, 489, 0,
	3, 421, 425, 486, 412, 39, 6, 0,
	3, 486, 482, 421, 6, 153, 412, 0,
	3, 482, 486, 487, 153, 6, 8, 0,
	3, 487, 483, 482, 8, 324, 153, 0,
	3, 483, 487, 488, 324, 8, 16, 0,
	3, 488, 484, 483, 16, 339, 324, 0,
	3, 484, 488, 489, 339, 16, 289, 0,
	3, 489, 485, 484, 289, 88, 339, 0,
	3, 425, 429, 490, 39, 249, 99, 0,
	3, 490, 486, 425, 99, 6, 39, 0,
	3, 486, 490, 491, 6, 99, 200, 0,
	3, 491, 487, 486, 200, 8, 6, 0,
	3, 487, 491, 492, 8, 200, 150, 0,
	3, 492, 488, 487, 150, 16, 8, 0,
	3, 488, 492, 493, 16, 150, 493, 0,
	3, 493, 489, 488, 493, 289, 16, 0,
	3, 429, 433, 494, 249, 506, 291, 0,
	3, 494, 490, 429, 291, 99, 249, 0,
	3, 490, 494, 495, 99, 291, 64, 0,
	3, 495, 491, 490, 64, 200, 99, 0,
	3, 491, 495, 496, 200, 64, 19, 0,
	3, 496, 492, 491, 19, 150, 200, 0,
	3, 492, 496, 497, 150, 19, 433, 0,
	3, 497, 493, 492, 433, 493, 150, 0,
	3, 433, 437, 498, 506, 59, 203, 0,
	3, 498, 494, 433, 203, 291, 506, 0,
	3, 494, 498, 499, 291, 203, 374, 0,
	3, 499, 495, 494, 374, 64, 291, 0,
	3, 495, 499, 500, 64, 374, 307, 0,
	3, 500, 496, 495, 307, 19, 64, 0,
	3, 496, 500, 501, 19, 307, 358, 0,
	3, 501, 497, 496, 358, 433, 19, 0,
	3, 437, 441, 502, 59, 498, 256, 0,
	3, 502, 498, 437, 256, 203, 59, 0,
	3, 498, 502, 503, 203, 256, 132, 0,
	3, 503, 499, 498, 132, 374, 203, 0,
	3, 499, 503, 504, 374, 132, 492, 0,
	3, 504, 500, 499, 492, 307, 374, 0,
	3, 500, 504, 505, 307, 492, 67, 0,
	3, 505, 501, 500, 67, 358, 307, 0,
	3, 441, 445, 506, 498, 388, 487, 0,
	3, 506, 502, 441, 487, 256, 498, 0,
	3, 502, 506, 507, 256, 487, 206, 0,
	3, 507, 503, 502, 206, 132, 256, 0,
	3, 503, 507, 508, 132, 206, 515, 0,
	3, 508, 504, 503, 515, 492, 132, 0,
	3, 504, 508, 509, 492, 515, 527, 0,
	3, 509, 505, 504, 527, 67, 492, 0,
	3, 445, 449, 510, 388, 72, 423, 0,
	3, 510, 506, 445, 423, 487, 388, 0,
	3, 506, 510, 511, 487, 423, 352, 0,
	3, 511, 507, 506, 352, 206, 487, 0,
	3, 507, 511, 512, 206, 352, 224, 0,
	3, 512, 508, 507, 224, 515, 206, 0,
	3, 508, 512, 513, 515, 224, 2, 0,
	3, 513, 509, 508, 2, 527, 515, 0,
	3, 449, 453, 514, 72, 139, 418, 0,
	3, 514, 510, 449, 418, 423, 72, 0,
	3, 510, 514, 515, 423, 418, 341, 0,
	3, 515, 511, 510, 341, 352, 423, 0,
	3, 511, 515, 516, 352, 341, 359, 0,
	3, 516, 512, 511, 359, 224, 352, 0,
	3, 512, 516, 517, 224, 359, 360, 0,
	3, 517, 513, 512, 360, 2, 224, 0,
	3, 453, 457, 518, 139, 57, 24, 0,
	3, 518, 514, 453, 24, 418, 139, 0,
	3, 514, 518, 519, 418, 24, 25, 0,
	3, 519, 515, 514, 25, 341, 418, 0,
	3, 515, 519, 520, 341, 25, 41, 0,
	3, 520, 516, 515, 41, 359, 341, 0,
	3, 516, 520, 521, 359, 41, 314, 0,
	3, 521, 517, 516, 314, 360, 359, 0,
	3, 457, 461, 522, 57, 264, 120, 0,
	3, 522, 518, 457, 120, 24, 57, 0,
	3, 518, 522, 523, 24, 120, 223, 0,
	3, 523, 519, 518, 223, 25, 24, 0,
	3, 519, 523, 524, 25, 223, 171, 0,
	3, 524, 520, 519, 171, 41, 25, 0,
	3, 520, 524, 525, 41, 171, 514, 0,
	3, 525, 521, 520, 514, 314, 41, 0,
	3, 461, 465, 526, 264, 526, 316, 0,
	3, 526, 522, 461, 316, 120, 264, 0,
	3, 522, 526, 527, 120, 316, 85, 0,
	3, 527, 523, 522, 85, 223, 120, 0,
	3, 523, 527, 528, 223, 85, 50, 0,
	3, 528, 524, 523, 50, 171, 223, 0,
	3, 524, 528, 529, 171, 50, 454, 0,
	3, 529, 525, 524, 454, 514, 171, 0,
	3, 465, 405, 466, 526, 75, 226, 0,
	3, 466, 526, 465, 226, 316, 526, 0,
	3, 526, 466, 467, 316, 226, 98, 0,
	3, 467, 527, 526, 98, 85, 316, 0,
	3, 527, 467, 468, 85, 98, 43, 0,
	3, 468, 528, 527, 43, 50, 85, 0,
	3, 528, 468, 469, 50, 43, 372, 0,
	3, 469, 529, 528, 372, 454, 50, 0
};


const int strip_vertices[] = {
	508, 508, 504, 509, 504, 505, 500, 501, 496, 497, 492, 493, 488, 489, 484, 485, 480, 481, 476, 477, 472, 473, -1,
	476, 475, 480, 479, 484, 483, 488, 487, 492, 491, 496, 495, 500, 499, 504, 499, 503, 498, 502, 437, 441, -1,
	527, 526, 467, 466, 471, 470, 475, 474, 479, 478, 483, 482, 487, 486, 491, 490, 495, 494, 499, 494, 498, -1,
	490, 490, 425, 486, 421, 482, 417, 478, 413, 474, 409, 470, 405, 466, 465, 526, 465, 461, 460, 456, 455, 451, -1,
	405, 465, 464, 460, 459, 455, 454, 450, -1,
	455, 451, 450, 446, 450, 401, 454, 458, 459, 463, 464, 404, 405, 404, 409, 408, 413, 412, 417, 416, 421, 420, -1,
	421, 420, 425, 420, 424, 419, 423, 418, 422, 418, 401, 414, 410, 415, 411, 416, 411, 412, 407, 408, 403, 404, 403, 463, -1,
	418, 418, 414, 419, 415, 420, 416, -1,
	407, 403, 402, 462, -1,
	403, 463, 462, 458, 462, 401, 402, 406, 407, 406, 411, 406, 410, 401, -1,
	494, 494, 498, 433, 437, 432, 436, 431, 435, 430, 434, 430, 401, 426, 422, 427, 423, 428, 424, 429, 425, 490, -1,
	430, 430, 426, 431, 427, 432, 428, 433, 429, 494, 490, -1,
	437, 437, 441, 436, 440, 435, 439, 434, 438, 401, 442, 446, 447, 451, 452, 456, 457, 461, 522, 526, 527, -1,
	452, 448, 447, -1,
	510, 445, 449, 444, 448, 443, 447, 443, 442, 443, 438, 443, 439, 444, 440, 445, 441, 506, 502, 507, 503, -1,
	510, 506, 445, -1,
	507, 506, 511, 510, 515, 510, 514, 449, 453, 448, 453, 452, 457, -1,
	527, 523, 522, 518, 457, 518, 453, 518, 514, 519, 515, -1,
	523, 519, 518, -1,
	504, 503, 508, 507, 512, 511, 516, 515, 520, 519, 524, 523, 528, 527, 468, 467, 472, 471, 476, 475, -1,
	472, 473, 468, 469, 528, 529, 524, 525, 520, 521, 516, 517, 512, 513, 508, 509, -1,
	211, 211, 214, 210, 209, -1,
	212, 215, 216, 219, 220, 223, 220, 211, 217, 214, 213, 209, 213, 208, 212, 147, -1,
	220, 217, 216, 213, 212, -1,
	251, 251, 248, 252, 249, 253, 250, 253, 211, 256, 210, 255, 209, 254, 208, 207, 147, 206, 147, 146, 147, 151, 212, 215, -1,
	206, 206, 202, 207, 203, 254, 251, 255, 252, 256, 253, -1,
	223, 223, 222, 219, 218, 215, 155, 151, 150, 146, 145, 146, 205, 206, 201, 202, 197, 202, 198, 203, 199, 251, 248, -1,
	145, 149, 150, 154, 155, 159, 218, 221, 222, 225, 226, 229, -1,
	204, 204, 145, 144, 149, 148, 149, 153, 154, 158, 159, 163, 221, 224, 225, 228, 229, 232, 229, 211, 226, 223, 222, -1,
	224, 224, 167, 163, 162, 158, 157, 153, 152, 148, 87, 148, 83, 144, 143, 204, 139, 200, 135, 196, 131, 192, -1,
	82, 83, 142, 143, 138, 139, 134, 135, 130, 131, 126, 127, 122, 123, 118, 123, 119, 184, 180, 185, 181, -1,
	81, 82, 141, 142, 137, 138, 133, 134, 129, 130, 125, 126, 121, 122, 117, 118, 113, 114, 109, 110, -1,
	80, 81, 140, 141, 136, 137, 132, 133, 128, 129, 124, 125, 120, 121, 116, 117, 112, 113, 108, 109, -1,
	4, 80, 79, 140, 74, 136, 69, 132, 64, 128, 59, 124, 54, 120, 49, 116, 44, 112, 39, 108, -1,
	79, 79, 73, 74, 68, 69, 63, 64, 58, 59, 53, 54, 48, 49, 48, 43, 42, 37, 36, 31, 30, 31, 25, -1,
	42, 42, 48, 47, 53, 52, 58, 57, 63, 62, 68, 67, 73, 72, 78, 77, 3, 2, 8, 7, 13, -1,
	36, 36, 42, 41, 47, 46, 52, 51, 57, 56, 62, 61, 67, 66, 72, 71, 77, 76, 2, 1, 7, -1,
	66, 66, 60, 61, 55, 56, 50, 51, 45, 46, 40, 41, 35, 36, 30, -1,
	31, 31, 25, 26, 20, 21, 15, 16, 10, 11, 5, 6, 0, 1, 75, 76, 70, 71, 65, 66, 60, -1,
	1, 1, 7, 6, 12, 11, 17, 16, 22, 21, 27, 26, 32, 31, 32, 37, 38, 43, 44, 49, -1,
	7, 7, 13, 12, 18, 17, 23, 22, 28, 27, 33, 32, 33, 38, -1,
	44, 44, 38, 39, 33, 34, 28, 29, 23, 24, 18, 19, 13, 14, 8, 9, 3, 4, 78, 79, 73, -1,
	39, 108, 34, 104, 29, 100, 24, 96, 19, 92, 14, 88, 9, 84, 4, 84, 80, 85, 81, 86, 81, 82, -1,
	108, 109, 104, 105, 100, 101, 96, 97, 92, 93, 88, 89, 84, 85, -1,
	109, 110, 105, 106, 101, 102, 97, 98, 93, 94, 89, 90, 85, 86, -1,
	118, 119, 114, 115, 110, 111, 106, 107, 102, 103, 98, 99, 94, 95, 90, 91, 86, 87, 82, 83, -1,
	111, 115, 176, -1,
	107, 111, 172, 176, 177, -1,
	103, 107, 168, 172, 173, 177, 178, -1,
	99, 103, 164, 168, 169, 173, 174, 178, 179, -1,
	95, 99, 160, 164, 165, 169, 170, 174, 175, 179, 233, -1,
	91, 95, 156, 160, 161, 165, 166, 170, 171, 175, 230, 233, 234, -1,
	87, 91, 152, 156, 157, 161, 162, 166, 167, 171, 227, 230, 231, 234, 235, 234, 238, 234, 237, 233, 236, 179, -1,
	185, 185, 181, 186, 182, 187, 183, 239, 236, 240, 237, 241, 238, 211, 235, 232, 231, 228, 227, 224, 167, -1,
	236, 179, 183, 178, 182, 177, 181, 176, 180, 115, 119, -1,
	131, 192, 127, 188, 123, 188, 184, 189, 185, 190, 186, 191, 187, 242, 239, 243, 240, 244, 241, 244, 211, 247, -1,
	192, 192, 188, 193, 189, 194, 190, 195, 191, 245, 242, 246, 243, 247, 244, -1,
	211, 247, 250, 246, 249, 245, 248, 195, 199, 194, 198, 193, 197, 192, 197, 196, 201, 200, 205, 204, 145, -1,
	393, 393, 394, 398, 399, 371, -1,
	399, 395, 394, -1,
	363, 363, 393, 397, 398, 370, 371, 375, -1,
	379, 375, 374, 370, 369, 397, 368, 363, 362, -1,
	396, 395, 400, 399, 372, 371, 376, 375, 380, 379, 384, 383, 388, 387, 392, 391, 396, 391, 395, 390, 394, -1,
	374, 378, 379, 378, 383, 382, 387, 386, 391, 386, 390, 385, 389, 353, 358, 352, 357, 351, 356, 350, 355, -1,
	341, 341, 347, 346, 352, 346, 351, 345, 350, -1,
	335, 334, 340, 339, 345, 344, 350, 349, 355, 354, -1,
	390, 390, 394, 389, 393, 358, 363, 357, 362, 356, 361, 355, 360, 354, 360, 359, 365, 364, 330, 329, 335, 334, -1,
	345, 346, 340, 341, 335, 336, 330, 331, 365, 366, 360, 366, 361, 367, 362, 367, 368, 333, 369, 373, 374, 378, -1,
	353, 353, 348, 385, 381, 386, 381, 382, 377, 378, 377, 373, 338, 333, 332, 367, 332, 366, 332, 331, 337, 336, 342, 341, 347, -1,
	332, 337, 338, 343, 377, 343, 381, 343, 348, 342, 348, 347, 353, 352, -1,
	337, 342, 343, -1,
	314, 314, 319, 318, 323, 322, 323, 327, -1,
	309, 309, 314, 313, 318, 317, 322, 321, 322, 326, 327, 299, -1,
	271, 271, 309, 276, 313, 281, 317, 286, 321, 291, 321, 325, 326, 298, 299, 303, -1,
	265, 265, 271, 270, 276, 275, 281, 280, 286, 285, 291, 290, 291, 296, 325, 297, 298, 302, 303, 307, -1,
	259, 259, 265, 264, 270, 269, 275, 274, 280, 279, 285, 284, 290, 289, 290, 295, 296, 261, 297, 301, 302, 306, 307, 311, -1,
	293, 293, 259, 258, 264, 263, 269, 268, 274, 273, 279, 278, 284, 283, 289, 288, 289, 294, 295, 260, 261, 266, -1,
	309, 305, 271, 266, 265, 260, 259, 294, 293, 288, 287, 288, 282, 283, 277, 278, 272, 273, 267, 268, 262, -1,
	268, 268, 262, 263, 257, 258, 292, 293, 287, -1,
	261, 266, 301, 305, 306, 310, 311, 315, 316, 320, -1,
	316, 316, 311, 312, 307, 308, 303, 304, 299, 300, 327, 328, 323, 324, 319, 320, 319, 315, 314, 310, 309, 305, -1
};


const int strip_normals[] = {
	515, 515, 492, 527, 492, 67, 307, 358, 19, 433, 150, 493, 16, 289, 339, 88, 489, 277, 258, 271, 232, 345, -1,
	258, 469, 489, 80, 339, 324, 16, 8, 150, 200, 19, 64, 307, 374, 492, 374, 132, 203, 256, 59, 498, -1,
	85, 316, 98, 226, 406, 519, 469, 227, 80, 157, 324, 153, 8, 6, 200, 99, 64, 291, 374, 291, 203, -1,
	99, 99, 39, 6, 412, 153, 351, 157, 121, 227, 241, 519, 75, 226, 526, 316, 526, 264, 389, 178, 51, 82, -1,
	75, 526, 86, 389, 387, 51, 70, 107, -1,
	51, 82, 107, 212, 107, 235, 70, 442, 387, 253, 86, 443, 75, 443, 241, 202, 121, 281, 351, 436, 412, 376, -1,
	412, 376, 39, 376, 158, 361, 21, 90, 52, 90, 235, 479, 263, 36, 196, 436, 196, 281, 306, 202, 119, 443, 119, 253, -1,
	90, 90, 479, 361, 36, 376, 436, -1,
	306, 119, 40, 450, -1,
	119, 253, 450, 442, 450, 235, 40, 189, 306, 189, 196, 189, 263, 235, -1,
	291, 291, 203, 506, 59, 65, 169, 229, 96, 432, 302, 432, 235, 424, 52, 373, 21, 375, 158, 249, 39, 99, -1,
	432, 432, 424, 229, 373, 65, 375, 506, 249, 291, 99, -1,
	59, 59, 498, 169, 460, 96, 30, 302, 452, 235, 525, 212, 299, 82, 391, 178, 57, 264, 120, 316, 85, -1,
	391, 166, 299, -1,
	423, 388, 72, 9, 166, 456, 299, 456, 525, 456, 452, 456, 30, 9, 460, 388, 498, 487, 256, 206, 132, -1,
	423, 487, 388, -1,
	206, 487, 352, 423, 341, 423, 418, 72, 139, 166, 139, 391, 57, -1,
	85, 223, 120, 24, 57, 24, 139, 24, 418, 25, 341, -1,
	223, 25, 24, -1,
	492, 132, 515, 206, 224, 352, 359, 341, 41, 25, 171, 223, 50, 85, 43, 98, 232, 406, 258, 469, -1,
	232, 345, 43, 372, 50, 454, 171, 514, 41, 314, 359, 360, 224, 2, 515, 527, -1,
	393, 393, 0, 216, 349, -1,
	486, 215, 327, 91, 177, 254, 177, 393, 512, 0, 231, 349, 231, 279, 486, 246, -1,
	177, 512, 327, 231, 486, -1,
	462, 462, 144, 76, 179, 464, 298, 464, 393, 128, 216, 113, 349, 500, 279, 101, 246, 7, 246, 395, 246, 384, 486, 215, -1,
	7, 7, 195, 101, 444, 500, 462, 113, 76, 128, 464, -1,
	254, 254, 285, 91, 149, 215, 83, 384, 325, 395, 520, 395, 315, 7, 143, 195, 129, 195, 461, 444, 475, 462, 144, -1,
	520, 308, 325, 415, 83, 297, 149, 504, 285, 162, 278, 446, -1,
	403, 403, 520, 276, 308, 404, 308, 272, 415, 416, 297, 317, 504, 125, 162, 60, 446, 110, 446, 393, 278, 254, 285, -1,
	125, 125, 459, 317, 334, 416, 137, 272, 47, 404, 511, 404, 1, 276, 54, 403, 45, 370, 490, 210, 29, 184, -1,
	336, 1, 251, 54, 164, 45, 463, 490, 378, 29, 453, 147, 222, 218, 301, 218, 242, 310, 130, 528, 34, -1,
	26, 336, 148, 251, 269, 164, 419, 463, 293, 378, 420, 453, 333, 222, 208, 301, 294, 56, 127, 228, -1,
	131, 26, 371, 148, 284, 269, 311, 419, 95, 293, 350, 420, 377, 333, 474, 208, 396, 294, 357, 127, -1,
	116, 131, 273, 371, 480, 284, 104, 311, 257, 95, 348, 350, 447, 377, 313, 474, 322, 396, 28, 357, -1,
	273, 273, 183, 480, 347, 104, 53, 257, 181, 348, 124, 447, 428, 313, 428, 435, 11, 270, 193, 305, 69, 305, 386, -1,
	11, 11, 428, 409, 124, 382, 181, 161, 53, 481, 347, 408, 183, 319, 151, 422, 448, 4, 165, 134, 394, -1,
	193, 193, 11, 495, 409, 44, 382, 385, 161, 478, 481, 320, 408, 37, 319, 524, 422, 328, 4, 465, 134, -1,
	37, 37, 431, 320, 136, 478, 513, 385, 27, 44, 467, 495, 115, 193, 69, -1,
	305, 305, 386, 20, 174, 182, 401, 211, 248, 106, 295, 309, 255, 465, 483, 328, 191, 524, 135, 37, 431, -1,
	465, 465, 134, 309, 102, 106, 427, 211, 507, 182, 410, 20, 503, 305, 503, 270, 445, 435, 322, 313, -1,
	134, 134, 394, 102, 455, 427, 5, 507, 23, 410, 405, 503, 405, 445, -1,
	322, 322, 445, 28, 405, 138, 23, 485, 5, 234, 455, 74, 394, 180, 165, 49, 448, 116, 151, 273, 183, -1,
	28, 357, 138, 268, 485, 287, 234, 81, 74, 78, 180, 103, 49, 220, 116, 220, 131, 476, 26, 38, 26, 336, -1,
	357, 127, 268, 252, 287, 398, 81, 274, 78, 154, 103, 62, 220, 476, -1,
	127, 228, 252, 141, 398, 440, 274, 363, 154, 190, 62, 488, 476, 38, -1,
	301, 242, 56, 517, 228, 33, 141, 18, 440, 466, 363, 304, 190, 417, 488, 484, 38, 511, 336, 1, -1,
	33, 517, 260, -1,
	18, 33, 390, 260, 497, -1,
	466, 18, 353, 390, 290, 497, 126, -1,
	304, 466, 187, 353, 123, 290, 522, 126, 501, -1,
	417, 304, 458, 187, 117, 123, 168, 522, 87, 501, 261, -1,
	484, 417, 430, 458, 343, 117, 438, 168, 426, 87, 482, 261, 329, -1,
	511, 484, 47, 430, 137, 343, 334, 438, 459, 426, 439, 482, 92, 329, 192, 329, 267, 329, 491, 261, 219, 501, -1,
	528, 528, 34, 145, 46, 356, 105, 472, 219, 48, 491, 247, 267, 393, 192, 110, 92, 60, 439, 125, 459, -1,
	219, 501, 105, 126, 46, 497, 34, 260, 130, 517, 242, -1,
	29, 184, 147, 156, 218, 156, 310, 402, 528, 146, 145, 17, 356, 411, 472, 364, 48, 441, 247, 441, 393, 509, -1,
	184, 184, 156, 63, 402, 354, 146, 335, 17, 239, 411, 13, 364, 509, 441, -1,
	393, 509, 298, 13, 179, 239, 144, 335, 475, 354, 461, 63, 129, 184, 129, 210, 143, 370, 315, 403, 520, -1,
	296, 296, 160, 133, 344, 330, -1,
	344, 323, 160, -1,
	159, 159, 296, 275, 133, 22, 330, 523, -1,
	198, 523, 77, 22, 286, 275, 437, 159, 499, -1,
	280, 323, 108, 344, 338, 330, 259, 523, 366, 198, 381, 240, 283, 10, 368, 243, 280, 243, 323, 35, 160, -1,
	77, 471, 198, 471, 240, 250, 10, 303, 243, 303, 35, 230, 282, 362, 163, 73, 318, 292, 93, 477, 262, -1,
	413, 413, 326, 399, 73, 399, 292, 100, 477, -1,
	122, 355, 414, 61, 100, 55, 477, 508, 262, 365, -1,
	35, 35, 160, 282, 296, 163, 159, 318, 499, 93, 505, 262, 340, 365, 340, 140, 68, 510, 518, 3, 122, 355, -1,
	100, 399, 414, 413, 122, 111, 518, 213, 68, 167, 340, 167, 505, 245, 499, 245, 437, 346, 286, 79, 77, 471, -1,
	362, 362, 221, 230, 516, 303, 516, 250, 207, 471, 207, 79, 521, 346, 468, 245, 468, 167, 468, 213, 473, 111, 204, 413, 326, -1,
	468, 473, 521, 217, 207, 217, 516, 217, 221, 204, 221, 326, 362, 73, -1,
	473, 204, 217, -1,
	94, 94, 185, 529, 429, 209, 429, 176, -1,
	379, 379, 94, 199, 529, 367, 209, 172, 209, 66, 176, 496, -1,
	312, 312, 379, 238, 199, 15, 367, 332, 172, 197, 172, 451, 66, 84, 496, 186, -1,
	266, 266, 312, 392, 238, 201, 15, 14, 332, 457, 197, 383, 197, 225, 451, 502, 84, 265, 186, 205, -1,
	236, 236, 266, 214, 392, 71, 201, 188, 14, 173, 457, 400, 383, 380, 383, 342, 225, 109, 502, 175, 265, 97, 205, 118, -1,
	152, 152, 236, 337, 214, 58, 71, 369, 188, 434, 173, 114, 400, 288, 380, 42, 380, 397, 342, 32, 109, 331, -1,
	379, 170, 312, 331, 266, 32, 236, 397, 152, 42, 194, 42, 407, 288, 142, 114, 12, 434, 233, 369, 244, -1,
	369, 369, 244, 58, 425, 337, 321, 152, 194, -1,
	109, 331, 175, 170, 97, 300, 118, 421, 31, 89, -1,
	31, 31, 118, 237, 205, 449, 186, 470, 496, 494, 176, 155, 429, 112, 185, 89, 185, 421, 94, 300, 379, 170, -1
};

// -- TEAPOT FUNCTIONS ---------------------------------------------------- 
//static void fghTeapot(GLint grid, GLdouble scale, GLenum type, GLint k);
//CVAO fghTeapot(GLint grid, GLdouble scale, GLenum type);
CVAO fghTeapot(bool flag_EBO);

// -- TEAPOT INTERFACE FUNCTIONS -------------------------------------------------- 
void glutSolidTeapot();				// Draws a solid Teapot
CVAO loadglutSolidTeapot_VAO();		// Loads a solid Teapot in VAO
CVAO loadglutSolidTeapot_EBO();		// Loads a solid Teapot in EBO

// ---------- PRIMITIVES GLU (CILINDRE, DISC, ESFERA) -------------------------
void gluCylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
CVAO loadgluCylinder_VAO(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
CVAO loadgluCylinder_EBO(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);

void gluDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops);
CVAO loadgluDisk_VAO(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops);
CVAO loadgluDisk_EBO(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops);

void gluPartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle);
CVAO loadgluPartialDisk_VAO(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle);
CVAO loadgluPartialDisk_EBO(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle);

void gluSphere(GLdouble radius, GLint slices, GLint stacks);
CVAO loadgluSphere_VAO(GLdouble radius, GLint slices, GLint stacks);
CVAO loadgluSphere_EBO(GLdouble radius, GLint slices, GLint stacks);

// ------------------- PRIMITIVA CILINDRE -------------------------
void cilindre(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
CVAO loadCilindre_VAO(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
CVAO loadCilindre_EBO(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);

// ------------------- PRIMITIVA SQUARE (QUADRAT) -------------------------
void glutSolidSquare(GLdouble dSize);
CVAO loadglutSolidSquare_VAO(GLdouble dSize);
CVAO loadglutSolidSquare_EBO(GLdouble dSize);


// ------------------------------- DIBUIX DE CORBES i SUPERFICIES --------------------------------

// ------------------------------- DIBUIX DE CORBES ----------------------------------------------
const int MAX_PATCH_CORBA = 25;		// M�xim tamany vector Punts de control per a Corbes
const double MIN_STEP_CORBA = 0.01;	// Minim pas del Par�metre t per a dibuixar una corba
const double MAX_STEP_CORBA = 1.0;	// M�xim pas del Par�metre t per a dibuixar una corba

// C�lcul Vector Normal de dos vectors 
//CPunt3D VNormal(CPunt3D v1, CPunt3D v2);

// C�lcul Producte Vectorial de dos vectors 
CPunt3D Prod_Vectorial(CPunt3D v1, CPunt3D v2);

// Vector Normal Principal del Triedre de Frenet (VBNxVT)
CPunt3D Vector_Normal_Principal(CPunt3D VBN, CPunt3D VT);

// dibuixa_TriedreFrenet: Dibuix del triedre de Frenet segons: VT (blau), VNP (verd) i VBN (vermell)
void dibuixa_Triedre_Frenet(GLuint sh_programID, CPunt3D vertex, CPunt3D VT, CPunt3D VNP, CPunt3D VBN);
// SetPatchColor: Defineix el color del patch de la corba Bezier, B-Spline, Catmull-Roll
CColor SetColorPatch(int ptch);

//----------------------------  POLYLINE
const GLdouble PAS_POLYLINE = 0.10;	// Pas Polyline. Precisi� del Polyline

void draw_PolyLine(CPunt3D* ctr_points, int nptsPolyLine, float pas);
CVAO load_PolyLine_VAO(CPunt3D* ctr_points, int nptsPolyLine, float pas);
void draw_TFPolyLine(GLuint sh_programID, CPunt3D* ctr_points, int nptsPolyLine, float pas);
CPunt3D Punt_PolyLine(float t, CPunt3D* ctr);
// D_Polyline: Funci� per a calcular la primera derivada de la Polylinesegons:
//     * t: par�metre entre (0,1).
//     * ctr: Extrems del segment de recta.
CPunt3D D_PolyLine(CPunt3D* ctr);
// D2_Polyline: Funci� per a calcular la segona derivada de la Polyline segons:
//     * t: par�metre entre (0,1).
//     * ctr: Extrems del segment de recta.
CPunt3D D2_PolyLine(CPunt3D* ctr);

//-- TRIEDRE DE FRENET PER A POLYLINE
// Vector Tangent
CPunt3D VT_PolyLine(CPunt3D* ctr);
// Vector BiNormal
CPunt3D VBN_PolyLine(CPunt3D* ctr);
// Vector Normal Principal
CPunt3D VNP_PolyLine(CPunt3D VBN, CPunt3D VT);

//----------------------------  CORBA LEMNISCATA
const GLdouble PAS_LEMNISCATA = 0.10;

void draw_Lemniscata2D(float escala, float pas);
CVAO load_Lemniscata2D_VAO(float escala, float pas);
CVAO load_Lemniscata2D_EBO(float escala, float pas);
void draw_TFLemniscata2D(GLuint sh_programID, float escala, float pas);
CPunt3D Punt_Lemniscata2D(float t, float scale);
CPunt3D D_Lemniscata2D(float t, float scale);
CPunt3D D2_Lemniscata2D(float t, float scale);
CPunt3D VT_Lemniscata2D(float t, float scale);
CPunt3D VBN_Lemniscata2D(float t, float scale);

void draw_Lemniscata3D(float escala, float pas);
CVAO load_Lemniscata3D_VAO(float escala, float pas);
CVAO load_Lemniscata3D_EBO(float escala, float pas);
void draw_TFLemniscata3D(GLuint sh_programID, float escala, float pas);
CPunt3D Punt_Lemniscata3D(float t, float scale);
CPunt3D D_Lemniscata3D(float t, float scale);
CPunt3D D2_Lemniscata3D(float t, float scale);
CPunt3D VT_Lemniscata3D(float t, float scale);
CPunt3D VBN_Lemniscata3D(float t, float scale);


//----------------------------  CORBA HERMITTE

// Matriu Hermitte
const double H[4][4] =
{
	{ -1.0,  2.0, -1.0, 0.0 },
	{  3.0, -5.0,  1.0, 1.0 },
	{ -3.0,  4.0,  0.0, 0.0 },
	{  1.0, -1.0,  0.0, 0.0 }
};


// corbaSH1: Vector dels punts de control de Corbes Hermitte
const CPunt3D corbaH1[] = { { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 }, { -128.0 - 16.0, 0.0, 75.0 },
{ -16.0, 64.0 + 32.0 + 32.0, 150.0 }, { 256.0 - 32.0, 64.0 - 32.0, 75.0 }, { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 } };
// Numero Pts control corbaH1
const int nptsCH1 = 9;
const GLdouble PAS_HERMITTE = 0.10;	// Pas Hermitte. Precisi� de la corba

void draw_Hermitte_Curve(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_Hermitte_Curve_VAO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_Hermitte_Curve_EBO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
void draw_TFHermitte_Curve(GLuint sh_programID, CPunt3D* ctr_points, int nptsCorba, float pas);
CPunt3D Punt_Corba_Hermitte(float t, CPunt3D* ctr);

// D_Hermitte_Curve: Funci� per a calcular la primera derivada de la corba Hermitte segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D_Hermitte_Curve(float t, CPunt3D* ctr);

// D2_Hermitte_Curve: Funci� per a calcular la segona derivada de la corba Hermitte segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D2_Hermitte_Curve(float t, CPunt3D* ctr);

//-- TRIEDRE DE FRENET PER A CORBES HERMITTE
// Vector Tangent
CPunt3D VT_Hermitte_Curve(float t, CPunt3D* ctr);

// Vector BiNormal
CPunt3D VBN_Hermitte_Curve(float t, CPunt3D* ctr);
//----------------------------  CORBA FI HERMITTE

//----------------------------  CORBA CATMULL-ROM

// Matriu Catmull-Rom
const double CR[4][4] =
{
	{ -0.5,  1.0, -0.5, 0.0 },
	{  2.0, -3.5,  0.5, 1.0 },
	{ -2.0,  3.0,  0.0, 0.0 },
	{  0.5, -0.5,  0.0, 0.0 }
};


// corbaCR1: Vector dels punts de control de Catmull-Rom
const CPunt3D corbaCR1[] = { { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 }, { -128.0 - 16.0, 0.0, 75.0 },
{ -16.0, 64.0 + 32.0 + 32.0, 150.0 }, { 256.0 - 32.0, 64.0 - 32.0, 75.0 }, { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 } };
// Numero Pts control corbaCR1
const int nptsCR1 = 9;
const GLdouble PAS_CATMULL_ROM = 0.10;	// Pas Catmull-Rom. Precisi� de la corba

void draw_CatmullRom_Curve(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_CatmullRom_Curve_VAO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_CatmullRom_Curve_EBO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
void draw_TFCatmullRom_Curve(GLuint sh_programID, CPunt3D* ctr_points, int nptsCorba, float pas);
CPunt3D Punt_Corba_CatmullRom(float t, CPunt3D* ctr);

// D_CatmullRom_Curve: Funci� per a calcular la primera derivada de la corba Hermitte segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D_CatmullRom_Curve(float t, CPunt3D* ctr);

// D2_CatmullRom_Curve: Funci� per a calcular la segona derivada de la corba Hermitte segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D2_CatmullRom_Curve(float t, CPunt3D* ctr);

//-- TRIEDRE DE FRENET PER A CORBES CATMULL-ROM
// Vector Tangent
CPunt3D VT_CatmullRom_Curve(float t, CPunt3D* ctr);

// Vector BiNormal
CPunt3D VBN_CatmullRom_Curve(float t, CPunt3D* ctr);
//----------------------------  CORBA FI CATMULL-ROM


//----------------------------  CORBA B-SPLINE

// Matriu dels BSplines
const double AS[4][4] =
{
	{ -1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0 },
	{ 0.5, -1.0, 0.0, 4.0 / 6.0 },
	{ -0.5, 0.5, 0.5, 1.0 / 6.0 },
	{ 1.0 / 6.0, 0.0, 0.0, 0.0 }
};

// Matriu dels BSplines Trasposada
const double AST[4][4] =
{
	{ -1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0 },
	{ 0.5, -1.0, 0.5, 0.0 },
	{ -0.5, 0.0, 0.5, 0.0 },
	{ 1.0 / 6.0, 4.0 / 6.0, 1.0 / 6.0, 0.0 }
};

// corbaS1: Vector dels punts de control de Corbes Spline
const CPunt3D corbaS1[] = { { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 }, { -128.0 - 16.0, 0.0, 75.0 },
{ -16.0, 64.0 + 32.0 + 32.0, 150.0 }, { 256.0 - 32.0, 64.0 - 32.0, 75.0 }, { 256.0 + 16.0, 256.0, 30.0 }, { -256.0, 256.0, -10.0 }, { -256.0, 0.0, 30.0 } };
// Numero Pts control corbaS1
const int nptsCS1 = 9;
const GLdouble PAS_BSPLINE = 0.10;	// Pas Spline. Precisi� de la corba

void draw_BSpline_Curve(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_BSpline_Curve_VAO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
CVAO load_BSpline_Curve_EBO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas);
void draw_TFBSpline_Curve(GLuint sh_programID, CPunt3D* ctr_points, int nptsCorba, float pas);
CPunt3D Punt_Corba_BSpline(float t, CPunt3D * ctr);

// D_BSpline_Curve: Funci� per a calcular la primera derivada de la corba B-Spline segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D_BSpline_Curve(float t, CPunt3D* ctr);

// D2BSpline_Curve: Funci� per a calcular la segona derivada de la corba B-Spline segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D2_BSpline_Curve(float t, CPunt3D* ctr);

//-- TRIEDRE DE FRENET PER A CORBES BSPLINE
// Vector Tangent
CPunt3D VT_BSpline_Curve(float t, CPunt3D* ctr);

// Vector BiNormal
CPunt3D VBN_BSpline_Curve(float t, CPunt3D* ctr);
//----------------------------  CORBA FI B-SPLINE

//----------------------------  CORBA BEZIER
// Matriu de la corba de Bezier
const double AB[4][4] =
{
	{ -1.0, 3.0, -3.0, 1.0 },
	{ 3.0, -6.0, 3.0, 0.0 },
	{ -3.0, 3.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0, 0.0 }
};
// Variables Corbes Bezier
const int MAX_PATCH_BEZIER = 25;	// M�xim tamany vector Punts de control
const GLdouble PAS_BEZIER = 0.10;	// Pas Bezier. Precisi� de la corba

// Dibuix Corba de Bezier en VBO
void draw_Bezier_Curve(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA],  float pas, bool tancat);
CVAO load_Bezier_Curve_VAO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas, bool tancat);
CVAO load_Bezier_Curve_EBO(int nptsCorba, CPunt3D ctr_points[MAX_PATCH_CORBA], float pas, bool tancat);
void draw_TFBezier_Curve(GLuint sh_programID, CPunt3D* ctr_points, int nptsCorba, float pas, bool tancat);
CPunt3D Punt_Bezier_Curve(float t, CPunt3D * ctr);

// D_CBezier: Funci� per a calcular la primera derivada de la corba Bezier segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D_Bezier_Curve(float t, CPunt3D* ctr);

// D2_CBezier: Funci� per a calcular la segona derivada de la corba Bezier segons:
//     * t: par�metre entre (0,1).
//     * ctr: Punts de control.
CPunt3D D2_Bezier_Curve(float t, CPunt3D* ctr);

//-- TRIEDRE DE FRENET PER A CORBES BEZIER
// Vector Tangent
CPunt3D VT_Bezier_Curve(float t, CPunt3D* ctr);

// Vector BiNormal
CPunt3D VBN_Bezier_Curve(float t, CPunt3D* ctr);
//----------------------------  FI CORBA BEZIER

// ------------------------- ACTIVACI� VERTEX ARRAY DE CADA FORMA GL_* PER A VBO
CVAO load_LINES_VAO(std::vector <double> vertices, std::vector <double> colors);
void draw_LINES_VAO(GLint vaoList_indx);
CVAO load_LINES_EBO(std::vector <double> vertices, std::vector <double> colors, std::vector <uint> indices);
void draw_LINES_EBO(GLint vaoList_indx);
CVAO load_TRIANGLES_VAO(std::vector <double> vertices, std::vector <double> normals, std::vector <double> colors, std::vector <double> textures);
void draw_TRIANGLES_VAO(GLint vaoList_indx);
CVAO load_TRIANGLES_EBO(std::vector <double> vertices, std::vector <double> normals, std::vector <double> colors, std::vector <double> textures, std::vector <uint> indices);
void draw_TRIANGLES_EBO(GLint vaoList_indx);

void draw_GL_LINES_VAO(std::vector <double> vertices, std::vector <double> colors);
void draw_GL_TRIANGLES_VAO(std::vector <double> vertices, std::vector <double> normals, std::vector <double> colors, std::vector <double> textures);
void draw_GL_TRIANGLE_FAN_VAO(std::vector <double> vertices, std::vector <double> normals, std::vector <double> colors, std::vector <double> textures);
void draw_GL_TRIANGLE_STRIP_VAO(std::vector <double> vertices, std::vector <double> normals, std::vector <double> colors, std::vector <double> textures);


void draw_LINES_EBO(GLint vaoList_indx);
void draw_TRIANGLES_EBO(GLint vaoList_indx);

// --- ACTIVACI� DEFINICI� COORDENADES TEXTURA PER A OBJECTES GLUT ------------------------ 
void Activa_Coordenades_Textura();
void Desactiva_Coordenades_Textura();

// --------------------------- OPERADORS
float round3dec(float val);
#endif  /* GLET_GEOMETRY_H */
/*** END OF FILE ***/
