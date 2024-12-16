//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2022 MONOFINESTRA amb OpenGL 4.3, interfície GLFW, ImGui i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2024)
// constants.h : Definició de constants compartides
//				 CENtornVGIView.cpp, visualitzacio.cpp i escena.cpp


#ifndef CONST_H
#define CONST_H

#include <vector>
#include "planeta.h"
#include "asteroide.h"
#include "objectesEspai.h"
//#include "GUI.h"

extern std::vector<Planeta> PLANETES;
extern std::vector<Asteroide> ASTEROIDES;
extern std::vector<Asteroide> ASTEROIDESCINTURO;
extern std::vector<objectesEspai> DIPOSITS;
extern std::vector<objectesEspai> ESTACIONS;
//extern GUI INTERFICIE;

//--------------- VGI: Tipus de Càmera
#define CAP ' '
#define CAM_ESFERICA 'E'
#define CAM_GEODE 'G'
#define CAM_NAVEGA 'N'
#define CAM_NAU 'S'

//--------------- VGI: Tipus de Projecció
#define AXONOM 'A'
#define ORTO 'O'
#define PERSPECT 'P'
#define IMA_PICK 3
#define PASSEIG_V 4


//--------------- VGI: Tipus de Polars (per la Visualització Interactiva)
#define POLARZ 'Z'
#define POLARY 'Y'
#define POLARX 'X'

//-------------- VGI: Tipus d'Objectes
//#define ARC 'a'
#define CAMIO 'm'
//#define CILINDRE 'y'
//#define CUB 'c'
//#define CUB_RGB 'd'
//#define C_BEZIER '2'
//#define C_LEMNISCATA 'K'
//#define C_LEMNISCATA2D 'W'
//#define C_BSPLINE 'q'
//#define C_HERMITTE 'h'
//#define C_CATMULL_ROM 'R'
//#define ESFERA 'e'
#define O_FRACTAL 'f'
#define HIDROAVIO 'H'
#define ICOSAEDRE 'i'
//#define MATRIUP 'M'
//#define MATRIUP_VAO 'm'
#define ROBOT 'u'
//#define TETERA 't'
#define TEXTE_BITMAP 'B'
#define TEXTE_STROKE 'S'
//#define TIE 'T'
#define TORUS 'o'
#define VAIXELL 'v'
#define OBJ3DS '3'		// Objecte format 3DS
#define OBJOBJ '4'		// Objecte format OBJ
#define OBJECTE_T 'z'
#define SPUTNIK 'Q'

#define DONUT_FACE 'D'
#define NAU_FACE 'X'

#define PROVA_PLANETA '9'
#define SHIP '8'

//-------------- VGI: Tipus d'Iluminacio
#define PUNTS 'P'
#define FILFERROS 'w'
#define PLANA 'f'
#define SUAU 's'

//-------------- VGI: Objectes precompilats OpenGL amb glNewList
#define EIXOS 1			// Eixos
#define FRACTAL 2		// Fractal
#define OBJECTE3DS 3	// Objecte 3DS sense textures
#define OBJECTE3DST 4	// Objecte 3DS amb textures
#define OBJECTEOBJ 5	// Objecte OBJ sense textures
#define OBJECTEOBJT 6   // Objecte OBJ amb textures
#define SEA 7			// Objecte SEA

// -------------- VGI: Definició dels valors del pla near i far del Volum de Visualització en Perspectiva
const double p_near=0.01;
const double p_far=50000.0;

//-------------- VGI: Tipus d'Objectes Picking
#define PICKCAP 0
#define PICKFAR 1
#define PICKVAIXELL 2 
#define PICKHIDRO 3 

// -------------- VGI: CONSTANTS TEXTURES
// Nombre màxim de textures
#define NUM_MAX_TEXTURES 10

// Tipus de textures
#define CAP ' '
#define FUSTA 'F'
#define MARBRE 'M'
#define METALL 'E'
#define FITXER 'f'
#define FITXERBMP 'f'
#define FITXERIMA 'I'



// --------------  VGI: NOMBRE DE LLUMS: Nombre de Llums de l'aplicació, les d'OpenGL
const int NUM_MAX_LLUMS = 8;

// Permet prendre les funcions _s enlloc de les deprecated (strcpy -> strcpy_s). Ja definit
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

// Elimina missatges warning que venen de crides deprecated (strcpy -> strcpy_s).
//#define _CRT_SECURE_NO_WARNINGS //-> Posat a "Project"->"Properties"->"Configuration properties"->"C/C++"->"Preprocessor"->"Preprocessor definitions".

// -------------- VGI: SHADERS --> Tipus de Shaders
#define CAP_SHADER ' '
#define FLAT_SHADER 'f'
#define GOURAUD_SHADER 'G'
#define PHONG_SHADER 'P'
#define FILE_SHADER 'F'
#define PROG_BINARY_SHADER 'p'
#define PROG_BINARY_SHADERW 'W'
// ASTEROIDES ISMAEL
const int NUM_ASTEROIDES = 50;
const int NUM_ASTEROIDES_CINTURO = 300;
const int NUM_DIPOSITS = 130;
const int NUM_ESTACIONS = 5;
const float MAX_DISTANCIA_ASTEROIDES = 250.0f;
// TRAJ ORBIT ISMAEL
const size_t BASE_POINTS = 300;
const double AU_IN_METERS = 1.496e11;
const double VELOCITAT_SIMULACIO = 60.0 * 60.0 * 24.0;
//LCR: s'afegeixen parametres lluna //
const std::string NAMES[10] = { u8"Sol", u8"Mercuri", u8"Venus", u8"Terra", u8"Mart", u8"Júpiter", u8"Saturn", u8"Urà", u8"Neptú", u8"Lluna" };
const std::string RUTES_TEXTURA[10] = { "sun.jpg","mercury.jpg","venus.jpg","earth.jpg","mars.jpg","jupiter.jpg","saturn.jpg","uranus.jpg","neptune.jpg", "moon.jpg" };
const std::string RUTES_TEXTURA_MENU[10] = { "sun.png","mercury.png","venus.png","earth.png","mars.png","jupiter.png","saturn.png","uranus.png","neptune.png", "moon.png" };
const double DISTANCIA_DEFAULT_TERRA = 50.0;
const double ESCALA_DISTANCIA = DISTANCIA_DEFAULT_TERRA / (1.0 * 1.496e11); //1.496e11
const double ESCALA_MASSA = 1.0;
const double RADIS[10] = { 12.96340e11, 2.4397e10, 6.0518e10 , 6.3710e10 , 3.3895e10 , 6.9911e11 , 5.8232e11 , 2.5362e11 , 2.4622e11, 0.737e10 }; // e + 3
const double SEMIEIXOS_MAJORS[9] = {
	0.3871, 0.7233, 1.0000, 1.5237, 5.2026, 9.5549, 19.2184, 30.1104, 0.0000257
};
const double EXCENTRICITATS[10] = {
	0.2056, 0.0068, 0.0167, 0.0934, 0.0484, 0.0555, 0.0463, 0.0095, 0.0549
};
const double INCLINACIONS[9] = {
	7.0049, 3.3947, 0.0000, 1.8506, 1.3030, 2.4845, 0.7699, 1.7692, 5.145
};
const double LONG_NODES_ASC[9] = {
	48.33167, 76.68069, 0.0, 49.57854, 100.55615, 113.71504, 74.22988, 131.72169, 125.08
};
const double PERIAPSIS[9] = {
	29.1241, 54.85229, 102.9373, 286.4623, 273.867, 339.392, 96.998857, 273.187, 318.15
};
const int NUMERO_DE_LLUNES[9] = { 0, 0, 0, 1, 2, 8, 8, 5, 5 };
const std::string RUTES_TEXTURA_MOONS[29] = {
	// Earth (1)
	"moon.jpg",
	// Mars (2)
	"phobos.png", "deimos.png",
	// Jupiter (8)
	"Io.jpeg", "Europa.jpg", "Ganymede.jpeg", "Callisto.jpg", "Amalthea.jpg", "Himalia.jpg", "Elara.jpg", "Pasiphae.jpg",
	// Saturn (8)
	"TitanClouds.jpg", "Rhea.jpg", "Iapetus.jpg", "Dione.jpeg", "Tethys.jpeg", "Enceladus.jpeg", "Mimas.jpg", "Hyperion.jpg",
	// Uranus (5)
	"moon.jpg", "moon.jpg", "moon.jpg", "moon.jpg", "moon.jpg",
	// Neptune (5)
	"moon.jpg", "moon.jpg", "moon.jpg", "moon.jpg", "moon.jpg"
};

const std::string NAMES_MOONS[29] = {
	"Lluna",
	// Mars (2)
	"Phobos", "Deimos",
	// Jupiter (8)
	"Io", "Europa", "Ganymede", "Callisto", "Amalthea", "Himalia", "Elara", "Pasiphae",
	// Saturn (8)
	"Titan", "Rhea", "Iapetus", "Dione", "Tethys", "Enceladus", "Mimas", "Hyperion",
	// Uranus (5)
	"Titania", "Oberon", "Umbriel", "Ariel", "Miranda",
	// Neptune (5)
	"Triton", "Proteus", "Nereid", "Larissa", "Galatea"
};

const double MASSES_MOONS[29] = {
	7.342e22f,
	// Mars (2)
	7.342e22f, 7.342e22f,
	// Jupiter (8)
	8.93e22f, 4.8e22f, 1.5e23f, 1.08e23f, 2.08e19f, 9.56e18f, 8.0e18f, 7.1e18f,
	// Saturn (8)
	1.345e23f, 2.31e21f, 1.8e21f, 1.05e21f, 7.9e20f, 1.08e20f, 3.8e19f, 5.6e19f,
	// Uranus (5)
	3.5e21f, 3.0e21f, 1.3e21f, 9.5e20f, 6.6e20f,
	// Neptune (5)
	2.14e22f, 4.4e19f, 2.3e19f, 1.2e19f, 1.1e19f
};

const int DIRECCIONS_ROTACIO_MOONS[29] = {
	// Earth (1)
	1,
	// Mars (2)
	-1, 1,
	// Jupiter (8)
	1, -1, -1, -1, 1, -1, 1, -1,
	// Saturn (8)
	1, -1, 1, 1, -1, 1, 1, -1,
	// Uranus (5)
	-1, 1, -1, -1, -1,
	// Neptune (5)
	-1, 1, 1, -1, 1
};

const float ANGLES_INCLINACIO_ROTACIO_MOONS[29] = {
	// Earth (1)
	6.0f,
	// Mars (2)
	2.0f, 0.0f,
	// Jupiter (8)
	7.0f, 5.0f, -6.0f, 3.0f, -5.0f, 0.0f, 6.0f, -7.0f,
	// Saturn (8)
	7.0f, 2.0f, -7.0f, 6.0f, 5.0f, -6.0f, 0.0f, 4.0f,
	// Uranus (5)
	7.0f, 1.5f, -7.0f, 0.0f, -5.0f,
	// Neptune (5)
	7.0f, 0.5f, -7.0f, 6.0f, 0.0f
};


const double RADIS_MOONS[29] = {
	// Earth (1)
	1.65825e10,
	// Mars (2)
	1.492425e10, 1.806075e10,
	// Jupiter (8)
	6.457575e10, 6.608775e10, 7.492425e10, 6.15825e10, 6.457575e10, 6.75855e10, 6.908625e10, 7.057725e10,
	// Saturn (8)
	6.15825e10, 6.608775e10, 6.457575e10, 6.15825e10, 7.357575e10, 6.306075e10, 7.057725e10, 6.75855e10,
	// Uranus (5)
	1.807575e10, 1.492425e10, 2.108775e10, 2.40885e10, 1.65825e10,
	// Neptune (5)
	1.65825e10, 1.957575e10, 1.806075e10, 1.357575e10, 2.557725e10
};



const double MASSES[9] = {
		1.989e30f,  // Sol
		3.301e23f,  // Mercuri
		4.867e24f,  // Venus
		5.972e24f,  // Terra
		6.417e23f,  // Mart
		1.898e27f,  // Júpiter
		5.683e26f,  // Saturn
		8.681e25f,  // Urà
		1.024e26f,   // Neptú
};
const int DIRECCIONS_ROTACIO[9] = {
		1,  // Sol
		1,  // Mercuri
	   -1,  // Venus
		1,  // Terra
		1,  // Mart
		1,  // Júpiter
		1,  // Saturn
	   -1,  // Urà 
		1,   // Neptú
};
const float ANGLES_INCLINACIO_ROTACIO[9] = {
		7.25f,    // Sol
		0.03f,    // Mercuri
		2.64f,    // Venus 
		23.44f,   // Terra
		25.19f,   // Mart
		3.13f,    // Júpiter
		26.73f,   // Saturn
		82.23f,   // Urà 
		28.32f,   // Neptú
};
const double RADI_ORBITAL[9] = {
		0.0f,        // Sol +++1
		57.9e10f,     // Mercuri
		108.2e10f,    // Venus
		149.6e10f,    // Terra
		227.9e10f,    // Mart
		778.5e10f,    // J�piter
		1.4335e13f,  // Saturn
		2.8725e13f,  // Ur�
		4.4951e13f,   // Nept�
};
//--------------- VGI: Valor constant de pi
const double PI=3.14159;
const double TWOPI = 2 * PI;
const double PID2 = PI / 2;
const double DEG_A_RAD = PI / 180.0;
//const double pi=3.14159265358979323846264338327950288419716939937510f;

// --------------- GMS. GRID
#define GRID_SIZE 50	// Maximum size of the grid in OpenGL World Coordenates unities.
#define PAS_GRID 1		// Step to shift the grid planes.

// --------------- VGI. TRUCK: Resolució de les rodes (Nombre de divisions del cilindre i discos)
#define RESOLUCIO_RODA 16

// --------------- VGI. MInterval temps Timer
#define elapsedTime 0.004f

// --------------- VGI: Estructura tamany 2D (Pre-definida en Visual Studio 2019)
struct CSize
{
	GLint cx;
	GLint cy;
};

// --------------- VGI: Estructura coordenada 2D (Ja definida en Visual Studio 2010)
struct CPoint
{   GLint x;
    GLint y;
};

// --------------- VGI: Estructura coordenada 3D
struct CPunt3D
{   GLdouble x;
    GLdouble y;
	GLdouble z;
	GLdouble w;
};

// --------------- GMS: 3Màscara booleana sobre coordenades 3D
struct CMask3D
{	bool x;
	bool y;
	bool z;
	bool w;
};

// --------------- VGI: Estructura de color R,G,B,A
struct CColor
{   GLdouble r;
    GLdouble g;
	GLdouble b;
	GLdouble a;
};

// --------------- VGI: Estructura coordenada Esfèrica 3D
struct CEsfe3D
{   GLdouble R;
    GLdouble alfa;
	GLdouble beta;
};

// --------------- VGI: Estructura LLista VAO
struct CVAO
{	GLuint vaoId;
	GLuint vboId;
	GLuint eboId;
	GLint nVertexs;
	GLint nIndices;
};

// --------------- VGI: INSTANCIA (TG d'instanciació d'un objecte)
struct INSTANCIA
{	CPunt3D VTras;	// Vector de Traslació
	CPunt3D VScal;	// Vector d'Escalatge
	CPunt3D VRota;	// Vector de Rotació
};

// --------------- VGI: Coeficients equació d'atenuació de la llum fatt=1/(ad2+bd+c)
struct CAtenua
{   GLdouble a;
    GLdouble b;
	GLdouble c;
};

// --------------- VGI: Estructura de coeficients de reflectivitat de materials
struct MATERIAL
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
};

// --------------- VGI: Estructura font de llum
struct LLUM
{	bool encesa;				// Booleana que controla si la llum és encesa [TRUE] o no [FALSE]
	CEsfe3D posicio;			// Posició d ela foont de llum en coordenades esfèriques.
	GLfloat difusa[4];			// Intensitat difusa de la font de llum (r,g,b,a)
	GLfloat especular[4];		// Intensitat especular de la font de llum (r,g,b,a)
	CAtenua atenuacio;			// Coeficients de l'equació d'atenuació de la llum fatt=1/(ad2+bd+c)
	bool restringida;			// Booleana que indica si la font de llum és restringida [TRUE] i per tant són vàlids els coeficients posteriors o no [FALSE].
	GLfloat spotdirection[3];	// Vector de direció de la font de llum restringida (x,y,z).
	GLfloat spotcoscutoff;		// Coseno de l'angle d'obertura de la font de llum restringida.
	GLfloat spotexponent;		// Exponent que indica l'atenuació de la font del centre de l'eix a l'exterior, segons model de Warn.
};

#endif