//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MONOFINESTRA amb OpenGL 4.3, interf�cie GLFW, ImGui i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2024)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

// Entorn VGI: OBJECTE OBJ. Include per la definici� de l'objecte Obj_OBJ
#include "objLoader.h"	
#include "nau.h"

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
void dibuixa_Eixos(GLuint ax_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista);
void dibuixa_Skybox(GLuint sk_programID, GLuint cmTexture, char eix_Polar, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista);

// Entorn VGI: dibuixa_EscenaGL -> Dibuix de l'escena GL
void dibuixa_EscenaGL(GLuint sh_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, char objecte, CColor col_object, 
	bool sw_mat[5], 
	bool textur, GLuint texturID[NUM_MAX_TEXTURES], bool textur_map, bool flagInvertY,
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, bool dib_TFrenet,
	COBJModel* objecteOBJ,
	glm::mat4 MatriuVista, glm::mat4 MatriuTG, float time, bool propulsat, Nau& nau, COBJModel* TestOBJ, COBJModel* CombustibleOBJ, COBJModel* EstacioOBJ);

/*MODIFIED*/
void objecte_t(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5]);
void sputnik(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, bool propulsat);
void donut_face(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time);
void nau_face(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time);
void d_nau(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], const Nau nau);
void drawOrbitPath(Planeta& planeta);


/* MODIFIED*/
void planeta(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, GLuint texturID[NUM_MAX_TEXTURES],bool textur, Nau& nau);
void asteroide(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* TestOBJ, CColor col_object, Nau& nau);
void asteroidesCinturo(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* TestOBJ, CColor col_object);
void objectes(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* CombustibleOBJ, CColor col_object);
void estacions(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* EstacioOBJ, CColor col_object);
void joc(float time, Nau& nau);
#endif
