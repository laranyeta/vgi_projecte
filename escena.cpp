//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MONOFINESTRA amb OpenGL 4.3, interf�cie GLFW, ImGui i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2024)
// escena.cpp : Aqui es on ha d'anar el codi de les funcions que 
//              dibuixin les escenes.
//
//    Versi� 2.0:	- Objectes Cub, Esfera, Tetera (primitives libreria GLUT)
//
//	  Versi� 2.2:	- Objectes Cub, Esfera, Tetera definides en fitxer font glut_geometry amb altres primitives GLUT
//
//	  Versi� 2.5:	- Objectes cubRGB i Tie (nau Star Wars fet per alumnes)
//

#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"
#include <iostream>

// Dibuixa Eixos Coordenades M�n i Reixes, activant un shader propi.
void dibuixa_Eixos(GLuint ax_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, 
	glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista)
{
// Visualitzaci� Eixos Coordenades M�n
	glUseProgram(ax_programID);

// Pas Matrius Projecci� i Vista Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(ax_programID, 0, "in_Vertex"); // V�rtexs
	glBindAttribLocation(ax_programID, 1, "in_Color");	// Color

//  Dibuix dels eixos
	if (eix) draw_Eixos(axis_Id);

// Dibuixa el grid actiu
	if ((reixa.x) || (reixa.y) || (reixa.z) || (reixa.w)) draw_Grid(reixa, hreixa);
}

// Dibuixa Skybox en forma de Cub, activant un shader propi.
void dibuixa_Skybox(GLuint sk_programID, GLuint cmTexture, char eix_Polar, glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista)
{
	glm::mat4 ModelMatrix(1.0);

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

// Activaci� shader per a cub skybox
	glUseProgram(sk_programID);

// Pas Matrius Projecci� i Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Rotar skyBox per a orientar sobre eix superior Z o X en Vista Esf�rica (POLARX, POLARY, POLARZ)
	if (eix_Polar == POLARZ) ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	else if (eix_Polar == POLARX) ModelMatrix = glm::rotate(ModelMatrix, radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));

// Escalar Cub Skybox a 5000 per encabir objectes escena a l'interior
	ModelMatrix = glm::scale(ModelMatrix, vec3(5000.0f, 5000.0f, 5000.0f));		//glScaled(5000.0, 5000.0, 5000.0);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

// Activar textura cubemaps del Skybox per encabir objectes escena
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cmTexture);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sk_programID, 0, "in_Vertex"); // V�rtexs

//  Dibuix del Skybox
	drawCubeSkybox();

	glDepthFunc(GL_LESS); // set depth function back to default
}


// dibuixa_EscenaGL: Dibuix de l'escena amb comandes GL
void dibuixa_EscenaGL(GLuint sh_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, char objecte, 
			CColor col_object, bool sw_mat[5],
			bool textur, GLuint texturID[NUM_MAX_TEXTURES], bool textur_map, bool flagInvertY,
			int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, bool dib_TFrenet,
			COBJModel* objecteOBJ,
			glm::mat4 MatriuVista, glm::mat4 MatriuTG, float time,bool propulsat)
{
	float altfar = 0;
	GLint npunts = 0, nvertexs = 0;
	int i, j, k;
	GLdouble tras[3] = { 0.0,0.0,0.0 }; //Sierpinski Sponge
	CColor color_vermell = { 0.0,0.0,0.0,1.0 }, color_Mar = { 0.0,0.0,0.0,0.0 };
	bool sw_material[5] = { 0.0,0.0,0.0,0.0,0.0 };
	
// Matrius de Transformaci�
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0), TransMatrix(1.0), ScaleMatrix(1.0), RotMatrix(1.0);

// VAO
	CVAO objectVAO = { 0,0,0,0,0 };
	objectVAO.vaoId = 0;	objectVAO.vboId = 0;	objectVAO.eboId = 0;	 objectVAO.nVertexs = 0; objectVAO.nIndices = 0;

	tras[0] = 0.0;	tras[1] = 0.0; tras[2] = 0.0;
	color_vermell.r = 1.0;	color_vermell.g = 0.0; color_vermell.b = 0.0; color_vermell.a = 1.0;
	sw_material[0] = false;	sw_material[1] = true; sw_material[2] = true; sw_material[3] = false;	sw_material[4] = true;

// Shader Visualitzaci� Objectes
	glUseProgram(sh_programID);

// Parametritzaci� i activaci�/desactivaci� de textures
	if (texturID[0] != -1) SetTextureParameters(texturID[0], true, true, textur_map, false);
	if (textur) {	glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
					glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE); //glEnable(GL_MODULATE);
				}
		else {	//glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_FALSE); //glDisable(GL_TEXTURE_2D);
				//glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_FALSE); //glDisable(GL_MODULATE);
			}
	glUniform1i(glGetUniformLocation(sh_programID, "flag_invert_y"), flagInvertY);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sh_programID, 0, "in_Vertex");		// V�rtexs
	glBindAttribLocation(sh_programID, 1, "in_Color");		// Color
	glBindAttribLocation(sh_programID, 2, "in_Normal");		// Normals
	glBindAttribLocation(sh_programID, 3, "in_TexCoord");	// Textura

// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	switch (objecte)
	{

// Arc
	case ARC:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		arc(sh_programID, MatriuVista, MatriuTG, sw_mat);

		// Activar transpar�ncia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Dibuix geometria Mar
		color_Mar.r = 0.5;	color_Mar.g = 0.4; color_Mar.b = 0.9; color_Mar.a = 0.5;
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, color_Mar, sw_mat);
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriVAO_Object(MAR_FRACTAL_VAO);

		// Desactivar transpar�ncia
		glDisable(GL_BLEND);
		break;
	/*MAV MODIFIED*/
	case OBJECTE_T:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		objecte_t(sh_programID, MatriuVista, MatriuTG, sw_mat);

		break;
		/*MAV MODIFIED*/
	case SPUTNIK:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		sputnik(sh_programID, MatriuVista, MatriuTG, sw_mat, time,propulsat);
		break;
	/*MAV MODIFIED*/
	case DONUT_FACE:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		donut_face(sh_programID, MatriuVista, MatriuTG, sw_mat, time);
		break;
	/*MAV MODIFIED*/
	case NAU_FACE:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		nau_face(sh_programID, MatriuVista, MatriuTG, sw_mat, time);
		break;

	case PROVA_PLANETA:
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		planeta(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur);
		// Activar transpar�ncia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Dibuix geometria Mar
		color_Mar.r = 0.5;	color_Mar.g = 0.4; color_Mar.b = 0.9; color_Mar.a = 0.5;
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, color_Mar, sw_mat);
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Desactivar transpar�ncia
		glDisable(GL_BLEND);
		break;

		

// Dibuix de l'objecte TIE (Nau enemiga Star Wars)
	case TIE:
		tie(sh_programID, MatriuVista, MatriuTG, sw_mat);
		break;

// Dibuix de l'objecte OBJ
	case OBJOBJ:
		ModelMatrix = MatriuTG;
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Definir caracter�stiques material de cada punt
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		// Objecte OBJ: Dibuix de l'objecte OBJ amb textures amb varis VAO's, un per a cada material.
		objecteOBJ->draw_TriVAO_OBJ(sh_programID);	// Dibuixar VAO a pantalla
		break;

// Corba Bezier
	case C_BEZIER:
		// Dibuixar Punts de Control
		if (sw_PC)
		{	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color vermell.
			SeleccionaColorMaterial(sh_programID, color_vermell, sw_material);

			for (int i = 0; i < nptsU; i++)
			{	//glPushMatrix();
				  //glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				  ModelMatrix = glm::translate(MatriuTG, vec3(PC_u[i].x, PC_u[i].y, PC_u[i].z));
				  // Pas ModelViewMatrix a shader
				  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				  // Pas NormalMatrix a shader
				  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				  draw_TriEBO_Object(GLU_SPHERE); //drawgluSphere(npunts);	//gluSphere(5.0, 20, 20);
				//glPopMatrix();
			}

		}
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		ModelMatrix = MatriuTG;
		// Pas ModelViewMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_LinEBO_Object(CRV_BEZIER); //draw_LinVAO_Object(CRV_BEZIER); //draw_Bezier_Curve(nptsU, PC_u, pasCS, false);
		if (dib_TFrenet) draw_TFBezier_Curve(sh_programID, PC_u, nptsU, pasCS, false); // Dibuixar Triedre de Frenet
		break;

// Corba Lemniscata
	case C_LEMNISCATA:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		ModelMatrix = MatriuTG;
		// Pas ModelViewMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_LinEBO_Object(CRV_LEMNISCATA3D); // draw_LinVAO_Object(CRV_LEMNISCATA3D); //draw_Lemniscata3D(800, pasCS*20.0);
		if (dib_TFrenet) draw_TFLemniscata3D(sh_programID, 800, pasCS * 20.0);
		break;

// Corba Spline
	case C_BSPLINE:
		// Dibuixar Punts de Control
		if (sw_PC)
		{	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color vermell.
			SeleccionaColorMaterial(sh_programID, color_vermell, sw_material);
			//objectVAO = loadgluSphere_VAO(5.0, 20, 20);
			for (int i = 0; i < nptsU; i++)
			{	//glPushMatrix();
				  //glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				ModelMatrix = glm::translate(MatriuTG, vec3(PC_u[i].x, PC_u[i].y, PC_u[i].z));
				// Pas ModelViewMatrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				draw_TriEBO_Object(GLU_SPHERE); // drawgluSphere(npunts);	//gluSphere(5.0, 20, 20);
				//glPopMatrix();
			}

		}
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		ModelMatrix = MatriuTG;
		// Pas ModelViewMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_LinEBO_Object(CRV_BSPLINE); //draw_LinVAO_Object(CRV_BSPLINE); //draw_BSpline_Curve(nptsU, PC_u, pasCS);
		if (dib_TFrenet) draw_TFBSpline_Curve(sh_programID, PC_u, nptsU, pasCS); // Dibuixar Triedre de Frenet
		break;

// Corba Hermitte
	case C_HERMITTE:
		// Dibuixar Punts de Control
		if (sw_PC)
		{	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color vermell.
			SeleccionaColorMaterial(sh_programID, color_vermell, sw_material);
			//objectVAO = loadgluSphere_VAO(5.0, 20, 20);
			for (int i = 0; i < nptsU; i++)
			{	//glPushMatrix();
				  //glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				ModelMatrix = glm::translate(MatriuTG, vec3(PC_u[i].x, PC_u[i].y, PC_u[i].z));
				// Pas ModelViewMatrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				draw_TriEBO_Object(GLU_SPHERE); //gluSphere(5.0, 20, 20);
				//glPopMatrix();
			}
		}
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		ModelMatrix = MatriuTG;
		// Pas ModelViewMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		//draw_LinVAO_Object(CRV_HERMITTE); //draw_BSpline_Curve(nptsU, PC_u, pasCS);
		draw_LinEBO_Object(CRV_HERMITTE);
		if (dib_TFrenet) draw_TFHermitte_Curve(sh_programID, PC_u, nptsU, pasCS); // Dibuixar Triedre de Frenet
		break;

// Corba Catmull-Rom
	case C_CATMULL_ROM:
		// Dibuixar Punts de Control
		if (sw_PC)
		{	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color vermell.
			SeleccionaColorMaterial(sh_programID, color_vermell, sw_material);
			//objectVAO = loadgluSphere_VAO(5.0, 20, 20);
			for (int i = 0; i < nptsU; i++)
			{	//glPushMatrix();
				  //glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				ModelMatrix = glm::translate(MatriuTG, vec3(PC_u[i].x, PC_u[i].y, PC_u[i].z));
				// Pas ModelViewMatrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				draw_TriEBO_Object(GLU_SPHERE); //gluSphere(5.0, 20, 20);
				//glPopMatrix();
			}
		}
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		ModelMatrix = MatriuTG;
		// Pas ModelViewMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		//draw_LinVAO_Object(CRV_CATMULL_ROM);
		draw_LinEBO_Object(CRV_CATMULL_ROM);
		if (dib_TFrenet) draw_TFCatmullRom_Curve(sh_programID, PC_u, nptsU, pasCS); // Dibuixar Triedre de Frenet
		break;

// Matriu de Primitives SENSE pre-compilaci� pr�via en VBO (precompilaci�, draw i alliberaci� VBO en una funci�)
	case MATRIUP:
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				for (k = 0; k < 10; k++)
				{	//glPushMatrix();
					  //glTranslated(i * 15.0, j * 15.0, k * 15.0);
					  //glScaled(5.0, 5.0, 5.0);
					TransMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, k * 15.0));
					ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
					// Pas ModelView Matrix a shader
					glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
					// Pas NormalMatrix a shader
					NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
					glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
					glutSolidCube(1.0);
					//glutSolidTorus(1.0,2.0,20,20);
					//glutSolidOctahedron();
					//glutSolidTetrahedron();
					//glutSolidIcosahedron();
					//glutSolidRhombicDodecahedron();
					//glutSolidSierpinskiSponge(3,tras,1.0);
					//glutSolidTeapot(1.0);
					//gluCylinder(0.5,0.5,1.0,20,20);
					//gluSphere(1.0, 20, 20);
					//glPopMatrix();
				}
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
			{	//glPushMatrix();
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				ModelMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, 160.0f));
				// Pas ModelView Matrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				  //glScaled(5.0, 5.0, 5.0);
				  //glutSolidCube(1.0);
				glutSolidTorus(2.0,3.0,20,20);
				//glutSolidOctahedron();
				//glutSolidTetrahedron();
				//glutSolidIcosahedron();
				//glutSolidRhombicDodecahedron();
				//glutSolidSierpinskiSponge(3,tras,1.0);
				//glutSolidTeapot(1.0);
				//gluCylinder(0.5,0.5,1.0,20,20);
				//gluSphere(1.0, 20, 20);
				//glPopMatrix();
			}
// Dibuix una esfera
		//glPushMatrix();
		  //glTranslated(200.0, 200.0, 200.0);
		  //glScaled(5.0, 5.0, 5.0);
		TransMatrix = glm::translate(MatriuTG, vec3(200.0f, 200.0f, 200.0f));
		ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		gluSphere(1.0, 20, 20);
		//glPopMatrix();
		break;

// Matriu de Primitives AMB pre-compilaci� pr�via en VBO 
//	(separaci� en 3 funcions: *_VBO() per precompilaci�, draw*() per dibuix i deleteVBO() per alliberar VBO)
	case MATRIUP_VAO:
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		//glutSolidCube_VAO(1.0);		// C�rrega de la geometria del Cub al VAO

		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				for (k = 0; k < 10; k++)
				{	//glPushMatrix();
					  //glTranslated(i * 15.0, j * 15.0, k * 15.0);
					  //glScaled(5.0, 5.0, 5.0);
					  TransMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, k * 15.0f));
					  ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
					  // Pas ModelView Matrix a shader
					  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
					  // Pas NormalMatrix a shader
					  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
					  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
					  
					  draw_TriEBO_Object(GLUT_CUBE); //drawSolidCube();	// Dibuix del cub dins VBO.

				}
		//deleteVAO(GLUT_CUBE);	// Eliminaci� del VAO cub.

		//nvertexs = glutSolidTorus_VAO(2.0, 3.0, 20, 20);	// C�rrega de la geometria del Torus al VAO
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
			{	//glPushMatrix();
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				  //glTranslated(i * 15.0, j * 15.0, 160.0);
				ModelMatrix = glm::translate(MatriuTG, vec3(i * 15.0f, j * 15.0f, 160.0f));
				// Pas ModelView Matrix a shader
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				// Pas NormalMatrix a shader
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				draw_TriEBO_Object(GLUT_TORUS); //drawSolidTorus(nvertexs);
				//glPopMatrix();

			}
		//deleteVAO(GLUT_CUBE);		// Eliminaci� del VAO cub.
		//deleteVAO(GLUT_TORUS);    // Eliminaci� del VAO Torus.
// Dibuix una esfera
		//glPushMatrix();
		  //glTranslated(200.0, 200.0, 200.0);
		  //glScaled(5.0, 5.0, 5.0);
		  TransMatrix = glm::translate(MatriuTG, vec3(200.0f, 200.0f, 200.0f));
		  ModelMatrix = glm::scale(TransMatrix, vec3(5.0f, 5.0f, 5.0f));
		  // Pas ModelView Matrix a shader
		  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		  // Pas NormalMatrix a shader
		  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		  draw_TriEBO_Object(GLU_SPHERE); //gluSphere(1.0, 20, 20);
		//glPopMatrix();
		break;

// Dibuix de la resta d'objectes
	default:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		dibuixa(sh_programID, objecte,MatriuVista, MatriuTG);
		break;
	}

// Enviar les comandes gr�fiques a pantalla
//	glFlush();
}


// dibuixa: Funci� que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(GLuint sh_programID, char obj, glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
//	std::string String;
//	const char* string;
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0); // TransMatrix(1.0); // ScaleMatrix(1.0), RotMatrix(1.0);
	GLdouble tras[3] = { 0.0,0.0,0.0 }; //Sierpinski Sponge
	
	tras[0] = 0.0;	tras[1] = 0.0; tras[2] = 0.0;

	switch(obj)
	{

// Cub
	case CUB:
		//glPushMatrix();
		  //glScaled(5.0,5.0,5.0);
		ModelMatrix = glm::scale(MatriuTG, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLUT_CUBE);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
		//glPopMatrix();

		break;

	case CUB_RGB:
		//glPushMatrix();
		  //glScaled(5.0,5.0,5.0);
		ModelMatrix = glm::scale(MatriuTG, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLUT_CUBE_RGB);	//draw_TriVAO_Object(GLUT_CUBE_RGB); // glutSolidCubeRGB(1.0);
		//glPopMatrix();
		break;

// Esfera
	case ESFERA:	
		//glPushMatrix();
		  //glScaled(5.0,5.0,5.0);
		ModelMatrix = glm::scale(MatriuTG, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLU_SPHERE); //draw_TriVAO_Object(GLU_SPHERE); //gluSphere(1.0, 40, 40);
		//glPopMatrix();
		break;

// Tetera
	case TETERA:
		//glPushMatrix();
		  //glScaled(5.0,5.0,5.0);
		  ModelMatrix = MatriuTG;
		  // Pas ModelView Matrix a shader
		  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		  // Pas NormalMatrix a shader
		  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		  glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		  draw_TriVAO_Object(GLUT_TEAPOT); // glutSolidTeapot(1.0);
		//glPopMatrix();
		break;
// Cilindre /*MAV MODIFIED*/
	case CILINDRE:
		//glPushMatrix();
		  //glScaled(5.0,5.0,5.0);
		ModelMatrix = glm::scale(MatriuTG, vec3(5.0f, 5.0f, 5.0f));
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		// Pas NormalMatrix a shader
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLUT_CYLINDER);	//draw_TriVAO_Object(GLUT_CUBE);  //glutSolidCube(1.0);
		//glPopMatrix();

		break;
	}
}

void objecte_t(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5])
{
	CColor col_object = { 0.0,0.0,0.0,1.0 };
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

// Pota central
	// generar forma
	ModelMatrix = glm::scale(MatriuTG, vec3(1.0f, 5.0f, 1.0f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);

// Cub esquerra
	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 2.0f, 1.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 2.0f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);
// Cub dreta
	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, -2.0f, 1.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 2.0f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);
// Cub balan�a
	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 2.0f, 3.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 5.0f, 1.0f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);
// Esfera
	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 4.0f, 4.0f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE); //gluSphere(0.5, 20, 20);
// Tetera
	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 3.5f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.25f, 0.25f, 0.25f));
	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriVAO_Object(GLUT_TEAPOT); //gluSphere(0.5, 20, 20);
}



void processaRotacions()
{
	// Calculem les coordenades dels eixos pels quals rotar� el planeta sobre ell mateix
	float velocitatsRotacio[9] = { 5.0f, 10.0f, 8.0f, 6.0f, 12.0f, 4.0f, 9.0f, 7.0f, 11.0f };

	for (int i = 0; i < PLANETES.size(); ++i) {
		float inclinacioRadians = glm::radians(ANGLES_INCLINACIO_ROTACIO[i]);
		glm::vec3 eixosRotacio = glm::vec3(
			0.0f,
			cos(inclinacioRadians),
			sin(inclinacioRadians)
		);

		// Assignem eix de rotaci� i direcci� de rotaci�
		PLANETES[i].setEixosRotacioPlaneta(eixosRotacio);
		PLANETES[i].setDireccioRotacio(DIRECCIONS_ROTACIO[i]);
		PLANETES[i].setVelocitatRotacio(velocitatsRotacio[i]);
		PLANETES[i].setName(NAMES[i]); // CANVIAR DE LLOC NO PINTA RES AQUI
		PLANETES[i].setRutaTextura(RUTES_TEXTURA[i]);
	}
}

void processaFisica()
{
	// Constant gravitacional
	double G = 6.67430e-11 * pow(ESCALA_DISTANCIA, 3);
	
	for (int i = 0; i < PLANETES.size(); i++)
	{
		// Mida planeta
		PLANETES[i].setRadi(RADIS[i] * ESCALA_DISTANCIA);

		// Massa planeta
		double massa = MASSES[i] * ESCALA_MASSA;
		PLANETES[i].setMassa(massa);

		// Sol no es mou (valors per defecte del constructor, es pot eliminar)
		if (i == 0)
		{
			PLANETES[i].setPosition(glm::vec3(0.0f));
			PLANETES[i].setVelocitat(glm::vec3(0.0f));
		}
		else
		{
			// Posici� inicial del planeta
			double distancia = RADI_ORBITAL[i] * ESCALA_DISTANCIA;
			// ISMAEL: Planetes repartits al voltant del sol, canviar
			double angleRad = 2.0 * PI * (i - 1) / (PLANETES.size() - 1); // Distribuci�n uniforme

			float x = distancia * cos(angleRad);
			float y = distancia * sin(angleRad);
			float z = 0.0f; // Puedes modificar esto para distribuci�n en 3D

			PLANETES[i].setPosition(glm::vec3(x, y, z));
			/*
			PLANETES[i].setPosition(glm::vec3(distancia, 0.0f, 0.0f));
			std::cout << PLANETES[i].getPosition().x << " " << PLANETES[i].getPosition().y << std::endl;
			*/
			// Calcular velocitat orbital
			double M = PLANETES[0].getMassa(); // Massa del Sol
			double v = sqrt(G * M / distancia);

			// velocitat perpendicular a la posici�
			glm::dvec3 direccio = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), PLANETES[i].getPosition()));
			glm::dvec3 velocitat = direccio * v;

			PLANETES[i].setVelocitat(velocitat);

			// Orbites 3D, en proc�s
			PLANETES[i].setSemieixMajor(SEMIEIXOS_MAJORS[i-1]);
			PLANETES[i].setExcentricitat(EXCENTRICITATS[i-1]);
			PLANETES[i].setLongitudNodeAscendent(LONG_NODES_ASC[i-1] * DEG_A_RAD);
			PLANETES[i].setInclinacio(INCLINACIONS[i-1] * DEG_A_RAD);
			PLANETES[i].setPeriapsis(PERIAPSIS[i-1] * DEG_A_RAD);
		}
	}
}

void processaTextures()
{
	// Per cada planeta carreguem la seva textura
	for (auto& planeta : PLANETES)
	{
		std::string rutaTextura = "textures/" + planeta.getRutaTextura();
		char* cstr = new char[rutaTextura.length() + 1];
		std::strcpy(cstr, rutaTextura.c_str());
		GLint id = loadIMA_SOIL(cstr);
		std::cout << id << std::endl;
		planeta.setTextureID(id);
		std::cout << planeta.getTextureID() << std::endl;
	}
}

void processaPlanetes()
{
	processaFisica();
	processaRotacions();
	processaTextures();
}

void updatePlanetes(float deltaTime)
{
	// Constant gravitacional
	double G = 6.67430e-11 * pow(ESCALA_DISTANCIA, 3);
	//std::cout << G << std::endl;
	// Reiniciem les acceleracionss
	for (auto& planeta : PLANETES)
	{
		planeta.setAcceleracio(glm::dvec3(0.0));
		//std::cout << masaSol << std::endl;
	}

	// Calcular forces gravitacionals y actualitzar acceleracions
	for (int i = 0; i < PLANETES.size(); ++i)
	{
		//::cout << "Posici�1: " << PLANETES[i].getPosition().x << ", " << PLANETES[i].getPosition().y << ", " << PLANETES[i].getPosition().z << std::endl;
		//std::cout << "Radi: " << PLANETES[i].getRadi() << std::endl;
		//std::cout << "Velocitat1: " << PLANETES[i].getVelocitat().x << ", " << PLANETES[i].getVelocitat().y << ", " << PLANETES[i].getVelocitat().z << std::endl;
		//std::cout << "Acceleracio1: " << PLANETES[i].getAcceleracio().x << ", " << PLANETES[i].getAcceleracio().y << ", " << PLANETES[i].getAcceleracio().z << std::endl;
		Planeta& planeta = PLANETES[i];
		
		// El sol no s'ha de moure
		if (i == 0) continue;

		// For�a gravitacional del sol
		Planeta& sol = PLANETES[0];
		glm::dvec3 direccio = sol.getPosition() - planeta.getPosition();
		double distancia = glm::length(direccio);
		//std::cout << "Distancia: " << distance << std::endl;
		if (distancia > 0.0f)
		{
			// Fisica orbita
			glm::dvec3 direccioFor�a = glm::normalize(direccio);
			double magnitudFor�a = G * (sol.getMassa() * planeta.getMassa()) / (distancia * distancia);
			
			glm::dvec3 for�a = direccioFor�a * magnitudFor�a;

			// F=m*a => a=F/m
			glm::dvec3 acceleracio = for�a / planeta.getMassa();
			planeta.setAcceleracio(acceleracio);
		}
	}

	// Actualitzar velocitats i posicions dels planetes
	for (auto& planeta : PLANETES)
	{
		//std::cout << "Posici�: " << planeta.getPosition().x << ", " << planeta.getPosition().y << ", " << planeta.getPosition().z << std::endl;
		//std::cout << "Velocitat: " << planeta.getVelocitat().x << ", " << planeta.getVelocitat().y << ", " << planeta.getVelocitat().z << std::endl;
		//std::cout << "Acceleraci�: " << planeta.getAcceleracio().x << ", " << planeta.getAcceleracio().y << ", " << planeta.getAcceleracio().z << std::endl;
		// Actualitzar velocitat: v = v+a*dt
		glm::dvec3 velocitat = planeta.getVelocitat() + planeta.getAcceleracio() * (double)deltaTime;
		planeta.setVelocitat(velocitat);

		// Actualitzar posici�: x = x+v*dt
		glm::vec3 position = planeta.getPosition() + (glm::vec3)planeta.getVelocitat() * deltaTime;
		planeta.setPosition(position);
	}
}


void planeta(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur)
{
	// Inicialitzaci� de planetes
	static bool inicialitzat = false;
	static double lastTime = time;
	if (!inicialitzat)
	{
		processaPlanetes();
		inicialitzat = true;
	}
	// Un dia per segon
	double deltaTime = time - lastTime;
	lastTime = time;
	double velocitatSimulacio = 60.0 * 60.0 * 24.0; 
	deltaTime *= velocitatSimulacio;
	// F�sica orbites 2D de moment
	updatePlanetes(velocitatSimulacio);
	for(auto& planeta : PLANETES)
	{
		// Posici� inicial
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);
		ModelMatrix = glm::translate(MatriuTG, planeta.getPosition());
		
		// Rotaci� sobre ell mateix
		float velocitatRotacio = planeta.getVelocitatRotacio();    // Graus per segon
		int direccioRotacio = planeta.getDireccioRotacio(); 
		float angle = time * velocitatRotacio * direccioRotacio;
		glm::vec3 eixosRotacio = planeta.getEixosRotacioPlaneta();
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), eixosRotacio);

		float radi = planeta.getRadi();
		ModelMatrix = glm::scale(ModelMatrix, vec3(radi, radi, radi));

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		//Textures planetes
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (GLint)planeta.getTextureID());
		glUniform1i(glGetUniformLocation(sh_programID, "texture0"), GLint(0));
		SetTextureParameters((GLint)planeta.getTextureID(), true, true, false, false);
		glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE);
		
		draw_TriEBO_Object(3);
	}
	
}


// Variables globals
float velocitat_satelit = 1.0f;  // Velocitat vertical del sat�l�lit
float temps_propulsio_rest = 2.0f; // Temps restant de la propulsi�
float semi_eix_major = 25.0f;

void dibuixar_orbita(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, float semi_eix_major, float excentricitat)
{
	// Nombre de segments per a l'�rbita (com m�s gran sigui, m�s suau ser�)
	int num_segments = 100;
	std::vector<glm::vec3> punts_orbita;

	// Calcular els punts de l'�rbita utilitzant coordenades polars
	for (int i = 0; i < num_segments; ++i) {
		float angle = 2.0f * glm::pi<float>() * float(i) / float(num_segments); // Angle entre punts en radians

		// Calcular la dist�ncia radial r en funci� de l'excentricitat i l'angle
		float radi_orbita = (semi_eix_major * (1.0f - excentricitat * excentricitat)) / (1.0f + excentricitat * cos(angle));

		// Coordenades x i y per a l'�rbita el�l�ptica
		float x = radi_orbita * cos(angle); // Coordenada x
		float y = radi_orbita * sin(angle); // Coordenada y

		// Afegir el punt al vector, considerant que orbita en el pla X-Y (amb Z constant)
		punts_orbita.push_back(glm::vec3(x, y, 0.0f));
	}

	// Dibuixar l'�rbita amb l�nies
	glUseProgram(sh_programID); // Assegurar-se que s'est� usant el programa shader correcte
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &MatriuTG[0][0]);

	glBegin(GL_LINE_LOOP); // Utilitzar l�nia tancada per a l'�rbita
	for (const auto& punt : punts_orbita) {
		glVertex3f(punt.x, punt.y, punt.z); // Dibuixar cada punt
	}
	glEnd();
}

void sputnik(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time, bool propulsat)
{
	CColor col_object = { 0.0, 0.0, 0.0, 1.0 };
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

	// Esfera (planeta)
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(5.0f, 5.0f, 5.0f));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE);

	// Par�metres de l'�rbita
	float forca_propulsio = 0.01f;
	float gravetat = 0.0098f;
	float radi_planeta = 5.0f;
	float excentricitat = 0.2f;

	// Manejar la propulsi�
	/*if (propulsat) {
		std::cout << "Propulsat => " << temps_propulsio_rest << std::endl;
		velocitat_satelit += forca_propulsio;
		temps_propulsio_rest -= 0.1f;

		if (temps_propulsio_rest <= 0.0f) {
			propulsat = false;
		}
	}
	else {
		velocitat_satelit -= gravetat;
	}*/
	if (propulsat) {
		std::cout << "Propulsat => " << temps_propulsio_rest << std::endl;
		velocitat_satelit += forca_propulsio;  // Augmentem la velocitat amb propulsi�
		temps_propulsio_rest -= 0.01f;

		if (temps_propulsio_rest <= 0.0f) {
			propulsat = false;  // Desactivar propulsi�
			//temps_propulsio_rest = 2.0f;
		}
		semi_eix_major += 0.001f;  // Decrementar semi-eix major per simular una �rbita m�s petita
		if (semi_eix_major < 1.0f) { // Assegurar que no baixi massa
			semi_eix_major = 1.0f;
		}
	}
	else {
		velocitat_satelit -= gravetat;  // Aplicar gravetat
		semi_eix_major -= 0.001f;  // Decrementar semi-eix major per simular una �rbita m�s petita
		if (semi_eix_major < 1.0f) { // Assegurar que no baixi massa
			semi_eix_major = 1.0f;
		}
	}

	float dist_focal = semi_eix_major * excentricitat;

	// C�lcul de la posici� el�l�ptica del sat�l�lit
	float anomalia = fmod((time /10)* velocitat_satelit, 360.0f);
	float radians_anomalia = glm::radians(anomalia);

	// Calcular la dist�ncia radial en funci� de l'excentricitat
	float radi_orbital = (semi_eix_major * (1.0f - excentricitat * excentricitat)) /
		(1.0f + excentricitat * cos(radians_anomalia));

	// Posicions x i y basades en el radi i l'anomalia veritable
	float posicio_x = radi_orbital * cos(radians_anomalia) - dist_focal;
	float posicio_y = radi_orbital * sin(radians_anomalia);

	// Dibuixar l'�rbita en el pla X-Y
	dibuixar_orbita(sh_programID, MatriuVista, MatriuTG, semi_eix_major, excentricitat);

	// Calcular l'angle d'orientaci� per a la nau
	//float angle_direccio = glm::degrees(radians_anomalia) + 90.0f;  // Afegim 90 graus per ajustar la orientaci�
	std::cout << "Time =>" << time << std::endl;
	std::cout << "velocitat_satelit =>" << velocitat_satelit << std::endl;
	std::cout << "Posicio_x =>" << posicio_x << std::endl;
	std::cout << "Posicio_y =>" << posicio_y << std::endl;
	if (!(posicio_x * posicio_x + posicio_y * posicio_y < radi_planeta * radi_planeta)) {
		// Dibuixar el sat�l�lit amb rotaci� per apuntar cap a la direcci� del moviment
		//ModelMatrix = glm::rotate(MatriuTG, radians(time * 15.0f), vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(MatriuTG, vec3(posicio_x, posicio_y, 0.0f));  // Mant� Z = 0
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(180.0f), vec3(1.0f, 0.0f, 0.0f));  // Rotar al voltant de l'eix Z
		ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 1.0f));  // Escalament

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLUT_CYLINDER);  // Dibuixar el sat�l�lit
		std::cout << "FORA PLANETA" << std::endl;
	}else{
		std::cout << "DINS PLANETA" << std::endl;
	}

}


void donut_face(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time)
{
	CColor col_object = { 1.0,1.0,1.0,1.0 };
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	objecte_t(sh_programID, MatriuVista, MatriuTG, sw_mat);

	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

	// donut
	col_object = { 0.0,1.0,0.0,1.0 };
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
	// generar forma
	ModelMatrix = glm::translate(inverse(MatriuVista), vec3(0.0f, 0.0f, -0.1f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(time*90.0f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.001f, 0.001f, 0.001f));

	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	draw_TriEBO_Object(GLUT_TORUS); //gluSphere(0.5, 20, 20);

}
void nau_face(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time)
{
	donut_face(sh_programID, MatriuVista, MatriuTG, sw_mat, time);

	// SPACESHIP
	CColor col_object = { 0.0,1.0,1.0,1.0 };
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

	// generar forma
	ModelMatrix = glm::translate(MatriuTG, vec3(3.0f, 0.0f, 3.0f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(time*15.0f), vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 1.0f));

	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	draw_TriEBO_Object(GLUT_TETRAHEDRON);
}


// OBJECTE ARC
void arc(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5])
{	CColor col_object = { 0.0,0.0,0.0,1.0 };
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

// Definir VAO del Cub
	//glutSolidCube_VAO(1.0);

// Pota Esquerra
	//glPushMatrix();
	  //glTranslated(0.0, 0.0, 2.5);
	  //glScaled(1.0, 1.0, 5.0);
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 2.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 5.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE); // drawSolidCube();	//  glutSolidCube(1.0);
	//glPopMatrix();

// Pota Dreta
	//glPushMatrix();
	//glTranslated(0.0, 5.0, 2.5);
	//glScaled(1.0, 1.0, 5.0);
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 5.0f, 2.5f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 5.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE); //drawSolidCube();	//  glutSolidCube(1.0);
	//glPopMatrix();

// Travesser
	//glPushMatrix();
	  //glTranslated(0.0, 2.5, 5.5);
	  //glRotated(90.0, 1.0, 0.0, 0.0);
	  //glScaled(1.0, 1.0, 6.0);
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 2.5f, 5.5f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(90.f),vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 6.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE);  //drawSolidCube();	//  glutSolidCube(1.0);
	//glPopMatrix();

// Eliminar VAO del Cub
	//deleteVAO(GLUT_CUBE);

// Esfera
	col_object.r = 0.0;		col_object.g = 1.0;		col_object.b = 1.0;		col_object.a = 1.0;	// Color blau clar
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
	//glPushMatrix();
	  //glTranslated(0.0, 5.0, 6.5);
    ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 5.0f, 6.5f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE); //gluSphere(0.5, 20, 20);
	//glPopMatrix();

// Tetera
	col_object.r = 1.0;		col_object.g = 1.0;		col_object.b = 0.0;		col_object.a = 1.0;	// Color groc
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
	//glPushMatrix();
	  //glTranslated(0.0, 0.0, 6.0);
	  //glRotated(-90.0, 0.0, 0.0, 1.0);
	  //glRotated(90.0, 1.0, 0.0, 0.0);
	  //glScaled(0.25, 0.25, 0.25);
	ModelMatrix = glm::translate(MatriuTG, vec3(0.0f, 0.0f, 6.0f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(0.25f, 0.25f, 0.25f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	// Pas NormalMatrix a shader
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriVAO_Object(GLUT_TEAPOT); //glutSolidTeapot(1.0);
	//glPopMatrix();
}


// Mar amb ondulacions
CVAO loadSea_VAO(CColor colorM)
{
	int i, j, step, it1, it2;
	double angle, delay, Nx;
	glm::mat4 ModelMatrix(1.0), NormalMatrix(1.0);

// VAO
	GLuint vaoId = 0; GLuint vboId = 0;
	CVAO seaVAO = { 0,0,0,0,0 };
	seaVAO.vaoId = 0;	seaVAO.vboId = 0;	seaVAO.nVertexs = 0;	seaVAO.eboId = 0; seaVAO.nIndices = 0;
	std::vector <double> vertices, normals, colors, textures;	// Definici� vectors din�mics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);	textures.resize(0);			// Reinicialitzar vectors

// Aigua amb ondulacions simulades a partir de normals sinusoidals
	step = 10; //step = 5;
	delay = 0;
	it1 = 0;

//   SeleccionaMaterial(MAT_DEFAULT);	
	float h = 2 * PI*step / 500;
	for (j = -250; j<250 - step; j = j + step)
	{	delay = 1.0*h*it1;

		it2 = 0;
		//glColor3f(0.5f, 0.4f, 0.9f);
		for (i = -250; i<250 - step; i = i + step)
		{	//glBegin(GL_POLYGON);
			  angle = 1.0*it2*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j, 0);			// V�rtex P1
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(0.0);			textures.push_back(0.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1.0)*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j, 0);		// V�rtex P2
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(0.0);										// Vector Textures
			  vertices.push_back(i+step);		vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1.0)*h * 15;
			  Nx = -cos(angle);
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j + step, 0);// V�rtex P3
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(Nx);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i+step);		vertices.push_back(j+step);		vertices.push_back(0.0);		// Vector Vertices

			//glEnd();
// ----------------------- VAO
			//std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
			//draw_GL_TRIANGLES_VAO(vertices, normals, colors, textures);
			//vertices.resize(0);	normals.resize(0);	colors.resize(0);	textures.resize(0);	// Reinicialitzar vectors

			//glBegin(GL_POLYGON);
			  angle = 1.0*it2*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j, 0);			// V�rtex P1
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j);			vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*(it2 + 1)*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i + step, j + step, 0);// V�rtex P2
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(1.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i + step);		vertices.push_back(j + step);	vertices.push_back(0.0);		// Vector Vertices

			  angle = 1.0*it2*h * 15;
			  //glNormal3f(-cos(angle), 0, 1);
			  //glVertex3f(i, j + step, 0);		// V�rtex P3
			  colors.push_back(colorM.r);		colors.push_back(colorM.g);		colors.push_back(colorM.b);		colors.push_back(colorM.a);  // Vector Colors
			  normals.push_back(-cos(angle));	normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
			  textures.push_back(0.0);			textures.push_back(1.0);										// Vector Textures
			  vertices.push_back(i);			vertices.push_back(j + step);		vertices.push_back(0.0);	// Vector Vertices

			//glEnd();

			it2++;
		}
		it1++;
	}
// ----------------------- VAO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	//draw_GL_TRIANGLES_VAO(vertices, normals, colors, textures);
	// 
// Creaci� d'un VAO i un VBO i c�rrega de la geometria. Guardar identificador VAO identificador VBO a struct CVAO.
	seaVAO = load_TRIANGLES_VAO(vertices, normals, colors, textures);
	//seaVAO.vaoId = vaoId;
	//seaVAO.vboId = vboId;

	seaVAO.nVertexs = (int)nv / 3;
	return seaVAO;
}


// OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------

// Objecte TIE
void tie(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{	Motor(shaderId,MatriuVista,MatriuTG, sw_mat);
	Alas(shaderId, MatriuVista, MatriuTG, sw_mat);
	Canon(shaderId, MatriuVista, MatriuTG, sw_mat);
	Cuerpo(shaderId, MatriuVista, MatriuTG, sw_mat);
	Cabina(shaderId, MatriuVista, MatriuTG, sw_mat);
};

void Alas(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{
// Matrius Transformaci�
	glm::mat4 TransMatrix(1.0), ModelMatrix(1.0), NormalMatrix(1.0);
	CColor col_object = { 0.0,0.0,0.0,1.0 };
	
	draw_TriEBO_Object(GLU_DISK); //int nvertD = gluDisk_VAO(0.0f, 5.0f, 6, 1);

// Ala 1 Parte central
//Parte Exterior
	//glPushMatrix();
	  //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	  col_object.r = 1.0;	col_object.g = 1.0;		col_object.b = 1.0;	 col_object.a = 1.0;
	  SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	  //glTranslatef(25.25f, 0.0f, 0.0f);
	  //glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScaled(10.0f, 10.0f, 5.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(25.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix,radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  
	  draw_TriEBO_Object(GLU_CYLINDER);	//gluCylinder(5.0f, 5.0f, 0.5f, 6, 1);
	//glPopMatrix();

	//Tapas
	//glPushMatrix();
//	  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	  //glTranslatef(25.25f, 0.0f, 0.0f);
	  //glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScaled(10.0f, 10.0f, 5.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(25.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); // drawgluDisk(nvertD);
	//glPopMatrix();

	//glPushMatrix();
//	  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	  //glTranslatef(27.75f, 0.0f, 0.0f);
	  //glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScaled(10.0f, 10.0f, 5.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(27.75f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); // drawgluDisk(nvertD);
	//glPopMatrix();

//Parte Interior
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  SetColor4d(0.0, 0.0, 0.0, 1.0);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	  col_object.r = 0.0;	col_object.g = 0.0;		col_object.b = 0.0;	 col_object.a = 1.0;
	  SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	  //glTranslated(25.25f, 0.0f, 0.0f);
	  //glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScaled(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(25.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  draw_TriEBO_Object(GLUT_USER1); // gluCylinder(5.0f, 5.0f, 2.0f, 6, 1);
	//glPopMatrix();

//Tapas
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //glTranslatef(25.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(25.75f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); //drawgluDisk(nvertD);
	//glPopMatrix();

	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //glTranslatef(29.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(29.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); //drawgluDisk(nvertD);
	//glPopMatrix();

//Decoracion Exterior
	int j;
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //glTranslatef(26.5f, 0.0f, 0.0f);
	  //glScalef(15.75f, 13.75f, 13.75f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(26.5f, 0.0f, 0.0f));
	  TransMatrix = glm::scale(TransMatrix, vec3(15.75f, 13.75f, 13.75f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(30.f), vec3(0.0f, 0.0f, 1.0f));
	  for (j = 0; j<3; j = j + 1)
		{	//glRotatef(60, 0, 0, 1);
			TransMatrix = glm::rotate(TransMatrix, radians(60.f), vec3(0.0f, 0.0f, 1.0f));
			//glPushMatrix();
			   //glScalef(12.7f * 0.583f, 0.1f, 0.3f);
				ModelMatrix = glm::scale(TransMatrix, vec3(12.7f * 0.583f, 0.1f, 0.3f));
				// Pas ModelView Matrix a shader
				glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
				NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
				// Pas NormalMatrix a shader
				glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
				draw_TriEBO_Object(GLUT_CUBE); //glutSolidCube(1.0f);
			//glPopMatrix();
		}
	//glPopMatrix();

	int u;
	//glPushMatrix();
	//glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	TransMatrix = MatriuTG;
	for (u = 0; u < 6; u = u + 1)
	{	//glRotated(60, 1.0, 0.0, 0.0);
		TransMatrix = glm::rotate(TransMatrix, radians(60.f), vec3(1.0f, 0.0f, 0.0f));
		//glPushMatrix();
			//glTranslatef(26.5f, 0.0f, 43.25f);
			//glRotatef(90, 0.0, 0.0, 1.0);
			//glScalef(10 * 5.155f, 5.0f, 3.0f);
			ModelMatrix = glm::translate(TransMatrix, vec3(26.5f, 0.0f, 43.25f));
			ModelMatrix = glm::rotate(ModelMatrix, radians(90.f), vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::scale(ModelMatrix, vec3(10 * 5.155f, 5.0f, 3.0f));
			// Pas ModelView Matrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
			NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
			// Pas NormalMatrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
			draw_TriEBO_Object(GLUT_CUBE); //glutSolidCube(1.0f);
		//glPopMatrix();
	}
	//glPopMatrix();


//Ala 2 Parte central 
//Parte Exterior
	//glPushMatrix();
	  //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	  SetColor4d(1.0, 1.0, 1.0, 1.0);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	  col_object.r = 1.0;	col_object.g = 1.0;		col_object.b = 1.0;	 col_object.a = 1.0;
	  SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	  //glTranslated(-27.75f, 0.0f, 0.0f);
	  //glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScaled(10.0, 10.0, 5.0);
	  TransMatrix = glm::translate(MatriuTG, vec3(-27.75f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  draw_TriEBO_Object(GLU_CYLINDER); //gluCylinder(5.0f, 5.0f, 0.5f, 6, 1);
	//glPopMatrix();

//Tapas
	//glPushMatrix();
	  //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	  //glTranslatef(-27.75f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(10.0f, 10.0f, 5.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-27.75f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); //drawgluDisk(nvertD);
	//glPopMatrix();

	//glPushMatrix();
	  //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	  //glTranslatef(-25.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(10.0f, 10.0f, 5.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-25.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(10.0f, 10.0f, 5.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); //drawgluDisk(nvertD);
	//glPopMatrix();

//Parte Interior
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  // Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	  col_object.r = 0.0;	col_object.g = 0.0;		col_object.b = 0.0;	 col_object.a = 1.0;
	  SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	  //glTranslatef(-29.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-29.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  draw_TriEBO_Object(GLUT_USER1); // gluCylinder(5.0f, 5.0f, 2.0f, 6, 1);
	//glPopMatrix();

//Tapas
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
 	  //glTranslatef(-29.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-29.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK);  //drawgluDisk(nvertD);
	//glPopMatrix();

	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //SetColor4d(0.0, 0.0, 0.0, 0.0);
	  //glTranslatef(-25.25f, 0.0f, 0.0f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glScalef(2.0f, 2.0f, 2.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-25.25f, 0.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.0f));
	  // Pas ModelView Matrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	  NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	  // Pas NormalMatrix a shader
	  glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	  //gluDisk(0.0f, 5.0f, 6, 1);
	  draw_TriEBO_Object(GLU_DISK); //drawgluDisk(nvertD);
	//glPopMatrix();

//Decoracion Exterior
	int w;
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //SetColor4d(0.0, 0.0, 0.0, 0.0);
	  //glTranslatef(-26.5f, 0.0f, 0.0f);
	  //glScalef(15.75f, 13.75f, 13.75f);
	  //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  //glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	  TransMatrix = glm::translate(MatriuTG, vec3(-26.5f, 0.0f, 0.0f));
	  TransMatrix = glm::scale(TransMatrix, vec3(15.75f, 13.75f, 13.75f));
	  TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	  TransMatrix = glm::rotate(TransMatrix, radians(30.f), vec3(0.0f, 0.0f, 1.0f));
	  for (w = 0; w<3; w = w + 1)
	  {	//glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
		TransMatrix = glm::rotate(TransMatrix, radians(60.f), vec3(0.0f, 0.0f, 1.0f));
		//glPushMatrix();
			//glScalef(12.7f * 0.583f, 0.1f, 0.3f);
			ModelMatrix = glm::scale(TransMatrix, vec3(12.7f * 0.583f, 0.1f, 0.3f));
			// Pas ModelView Matrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
			NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
			// Pas NormalMatrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
			draw_TriEBO_Object(GLUT_CUBE); //glutSolidCube(1.0f);
		//glPopMatrix();
	}
	//glPopMatrix();

	int h;
	//glPushMatrix();
	  //glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	  //SetColor4d(0.0, 0.0, 0.0, 0.0);
	  TransMatrix = MatriuTG;
	  for (h = 0; h < 6; h = h + 1)
	  {	//glRotated(60, 1.0, 0.0, 0.0);
		TransMatrix = glm::rotate(TransMatrix, radians(60.f), vec3(1.0f, 0.0f, 0.0f));
		//glPushMatrix();
			//glTranslatef(-26.5f, 0.0f, 43.25f);
			//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			//glScalef(10 * 5.155f, 5.0f, 3.0f);
			ModelMatrix = glm::translate(TransMatrix, vec3(-26.5f, 0.0f, 43.25f));
			ModelMatrix = glm::rotate(ModelMatrix, radians(90.f), vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::scale(ModelMatrix, vec3(10 * 5.155f, 5.0f, 3.0f));
			// Pas ModelView Matrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
			NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
			// Pas NormalMatrix a shader
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
			draw_TriEBO_Object(GLUT_CUBE); //glutSolidCube(1.0f);
		//glPopMatrix();
	  }
	//glPopMatrix();
	  //deleteVAO(GLU_DISK);
};


void Motor(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{
// Matrius  
	glm::mat4 TransMatrix(1.0), ModelMatrix(1.0), NormalMatrix(1.0);
	CColor col_object = { 0.0,0.0,0.0,1.0 };

//Helices Motor
	int j;
	//glPushMatrix();
	  //glColor4f(0.58f, 0.58f, 0.58f, 0.0f);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 0.58;	col_object.g = 0.58;	col_object.b = 0.58;	 col_object.a = 1.0;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glTranslatef(0.0f, -18.0f, 0.0f);
	//glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	//glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(45, 0, 0, 1);
	TransMatrix = glm::translate(MatriuTG, vec3(0.0f, -18.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(45.f), vec3(0.0f, 0.0f, 1.0f));
	for (j = 0; j<6; j = j + 1)
	{	//glRotatef(30, 0, 0, 1);
	TransMatrix = glm::rotate(TransMatrix, radians(30.f), vec3(0.0f, 0.0f, 1.0f));
	//glPushMatrix();
	//glScalef(12 * 0.583f, 0.1f, 0.3f);
	ModelMatrix = glm::scale(TransMatrix, vec3(12 * 0.583f, 0.1f, 0.3f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_CUBE); //glutSolidCube(1.0f);
	//glPopMatrix();
	}
	//glPopMatrix();

//Soporte Motor
	//glPushMatrix();
	//glColor4f(0.28f, 0.28f, 0.28f, 0.0f);
	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 0.28;	col_object.g = 0.28;	col_object.b = 0.28;	 col_object.a = 1.0;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glTranslatef(0.0f, -18.0f, 0.0f);
	//glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	//glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	TransMatrix = glm::translate(MatriuTG, vec3(0.0f, -18.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_TORUS); //glutSolidTorus(1.0, 5.0, 20, 20);
	//glPopMatrix();
};

void Canon(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{
// Matrius Transformaci�
	glm::mat4 TransMatrix(1.0), ModelMatrix(1.0), NormalMatrix(1.0);
	CColor col_object = { 0.0,0.0,0.0,1.0 };

//Ca�ones

// Salida ca�on 1
	//glPushMatrix();
	//glColor4d(0.28, 0.28, 0.28, 0.0);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 0.28;	col_object.g = 0.28;	col_object.b = 0.28;	 col_object.a = 1.0;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glTranslated(5.0, 8.0, -10.0);
	//glRotated(-90.0, 1.0, 0.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(5.0f, 8.0f, -10.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER2); //gluCylinder(1.0f, 0.5f, 5.0f, 60, 1);
	//glPopMatrix();

// Salida ca�on 2
	//glPushMatrix();
	//glColor4d(0.28, 0.28, 0.28, 0.0);
	//glTranslated(-5.0, 8.0, -10.0);
	//glRotated(-90.0, 1.0, 0.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(-5.0f, 8.0f, -10.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER2); // gluCylinder(1.0f, 0.5f, 5.0f, 60, 1);
	//glPopMatrix();

// Ca�on 1
	//glPushMatrix();
		//glColor4d(0.58, 0.58, 0.58, 0.0);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 0.58;	col_object.g = 0.58;		col_object.b = 0.58;	 col_object.a = 1.0;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glTranslated(5.0, 10.0, -10.0);
	//glRotated(-90.0, 1.0, 0.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(5.0f, 10.0f, -10.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER3); // gluCylinder(0.35f, 0.35f, 5.0f, 80, 1);
	//glPopMatrix();

//Ca�on 2
	//glPushMatrix();
	//glColor4d(0.58, 0.58, 0.58, 1.0);
 	//glTranslated(-5.0, 10.0, -10.0);
	//glRotated(-90.0, 1.0, 0.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(-5.0f, 10.0f, -10.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER3); // gluCylinder(0.35f, 0.35f, 5.0f, 80, 1);
	//glPopMatrix();
}

void Cuerpo(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{
// Matrius Transformaci�
	glm::mat4 TransMatrix(1.0), ModelMatrix(1.0), NormalMatrix(1.0);
	CColor col_object = { 0.0,0.0,0.0,1.0 };

// Activar transpar�ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//Sujeccion de las Alas

//Lado2
	//glPushMatrix();
	//glColor4d(0.16, 0.16, 0.16, 1.0);
// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 0.16;	col_object.g = 0.16;	col_object.b = 0.16;	 col_object.a = 0.5;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glRotated(-90.0, 0.0, 1.0, 0.0);
	//glRotated(90.0, 0.0, 0.0, 1.0);
	//glScaled(2.0, 2.0, 2.5);
	TransMatrix = glm::rotate(MatriuTG, radians(-90.f), vec3(0.0f, 1.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.5f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER4); // gluCylinder(4.0f, 2.0f, 10.25f, 40, 1);
	//glPopMatrix();

//X2
	//glPushMatrix();
	//glColor4d(0.16, 0.16, 0.16, 1.0);
	//glTranslated(-25.0, 0.0, 0.0);
	//glRotated(90.0, 0.0, 1.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(-25.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_TORUS); // glutSolidTorus(1.0, 5.0, 20, 20);
	//glPopMatrix();

//Lado 1
	//glPushMatrix();
	//glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	//SetColor4d(0.16, 0.16, 0.16, 1.0);
	//glRotated(90.0, 0.0, 1.0, 0.0);
	//glRotated(90.0, 0.0, 0.0, 1.0);
	//glScaled(2.0, 2.0, 2.5);
	TransMatrix = glm::rotate(MatriuTG, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(TransMatrix, vec3(2.0f, 2.0f, 2.5f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER4); // gluCylinder(4.0f, 2.0f, 10.25f, 40, 1);
	//glPopMatrix();

//X1
	//glPushMatrix();
	//glColor4d(0.16, 0.16, 0.16, 1.0);
	//SetColor4d(0.16, 0.16, 0.16, 1.0);
	//glTranslated(25.25, 0.0, 0.0);
	//glRotated(90.0, 0.0, 1.0, 0.0);
	TransMatrix = glm::translate(MatriuTG, vec3(25.25f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_TORUS); //glutSolidTorus(1.0, 5.0, 20, 20);
	//glPopMatrix();

//Cuerpo
	//glPushMatrix();
	//glColor4d(0.16, 0.16, 0.16, 1.0);
	//SetColor4d(0.16, 0.16, 0.16, 1.0);
	//glScaled(1.75f, 1.75f, 1.5f);
	ModelMatrix = glm::scale(MatriuTG, vec3(1.75f, 1.75f, 1.5f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLU_SPHERE); //gluSphere(10.0f, 80, 80);
	//glPopMatrix();

 // Desactivar transpar�ncia
	glDisable(GL_BLEND);
}

void Cabina(GLint shaderId, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[4])
{
// Matrius Transformaci�
	glm::mat4 TransMatrix(1.0), ModelMatrix(1.0), NormalMatrix(1.0);
	CColor col_object = { 0.0,0.0,0.0,1.0 };

// Activar transpar�ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Tapa Cabina
	//glPushMatrix();
	//glColor4d(1.0, 0.058, 0.058, 0.5);
	// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
	col_object.r = 1.0;	col_object.g = 0.058;	col_object.b = 0.058;	 col_object.a = 0.5;
	SeleccionaColorMaterial(shaderId, col_object, sw_mat);
	//glTranslated(0.0, 19.45, 0.0);
	//glRotated(-90.0, 0.0, 0.0, 1.0);
	//glRotated(90.0, 0.0, 1.0, 0.0);
	//glScaled(1.75, 1.75, 1.75);
	TransMatrix = glm::translate(MatriuTG, vec3(0.0f, 19.45f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::scale(TransMatrix, vec3(1.75f, 1.75f, 1.75f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER6); //gluDisk(0.0f, 1.5f, 8, 1);
	//glPopMatrix();

// Cristal Cabina
	//glPushMatrix();
	//glColor4d(1.0, 0.058, 0.058, 0.5);
	//glTranslated(0.0f, 19.45f, 0.0f);
	//glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	//glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	//glScaled(1.75f, 1.75f, 1.75f);
	TransMatrix = glm::translate(MatriuTG, vec3(0.0f, 19.45f, 0.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(-90.f), vec3(0.0f, 0.0f, 1.0f));
	TransMatrix = glm::rotate(TransMatrix, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::scale(TransMatrix, vec3(1.75f, 1.75f, 1.75f));
	// Pas ModelView Matrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	// Pas NormalMatrix a shader
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	draw_TriEBO_Object(GLUT_USER5); //gluCylinder(1.5f, 4.5f, 2.0f, 8, 1);
	//glPopMatrix();

// Desactivar transpar�ncia
	glDisable(GL_BLEND);
}
// FI OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------
