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
			glm::mat4 MatriuVista, glm::mat4 MatriuTG, float time,bool propulsat, Nau nau, COBJModel* TestOBJ)
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
		asteroide(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur, TestOBJ, col_object);
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

			// TEMPORAL: ISMAEL
			if (PLANETES[i].getName() == "Lluna")
			{
				double distanciaTerraLluna = 3.844e8 * ESCALA_DISTANCIA;
				glm::vec3 posRelativa = glm::vec3(distanciaTerraLluna, 0.0f, 0.0f);

				PLANETES[i].setPosition(PLANETES[3].getPosition() + posRelativa);

				double v = sqrt(G * PLANETES[3].getMassa() / distanciaTerraLluna);

				glm::dvec3 direccio = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), posRelativa));
				glm::dvec3 velocitat = direccio * v;

				PLANETES[i].setVelocitat(PLANETES[3].getVelocitat() + velocitat);
			}
			else {
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
	inicialitzaDades();
	processaRotacions();
	processaFisica();
	processaTextures();
}

void updatePlanetesAnalytical(double time)
{
	const double G = 6.67430e-11 * pow(ESCALA_DISTANCIA, 3);
	const Planeta& sol = PLANETES[0];

	for (int i = 1; i < PLANETES.size(); ++i) // Comenzamos desde 1 para omitir el Sol
	{
		Planeta& planeta = PLANETES[i];

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
	float distanceSquared = glm::dot(pos, pos); // Equivalent to glm::length2(pos)
	return distanceSquared > (MAX_DISTANCIA_ASTEROIDES * MAX_DISTANCIA_ASTEROIDES);
}

void resetAsteroide(Asteroide& asteroide, std::mt19937& gen)
{
	std::uniform_real_distribution<float> pos_dist(-MAX_DISTANCIA_ASTEROIDES / 2.0f, MAX_DISTANCIA_ASTEROIDES / 2.0f);
	std::uniform_real_distribution<double> vel_dist(-0.5, 0.5);
	std::uniform_real_distribution<float> radius_dist(0.5f, 1.5f);
	std::uniform_real_distribution<double> mass_dist(1.0e12, 1.0e13);

	float radius = radius_dist(gen);         // Radius between 1.0 and 2.0
	double mass = mass_dist(gen);            // Mass between 1.0e12 and 1.0e13

	glm::vec3 position(pos_dist(gen), pos_dist(gen), pos_dist(gen));
	glm::dvec3 velocity(vel_dist(gen), vel_dist(gen), vel_dist(gen));

	asteroide.setRadi(radius);
	asteroide.setMassa(mass);
	asteroide.setVelocitat(velocity);
	asteroide.setPosition(position);
	asteroide.posicionesHistoricas.clear();
}

void actualitzarAsteroides(double deltaTime)
{
	for (auto& asteroide : ASTEROIDES)
	{
		glm::vec3 pos = asteroide.getPosition();
		glm::dvec3 vel = asteroide.getVelocitat();
		pos += glm::vec3(vel * deltaTime); // Assuming velocity is in units per second
		asteroide.setPosition(pos);
	}
}

// ISMAEL ASTEROIDES
void generarAsteroides()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> pos_dist(-2000.0f, 2000.0f); 
	std::uniform_real_distribution<double> vel_dist(-0.5, 0.5);       
	std::uniform_real_distribution<float> radius_dist(0.5f, 1.5f);     
	std::uniform_real_distribution<double> mass_dist(1.0e12, 1.0e13);   

	for (size_t i = 0; i < NUM_ASTEROIDES; ++i) {
		/* TESTING
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
		*/
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

void processaAsteroides()
{
	generarAsteroides();
}

void checkCollisions()
{
	for (size_t i = 0; i < ASTEROIDES.size(); ++i)
	{
		for (size_t j = i + 1; j < ASTEROIDES.size(); ++j)
		{
			Asteroide& asteroidA = ASTEROIDES[i];
			Asteroide& asteroidB = ASTEROIDES[j];

			if (asteroidA.isCollidingWith(asteroidB))
			{
				asteroidA.resolveCollision(asteroidB);
				std::cout << "Collision!" << std::endl;
			}
		}
	}
}

void asteroide(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur, COBJModel* TestOBJ, CColor col_object)
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
	//int count = 0;
	for (auto& asteroide : ASTEROIDES)
	{
		/* TESTING
		if (count == 2) continue;
		count++;
		*/
		actualitzarAsteroides(deltaTime);
		checkCollisions();
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
	// Un dia per segon
	double deltaTime = time - lastTime;
	lastTime = time;

	deltaTime *= VELOCITAT_SIMULACIO;
	// F�sica orbites 2D de moment
	updatePlanetesAnalytical(time);
	for (auto& planeta : PLANETES)
	{
		//drawOrbitPath(planeta);
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
		SetTextureParameters((GLint)planeta.getTextureID(), true, true, false, false);
		glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE);

		draw_TriEBO_Object(3);

		glm::mat4 ModelMatrixOrbit = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrixOrbit[0][0]);
		planeta.agregarPosicionHistorica(planeta.getPosition());
		drawHistoricalPath(planeta.getPosicionesHistoricas());
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
	nau.getModel()->draw_TriVAO_OBJ(sh_programID);
}