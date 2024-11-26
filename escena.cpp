//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2022 MONOFINESTRA amb OpenGL 4.3, interfície GLFW, ImGui i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2024)
// escena.cpp : Aqui es on ha d'anar el codi de les funcions que 
//              dibuixin les escenes.
//
//    Versió 2.0:	- Objectes Cub, Esfera, Tetera (primitives libreria GLUT)
//
//	  Versió 2.2:	- Objectes Cub, Esfera, Tetera definides en fitxer font glut_geometry amb altres primitives GLUT
//
//	  Versió 2.5:	- Objectes cubRGB i Tie (nau Star Wars fet per alumnes)
//

#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"
#include <iostream>

// Dibuixa Eixos Coordenades Món i Reixes, activant un shader propi.
void dibuixa_Eixos(GLuint ax_programID, bool eix, GLuint axis_Id, CMask3D reixa, CPunt3D hreixa, 
	glm::mat4 MatriuProjeccio, glm::mat4 MatriuVista)
{
// Visualització Eixos Coordenades Mòn
	glUseProgram(ax_programID);

// Pas Matrius Projecció i Vista Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(ax_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(ax_programID, 0, "in_Vertex"); // Vèrtexs
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

// Activació shader per a cub skybox
	glUseProgram(sk_programID);

// Pas Matrius Projecció i Vista a shader
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "projectionMatrix"), 1, GL_FALSE, &MatriuProjeccio[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "viewMatrix"), 1, GL_FALSE, &MatriuVista[0][0]);

// Rotar skyBox per a orientar sobre eix superior Z o X en Vista Esfèrica (POLARX, POLARY, POLARZ)
	if (eix_Polar == POLARZ) ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	else if (eix_Polar == POLARX) ModelMatrix = glm::rotate(ModelMatrix, radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));

// Escalar Cub Skybox a 5000 per encabir objectes escena a l'interior
	ModelMatrix = glm::scale(ModelMatrix, vec3(5000.0f, 5000.0f, 5000.0f));		//glScaled(5000.0, 5000.0, 5000.0);
	glUniformMatrix4fv(glGetUniformLocation(sk_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

// Activar textura cubemaps del Skybox per encabir objectes escena
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cmTexture);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sk_programID, 0, "in_Vertex"); // Vèrtexs

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
	
// Matrius de Transformació
	glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0), TransMatrix(1.0), ScaleMatrix(1.0), RotMatrix(1.0);

// VAO
	CVAO objectVAO = { 0,0,0,0,0 };
	objectVAO.vaoId = 0;	objectVAO.vboId = 0;	objectVAO.eboId = 0;	 objectVAO.nVertexs = 0; objectVAO.nIndices = 0;

	tras[0] = 0.0;	tras[1] = 0.0; tras[2] = 0.0;
	color_vermell.r = 1.0;	color_vermell.g = 0.0; color_vermell.b = 0.0; color_vermell.a = 1.0;
	sw_material[0] = false;	sw_material[1] = true; sw_material[2] = true; sw_material[3] = false;	sw_material[4] = true;

// Shader Visualització Objectes
	glUseProgram(sh_programID);

// Parametrització i activació/desactivació de textures
	if (texturID[0] != -1) SetTextureParameters(texturID[0], true, true, textur_map, false);
	if (textur) {	glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE); //glEnable(GL_TEXTURE_2D);
					glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE); //glEnable(GL_MODULATE);
				}
		else {	//glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_FALSE); //glDisable(GL_TEXTURE_2D);
				//glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_FALSE); //glDisable(GL_MODULATE);
			}
	glUniform1i(glGetUniformLocation(sh_programID, "flag_invert_y"), flagInvertY);

// Attribute Locations must be setup before calling glLinkProgram()
	glBindAttribLocation(sh_programID, 0, "in_Vertex");		// Vèrtexs
	glBindAttribLocation(sh_programID, 1, "in_Color");		// Color
	glBindAttribLocation(sh_programID, 2, "in_Normal");		// Normals
	glBindAttribLocation(sh_programID, 3, "in_TexCoord");	// Textura

// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material.
	SeleccionaColorMaterial(sh_programID, col_object, sw_mat);

	switch (objecte)
	{

	/*MAV MODIFIED*/
	case OBJECTE_T:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		objecte_t(sh_programID, MatriuVista, MatriuTG, sw_mat);

		break;
		/*MAV MODIFIED*/
	case SPUTNIK:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		sputnik(sh_programID, MatriuVista, MatriuTG, sw_mat, time,propulsat);
		break;
	/*MAV MODIFIED*/
	case DONUT_FACE:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		donut_face(sh_programID, MatriuVista, MatriuTG, sw_mat, time);
		break;
	/*MAV MODIFIED*/
	case NAU_FACE:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		nau_face(sh_programID, MatriuVista, MatriuTG, sw_mat, time);
		break;

	case PROVA_PLANETA:
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		planeta(sh_programID, MatriuVista, MatriuTG, sw_mat, time, texturID, textur);
		// Activar transparència
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Dibuix geometria Mar
		color_Mar.r = 0.5;	color_Mar.g = 0.4; color_Mar.b = 0.9; color_Mar.a = 0.5;
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material pel color de l'objecte.
		SeleccionaColorMaterial(sh_programID, color_Mar, sw_mat);
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Desactivar transparència
		glDisable(GL_BLEND);

		////////////////////////////////////////////nau///////////////////////////////////////////////////////

		// Aplica la traslación
		//Julia: falta moure la nau a fora del sol
		
		ModelMatrix = glm::translate(inverse(MatriuVista), vec3(0.0f, -0.02f, -0.1f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.005f, 0.005f, 0.005)); // Ejemplo de escala
		ModelMatrix = glm::rotate(ModelMatrix, radians(7.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		// Pasar la ModelMatrix actualizada al shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);

		// Calcular y pasar la NormalMatrix al shader
		NormalMatrix = glm::transpose(glm::inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Configuración del material y dibujo del objeto
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		objecteOBJ->draw_TriVAO_OBJ(sh_programID);
		break;

		

// Dibuix de l'objecte OBJ
	case OBJOBJ:
		ModelMatrix = MatriuTG;
		// Pas ModelView Matrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		// Pas NormalMatrix a shader
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

		// Definir característiques material de cada punt
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		// Objecte OBJ: Dibuix de l'objecte OBJ amb textures amb varis VAO's, un per a cada material.
		objecteOBJ->draw_TriVAO_OBJ(sh_programID);	// Dibuixar VAO a pantalla
		break;

// Dibuix de la resta d'objectes
	default:
		// Definició propietats de reflexió (emissió, ambient, difusa, especular) del material.
		SeleccionaColorMaterial(sh_programID, col_object, sw_mat);
		break;
	}

// Enviar les comandes gràfiques a pantalla
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
// Cub balança
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
	}
}


void processaRotacions()
{
	// Calculem les coordenades dels eixos pels quals rotarà el planeta sobre ell mateix
	// 
	// LCR - s'ha afegit velocitat de rotació de la lluna (posicio 9)
	float velocitatsRotacio[10] = { 5.0f, 10.0f, 8.0f, 6.0f, 12.0f, 4.0f, 9.0f, 7.0f, 11.0f, 0.27f };

	for (int i = 0; i < PLANETES.size(); ++i) {
		float inclinacioRadians = glm::radians(ANGLES_INCLINACIO_ROTACIO[i]);
		glm::vec3 eixosRotacio = glm::vec3(
			0.0f,
			sin(inclinacioRadians),
			cos(inclinacioRadians)
		);

		// Assignem eix de rotació i direcció de rotació
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

		double mu = G * PLANETES[0].getMassa(); // Paràmetre gravitacional
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

				// Posició en el pla orbital (2D)
				double x_plaOrbital = r * cos(nu);
				double y_plaOrbital = r * sin(nu);
				double z_plaOrbital = 0.0;

				// Moment angular relatiu específic
				double h = sqrt(mu * a * (1 - e * e));

				// Velocitat en el pla orbital
				// Ens diu cap a on i que tant ràpid es mou el planeta en la seva órbita
				double vx_plaOrbital = -(mu / h) * sin(nu);
				double vy_plaOrbital = (mu / h) * (e + cos(nu));
				double vz_plaOrbital = 0.0;

				// Vector de posició i velocitat en el pla orbital
				glm::dvec3 posicio_plaOrbital(x_plaOrbital, y_plaOrbital, z_plaOrbital);
				glm::dvec3 velocitat_plaOrbital(vx_plaOrbital, vy_plaOrbital, vz_plaOrbital);

				// Matrius de rotació per passar del pla orbital a l'espai 3D
				// S'inclinen i es giren les òrbites per passar del pla al 3D 
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

void updatePlanetes(float deltaTime)
{
	// Constant gravitacional
	double G = 6.67430e-11 * pow(ESCALA_DISTANCIA, 3);

	// Reiniciem les acceleracionss
	for (auto& planeta : PLANETES)
		planeta.setAcceleracio(glm::dvec3(0.0));

	// Calcular forces gravitacionals y actualitzar acceleracions
	for (int i = 0; i < PLANETES.size(); ++i)
	{
		Planeta& planeta = PLANETES[i];

		// El sol no s'ha de moure
		if (i == 0)
			continue;

		// LCR - ORBITA LLUNA AL VOLTANT DE LA TERRA //
		
		else if (i == 9) //si es lluna
		{
			Planeta& terra = PLANETES[3];
			double distanciaTerraLluna = 3.844e11 * ESCALA_DISTANCIA; //distancia aproximada terra-lluna
			static double angleRadLluna = 0.0;
			double velocitatOrbitaLluna = sqrt(G * MASSES[3] / distanciaTerraLluna);
			angleRadLluna += 2.0 * PI * deltaTime * velocitatOrbitaLluna; //orbita lluna al voltant de la terra

			float lluna_X = distanciaTerraLluna * cos(angleRadLluna);
			float lluna_Y = distanciaTerraLluna * sin(angleRadLluna);

			glm::vec3 posLluna = glm::vec3(lluna_X, lluna_Y, 0.0f);

			planeta.setPosition(terra.getPosition() + posLluna);
		}
	

		else
		{
			Planeta& sol = PLANETES[0];
			glm::dvec3 direccio = sol.getPosition() - planeta.getPosition();
			double distancia = glm::length(direccio);
			//std::cout << "Distancia: " << distance << std::endl;
			if (distancia > 0.0f)
			{
				// Força d'atracció gravitacional entre el sol i el planeta
				// Llei universal gravitacional de Newton
				glm::dvec3 direccioForça = glm::normalize(direccio);
				double magnitudForça = G * (sol.getMassa() * planeta.getMassa()) / (distancia * distancia);
				glm::dvec3 força = direccioForça * magnitudForça;

				// F=m*a => a=F/m
				// Segona llei de newton
				glm::dvec3 acceleracio = força / planeta.getMassa();
				planeta.setAcceleracio(acceleracio);
			}

		}
	}

	// Actualitzar velocitats i posicions dels planetes
	for (auto& planeta : PLANETES)
	{
		// Actualitzar velocitat: v = v+a*dt
		glm::dvec3 velocitat = planeta.getVelocitat() + planeta.getAcceleracio() * (double)deltaTime;
		planeta.setVelocitat(velocitat);

		// Actualitzar posició: x = x+v*dt
		glm::vec3 position = planeta.getPosition() + (glm::vec3)planeta.getVelocitat() * deltaTime;
		planeta.setPosition(position);
	}
}

void drawOrbitPath(Planeta& planeta) {
	// Define the number of points for the orbit
	const int numPoints = 100;
	double a = planeta.getSemieixMajor() * AU_IN_METERS * ESCALA_DISTANCIA; // Semi-major axis
	double e = planeta.getExcentricitat(); // Eccentricity
	double inclinacio = planeta.getInclinacio(); // Inclination
	double longNodeAsc = planeta.getLongitudNodeAscendent(); // Longitude of ascending node
	double periapsis = planeta.getPeriapsis(); // Argument of periapsis

	// Rotation matrices for transforming the orbit from 2D to 3D
	glm::mat3 R_periapsis = glm::mat3(glm::rotate(glm::mat4(1.0), (float)periapsis, glm::vec3(0.0, 0.0, 1.0)));
	glm::mat3 R_inclinacio = glm::mat3(glm::rotate(glm::mat4(1.0), (float)inclinacio, glm::vec3(1.0, 0.0, 0.0)));
	glm::mat3 R_longNodeAsc = glm::mat3(glm::rotate(glm::mat4(1.0), (float)longNodeAsc, glm::vec3(0.0, 0.0, 1.0)));
	glm::mat3 R = R_periapsis * R_inclinacio * R_longNodeAsc;

	// Start drawing the orbit (do not draw the planet itself, just the orbit)
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= numPoints; ++i) {
		// True anomaly (angle around orbit)
		double nu = 2.0 * pi<float>() * i / numPoints;

		// Radius for this point in the orbit
		double r = a * (1 - e * e) / (1 + e * cos(nu));

		// Position in the orbital plane
		double x_plaOrbital = r * cos(nu);
		double y_plaOrbital = r * sin(nu);
		double z_plaOrbital = 0.0;

		// Transform from orbital plane to 3D space relative to the Sun
		glm::dvec3 posicio_plaOrbital(x_plaOrbital, y_plaOrbital, z_plaOrbital);
		glm::dvec3 posicio_3D = R * posicio_plaOrbital;

		// Draw the orbit path in OpenGL
		glVertex3f(posicio_3D.x, posicio_3D.y, posicio_3D.z);
	}
	glEnd();
}



void planeta(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, bool sw_mat[5], float time,
	GLuint texturID[NUM_MAX_TEXTURES], bool textur)
{
	// Inicialització de planetes
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
	// Física orbites 2D de moment
	updatePlanetes(deltaTime);
	for (auto& planeta : PLANETES)
	{
		//drawOrbitPath(planeta);
		// Posició inicial
		glm::mat4 NormalMatrix(1.0), ModelMatrix(1.0);

		// LCR: cas lluna //
		ModelMatrix = glm::translate(MatriuTG, planeta.getPosition());

		// Rotació sobre ell mateix
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
float velocitat_satelit = 1.0f;  // Velocitat vertical del satèl·lit
float temps_propulsio_rest = 2.0f; // Temps restant de la propulsió
float semi_eix_major = 25.0f;

void dibuixar_orbita(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG, float semi_eix_major, float excentricitat)
{
	// Nombre de segments per a l'òrbita (com més gran sigui, més suau serà)
	int num_segments = 100;
	std::vector<glm::vec3> punts_orbita;

	// Calcular els punts de l'òrbita utilitzant coordenades polars
	for (int i = 0; i < num_segments; ++i) {
		float angle = 2.0f * glm::pi<float>() * float(i) / float(num_segments); // Angle entre punts en radians

		// Calcular la distància radial r en funció de l'excentricitat i l'angle
		float radi_orbita = (semi_eix_major * (1.0f - excentricitat * excentricitat)) / (1.0f + excentricitat * cos(angle));

		// Coordenades x i y per a l'òrbita el·líptica
		float x = radi_orbita * cos(angle); // Coordenada x
		float y = radi_orbita * sin(angle); // Coordenada y

		// Afegir el punt al vector, considerant que orbita en el pla X-Y (amb Z constant)
		punts_orbita.push_back(glm::vec3(x, y, 0.0f));
	}

	// Dibuixar l'òrbita amb línies
	glUseProgram(sh_programID); // Assegurar-se que s'està usant el programa shader correcte
	glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &MatriuTG[0][0]);

	glBegin(GL_LINE_LOOP); // Utilitzar línia tancada per a l'òrbita
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

	// Paràmetres de l'òrbita
	float forca_propulsio = 0.01f;
	float gravetat = 0.0098f;
	float radi_planeta = 5.0f;
	float excentricitat = 0.2f;

	// Manejar la propulsió
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
		velocitat_satelit += forca_propulsio;  // Augmentem la velocitat amb propulsió
		temps_propulsio_rest -= 0.01f;

		if (temps_propulsio_rest <= 0.0f) {
			propulsat = false;  // Desactivar propulsió
			//temps_propulsio_rest = 2.0f;
		}
		semi_eix_major += 0.001f;  // Decrementar semi-eix major per simular una òrbita més petita
		if (semi_eix_major < 1.0f) { // Assegurar que no baixi massa
			semi_eix_major = 1.0f;
		}
	}
	else {
		velocitat_satelit -= gravetat;  // Aplicar gravetat
		semi_eix_major -= 0.001f;  // Decrementar semi-eix major per simular una òrbita més petita
		if (semi_eix_major < 1.0f) { // Assegurar que no baixi massa
			semi_eix_major = 1.0f;
		}
	}

	float dist_focal = semi_eix_major * excentricitat;

	// Càlcul de la posició el·líptica del satèl·lit
	float anomalia = fmod((time /10)* velocitat_satelit, 360.0f);
	float radians_anomalia = glm::radians(anomalia);

	// Calcular la distància radial en funció de l'excentricitat
	float radi_orbital = (semi_eix_major * (1.0f - excentricitat * excentricitat)) /
		(1.0f + excentricitat * cos(radians_anomalia));

	// Posicions x i y basades en el radi i l'anomalia veritable
	float posicio_x = radi_orbital * cos(radians_anomalia) - dist_focal;
	float posicio_y = radi_orbital * sin(radians_anomalia);

	// Dibuixar l'òrbita en el pla X-Y
	dibuixar_orbita(sh_programID, MatriuVista, MatriuTG, semi_eix_major, excentricitat);

	// Calcular l'angle d'orientació per a la nau
	//float angle_direccio = glm::degrees(radians_anomalia) + 90.0f;  // Afegim 90 graus per ajustar la orientació
	std::cout << "Time =>" << time << std::endl;
	std::cout << "velocitat_satelit =>" << velocitat_satelit << std::endl;
	std::cout << "Posicio_x =>" << posicio_x << std::endl;
	std::cout << "Posicio_y =>" << posicio_y << std::endl;
	if (!(posicio_x * posicio_x + posicio_y * posicio_y < radi_planeta * radi_planeta)) {
		// Dibuixar el satèl·lit amb rotació per apuntar cap a la direcció del moviment
		//ModelMatrix = glm::rotate(MatriuTG, radians(time * 15.0f), vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(MatriuTG, vec3(posicio_x, posicio_y, 0.0f));  // Manté Z = 0
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(180.0f), vec3(1.0f, 0.0f, 0.0f));  // Rotar al voltant de l'eix Z
		ModelMatrix = glm::scale(ModelMatrix, vec3(1.0f, 1.0f, 1.0f));  // Escalament

		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "modelMatrix"), 1, GL_FALSE, &ModelMatrix[0][0]);
		NormalMatrix = transpose(inverse(MatriuVista * ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(sh_programID, "normalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);
		draw_TriEBO_Object(GLUT_CYLINDER);  // Dibuixar el satèl·lit
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