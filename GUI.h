#pragma once
#include <ImGui/imgui.h>
#include <vector>
//#include <glm/glm.hpp>
#include <string>
#include <gl/glew.h>
#include "irrKlang.h"
#include "stdafx.h"
#include "nau.h"
#include <ImGui/imgui_internal.h>
#include "visualitzacio.h"


using namespace irrklang;

//#include "main.h"
#include <iostream>

class GUI
{
public:
	void inicialitzarWindow(GLFWmonitor* temp_primary, GLFWwindow* temp_window, Nau* temp_nau);
	void inicialitzarImatges();
	void inicialitzarFonts(ImGuiIO& io);
	ImFont* fontPrincipal();
	ImFont* fontDroidsans();
	void inicialitzarSons(irrklang::ISoundEngine* temp_engine,irrklang::ISound* temp_so_alerta,
		irrklang::ISound* temp_so_nau,
		irrklang::ISound* temp_musica_menu,
		irrklang::ISound* temp_musica_partida,
		float* temp_volum_nau,
		float* temp_volum_menu,
		float* temp_volum_alerta,
		float* temp_volum_partida);

	void inicalitzarInterficieGrafica(ImVec2* screenSize);


	void MostrarPantallaInicial(ImVec2* screenSize);
	//void MostrarMenuDebug(ImVec2* screenSize);
	void MostrarPantallaMenu(ImVec2* screenSize);
	void MostrarPantallaConfiguracio(ImVec2* screenSize);
	void MostrarPantallaSelector(ImVec2* screenSize, const char* descripcio);
	void MostrarPantallaSelectorD(ImVec2* screenSize, const char* descripcio);
	void MostrarPantallaJoc(ImVec2* screenSize);
	void MostrarPantallaCarrega(ImVec2* screenSize);
	float distanciaEuclidiana(const glm::vec3& point1, const glm::vec3& point2);
	void CircularProgressBar(const char* label, float progress, const ImVec2& size, const ImVec4& color);
	void Alerta(ImVec2* screenSize, ImVec4* color, const char* text);
	ImVec2 convertirAPosicioMiniMapa(const glm::vec3& posicioMon, const glm::vec3& worldSize, const ImVec2& minimapSize, const ImVec2& minimapPosition);
	ImVec2 convertirAPosicioMiniMapaDesdeJugador(const glm::vec3& posicioMon, 
		const glm::vec3& worldSize, 
		const ImVec2& minimapSize, 
		const ImVec2& minimapPosition, 
		const glm::vec3& posicioJugador);
	ImVec2 convertirAPosicioMiniMapaDesdeJugadorVertical(const glm::vec3& posicioMon, const glm::vec3& worldSize, const ImVec2& minimapSize, const ImVec2& minimapPosition, const glm::vec3& posicioJugador);
	void MostrarPantallaMenuJugador(ImVec2* screenSize);
	float distanciaEntrePunts(const ImVec2& a, const ImVec2& b);
	void crearMiniMapaCentratJugador(ImVec2 minimapSize, ImVec2 minimapPosition);
	void crearMiniMapaCentratSol(ImVec2 minimapSize, ImVec2 minimapPosition);
	void crearMiniMapaCentratSolCircular(ImVec2 minimapSize, ImVec2 minimapPosition, bool abaix, float borderThickness);
	void ferRectangleAcceleracio(ImVec2* screenSize, ImGuiWindowFlags window_flags);
	void crearRadarVertical(ImVec2 radarSize, ImVec2 radarPosition, bool abaix, float borderThickness);
	void crearRadarVerticalQuadrat(ImVec2 radarSize, ImVec2 radarPosition, bool abaix, float borderThickness);
	void crearColoPickerFill(ImVec4* color, ImVec2 tamany, const char* text);
	void crearColorPickerU32(ImU32* color, ImVec2 tamany, const char* text);
	void crearMiniMapaCentratJugadorCircular(ImVec2 minimapSize, ImVec2 minimapPosition, bool abaix, float borderThickness);
	void dibuixarOrbita2D(const Planeta& planeta, ImVec2 minimapSize, ImVec2 minimapPosition, ImDrawList* drawList, bool circular, float radius, ImVec2 center, bool centratsol);
	void DrawSpeedometer(float value, float maxValue, float centerX, float centerY, float radius, bool isRPM);

	void DrawRotatedImage(ImVec2* screenSize, ImTextureID texture, ImVec2 pos, ImVec2 size, float landa);
	void MostrarMapaSistemaSolar(ImVec2* screenSize);

	//Getters
	bool getMenuJugadorConfig() const;
	bool* getWindowAbout();
	bool getPause();
	bool* getDebugWindow();
	bool* getDemoWindow();
	bool* getMapaWindow();
	int getPlanetaOrigen();
	int getPlanetaDesti();

	//Setters
	void switchMenuJugadorConfig();
	void switchPause();
	void switchMapaWindow();
private:
	bool pause = false;

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_EntornVGI_window = false;
	bool show_window_about = false;

	bool show_debug_windows = false;
	bool show_user_windows = true;
	bool show_menu_game = false;
	bool show_selector_planeta_origen = false;
	bool show_selector_planeta_desti = false;
	bool show_game_window = false;
	bool show_game_settings = false;
	bool show_fons = true;
	bool show_pantalla_carrega = false;
	bool show_menu_jugador_config = false;
	bool show_mapa_windows = false;

	bool show_config_grafics = true;
	bool show_config_so = false;
	bool show_config_controladors = false;
	bool show_config_credits = false;


	//Minimapa
	bool minimapas_circulars = true;
	bool minimapas_centrat_sol = false;

	int tamanyminimapa_x = 500;
	int tamanyminimapa_y = 300;
	int tamanyradar = 300;

	bool asteroides_minimapa = true;
	bool diposits_minimapa = true;
	bool estacions_minimapa = true;
	bool orbites_minimapa = true;


	ImFont* rainyhearts;
	ImFont* silkscreen;
	ImFont* droidsans;
	ImFont* silkscreentitle;
	ImFont* silkscreensubtitle;
	ImFont* silkscreenh3;
	ImFont* opensanstitleUp;
	ImFont* barlowtitleDown;

	int PlanetOrigen = -1;
	int PlanetDesti = -1;
	//static int selectedIndex = 0;  // Índex del botó seleccionat
	int tamanySS = 200;

	GLuint mars;
	GLuint soyut;
	GLuint iss;
	GLuint cometa;
	GLuint fons;
	GLuint menu;
	GLuint endarrera;
	GLuint interficie_1;
	GLuint interficie_2;
	GLuint controls;
	GLuint icona;
	GLuint earth;

	//Boto General de totes les interficies
	ImVec4 ButtonGeneral = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 HoverButtonGeneral = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	ImVec4 ActiveButtonGeneral = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);


	ImVec4 colorVerd = ImVec4(0.0f, 0.749f, 0.388f, 1.0f);
	ImVec4 colorVermell = ImVec4(1.0f, 0.192f, 0.192f, 1.0f);
	ImVec4 colorTaronja = ImVec4(1.0f, 0.569f, 0.302f, 1.0f);

	// Color per als planetes
	ImU32 colorPlanetes = IM_COL32(255, 255, 255, 255);  // Blanc
	// Color per al jugador
	ImU32 colorJugador = IM_COL32(255, 255, 0, 255);  // Groc
	// Color per als asteroides
	ImU32 colorAsteroides = IM_COL32(255, 0, 0, 255);  // Vermell
	// Color per als asteroides
	ImU32 colorAsteroidescinturons = IM_COL32(139, 69, 19, 155);  // Marró roca
	// Color per als Diposits FUEL
	ImU32 colorDiposits = IM_COL32(0, 255, 255, 255); // Blau Brillant
	// Color per al planeta d'origen
	ImU32 colorPlanetaOrigen = IM_COL32(0, 255, 0, 255);  // Verd
	// Color per al planeta de destí
	ImU32 colorPlanetaDesti = IM_COL32(0, 0, 255, 255);  // Blau
	// Color per al Sol
	ImU32 colorSol = IM_COL32(255, 255, 0, 255);  // Groc brillant
	//Color per Estacions de vida
	ImU32 colorEstacions = IM_COL32(255, 165, 0, 255); // Taronja Brillant 

	ImU32 color_interficie = IM_COL32(200, 200, 200, 255);  // Groc brillant

	// Color base: RGB(18, 35, 96)
	ImVec4 Title_config_Color = ImVec4(18.0f / 255.0f, 35.0f / 255.0f, 96.0f / 255.0f, 1.0f); // Blau fosc

	// Text blanc per contrastar
	ImVec4 FonsMenuPausa = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);          // Blanc opac
	ImVec4 TextMenuPausa = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);          // Blanc opac

	// Botó amb base blau i variacions més contrastades per "hover" i "active"
	ImVec4 ButtonMenuPausa = ImVec4(28.0f / 255.0f, 50.0f / 255.0f, 130.0f / 255.0f, 1.0f);      // Blau pastel (base)
	ImVec4 HoverButtonMenuPausa = ImVec4(50.0f / 255.0f, 80.0f / 255.0f, 180.0f / 255.0f, 1.0f);  // Blau clar més vibrant per "hover"
	ImVec4 ActiveButtonMenuPausa = ImVec4(15.0f / 255.0f, 30.0f / 255.0f, 80.0f / 255.0f, 1.0f);  // Blau més fosc per "active"

	//Sons
	irrklang::ISoundEngine* engine; //inicialització de soundEngine
	irrklang::ISound* so_alerta; //inicialització de so d'alerta
	irrklang::ISound* so_nau; //inicialització de so de la nau
	irrklang::ISound* musica_menu; //inicialització de música de menú
	irrklang::ISound* musica_partida; //inicialització de música de partida

	float* volum_nau;
	float* volum_menu;
	float* volum_alerta;
	float* volum_partida;

	GLFWmonitor* primary;
	//const GLFWvidmode* mode;
	GLFWwindow* window;

	Nau* nau;
};

void IniciarSimulador();
void OnFull_Screen(GLFWmonitor* monitor, GLFWwindow* window);
void ShowEntornVGIWindow(bool* p_open, int pos_x, int pos_y, int size_x, int size_y, ImGuiWindowFlags window_flags);
void MostrarMenuDebug(ImVec2* screenSize);