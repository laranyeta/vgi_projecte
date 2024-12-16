//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2022 MONOFINESTRA amb OpenGL 4.3, interf�cie GLFW, ImGui i llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2024)
// main.h : interface of the CEntornVGI class
//
/////////////////////////////////////////////////////////////////////////////


// Entorn VGI: Llibreries i constants Constants de l'aplicaci� EntornVGI
#include "stdafx.h"
// Entorn VGI: OBJECTE OBJ. Include per la definici� de l'objecte Obj_OBJ
#include "objLoader.h"	
#include "camera.h"
#include "nau.h"
#include "shader.h"

//-------------- Entorn VGI: Variables globals de main

// Retrieving main monitor
GLFWmonitor* primary;

// To get current video mode of a monitor
const GLFWvidmode* mode;

// Entorn VGI: Finestra principal 
GLFWwindow* window;

// Entorn VGI: Variable de control per a Status Bar (consola) 
bool statusB;	// Opci� booleana per a mostrar Status Bar per consola [0:NO,1:SI]

// EntornVGI.ImGui: Gesti� de finestres de men� ImGui


// Entorn V3D: Variables de control per Men� C�mera: Esf�rica, Navega, M�bil, Zoom, Satelit, Polars... 
char camera;	// Variable que controla el tipus de c�mera segons valors definits en constants.h
static int oCamera = 0;	// Variable que controla desplegable CAMERA d'ImGui
bool mobil;		// Opci� canvi de Punt de Vista interactiu (mobil) [0:NO,1:SI]
bool zzoom;		// Opci� Zoom interactiu (zoom) [0:NO,1:SI]
bool zzoomO;	// Opci� Zoom en Projecci� Ortogr�fica adaptant Volum Visualitzaci� [0:NO,1:SI]
bool satelit;	// Opci� de navegaci� animada al volt de l'objecte centrat definint increment per mouse (SAT�LIT)

// Entorn VGI: Variables de control de l'opci� C�mera->Navega?
GLdouble n[3];				// Punt cap on mira.
CPunt3D opvN;				// Definici� Or�gen Punt de Vista (en coordenades m�n)
double angleZ;				// angle de rotaci� de la traject�ria.
glm::mat4 ViewMatrix(1.0);	// Matriu de C�mera a passar al shader

// Entorn VGI: Variables de control de l'opci� C�mera->Geode?
CEsfe3D OPV_G;			// Par�metres camera en coord. esf�riques (R,alfa,beta) per a Vista Geode

// Entorn VGI: Variables de control per Men� Vista: fullsecreen, pan, dibuixar eixos i grid. 
bool fullscreen;	// Opci� booleana per Pantalla Completal [0:NO,1:SI]
bool pan;			// Opcio Pan. Despla�ament del centre de l'esfera de Vista [0:NO,1:SI]
bool eixos = 0;			// Opci� per dibuixar els eixos X,Y,Z (Eixos?) [0:NO,1:SI]
Shader shaderEixos;	// Ientificador pel shader d'eixos.
GLuint eixos_programID;
GLuint eixos_Id;	// Identificador del VBO per a dibuixar els eixos.
bool sw_grid;		// Opci� per activar comandes teclat per moure grids [TRUE] o no [FALSE]
CMask3D grid;		// Opci� per a dibuixar grids (.x: grid XY, .y:grid XZ, .z: grid YZ, .w:grid XYZ)
CPunt3D hgrid;		// Al�ada de cada grid (.x: grid XY, .y:grid XZ, .z: grid YZ, .w:grid XYZ)

// Entorn VGI: Variables de l'opci� Vista->Pan
double fact_pan;	// Factor de despla�ament de la c�mara (opci� pan).
CPunt3D tr_cpv;		// Vector de Traslaci� del Centre del Punt de Vista actiu dins opci� pan.
CPunt3D tr_cpvF;	// Vector de Traslaci� del Centre del Punt de Vista (fixat amb INSERT dins opci� pan) 
//       i actiu fora l'opci� pan.

// Entorn VGI: Variables de control per les opcions de men� Projecci�, Objecte
char projeccio = 'P';					// Men� Projecci�: Tipus de projeccio
static int oProjeccio = 3;		// ImGui: Variable que controla desplegable TIPUS PROJECCIO d'ImGui
glm::mat4 ProjectionMatrix(1.0);// Matriu de Projecci� a passar al shader
char objecte;					// Men� Objecte: Tipus d'Objecte
static int oObjecte = 0;		// ImGui: Variable que controla desplegable TIPUS OBJECTE d'ImGui

// Entorn VGI: Variables de control Skybox Cube
bool SkyBoxCube;			// Booleana que controla si es visualitza Skybox [TRUE] o no [FALSE].
Shader shader_SkyBoxC;		// Shader Skybox Cub
GLuint skC_programID;		// Identificador program Skybox Cube
CVAO skC_VAOID;				// Identificador VAO List (vaoId, vboId, nVertexs) per a Skybox Cube
GLuint cubemapTexture;		// Identificador textura cubemap.
Shader shaderSkyBox;		// Shader SkyBox

// Entorn VGI: Variables de control del men� Transforma
bool transf;	// Booleana per activar Transformacions (true) o no (false).
bool trasl;		// Booleana d'activaci� de la Traslaci� (true) o no (false).
bool rota;		// Booleana d'activaci� de la Rotaci� (true) o no (false).
bool escal;		// Booleana d'activaci� de l'Escalatge (true) o no (false).
double fact_Tras, fact_Rota;	// Increments de Traslaci� i Rotaci�.
INSTANCIA TG;	// Estructura que cont� TG del men� Transforma actiu dins qualsevol opci� de Transforma 
//      (Traslaci� Rotaci� i Escalatge).
INSTANCIA TGF;	// Estructura que cont� TG del men� Transforma fixat amb INSERT dins les opcions de Transforma
//     i actiu fora l'opci� Transforma.
bool transX;	// Opci� Mobil Eix X?: TG interactives per l'eix X via mouse [F:NO,T:SI].
bool transY;	// Opci� Mobil Eix Y?: TG interactives per l'eix Y via mouse [F:NO,T:SI].
bool transZ;	// Opci� Mobil Eix Z?: TG interactives per l'eix Z via mouse [F:NO,T:SI].
glm::mat4 GTMatrix; // Matriu de Transformacions Geom�triques a passar al shader

// Entorn VGI: Variables de control per les opcions de men� Ocultacions
bool front_faces;// Men� ocultacions: Determina si les cares visibles s�n les frontals [true-defecte] o les back [false] pel Test de Visibilitat.
bool test_vis;  // Men� ocultacions: Activa [true] o desactiva [false] Test Visibilitat.
bool oculta;    // Men� ocultacions: Activa [true] o desactiva [false] Ocultacions (Z-buffer).
bool back_line; // Men� ocultacions: Activa [true] o desactiva [false] dibuix cares back com a l�nies.

// Entorn VGI: Variables de control del men� Iluminaci�	
bool ifixe;         // Iluminaci� fixe independent del PV (ifixe=1) 
// o depenent (mobil) respecte el PV (casc miner) (ifixe=0)
bool ilum2sides;	// Iluminaci� de les cares FRONT i BACK [TRUE] o nom�s les FRONT [FALSE]
char ilumina;		// Tipus d'il.luminaci� [FILFERROS 'f',PLANA 'c',SUAU 'c']
static int oIlumina = 3;	// Variable que controla desplegable TIPUS ILUMINACIO d'ImGui
bool sw_material[5];// Variable que controla els coeficients de reflectivitat del material [TRUE] o no [FALSE]:
// [0]: emission, [1]: ambient, [2]: difusa, [3] especular.
bool sw_material_old[5]; // Variable que guarda els valors de sw_material mentre no hi ha reflectivitat de material (refl_material=false).
bool textura;       // Control de textures desactivades [0:NO] o activades [1:SI]
char t_textura;		// Tipus de textures (predefinides o per fitxer)
bool textura_map;	// Mapping de textura modulat amb la llum [TRUE] o calcat [FALSE]
GLuint texturesID[NUM_MAX_TEXTURES];// Vector d'identificadors de textura de l'entorn. Si no hi ha textura activa, agafa el valor -1.
// 0: Textura general, assignada a la lectura de fitxer.
// 1-6: Textures de l'objecte Truck
// 7: Textura pel Fractal
// 8-9: Lliures
bool tFlag_invert_Y; // Booleana que activa la inversi� coordenada textura t (o Y) a 1.0-cty segons llibreria SOIL (TRUE) o no (FALSE).

// Entorn VGI: Variables de control del men� Llums
bool llum_ambient;		// Booleana que controla la llum ambient (SI/NO).
LLUM llumGL[NUM_MAX_LLUMS];		// Vector de llums d'OpenGL
bool sw_llambient;		// Booleana que controla modus de configurar el color de la llum ambient [TRUE] o no [FALSE]
CColor col_llambient;	// Color llum ambient.

// Entorn VGI: Variables de control del men� Shaders
char shader;				// Tipus de shader [FLAT, GOURAUD, PHONG, FILE, PROG_BINARY_SHADER]
static int oShader = 1;		// Variable que controla desplegable SHADER d'ImGui
GLuint shader_programID;	// Shader Program que cont� el Vertex i Fragment program.
Shader shaderLighting;		// Shader que implementa els codis GLSL d'il.luminaci�.

// Entorn VGI: Variables butons de mouse 
CPoint m_PosEAvall, m_PosDAvall;	// Coordenades del cursor quan el boto esquerre(E) o dret(D) del 
//    mouse ha estat clicat.
bool m_ButoEAvall, m_ButoDAvall;	// TRUE si el boto esquerre(E) o dret(D) del mouse esta clicat.
CEsfe3D m_EsfeEAvall;				// Coordenades Esf�riques del PV (OPV) quan el boto esquerre(E) o dret(D) del 
//		mouse ha estat clicat.
CEsfe3D m_EsfeIncEAvall;			// Increment de despla�ament en coordenades Esf�riques del PV (OPV).

// Entorn VGI: Variables que controlen par�metres visualitzaci�: Mides finestra Windows i PV
int w, h;				// Mides de la finestra Windows (w-amplada,h-al�ada)
int width_old, height_old;	// Mides de la resoluci� actual de la pantalla (finestra Windows)
int w_old, h_old;		// Mides de la finestra Windows (w-amplada,h-al�ada) per restaurar Finestra des de fullscreen
CEsfe3D OPV;			// Par�metres camera en coord. esf�riques (R,alfa,beta)
float cam_Esferica[3] = { 15.0f, 0.0f, 0.0f }; // ImGui: Coordenades Esf�riques C�mera
char Vis_Polar;			// Variable que controla orientaci� dels eixos en Visualitzaci� Interactiva (POLARZ,POLARY,POLARX)

// Entorn VGI: Color de fons i de l'objecte
bool fonsR, fonsG, fonsB;	// Booleanes per controlar variaci� de color per teclat.
CColor c_fons;				// Intensitat de color de fons.
bool sw_color;				// Booleana que controla el modus de configurar color de l'objecte per teclat [TRUE] o no [FALSE]
CColor col_obj;				// Color de l'objecte simple.
ImVec4 clear_colorB = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);	// ImGui: Color de fons
ImVec4 clear_colorO = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);	// ImGui: Color de l'objecte.

// Entorn VGI: Objecte OBJ:
COBJModel* ObOBJ;		// Variable d'objecte format OBJ (*.OBJ)
CVAO vao_OBJ;			// Identificador VAO per a objecte OBJ

// Entorn VGI: OBJECTE --> Corbes Bezier i BSpline
int npts_T;							// N�mero de punts de control de la corba en el Vector corbaSpline (<=MAX_PATH_SPLINE)
CPunt3D PC_t[MAX_PATCH_CORBA];		// Vector que enmagatzema Punts de Control Corba Spline
GLdouble pas_Corba;					// Increment del par�metre t per al dibuix de les corbes.
GLdouble pas_CS;					// Increment del par�metre t per al dibuix de corbes i superficies.
bool sw_Punts_Control;				// Booleana que activa o desactiva la visualitzaci� dels punts de control de la corba o de la superficie

// Entorn VGI. TRIEDRE DE FRENET / DARBOUX: VT: vector Tangent, VNP: Vector Normal Principal, VBN: vector BiNormal
bool dibuixa_TriedreFrenet;			// Booleana que controla dibuix de Triedre de Frenet per a cada punt de la Corba [TRUE-dibuixa, FALSE-no dibuixa]
bool dibuixa_TriedreDarboux;		// Booleana que controla dibuix de Triedre de Darboux per a cada punt de la Corba Loxodroma[TRUE-dibuixa, FALSE-no dibuixa]
CPunt3D VT, VNP, VBN;				// TRIEDRE de FRENET: VT: Vector Tangent, VNP: Vector Normal Principal, VBN: Vector BiNormal.

// Entorn VGI: Variables del Timer
double t;		// Par�metre t pel Timer.
bool anima;		// Booleana que controla si l'animaci� �s activa (TRUE) o no (FALSE)
//    dins la funci� de control del rellotge OnTimer.

// Entorn VGI: Variables de l'objecte FRACTAL
char t_fractal;		// Tipus de fractal.
char soroll;		// Men� Fractals: Tipus de soroll
int pas, pas_ini;	// Resoluci� del fractal inicial (pas_ini) i de visualitzaci� (pas).
bool sw_il;			// Booleana que controla si cal compilar el fractal (sw_il=1) o no (sw_il=0)
bool palcolFractal;	// Booleana que activa coloraci� del fractal segons paleta de colors [TRUE] o no [FALSE].

// Entorn VGI: Altres variables
GLdouble mida;		// Factor d'escala per calcular Volum de Visualitzaci� de l'objecte que encaixi.
std::string nom;	// Nom de fitxer.
std::string buffer; // Buffer que magatzema string caracters corresponent a variables double a printar en Status Bar (funci� Barra_Estat).

// MAV: variables per camera nau
double G_TIME, G_DELTA;
bool PROPULSIO_NAU = false;
double angleA, angleB, angleC;
static const double vdir_ini[3] = { -1, 0, 0 }, vright_ini[3] = { 0, 1, 0 }, vup_ini[3] = { 0, 0, 1 };
double v[3]; //direccio vertical
double u[3]; //direccio derecha
bool pressW, pressS, pressA, pressD, pressZ, pressX, pressUP, pressDOWN, pressLEFT, pressRIGHT, pressQ, pressE, pressR, pressM;
bool mouseControl;
COBJModel* TestOBJ;
COBJModel* CombustibleOBJ;
COBJModel* EstacioOBJ;

int moveN, moveV, moveU, moveCount;
int rotateN, rotateV, rotateU, rotateCount;

//bool moveControl[6]; int moveCount;
//bool angleControl[6]; int angleCount;
Nau nau;
Camera camProva;

COBJModel* nullObj = NULL;
//bool pause;
//-------------- Entorn VGI: Fi De Variables globals de main

//-------------- Entorn VGI: Declaraci� funcions main
void Moviment_Nau();
void Moviment_Nau2();


// Inicialitzaci� variables de control
void InitGL();

void InitAPI();
void GetGLVersion(int* major, int* minor);

// Entorn VGI: Control de l'EVENT ONSIZE
void OnSize(GLFWwindow* window, int width, int height);

void OnPaint(/*GLFWwindow* window,*/ float time);
void configura_Escena();
void dibuixa_Escena(float time);
void Barra_Estat();

// EntornVGI: Funcions de mostrar Finestres ImGui
void draw_Menu_ImGui();
//void MostraEntornVGIWindow(bool* p_open);
void ShowArxiusOptions();
//void ShowAboutWindow(bool* p_open);
int shortCut_Camera();
int shortCut_Projeccio();
int shortCut_Objecte();
int shortCut_Iluminacio();
//void ShowEntornVGIWindow(bool* p_open);

// EntornVGI: Funcions de les opcions de Men� Shader.
void Menu_Shaders_Opcio_CarregarVSFS();

// Entorn VGI: Control de l'EVENT TECLAT
void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnKeyUp(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnTextDown(GLFWwindow* window, unsigned int codepoint);

// Entorn VGI: Funcions de tractament de teclat en diferents modus
void Teclat_Shift(int key, GLFWwindow* window);
void Teclat_Ctrl(int key);
void Teclat_ColorObjecte(int key, int action);
void Teclat_ColorFons(int key, int action);
void Teclat_Navega(int key, int action);
void Teclat_Nau(int key, int action);
void Teclat_Pan(int key, int action);
void Teclat_TransEscala(int key, int action);
void Teclat_TransRota(int key, int action);
void Teclat_TransTraslada(int key, int action);
void Teclat_Grid(int key, int action);
void Teclat_PasCorbes(int key, int action);

// Entorn VGI: Control de l'EVENT MOUSE
void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
void RatoliPress_Nau();
void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
void Ratoli_Nau();
void OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset);

// Entorn VGI: Control de l'EVENT TIMER
void OnTimer();

// ---------------- Entorn VGI: Funcions locals a main.cpp
int Log2(int num);							// Log2: C�lcul del log base 2 de num
int llegir_ptsC(const char* nomf);				// Llegir Punts Control Corbes Bezier i B-Spline
//void OnFull_Screen(GLFWmonitor* monitor, GLFWwindow* window);
// ---------------- Entorn VGI: Tractament d'errors
void error_callback(int code, const char* description);
GLenum glCheckError_(const char* file, int line);
void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);

//Funcions propies

void SetWindowIcon(GLFWwindow* window, const char* iconPath);
void generarAsteroides();
void generarAsteroidesCinturo();
void generarDiposits();
void generarEstacions();
void PosicionsInicialsSistemaSolar();
