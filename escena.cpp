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
#include <random>

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
	glm::mat4 MatriuVista, glm::mat4 MatriuTG, float time, bool propulsat, Nau& nau, COBJModel* TestOBJ, COBJModel* CombustibleOBJ, COBJModel* EstacioOBJ)
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
	if (textur) {
		glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
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

		/*MAV MODIFIED*/
	case OBJECTE_T:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		objecte_t(sh_programID, MatriuVista, MatriuTG, sw_mat);

		break;
		/*MAV MODIFIED*/
	case SPUTNIK:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material pel color de l'objecte.
		sputnik(sh_programID, MatriuVista, MatriuTG, sw_mat, time, propulsat);
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
		planeta(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, nau);
		asteroide(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, TestOBJ, col_object, nau);
		asteroidesCinturo(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, TestOBJ, col_object);
		objectes(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, CombustibleOBJ, col_object);
		estacions(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, EstacioOBJ, col_object);
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

		////////////////////////////////////////////nau///////////////////////////////////////////////////////
		/*
		// Aplica la traslaci�n
		//Julia: falta moure la nau a fora del sol

		ModelMatrix = glm::translate(inverse(MatriuVista), vec3(0.0f, -0.02f, -0.1f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.005f, 0.005f, 0.005)); // Ejemplo de escala
		ModelMatrix = glm::rotate(ModelMatrix, radians(7.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		// Pasar la ModelMatrix actualizada al shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

		// Calcular y pasar la NormalMatrix al shader
		NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Configuraci�n del material y dibujo del objeto
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		objecteOBJ->draw_TriVAO_OBJ(sh_programID);
		*/
		d_nau(sh_programID, MatriuVista, MatriuTG, sw_mat, nau);

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

		// Dibuix de la resta d'objectes
	default:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		break;
	}

	// Enviar les comandes gr�fiques a pantalla
	//	glFlush();
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

void inicialitzaDades()
{
	for (int i = 1; i < PLANETES.size(); i++)
	{
		PLANETES[i].setSemieixMajor(SEMIEIXOS_MAJORS[i - 1]);
		PLANETES[i].setExcentricitat(EXCENTRICITATS[i - 1]);
		PLANETES[i].setLongitudNodeAscendent(LONG_NODES_ASC[i - 1] * DEG_A_RAD);
		PLANETES[i].setInclinacio(INCLINACIONS[i - 1] * DEG_A_RAD);
		PLANETES[i].setPeriapsis(PERIAPSIS[i - 1] * DEG_A_RAD);
		// ISMAEL TRAJ ORBITA

		if (i > 4)
			PLANETES[i].setPuntsOrbita(BASE_POINTS * i * 4);
		else
			PLANETES[i].setPuntsOrbita(BASE_POINTS * i);
	}
}


void processaRotacions()
{
	// Calculem les coordenades dels eixos pels quals rotar� el planeta sobre ell mateix
	// 
	// LCR - s'ha afegit velocitat de rotaci� de la lluna (posicio 9)
	float velocitatsRotacio[10] = { 5.0f, 10.0f, 8.0f, 6.0f, 12.0f, 4.0f, 9.0f, 7.0f, 11.0f, 0.27f };

	for (int i = 0; i < PLANETES.size(); ++i) {
		float inclinacioRadians = glm::radians(ANGLES_INCLINACIO_ROTACIO[i]);
		glm::vec3 eixosRotacio = glm::vec3(
			0.0f,
			sin(inclinacioRadians),
			cos(inclinacioRadians)
		);

		// Assignem eix de rotaci� i direcci� de rotaci�
		PLANETES[i].setEixosRotacioPlaneta(eixosRotacio);
		PLANETES[i].setDireccioRotacio(DIRECCIONS_ROTACIO[i]);
		PLANETES[i].setVelocitatRotacio(velocitatsRotacio[i]);
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
		// TEMPORAL: ISMAEL
		if (i == 0)
			PLANETES[i].setRadi(RADIS[i] * (1.0 / 1.496e11));
		else
			PLANETES[i].setRadi(RADIS[i] * (1.0 / 1.496e11) * 2.1);

		// Massa planeta
		double massa = MASSES[i] * ESCALA_MASSA;
		PLANETES[i].setMassa(massa);

		double mu = G * PLANETES[0].getMassa(); // Par�metre gravitacional
		// Sol no es mou (valors per defecte del constructor, es pot eliminar)
		if (i == 0)
		{
			PLANETES[i].setPosition(glm::vec3(0.0f));
			PLANETES[i].setVelocitat(glm::vec3(0.0f));
		}
		else
		{
				// Elements orbitals keplerians
				double a = PLANETES[i].getSemieixMajor() * AU_IN_METERS * ESCALA_DISTANCIA;
				double e = PLANETES[i].getExcentricitat();
				double inclinacio = PLANETES[i].getInclinacio() * DEG_A_RAD;
				double longNodeAsc = PLANETES[i].getLongitudNodeAscendent() * DEG_A_RAD;
				double periapsis = PLANETES[i].getPeriapsis() * DEG_A_RAD;
				// True anomaly
				// CANVIAR: Modificat per repartir els planetes
				//double nu = 2.0 * PI * (i - 1) / (PLANETES.size() - 1);
				double nu = 0.0;

				// Distancia del planeta al sol
				double r = a * (1 - e * e) / (1 + e * cos(nu));

				// Posici� en el pla orbital (2D)
				double x_plaOrbital = r * cos(nu);
				double y_plaOrbital = r * sin(nu);
				double z_plaOrbital = 0.0;

				// Moment angular relatiu espec�fic
				double h = sqrt(mu * a * (1 - e * e));

				// Velocitat en el pla orbital
				// Ens diu cap a on i que tant r�pid es mou el planeta en la seva �rbita
				double vx_plaOrbital = -(mu / h) * sin(nu);
				double vy_plaOrbital = (mu / h) * (e + cos(nu));
				double vz_plaOrbital = 0.0;

				// Vector de posici� i velocitat en el pla orbital
				glm::dvec3 posicio_plaOrbital(x_plaOrbital, y_plaOrbital, z_plaOrbital);
				glm::dvec3 velocitat_plaOrbital(vx_plaOrbital, vy_plaOrbital, vz_plaOrbital);

				// Matrius de rotaci� per passar del pla orbital a l'espai 3D
				// S'inclinen i es giren les �rbites per passar del pla al 3D 
				glm::mat3 R_periapsis = glm::mat3(glm::rotate(glm::mat4(1.0), (float)periapsis, glm::vec3(0.0, 0.0, 1.0)));
				glm::mat3 R_inclinacio = glm::mat3(glm::rotate(glm::mat4(1.0), (float)inclinacio, glm::vec3(1.0, 0.0, 0.0)));
				glm::mat3 R_longNodeAsc = glm::mat3(glm::rotate(glm::mat4(1.0), (float)longNodeAsc, glm::vec3(0.0, 0.0, 1.0)));

				// Combinem totes les rotacions
				glm::mat3 R = R_periapsis * R_inclinacio * R_longNodeAsc;

				// Transformem les posicions i velocitats del pla orbital a espai 3D
				glm::dvec3 posicio_3D = R * posicio_plaOrbital;
				glm::dvec3 velocitat_3D = R * velocitat_plaOrbital;

				PLANETES[i].setPosition(glm::vec3(posicio_3D));
				PLANETES[i].setVelocitat(velocitat_3D);
			
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
		//std::cout << id << std::endl;
		planeta.setTextureID(id);
		//std::cout << planeta.getTextureID() << std::endl;
	}
}

void processaPlanetes()
{
	inicialitzaDades();
	processaRotacions();
	processaFisica();
	processaTextures();
}

void updateSatelitsAnalytical(double time, Planeta& planeta)
{
	std::vector<Planeta>& moons = planeta.moons;
	if (moons.empty()) return;

	std::string pname = planeta.getName();

	double baseRadius = 0.0;
	double radiusIncrement = 0.1;
	double orbitalPeriod = 0.0;

	if (pname == "Terra") {
		baseRadius = 6084400e3;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else if (pname == "Mart") {
		baseRadius = 6084400e3;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else if (pname == "Júpiter") {
		double avgRadius = 5.9911e10;
		baseRadius = avgRadius;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else if (pname == "Saturn") {
		double avgRadius = 5.9911e10;
		baseRadius = avgRadius;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else if (pname == "Urà") {
		double avgRadius = 2.9911e10;
		baseRadius = avgRadius;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else if (pname == "Neptú") {
		double avgRadius = 2.9911e10;
		baseRadius = avgRadius;
		orbitalPeriod = 67.32 * 86400.0;
	}
	else {
		baseRadius = 6084400e3;
		orbitalPeriod = 67.32 * 86400.0;
	}

	double angularSpeed = TWOPI / orbitalPeriod;
	double angle = angularSpeed * time * VELOCITAT_SIMULACIO;
	angle = fmod(angle, TWOPI);

	glm::vec3 planetPos = planeta.getPosition();

	for (size_t i = 0; i < moons.size(); ++i) {
		Planeta& moon = moons[i];

		double currentRadius = baseRadius + radiusIncrement * i * baseRadius;

		double orbitalRadius = currentRadius * (DISTANCIA_DEFAULT_TERRA / (1.0 * 1.496e11));

		double moonAngle = angle + moon.getOffsetInicial();

		double x_rel = orbitalRadius * cos(moonAngle);
		double y_rel = orbitalRadius * sin(moonAngle);
		double z_rel = 0.0;

		float inclination = moon.getAngleRotacio();
		float inclinationRad = glm::radians(inclination);

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),
			inclinationRad,
			glm::vec3(1.0f, 0.0f, 0.0f));

		glm::vec4 pos4D(x_rel, y_rel, z_rel, 1.0f);
		pos4D = rotationMatrix * pos4D;

		glm::vec3 rotatedPos = glm::vec3(pos4D);

		glm::vec3 moonPosition = planetPos + rotatedPos;
		moon.setPosition(moonPosition);

		moon.agregarPosicionHistorica(moonPosition);
	}
}


void updatePlanetesAnalytical(double time)
{
	const double G = 6.67430e-11 * pow(ESCALA_DISTANCIA, 3);
	const Planeta& sol = PLANETES[0];

	for (int i = 1; i < PLANETES.size(); ++i) // Comenzamos desde 1 para omitir el Sol
	{
		Planeta& planeta = PLANETES[i];

		updateSatelitsAnalytical(time, planeta);

		// Obtener parámetros orbitales
		double a = planeta.getSemieixMajor() * AU_IN_METERS * ESCALA_DISTANCIA; // Semieje mayor en metros escalados
		double e = planeta.getExcentricitat(); // Excentricidad
		double inclinacio = planeta.getInclinacio() * DEG_A_RAD; // Inclinación en radianes
		double longNodeAsc = planeta.getLongitudNodeAscendent() * DEG_A_RAD; // Longitud del nodo ascendente en radianes
		double periapsis = planeta.getPeriapsis() * DEG_A_RAD; // Argumento del periapsis en radianes

		// Parámetro gravitacional estándar (mu)
		double mu = G * sol.getMassa();

		// Calcular el movimiento medio n = sqrt(mu / a^3)
		double n = sqrt(mu / (a * a * a));

		// Calcular la anomalía media M = M0 + n * t
		double M0 = 0.0; // Anomalía media en t0 (puede ser 0)
		double M = M0 + n * time * VELOCITAT_SIMULACIO;

		// Normalizar M al rango [0, 2π]
		M = fmod(M, TWOPI);

		// Resolver la ecuación de Kepler para obtener la anomalía excéntrica E
		double E = M; // Suposición inicial
		const int maxIter = 10;
		for (int iter = 0; iter < maxIter; ++iter)
		{
			double deltaE = (M - E + e * sin(E)) / (1 - e * cos(E));
			E += deltaE;
			if (fabs(deltaE) < 1e-6) // Tolerancia
				break;
		}

		// Calcular la anomalía verdadera ν a partir de E
		double sinV = (sqrt(1 - e * e) * sin(E)) / (1 - e * cos(E));
		double cosV = (cos(E) - e) / (1 - e * cos(E));
		double nu = atan2(sinV, cosV);

		// Calcular la distancia radial r
		double r = a * (1 - e * cos(E));

		// Posición en el plano orbital
		double x_orb = r * cos(nu);
		double y_orb = r * sin(nu);
		double z_orb = 0.0;

		// Matrices de rotación para transformar del plano orbital al espacio 3D
		glm::mat3 R_periapsis = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)periapsis, glm::vec3(0.0, 0.0, 1.0)));
		glm::mat3 R_inclinacio = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)inclinacio, glm::vec3(1.0, 0.0, 0.0)));
		glm::mat3 R_longNodeAsc = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)longNodeAsc, glm::vec3(0.0, 0.0, 1.0)));
		glm::mat3 R = R_longNodeAsc * R_inclinacio * R_periapsis;

		// Transformar a coordenadas espaciales
		glm::dvec3 posicion_orb(x_orb, y_orb, z_orb);
		glm::dvec3 posicion_3D = R * posicion_orb;

		// Establecer la posición del planeta
		planeta.setPosition(glm::vec3(posicion_3D));
	}
}


void drawOrbitPath(Planeta& planeta) {
	// Define el número de puntos para la órbita
	const int numPoints = 360;
	double a = planeta.getSemieixMajor() * AU_IN_METERS * ESCALA_DISTANCIA; // Semieje mayor en metros escalados
	double e = planeta.getExcentricitat(); // Excentricidad
	double inclinacio = planeta.getInclinacio() * DEG_A_RAD; // Inclinación en radianes
	double longNodeAsc = planeta.getLongitudNodeAscendent() * DEG_A_RAD; // Longitud del nodo ascendente en radianes
	double periapsis = planeta.getPeriapsis() * DEG_A_RAD; // Argumento del periapsis en radianes

	// Matrices de rotación para transformar la órbita del plano orbital al espacio 3D
	glm::mat3 R_periapsis = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)periapsis, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat3 R_inclinacio = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)inclinacio, glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat3 R_longNodeAsc = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)longNodeAsc, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat3 R = R_longNodeAsc * R_inclinacio * R_periapsis;

	// Comenzar a dibujar la órbita
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numPoints; ++i) {
		// Anomalía verdadera (ángulo alrededor de la órbita)
		double nu = 2.0 * PI * i / numPoints;

		// Radio para este punto en la órbita
		double r = a * (1 - e * e) / (1 + e * cos(nu));

		// Posición en el plano orbital
		double x_orb = r * cos(nu);
		double y_orb = r * sin(nu);
		double z_orb = 0.0;

		// Transformar del plano orbital al espacio 3D
		glm::dvec3 posicion_orb(x_orb, y_orb, z_orb);
		glm::dvec3 posicion_3D = R * posicion_orb;

		// Dibujar el punto en la órbita
		glVertex3d(posicion_3D.x, posicion_3D.y, posicion_3D.z);
	}
	glEnd();
}

void drawHistoricalPath(std::vector<glm::vec3> posiciones) {
	size_t numPositions = posiciones.size();

	if (numPositions < 2)
		return;

	glLineWidth(1.0f);

	glEnable(GL_BLEND);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i < numPositions; ++i) {
		float alpha = static_cast<float>(i) / static_cast<float>(numPositions - 1);
		alpha = 1.0f - alpha;
		glColor4f(1.0f, 1.0f, 0.0f, alpha);

		// Dibujar el vértice
		const glm::vec3& posicion = posiciones[i];
		glVertex3f(posicion.x, posicion.y, posicion.z);
	}
	glEnd();
}

bool estaForaDelsLimits(const Asteroide& asteroide)
{
	glm::vec3 pos = asteroide.getPosition();
	float distanceSquared = glm::dot(pos, pos);
	return distanceSquared > (MAX_DISTANCIA_ASTEROIDES * MAX_DISTANCIA_ASTEROIDES);
}
/*
	Mètode per evitar que els asteroides es moguin massa lluny del punt d'origen (el sol)
	MAX_DISTANCIA_ASTEROIDES indica la màxima distancia a la que poden estar, si s'allunyen
	massa, en comptes d'eliminar-lo, tornem a utilitzar un generador aleatori per alterar les
	seves propietats i el moguem a la zona de generació d'asteroides.
*/
void resetAsteroide(Asteroide& asteroide, std::mt19937& gen)
{
	std::uniform_real_distribution<float> pos_dist(-MAX_DISTANCIA_ASTEROIDES / 2.0f, MAX_DISTANCIA_ASTEROIDES / 2.0f);
	std::uniform_real_distribution<double> vel_dist(-0.5, 0.5);
	std::uniform_real_distribution<float> radius_dist(0.5f, 1.5f);
	std::uniform_real_distribution<double> mass_dist(1.0e12, 1.0e13);

	float radius = radius_dist(gen);
	double mass = mass_dist(gen);

	glm::vec3 position(pos_dist(gen), pos_dist(gen), pos_dist(gen));
	glm::dvec3 velocity(vel_dist(gen), vel_dist(gen), vel_dist(gen));

	asteroide.setRadi(radius);
	asteroide.setMassa(mass);
	asteroide.setVelocitat(velocity);
	asteroide.setPosition(position);
	asteroide.posicionesHistoricas.clear();
}

/*
	Moviment dels asteroides
*/
void actualitzarAsteroides(double deltaTime)
{
	for (auto& asteroide : ASTEROIDES)
	{
		glm::vec3 pos = asteroide.getPosition();
		glm::dvec3 vel = asteroide.getVelocitat();
		pos += glm::vec3(vel * deltaTime);
		asteroide.setPosition(pos);
	}
}

// ISMAEL ASTEROIDES
/*
	Generació d'asteroides en posicions aleatories amb velocitats, radi i massa aleatoria
	NUM_ASTEROIDES: màxim d'asteroides
*/
void generarAsteroides()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> pos_dist(-2000.0f, 2000.0f);
	std::uniform_real_distribution<double> vel_dist(-0.5, 0.5);
	std::uniform_real_distribution<float> radius_dist(0.5f, 1.5f);
	std::uniform_real_distribution<double> mass_dist(1.0e12, 1.0e13);

	for (size_t i = 0; i < NUM_ASTEROIDES; ++i) {
		if (i == 0) {
			ASTEROIDES[i].setRadi(1.5f);
			ASTEROIDES[i].setMassa(1.0e12);
			ASTEROIDES[i].setPosition(glm::vec3(-200.0f, 50.0f, 50.0f));
			ASTEROIDES[i].setVelocitat(glm::dvec3(-5.0, 0.0, 0.0));
		}
		else if (i == 1) {
			ASTEROIDES[i].setRadi(3.5f);
			ASTEROIDES[i].setMassa(3.0e12);
			ASTEROIDES[i].setPosition(glm::vec3(200.0f, 50.0f, 50.0f));
			ASTEROIDES[i].setVelocitat(glm::dvec3(10.0, 0.0, 0.0));
		}
		else
		{


			float radius = radius_dist(gen);
			double mass = mass_dist(gen);

			glm::vec3 position(pos_dist(gen), pos_dist(gen), pos_dist(gen));
			glm::dvec3 velocity(vel_dist(gen), vel_dist(gen), vel_dist(gen));

			ASTEROIDES[i].setMassa(mass);
			ASTEROIDES[i].setRadi(radius);
			ASTEROIDES[i].setVelocitat(velocity);
			ASTEROIDES[i].setPosition(position);
		}
	}
}

glm::vec3 randomUnitVector() {
	float theta = static_cast<float>(rand()) / RAND_MAX * glm::two_pi<float>();
	float phi = acos(2.0f * static_cast<float>(rand()) / RAND_MAX - 1.0f);

	float x = sin(phi) * cos(theta);
	float y = sin(phi) * sin(theta);
	float z = cos(phi);

	return glm::vec3(x, y, z);
}

void generarAsteroidesCinturo() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * glm::pi<float>()); // Angle al voltant del cercle
	std::uniform_real_distribution<float> radius_dist(160.0f, 180.0f);               // Radi del cercle (cinturó 1)
	std::uniform_real_distribution<float> radius_dist2(1560.0f, 1580.0f);               // Radi del cercle (cinturó 2)
	std::uniform_real_distribution<float> height_dist(-8.0f, 8.0f);                // Alçada limitada en l'eix Y
	std::uniform_real_distribution<float> scale_dist(0.1f, 0.5f);                    // Escala dels asteroides
	std::uniform_real_distribution<double> mass_dist(1.0e12, 1.0e13);                // Massa dels asteroides

	//ASTEROIDESCINTURO.clear(); // Esborra els asteroides existents si n'hi ha

	for (size_t i = 0; i < NUM_ASTEROIDES_CINTURO; ++i) {
		float angle = angle_dist(gen);    // Angle en radians al voltant del cercle
		float radius = 0.0; // Distància radial des del centre
		//std::cout << NUM_ASTEROIDES_CINTURO / 2 << std::endl;
		//std::cout << i << std::endl;
		//std::cout << "  " << std::endl;
		if (i >= NUM_ASTEROIDES_CINTURO/2) {
			radius = radius_dist2(gen);
		}else{
			radius = radius_dist(gen);
		}
		float height = height_dist(gen); // Posició en l'eix vertical (Y)

		// Calcula la posició en coordenades cartesianes
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		float z = height; // Limitat a un rang estret (-10 a 10)

		// Propietats de l'asteroide
		float scale = scale_dist(gen);
		double mass = mass_dist(gen);

		ASTEROIDESCINTURO[i].setMassa(mass);
		ASTEROIDESCINTURO[i].setRadi(scale);
		ASTEROIDESCINTURO[i].setPosition(glm::vec3(x, y,z)); // Assignar posició
		ASTEROIDESCINTURO[i].setVelocitat(glm::dvec3(0.0, 0.0, 0.0)); // Velocitat inicial nul·la (per girar després)
	}
}
/*
void processaObjJoc() {
	generarDiposits();
}*/

void generarDiposits() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * PI); // Angle al voltant del cercle
	std::uniform_real_distribution<float> radius_dist(30.0f, 1250.0f);              // Radi del cercle (cinturó més gran)
	//std::uniform_real_distribution<float> height_dist(-5.0f, 5.0f);                 // Alçada limitada en l'eix Y
	std::uniform_real_distribution<float> fuel_dist(100.0f, 500.0f);                // Combustible disponible

	for (size_t i = 0; i < NUM_DIPOSITS; ++i) {
		float angle = angle_dist(gen);    // Angle en radians al voltant del cercle
		float radius = radius_dist(gen);
		//float height = height_dist(gen); // Posició en l'eix vertical (Y)

		// Calcula la posició en coordenades cartesianes
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		float z = 0.0f; // Limitat a un rang estret (-5 a 5)

		// Propietats del dipòsit
		float fuel = fuel_dist(gen);

		// Crear el dipòsit de combustible
		DIPOSITS[i].setRadi(1.0f);                     // Radi del dipòsit
		DIPOSITS[i].setPosition(glm::vec3(x, y, z));    // Assignar posició
		DIPOSITS[i].setVelocitat(glm::dvec3(0.0, 0.0, 0.0)); // Velocitat inicial nul·la
		DIPOSITS[i].setValor(fuel);               // Assignar la quantitat de combustible
	}
}

void spawnAsteroidToCollide(
	double t,
	const glm::vec3& shipPosition,
	const glm::dvec3& shipVelD
) {
	glm::vec3 shipVelocity = glm::vec3(shipVelD);

	glm::vec3 shipFuturePos = shipPosition + shipVelocity * (float)t;
	//std::cout << "Posición futura nave: X: " << shipFuturePos.x << " Y: " << shipFuturePos.y << " Z: " << shipFuturePos.z << std::endl;
	glm::vec3 asteroidDir = randomUnitVector();
	float asteroidSpeed = 2.5f + static_cast<float>(rand()) / RAND_MAX;
	glm::vec3 asteroidVelocity = asteroidDir * asteroidSpeed;
	glm::vec3 asteroidInitialPos = shipFuturePos - (asteroidVelocity * (float)t);
	//std::cout << "Posición inicial asteroide X: " << asteroidInitialPos.x << " Y: " << asteroidInitialPos.y << " Z: " << asteroidInitialPos.z << std::endl;
	//std::cout << "Velocidad asteroide X: " << asteroidVelocity.x << " Y: " << asteroidVelocity.y << " Z: " << asteroidVelocity.z << std::endl;

	Asteroide newAsteroid;
	newAsteroid.setRadi(1.0f);
	newAsteroid.setMassa(1.0e12);
	newAsteroid.setPosition(asteroidInitialPos);
	newAsteroid.setVelocitat(glm::dvec3(asteroidVelocity.x, asteroidVelocity.y, asteroidVelocity.z));
	std::string name = "Asteroide" + std::to_string(ASTEROIDES.size());
	newAsteroid.setName(name);

	ASTEROIDES.push_back(newAsteroid);
}



void processaAsteroides()
{
	generarAsteroides();
}

bool OBBvsSphere(const OBB& obb, const glm::vec3& sphereCenter, float sphereRadius, glm::vec3& closestPointOut) {
	// Vector del centre de l'esfera al centre de la OBB
	glm::vec3 d = sphereCenter - obb.center;

	glm::vec3 closestPoint = obb.center;

	// Trobem el punt més proper de la OBB al centre de l'esfera
	for (int i = 0; i < 3; i++) {
		float dist = glm::dot(d, obb.axes[i]);

		if (dist > obb.halfExtents[i]) dist = obb.halfExtents[i];
		else if (dist < -obb.halfExtents[i]) dist = -obb.halfExtents[i];

		closestPoint += dist * obb.axes[i];
	}
	// Guardem el punt més proper per utilitzar-lo en el tractament
	// de la col·lisió
	closestPointOut = closestPoint;

	glm::vec3 difference = closestPoint - sphereCenter;
	float distanceSquared = glm::dot(difference, difference);

	// Si la distancia del punt més proper de la OBB al centre de la esfera
	// és menor que el radi, tenim col·lisió
	return distanceSquared <= sphereRadius * sphereRadius;
}

void checkCollisions(Nau& nau)
{
	bool isColliding = false;
	// Actualitzo la hitbox
	nau.updateOBB();
	// Actualitzo vector de direcció + velocitat
	nau.updateVelocity();
	for (size_t i = 0; i < ASTEROIDES.size(); ++i)
	{
		Asteroide& asteroidA = ASTEROIDES[i];
		// Col·lisions asteroide amb asteroide
		// Si distancia del centre de cada asteroide és més petita que el radi
		// tenim col·lisió
		for (size_t j = i + 1; j < ASTEROIDES.size(); ++j)
		{

			Asteroide& asteroidB = ASTEROIDES[j];

			if (asteroidA.isCollidingWith(asteroidB))
			{
				// Tractar col·lisió
				asteroidA.resolveCollision(asteroidB);
				std::cout << "Collision!" << std::endl;
			}

		}
		// Col·lisió asteroide amb nau (OBB)
		glm::vec3 closestPointOut(0.0f, 0.0f, 0.0f);
		if (OBBvsSphere(nau.getOBB(), asteroidA.getPosition(), asteroidA.getRadi() * 2.2, closestPointOut))
		{
			isColliding = true;
			if (nau.getCollisionState() == Nau::NotColliding)
			{
				// Tractar col·lisió
				nau.resolveCollisionWithAsteroid(asteroidA, closestPointOut);
				nau.setCollisionState(Nau::Colliding);
			}

		}

	}
	if (!isColliding && nau.getCollisionState() == Nau::Colliding)
	{
		nau.setCollisionState(Nau::NotColliding);
	}
}

/* COLISIONS DEBUG */


std::vector<glm::vec3> getOBBCorners(const OBB& obb) {
	std::vector<glm::vec3> corners(8);

	glm::vec3 axis0 = obb.axes[0] * obb.halfExtents.x;
	glm::vec3 axis1 = obb.axes[1] * obb.halfExtents.y;
	glm::vec3 axis2 = obb.axes[2] * obb.halfExtents.z;

	corners[0] = obb.center - axis0 - axis1 - axis2; // (-,-,-)
	corners[1] = obb.center + axis0 - axis1 - axis2; // ( +,- -)
	corners[2] = obb.center + axis0 + axis1 - axis2; // (+, +,-)
	corners[3] = obb.center - axis0 + axis1 - axis2; // (-,+,-)
	corners[4] = obb.center - axis0 - axis1 + axis2; // (-,-,+)
	corners[5] = obb.center + axis0 - axis1 + axis2; // (+,- ,+)
	corners[6] = obb.center + axis0 + axis1 + axis2; // (+,+,+)
	corners[7] = obb.center - axis0 + axis1 + axis2; // (-,+,+ )

	return corners;
}

void drawOBBImmediateMode(const OBB& obb) {
	std::vector<glm::vec3> corners = getOBBCorners(obb);

	glBegin(GL_LINES);
	// Bottom
	glVertex3fv(glm::value_ptr(corners[0])); glVertex3fv(glm::value_ptr(corners[1]));
	glVertex3fv(glm::value_ptr(corners[1])); glVertex3fv(glm::value_ptr(corners[2]));
	glVertex3fv(glm::value_ptr(corners[2])); glVertex3fv(glm::value_ptr(corners[3]));
	glVertex3fv(glm::value_ptr(corners[3])); glVertex3fv(glm::value_ptr(corners[0]));
	// Top
	glVertex3fv(glm::value_ptr(corners[4])); glVertex3fv(glm::value_ptr(corners[5]));
	glVertex3fv(glm::value_ptr(corners[5])); glVertex3fv(glm::value_ptr(corners[6]));
	glVertex3fv(glm::value_ptr(corners[6])); glVertex3fv(glm::value_ptr(corners[7]));
	glVertex3fv(glm::value_ptr(corners[7])); glVertex3fv(glm::value_ptr(corners[4]));
	// Lados
	glVertex3fv(glm::value_ptr(corners[0])); glVertex3fv(glm::value_ptr(corners[4]));
	glVertex3fv(glm::value_ptr(corners[1])); glVertex3fv(glm::value_ptr(corners[5]));
	glVertex3fv(glm::value_ptr(corners[2])); glVertex3fv(glm::value_ptr(corners[6]));
	glVertex3fv(glm::value_ptr(corners[3])); glVertex3fv(glm::value_ptr(corners[7]));
	glEnd();
}

void asteroide(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* TestOBJ, CColor col_object, Nau& nau)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	static bool inicialitzat = false;
	static double lastTime = time;
	if (!inicialitzat)
	{
		processaAsteroides();
		inicialitzat = true;
	}
	double deltaTime = time - lastTime;
	lastTime = time;
	static double lastSpawnTime = 0.0;

	// Inside your update/render loop:
	if (time > 10) {
		if (time - lastSpawnTime >= 3.0) {
			spawnAsteroidToCollide(40.0, nau.getO(), nau.getVelocitat());
			lastSpawnTime = time;
		}
	}
	int count = 0;
	actualitzarAsteroides(deltaTime);
	checkCollisions(nau);
	for (auto& asteroide : ASTEROIDES)
	{
		/*
		if (count == 2)
		{
			static double lastSpawnTime2 = 0.0;
			static vec3 oldPosition = asteroide.getPosition();
			if (time > 20) {
				if (time - lastSpawnTime2 >= 1.0) {
					std::cout << "Nom: " << asteroide.getName() << std::endl;
					std::cout << "Posicio actual aster: " << asteroide.getPosition().x << " " << asteroide.getPosition().y << " " << asteroide.getPosition().z << std::endl;
					std::cout << "Velocitat actual aster: " << asteroide.getVelocitat().x << " " << asteroide.getVelocitat().y << " " << asteroide.getVelocitat().z << std::endl;
					vec3 distanciaRecorrida = asteroide.getPosition() - oldPosition;
					std::cout << "Distancia recorrida en 1 seg aster: " << distanciaRecorrida.x << " " << distanciaRecorrida.y << " " << distanciaRecorrida.z << std::endl;
					lastSpawnTime2 = time;
					oldPosition = asteroide.getPosition();
				}
			}
		}
		count++;
		*/
		// Si se'n va molt lluny, reset asteroide amb nous paràmetres
		if (estaForaDelsLimits(asteroide)) resetAsteroide(asteroide, gen);

		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);
		ModelMatrix = glm::translate(MatriuTG, asteroide.getPosition());
		float radi = asteroide.getRadi();
		ModelMatrix = glm::scale(ModelMatrix, vec3(radi, radi, radi));

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		TestOBJ->draw_TriVAO_OBJ(sh_programID);

		glm::mat4 ModelMatrixOrbit = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrixOrbit[0][0]);
		asteroide.agregarPosicionHistorica(asteroide.getPosition());
		drawHistoricalPath(asteroide.getPosicionesHistoricas());

		// DEBUG
		drawOBBImmediateMode(nau.getOBB());
	}

}

void renderSaturnRings(GLuint sh_programID, glm::mat4 MatriuVista, Planeta& saturn)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(sh_programID);

	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), saturn.getPosition());

	float tiltAngle = 26.73f;
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(tiltAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	float ringScale = saturn.getRadi();
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(ringScale, ringScale, ringScale));

	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
	std::string buf("textures/saturn_ring.png");
	GLuint img = loadIMA_SOIL(buf.c_str());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, img);
	glUniform1i(glGetUniformLocation(sh_programID, "texture0"), 0);

	SetTextureParameters(img, true, true, false, true);

	glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE);
	glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE);

	draw_TriEBO_Object(GLU_DISK);

	glDisable(GL_BLEND);
}

void actualitzarAsteroidesCinturo(double deltaTime)
{
	float velocitatAngulartemp = 0.005f; // Velocitat angular (rad/s). Ajusta segons el que sembli més natural.
	int i = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> vel_rand(0.0001f, 0.001f);
	float velocitatAngular = velocitatAngulartemp + vel_rand(gen);

	for (auto& asteroide : ASTEROIDESCINTURO)
	{
		if (i >= NUM_ASTEROIDES_CINTURO / 2) {
			velocitatAngular = velocitatAngulartemp / 10 + vel_rand(gen);
		}

		glm::vec3 pos = asteroide.getPosition();
		float radiOrbita = glm::length(glm::vec2(pos.x, pos.y)); // Distància al centre en el pla XZ.

		// Calcular l'angle actual i el nou angle d'òrbita
		float angleActual = atan2(pos.y, pos.x); // Angle polar en el pla XZ
		float angleNou = angleActual + velocitatAngular * deltaTime; // Nou angle actualitzat

		// Calcula la nova posició orbital al pla XZ
		pos.x = radiOrbita * cos(angleNou);
		pos.y = radiOrbita * sin(angleNou);

		// Moviment oscil·latori opcional en Y per fer que sembli més natural
		//float amplitudOscilY = 5.0f; // Amplitud del moviment en Y
		//float freqOscilY = 0.1f;    // Freqüència d'oscil·lació en Y
		//pos.z = amplitudOscilY * sin(angleNou * freqOscilY);

		// Actualitza la posició de l'asteroide
		asteroide.setPosition(pos);
		i++;
	}
}

void actualitzarDiposits(double deltaTime)
{
	float velocitatAngulartemp = 0.005f; // Velocitat angular (rad/s). Ajusta segons el que sembli més natural.
	int i = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> vel_rand(0.0001f, 0.001f);
	float velocitatAngular = vel_rand(gen);

	for (auto& objJoc : DIPOSITS)
	{
		glm::vec3 pos = objJoc.getPosition();
		float radiOrbita = glm::length(glm::vec2(pos.x, pos.y)); // Distància al centre en el pla XZ.

		// Calcular l'angle actual i el nou angle d'òrbita
		float angleActual = atan2(pos.y, pos.x); // Angle polar en el pla XZ
		float angleNou = angleActual + velocitatAngular * deltaTime; // Nou angle actualitzat

		// Calcula la nova posició orbital al pla XZ
		pos.x = radiOrbita * cos(angleNou);
		pos.y = radiOrbita * sin(angleNou);

		// Actualitza la posició de l'asteroide
		objJoc.setPosition(pos);
		i++;
	}
}

void objectes(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* CombustibleOBJ, CColor col_object) {
	std::random_device rd;
	std::mt19937 gen(rd());
	static bool inicialitzat = false;
	static double lastTime = time;

	if (!inicialitzat) {
		generarDiposits(); // Generar asteroides
		inicialitzat = true;
	}
	
	double deltaTime = time - lastTime; // Calcula el temps entre frames
	lastTime = time;

	// Actualitza la posició dels asteroides del cinturó
	actualitzarDiposits(deltaTime);

	for (auto& objJoc : DIPOSITS)
	{
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);
		ModelMatrix = glm::translate(MatriuTG, objJoc.getPosition());
		//float radi = objJoc.getRadi();
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(radi, radi, radi));
		//ModelMatrix = glm::rotate(ModelMatrix, radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f)); // Ejemplo de escala

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		CombustibleOBJ->draw_TriVAO_OBJ(sh_programID);
	}
}

void asteroidesCinturo(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* TestOBJ, CColor col_object) {
	std::random_device rd;
	std::mt19937 gen(rd());
	static bool inicialitzat = false;
	static double lastTime = time;

	if (!inicialitzat) {
		generarAsteroidesCinturo(); // Generar asteroides
		inicialitzat = true;
	}

	double deltaTime = time - lastTime; // Calcula el temps entre frames
	lastTime = time;

	// Actualitza la posició dels asteroides del cinturó
	actualitzarAsteroidesCinturo(deltaTime);

	for (auto& asteroide : ASTEROIDESCINTURO)
	{
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);
		ModelMatrix = glm::translate(MatriuTG, asteroide.getPosition());
		float radi = asteroide.getRadi();
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(radi, radi, radi));

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		TestOBJ->draw_TriVAO_OBJ(sh_programID);
	}
}

void generarEstacions() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * PI); // Angle al voltant del cercle
	std::uniform_real_distribution<float> radius_dist(20.0f, 100.0f);  // Radi de l'òrbita (proper al planeta)
	std::uniform_real_distribution<float> height_dist(-5.0f, 5.0f);    // Alçada limitada
	std::uniform_real_distribution<float> fuel_dist(100.0f, 500.0f);   // Combustible disponible
	std::uniform_int_distribution<int> num_estacions(3, 8);            // Nombre d'estacions per planeta

	size_t estacio_index = 0;

	for (auto& planeta : PLANETES) {
		glm::vec3 pos_planeta = planeta.getPosition(); // Posició del planeta
		int numEstacions = num_estacions(gen);         // Nombre d'estacions per aquest planeta

		for (int i = 0; i < numEstacions; ++i) {
			if (estacio_index >= NUM_ESTACIONS) break;

			float angle = angle_dist(gen);   // Angle en radians al voltant del planeta
			float radius = radius_dist(gen); // Radi d'òrbita
			float height = height_dist(gen); // Alçada respecte al pla orbital

			// Calcula la posició de l'estació en coordenades cartesianes
			float x = pos_planeta.x + radius * cos(angle);
			float y = pos_planeta.y + radius * sin(angle);
			float z = pos_planeta.z + height;

			float fuel = fuel_dist(gen); // Combustible disponible

			// Configura l'estació
			ESTACIONS[estacio_index].setRadi(0.01f);
			ESTACIONS[estacio_index].setPosition(glm::vec3(x, y, z));
			ESTACIONS[estacio_index].setVelocitat(glm::dvec3(0.0, 0.0, 0.0));
			ESTACIONS[estacio_index].setValor(fuel);

			++estacio_index;
		}
	}
}
void actualitzarEstacions(double deltaTime)
{
	float velocitatAngulartemp = 0.005f; // Velocitat angular (rad/s). Ajusta segons el que sembli més natural.
	int i = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> vel_rand(0.0001f, 0.001f);
	float velocitatAngular = vel_rand(gen);

	for (auto& objJoc : ESTACIONS)
	{
		glm::vec3 pos = objJoc.getPosition();
		float radiOrbita = glm::length(glm::vec2(pos.x, pos.y)); // Distància al centre en el pla XZ.

		// Calcular l'angle actual i el nou angle d'òrbita
		float angleActual = atan2(pos.y, pos.x); // Angle polar en el pla XZ
		float angleNou = angleActual + velocitatAngular * deltaTime; // Nou angle actualitzat

		// Calcula la nova posició orbital al pla XZ
		pos.x = radiOrbita * cos(angleNou);
		pos.y = radiOrbita * sin(angleNou);

		// Actualitza la posició de l'asteroide
		objJoc.setPosition(pos);
		i++;
	}
}

void estacions(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* EstacioOBJ, CColor col_object) {
	std::random_device rd;
	std::mt19937 gen(rd());
	static bool inicialitzat = false;
	static double lastTime = time;

	if (!inicialitzat) {
		generarEstacions(); // Generar asteroides
		inicialitzat = true;
	}

	double deltaTime = time - lastTime; // Calcula el temps entre frames
	lastTime = time;

	// Actualitza la posició dels asteroides del cinturó
	actualitzarDiposits(deltaTime);

	for (auto& objJoc : ESTACIONS)
	{
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);
		ModelMatrix = glm::translate(MatriuTG, objJoc.getPosition());
		float radi = objJoc.getRadi();
		ModelMatrix = glm::rotate(ModelMatrix, radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(radi, radi, radi));
		//ModelMatrix = glm::rotate(ModelMatrix, radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		EstacioOBJ->draw_TriVAO_OBJ(sh_programID);
	}
}



void planeta(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, Nau& nau)
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
	// Un dia per segon
	double deltaTime = time - lastTime;
	lastTime = time;

	deltaTime *= VELOCITAT_SIMULACIO;
	// F�sica orbites 2D de moment
	updatePlanetesAnalytical(time);
	//std::cout << "X: " << nau.getO().x << "Y: " << nau.getO().y << "Z: " << nau.getO().z << std::endl;
	if (time > 17)
	{
		nau.updatePhysicsWithPlanets(PLANETES, deltaTime);
	}
	for (auto& planeta : PLANETES)
	{

		// Posici� inicial
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

		// LCR: cas lluna //
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
		SetTextureParameters((GLint)planeta.getTextureID(), true, true, true, true);
		glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
		//glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE);

		draw_TriEBO_Object(3);

		if (planeta.getName() == "Saturn")
		{
			renderSaturnRings(sh_programID, MatriuVista, planeta);
		}

		glm::mat4 ModelMatrixOrbit = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrixOrbit[0][0]);
		planeta.agregarPosicionHistorica(planeta.getPosition());
		if (paintorbit) {
			drawOrbitPath(planeta);
		}
		else {
			drawHistoricalPath(planeta.getPosicionesHistoricas());
		}
		// moons
		std::vector<Planeta>& moons = planeta.moons;
		for (auto& moon : moons)
		{
			glm::mat4 MoonModelMatrix(1.0f);
			MoonModelMatrix = glm::translate(MatriuTG, moon.getPosition());

			float moonVelRot = moon.getVelocitatRotacio();
			int moonDirRot = moon.getDireccioRotacio();
			float moonAngle = time * moonVelRot * moonDirRot;
			glm::vec3 moonAxis = moon.getEixosRotacioPlaneta();
			MoonModelMatrix = glm::rotate(MoonModelMatrix, glm::radians(moonAngle), moonAxis);

			float moonRadi = moon.getRadi();
			MoonModelMatrix = glm::scale(MoonModelMatrix, glm::vec3(moonRadi, moonRadi, moonRadi));

			glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &MoonModelMatrix[0][0]);
			glm::mat4 MoonNormalMatrix = transpose(inverse(MatriuVista * MoonModelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &MoonNormalMatrix[0][0]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (GLint)moon.getTextureID());
			glUniform1i(glGetUniformLocation(sh_programID, "texture0"), GLint(0));
			SetTextureParameters((GLint)moon.getTextureID(), true, true, true, true);
			glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE);
			draw_TriEBO_Object(3);

			glm::mat4 MoonModelMatrixOrbit = glm::mat4(1.0f);
			glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &MoonModelMatrixOrbit[0][0]);
			//moon.agregarPosicionHistorica(moon.getPosition());
			// drawOrbitPath(moon);
			//drawHistoricalPath(moon.getPosicionesHistoricas());
		}

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
	float anomalia = fmod((time / 10) * velocitat_satelit, 360.0f);
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
	}
	else {
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
	ModelMatrix = glm::rotate(ModelMatrix, radians(time * 90.0f), vec3(0.0f, 0.0f, 1.0f));
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
	ModelMatrix = glm::rotate(ModelMatrix, radians(time * 15.0f), vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 1.0f));

	// Pas a shaders Model
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

	// Pas a shader Normal
	NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	draw_TriEBO_Object(GLUT_TETRAHEDRON);
}

void d_nau(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], const Nau nau)
{
	// SPACESHIP
	CColor col_object = { 0.0,1.0,1.0,1.0 };
	//SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);


	ModelMatrix = glm::translate(MatriuTG, nau.getO());
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.05f, 0.05f, 0.05)); // Ejemplo de escala


	ModelMatrix = ModelMatrix * nau.getR();

	ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));

	// Pasar la ModelMatrix actualizada al shader
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

	// Calcular y pasar la NormalMatrix al shader
	NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

	// Configuraci�n del material y dibujo del objeto
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	COBJModel* nauModel = nau.getModel();
	if(nauModel != NULL)
		nauModel->draw_TriVAO_OBJ(sh_programID);
}