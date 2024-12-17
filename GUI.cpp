#include "GUI.h"

void GUI::inicialitzarWindow(GLFWmonitor* temp_primary, GLFWwindow* temp_window, Nau* temp_nau) {
	primary = temp_primary;
	window = temp_window;
	nau = temp_nau;
}

void GUI::inicialitzarImatges() {
	menu = loadIMA_SOIL("textures/menu/menu.png");
	mars = loadIMA_SOIL("textures/menu/mars.png");
	soyut = loadIMA_SOIL("textures/menu/soyut.png");
	iss = loadIMA_SOIL("textures/menu/iss.png");
	cometa = loadIMA_SOIL("textures/menu/asteroid.png");
	//fons = loadIMA_SOIL("textures/menu/space2gran.jpeg");
	fons = loadIMA_SOIL("textures/menu/fons5.png");
	endarrera = loadIMA_SOIL("textures/menu/atras.png");
	interficie_1 = loadIMA_SOIL("textures/menu/2.png");
	interficie_2 = loadIMA_SOIL("textures/menu/1.png");
	controls = loadIMA_SOIL("textures/menu/3.png");
	icona = loadIMA_SOIL("textures/menu/icon.png");
	earth = loadIMA_SOIL("textures/menu/select/earth.png");
}

void GUI::inicialitzarFonts(ImGuiIO& io) {
	droidsans = io.Fonts->AddFontFromFileTTF("textures/menu/DroidSans.ttf", 18.0f);
	silkscreen = io.Fonts->AddFontFromFileTTF("textures/menu/Silkscreen-Regular.ttf", 24.0f);
	silkscreentitle = io.Fonts->AddFontFromFileTTF("textures/menu/Silkscreen-Bold.ttf", 150.0f);
	silkscreensubtitle = io.Fonts->AddFontFromFileTTF("textures/menu/Silkscreen-Bold.ttf", 58.0f);
	silkscreenh3 = io.Fonts->AddFontFromFileTTF("textures/menu/Silkscreen-Bold.ttf", 36.0f);
	rainyhearts = io.Fonts->AddFontFromFileTTF("textures/menu/rainyhearts.ttf", 18.0f);
	opensanstitleUp = io.Fonts->AddFontFromFileTTF("textures/menu/OpenSans_Condensed-Bold.ttf", 160.0f);
	barlowtitleDown = io.Fonts->AddFontFromFileTTF("textures/menu/BarlowCondensed-ExtraBold.ttf", 400.0f);
}

void GUI::inicialitzarTime(float temp) {
	m_time = temp;
}

void GUI::DrawRotatedImage(ImVec2* screenSize, ImTextureID texture, ImVec2 pos, ImVec2 size, float landa)
{
	static float rotation_angle = 0.0f; // Angle inicial
	rotation_angle += ImGui::GetIO().DeltaTime * landa; // Incrementa l'angle basant-se en el temps

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * pos.x, screenSize->y * pos.y));
	ImGui::SetNextWindowSize(ImVec2(1920, 1080));
	ImGui::Begin("Imatge Terra rot", &show_user_windows, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	// Calcula el centre de la imatge dins la finestra
	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	ImVec2 center = ImVec2(window_pos.x + window_size.x / 2, window_pos.y + window_size.y / 2); // posicio imatge

	// Dibuixa la imatge rotada
	// Defineix els quatre punts inicials de la imatge
	ImVec2 points[4] = {
		ImVec2(-size.x, -size.y),
		ImVec2(size.x, -size.y),
		ImVec2(size.x, size.y),
		ImVec2(-size.x, size.y)
	};
	for (int i = 0; i < 4; ++i) {
		float x_new = points[i].x * cos(rotation_angle) - points[i].y * sin(rotation_angle);
		float y_new = points[i].x * sin(rotation_angle) + points[i].y * cos(rotation_angle);
		points[i].x = x_new + center.x;
		points[i].y = y_new + center.y;
	}

	// Dibuixa la imatge rotada
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddImageQuad(
		texture,
		points[0], points[1], points[2], points[3]
	);

	ImGui::End();
}

ImFont* GUI::fontPrincipal() {
	return silkscreen;
}


ImFont* GUI::fontDroidsans() {
	return droidsans;
}

void GUI::inicialitzarSons(irrklang::ISoundEngine* temp_engine, irrklang::ISound* temp_so_alerta, irrklang::ISound* temp_so_nau, irrklang::ISound* temp_musica_menu, irrklang::ISound* temp_musica_partida, float* temp_volum_nau, float* temp_volum_menu, float* temp_volum_alerta, float* temp_volum_partida) {
	engine = temp_engine;
	so_alerta = temp_so_alerta;
	so_nau = temp_so_nau;
	musica_menu = temp_musica_menu;
	musica_partida = temp_musica_partida;
	volum_nau = temp_volum_nau;
	volum_menu = temp_volum_menu;
	volum_alerta = temp_volum_alerta;
	volum_partida = temp_volum_partida;
}

void GUI::inicalitzarInterficieGrafica(ImVec2* screenSize) {
	if (show_fons) {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs;

		//GLuint my_image_texture = loadIMA_SOIL("textures/menu/space2.jpg");
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		// Estableix el color de fons d'ImGui a negre
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Fons de la finestra
		ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Fons del frame
		ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Fons del child
		ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Fons dels popups

		//Imatges de la pantalla inicial
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(*screenSize);
		ImGui::Begin("Imatge", &show_fons, window_flags);
		ImGui::Image((ImTextureID)(intptr_t)fons, *screenSize); // Adjust size as needed
		ImGui::End();
		ImGui::PopStyleVar();
	}

	if (show_pantalla_carrega) {
		MostrarPantallaCarrega(screenSize);
	}

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	if (show_user_windows) {
		MostrarPantallaInicial(screenSize);
	}

	if (show_debug_windows) {
		MostrarMenuDebug(screenSize);
	}

	if (show_menu_game) {
		MostrarPantallaMenu(screenSize);
	}

	if (show_menu_jugador_config) {
		MostrarPantallaMenuJugador(screenSize);
	}

	if (show_selector_planeta_origen && !show_selector_planeta_desti) {
		MostrarPantallaSelector(screenSize, "Selecciona Planeta on començar");
	}

	if (show_selector_planeta_desti && !show_selector_planeta_origen) {
		MostrarPantallaSelectorD(screenSize, "Selecciona Destinació");
	}

	if (show_game_window) {
		MostrarPantallaJoc(screenSize);
	}

	if (show_mapa_windows) {
		MostrarMapaSistemaSolar(screenSize);
	}

	if (show_game_settings) {
		MostrarPantallaConfiguracio(screenSize);
	}

	if (show_winner) {
		MostrarPantallaGuanyador(screenSize);
	}

	if (show_loser) {
		MostrarPantallaGuanyador(screenSize);
	}
}

void GUI::MostrarPantallaInicial(ImVec2* screenSize) {

	if (musica_menu) {
		float volumActual = musica_menu->getVolume();
		if (musica_menu->getIsPaused())
			musica_menu->setIsPaused(false);
		if (volumActual < *volum_menu)
			musica_menu->setVolume(volumActual + 0.0005);
		else if (volumActual > *volum_menu)
			musica_menu->setVolume(*volum_menu);
	}
	if (musica_partida) {
		if (!musica_partida->getIsPaused())
			musica_partida->setIsPaused(true);
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/


	/*ImGui::SetNextWindowPos(ImVec2(-250, screenSize->y - 450));
	ImGui::SetNextWindowSize(ImVec2(700, 700));
	ImGui::Begin("Imatge MARS", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::Image((ImTextureID)(intptr_t)mars, ImVec2(700, 700)); // Adjust size as needed
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.075, screenSize->y * 0.4));
	ImGui::SetNextWindowSize(ImVec2(150, 100));
	ImGui::Begin("Imatge iss", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::Image((ImTextureID)(intptr_t)iss, ImVec2(110, 100)); // Adjust size as needed
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5, screenSize->y * 0.5));
	ImGui::SetNextWindowSize(ImVec2(110, 110));
	ImGui::Begin("Imatge soyut", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::Image((ImTextureID)(intptr_t)soyut, ImVec2(60, 60)); // Adjust size as needed
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.85, screenSize->y * 0.4));
	ImGui::SetNextWindowSize(ImVec2(270, 220));
	ImGui::Begin("Imatge cometa", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::Image((ImTextureID)(intptr_t)cometa, ImVec2(250, 200)); // Adjust size as needed
	ImGui::End();
	*/
	// terra rotatoria menu
	DrawRotatedImage(screenSize, (ImTextureID)(intptr_t)earth, ImVec2(0.0, 0.6), ImVec2(970, 550), 0.15);

	float windowX = screenSize->x * 0.5f - 450;  // Acomoda el desplaçament lateral (325)
	float windowY = screenSize->y * 0.2f;  // Centrar verticalment a la posició 20% de l'altura de la pantalla
	ImGui::SetNextWindowPos(ImVec2(windowX + 160, windowY - 40));
	ImGui::SetNextWindowSize(ImVec2(700, 200));
	ImGui::Begin("TitolUp", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::PushFont(opensanstitleUp);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text("S   O   L   A   R");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(windowX, windowY));
	ImGui::SetNextWindowSize(ImVec2(900, 400));
	ImGui::Begin("TitolDown", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::PushFont(barlowtitleDown);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text("SPRINT");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(10, 200));
	ImGui::SetNextWindowSize(ImVec2(250, 100));

	ImGui::Begin("Opcions", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color del botó (blanc)
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Color quan es passa el ratolí (grisa clara)
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f)); // Color quan es fa clic (grisa)

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
	if (ImGui::Button("Developer", ImVec2(200, 35))) {
		show_debug_windows = true;
		show_user_windows = false;
		show_fons = false;
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::End();

	// Calcula les dimensions de la finestra principal
	ImVec2 windowSize(400, 100);
	// Calcula la posició per centrar la finestra a la pantalla
	ImVec2 windowPos = ImVec2(
		(screenSize->x - windowSize.x) * 0.5f,
		(screenSize->y - windowSize.y) - 50
	);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(440, 150));

	ImGui::Begin("Finestra Usuari", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);


	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color del botó (blanc)
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Color quan es passa el ratolí (grisa clara)
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f)); // Color quan es fa clic (grisa)

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
	// Mida del botó
	//ImGui::SetKeyboardFocusHere();
	//ImGui::PushFont(silkscreensubtitle);

	if (ImGui::Button("Iniciar Simulador", ImVec2(400, 55))) {
		engine->play2D("./media/altres/seleccio_menu.wav", false, false, false);
		show_user_windows = false;
		show_menu_game = true;
	}
	//ImGui::PopFont();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::End();

}


void GUI::MostrarPantallaMenu(ImVec2* screenSize) {

	if (musica_menu) {
		float volumActual = musica_menu->getVolume();
		if (musica_menu->getIsPaused())
			musica_menu->setIsPaused(false);
		if (volumActual < *volum_menu)
			musica_menu->setVolume(volumActual + 0.05);
		else if (volumActual > *volum_menu)
			musica_menu->setVolume(*volum_menu);
	}
	if (musica_partida) {
		if (!musica_partida->getIsPaused())
			musica_partida->setIsPaused(true);
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	// Calcula les dimensions de la finestra principal
	ImVec2 tamany_buttons(400, 55);
	ImVec2 windowSize(tamany_buttons.x, tamany_buttons.y * 5);
	ImVec2 espai(0.0f, 30.0f);

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5 - 250, screenSize->y * 0.2));
	ImGui::SetNextWindowSize(ImVec2(600, 150));
	ImGui::Begin("Titol", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);
	ImGui::PushFont(silkscreensubtitle);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text("Menu Principal");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	//terra rotatoria menu
	DrawRotatedImage(screenSize, (ImTextureID)(intptr_t)earth, ImVec2(0.0, 0.6), ImVec2(970, 550), 0.15);

	// Calcula la posició per centrar la finestra a la pantalla
	ImVec2 windowPos = ImVec2(
		(screenSize->x - windowSize.x) * 0.5f,
		(screenSize->y - windowSize.y) * 0.5f
	);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::Begin("Menus", &show_menu_game, window_flags | ImGuiWindowFlags_NoBackground);
	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color del botó (blanc)
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Color quan es passa el ratolí (grisa clara)
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f)); // Color quan es fa clic (grisa)

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f); // Canvia el valor per ajustar el grau d'arrodoniment

	if (ImGui::Button("Iniciar Partida", tamany_buttons)) {
		engine->play2D("./media/altres/seleccio_menu.wav", false, false, false);
		show_menu_game = false;
		show_selector_planeta_origen = true;
	}

	ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
	if (ImGui::Button("Exploració lliure", tamany_buttons)) {
		engine->play2D("./media/altres/seleccio_menu.wav", false, false, false);
		show_menu_game = false;
		show_pantalla_carrega = false;
		show_game_window = true;
		show_fons = false;
		IniciarSimulador();
	}

	ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
	if (ImGui::Button("Configuració", tamany_buttons)) {
		engine->play2D("./media/altres/seleccio_menu.wav", false, false, false);
		//show_menu_game = false;
		show_game_settings = true;
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::End();
	ImGui::PopStyleVar();
}

void GUI::MostrarPantallaConfiguracio(ImVec2* screenSize) {

	if (musica_menu) {
		float volumActual = musica_menu->getVolume();
		if (musica_menu->getIsPaused())
			musica_menu->setIsPaused(false);
		if (volumActual < *volum_menu)
			musica_menu->setVolume(volumActual + 0.05);
		else if (volumActual > *volum_menu)
			musica_menu->setVolume(*volum_menu);
	}
	if (musica_partida) {
		if (!musica_partida->getIsPaused())
			musica_partida->setIsPaused(true);
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	//Variables de config 
	int posY = 100;
	int marge = 60;

	ImVec2 tamany_buttons(200, 45);
	ImVec2 windowSize(tamany_buttons.x + 40, (tamany_buttons.y + marge) * 3 + 40);
	ImVec2 espai(0.0f, 20.0f);
	float espai_lateral = 100.0f;


	ImVec2 windowPos = ImVec2(screenSize->x - marge * 2, marge); // Ajusta el -250 segons la mida de la finestra
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(marge + 10, marge + 10)); // Mida de la finestra
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

	ImGui::Begin("Endarrera-Config", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);

	ImGui::PushStyleColor(ImGuiCol_Button, ButtonGeneral);      // Color del botó (blanc)
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoverButtonGeneral); // Color quan es passa el ratolí
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveButtonGeneral); // Color quan es fa clic


	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);

	if (ImGui::ImageButton((void*)(intptr_t)endarrera, ImVec2(40, 40))) {
		show_game_settings = false;
		show_config_grafics = true;
		show_config_so = false;
		show_config_controladors = false;
		show_config_credits = false;
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::End();
	ImGui::PopStyleVar();



	//Titol
	ImGui::SetNextWindowPos(ImVec2(marge * 3, marge));
	ImGui::SetNextWindowSize(ImVec2(600, 100));
	ImGui::Begin("Titol-Config", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);
	ImGui::PushFont(silkscreensubtitle);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text("Configuració");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();



	ImGui::SetNextWindowPos(ImVec2(marge, posY + marge), ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
	// Establir el color de fons de la finestra a blanc
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 0.9f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);   // Arrodoniment del borde

	ImGui::Begin("Menus-Config", &show_menu_game, window_flags | ImGuiWindowFlags_NoScrollbar);
	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoverButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_Text, TextMenuPausa);

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f); // Canvia el valor per ajustar el grau d'arrodoniment

	if (ImGui::Button("Interficie", tamany_buttons)) {
		show_config_grafics = true;
		show_config_so = false;
		show_config_controladors = false;
		show_config_credits = false;
	}

	ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
	if (ImGui::Button("So", tamany_buttons)) {
		show_config_grafics = false;
		show_config_so = true;
		show_config_controladors = false;
		show_config_credits = false;
	}

	ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
	if (ImGui::Button("Controladors", tamany_buttons)) {
		show_config_grafics = false;
		show_config_so = false;
		show_config_credits = false;
		show_config_controladors = true;
	}

	ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
	if (ImGui::Button("Credits", tamany_buttons)) {
		show_config_grafics = false;
		show_config_so = false;
		show_config_controladors = false;
		show_config_credits = true;
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(4);
	ImGui::End();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();


	ImVec2 tamany_buttons_dins_config(300, 45);

	ImVec2 subwindowSize(screenSize->x - tamany_buttons.x - marge * 3, screenSize->y - marge * 5);

	ImGui::SetNextWindowPos(ImVec2(tamany_buttons.x + marge * 2, posY + marge), ImGuiCond_Always);
	ImGui::SetNextWindowSize(subwindowSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

	// Establir el color de fons de la finestra a blanc
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);   // Arrodoniment del borde

	ImGui::Begin("subMenus-Config", &show_menu_game, window_flags);
	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoverButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_Text, TextMenuPausa);

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f); // Canvia el valor per ajustar el grau d'arrodoniment

	if (show_config_grafics) {
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Disseny Interficie");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		if (ImGui::ImageButton((void*)(intptr_t)interficie_1, ImVec2(384, 216))) {
			minimapas_circulars = true;
		}
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)(intptr_t)interficie_2, ImVec2(384, 216))) {
			minimapas_circulars = false;
		}


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Opcions MiniMapa i Radar");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		if (ImGui::Button("Centrat Sol/Jugador", tamany_buttons_dins_config)) {
			minimapas_centrat_sol = !minimapas_centrat_sol;
		}
		ImGui::SameLine();
		if (ImGui::Button("Asteroides", tamany_buttons_dins_config)) {
			asteroides_minimapa = !asteroides_minimapa;
		}
		ImGui::SameLine();
		if (ImGui::Button("Diposits", tamany_buttons_dins_config)) {
			diposits_minimapa = !diposits_minimapa;
		}
		ImGui::SameLine();
		if (ImGui::Button("Estacions", tamany_buttons_dins_config)) {
			estacions_minimapa = !estacions_minimapa;
		}

		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		if (ImGui::Button("Orbites Planetes", tamany_buttons_dins_config)) {
			orbites_minimapa = !orbites_minimapa;
		}



		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Butons d'Accions");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		if (ImGui::Button("Dibuixa Orbita Completa", tamany_buttons_dins_config)) {
			paintorbit = !paintorbit;
		}
		ImGui::SameLine();
		if (ImGui::Button("Pantalla Completa", tamany_buttons_dins_config)) {
			OnFull_Screen(primary, window);
			//fullscreen = true;
		}


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Colors Alertes");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		ImVec2 tamany_color_picker = ImVec2(280, 280);

		crearColoPickerFill(&colorVerd, tamany_color_picker, "Correcte");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&colorTaronja, tamany_color_picker, "Alerta");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&colorVermell, tamany_color_picker, "Perill");


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Colors Interficie Principal");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		crearColoPickerFill(&ButtonGeneral, tamany_color_picker, "Buto General");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&HoverButtonGeneral, tamany_color_picker, "Hover Boto General");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&ActiveButtonGeneral, tamany_color_picker, "Clicar Boto General");


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Colors Menus");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		crearColoPickerFill(&Title_config_Color, tamany_color_picker, "Titol");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&ButtonMenuPausa, tamany_color_picker, "Buto Menus");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&HoverButtonMenuPausa, tamany_color_picker, "Hover Boto Menus");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColoPickerFill(&ActiveButtonMenuPausa, tamany_color_picker, "Clicar Boto Menus");


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Colors Interficie");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		crearColorPickerU32(&color_interficie, tamany_color_picker, "Contorns");


		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Colors Minimapes");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels

		crearColorPickerU32(&colorPlanetes, tamany_color_picker, "Planetes");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorAsteroides, tamany_color_picker, "Asteroides");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorAsteroidescinturons, tamany_color_picker, "Cinturo Asteroides");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorPlanetaOrigen, tamany_color_picker, "Planeta Origen");

		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		crearColorPickerU32(&colorPlanetaDesti, tamany_color_picker, "Planeta Destí");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorSol, tamany_color_picker, "Sol");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorEstacions, tamany_color_picker, "Estacions");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + espai_lateral);  // Afegim un altre espai
		crearColorPickerU32(&colorDiposits, tamany_color_picker, "Diposits");

		ImGui::Dummy(espai); // Afegeix un espai vertical de 10 píxels
		crearColorPickerU32(&colorJugador, tamany_color_picker, "Jugador");
		//ImGui::SameLine();


	}
	else if (show_config_so) {
		static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Sons del Joc");
		ImGui::PopStyleColor();
		ImGui::PopFont();

		// Colors personalitzats per als sliders
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));         // Fons del slider
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.25f, 0.25f, 0.25f, 1.0f)); // Quan es passa per sobre
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));   // Quan està actiu
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ButtonMenuPausa.x * 1.2f, ButtonMenuPausa.y * 1.2f, ButtonMenuPausa.z * 1.2f, 1.0f)); // Color del maneig principal
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ButtonMenuPausa.x * 1.4f, ButtonMenuPausa.y * 1.4f, ButtonMenuPausa.z * 1.4f, 1.0f)); // Color del maneig quan es manté arrossegant

		// Ajustos visuals
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f); // Arrodoniment del slider
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 6.0f));  // Espai dins del quadre
		ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 15.0f);                // Mida mínima del maneig
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 12.0f);               // Arrodoniment del maneig

		ImGui::Dummy(espai);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Sons Partida");
		ImGui::PopStyleColor();
		float percentatge_partida = *volum_partida * 100.0f;
		if (ImGui::SliderFloat("partida-sons", &percentatge_partida, 0.0f, 100.0f, "%.0f%%")) {
			*volum_partida = percentatge_partida / 100.0f;
		}

		ImGui::Dummy(espai);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Sons dels Menus");
		ImGui::PopStyleColor();
		float percentatge_menu = *volum_menu * 100.0f;
		if (ImGui::SliderFloat("menus-sons", &percentatge_menu, 0.0f, 100.0f, "%.0f%%")) {
			*volum_menu = percentatge_menu / 100.0f;
		}

		ImGui::Dummy(espai);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Sons del Jugador");
		ImGui::PopStyleColor();
		float percentatge_nau = *volum_nau * 100.0f;
		if (ImGui::SliderFloat("jugador-sons", &percentatge_nau, 0.0f, 100.0f, "%.0f%%")) {
			*volum_nau = percentatge_nau / 100.0f;
		}

		ImGui::Dummy(espai);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Sons Alertes");
		ImGui::PopStyleColor();
		float percentatge_alerta = *volum_alerta * 100.0f;
		if (ImGui::SliderFloat("alertes-sons", &percentatge_alerta, 0.0f, 100.0f, "%.0f%%")) {
			*volum_alerta = percentatge_alerta / 100.0f;
		}

		// Restableix tots els estils
		ImGui::PopStyleVar(4);
		ImGui::PopStyleColor(5);


	}
	else if (show_config_controladors) {
		float tamany_buttons = 360.0f;
		float text_offset_x = 20.0f; // Espai a l'esquerra per al text dins del botó

		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		ImGui::BeginChild("Botons controladors", ImVec2(tamany_buttons, subwindowSize.y - espai.y * 2), true, window_flags);

		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Text("Controls");
		ImGui::PopStyleColor();
		ImGui::PopFont();

		const char* texts[] = {
			"1 - Rotar Esquerra", "2 - Inc Velocitat", "3 - Rotar Dreta",
			"4 - Desplaçament Lateral", "5 - Dec Velocitat", "6 - Desplaçament Lateral",
			"7 - Mirar Cap a Amunt", "8 - Girar Dreta", "9 - Girar Esquerra",
			"10 - Mirar Cap a Baix", "11 - Camara Interior", "12 - Camara desde Davant",
			"13 - Camara Principal", "14 - Menu", "15 - Pantalla Completa",
			"16 - Mapa Gran", "17 - Baixar Nau", "18 - Pujar Nau", "19 - Sense Ús"
		};

		for (int i = 0; i < IM_ARRAYSIZE(texts); ++i) {
			ImVec2 buttonSize = tamany_buttons_dins_config;
			ImVec2 cursorPos = ImGui::GetCursorScreenPos(); // Obtenir la posició actual

			// Crear un botó invisible
			//ImGui::InvisibleButton(("btn" + std::to_string(i)).c_str(), buttonSize);
			ImU32 color_u32 = ImGui::ColorConvertFloat4ToU32(ButtonMenuPausa);

			// Dibuixar manualment el text a l'esquerra
			ImGui::GetWindowDrawList()->AddText(
				ImVec2(cursorPos.x + text_offset_x, cursorPos.y + buttonSize.y / 2 - ImGui::GetFontSize() / 2),
				color_u32, // Color del text (negre)
				texts[i]
			);

			ImGui::Dummy(ImVec2(espai.x, espai.y * 2)); // Espai entre botons
		}

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SameLine();


		float borderRadius = 20.0f; // Arrodoniment dels bordes
		float borderWidth = 4.0f;   // Amplada del contorn
		ImVec2 childSize = ImVec2(subwindowSize.x - tamany_buttons - marge + 10, subwindowSize.y - espai.y * 2);
		ImVec2 imageSize = ImVec2(subwindowSize.x - tamany_buttons - marge + 10, subwindowSize.y - espai.y * 2);

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 childMin = pos;
		ImVec2 childMax = ImVec2(pos.x + childSize.x, pos.y + childSize.y);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("imatge controladors", childSize, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImVec2 imageMin = ImVec2(pos.x + borderWidth / 2, pos.y + borderWidth / 2);
		ImVec2 imageMax = ImVec2(pos.x + imageSize.x - borderWidth / 2, pos.y + imageSize.y - borderWidth / 2);
		drawList->AddImageRounded((ImTextureID)(intptr_t)controls, imageMin, imageMax, ImVec2(0, 0), ImVec2(1, 1), ImColor(1.0f, 1.0f, 1.0f, 1.0f), borderRadius - 2);

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		if (borderWidth > 0.0f) {
			drawList->AddRect(childMin, childMax, ImColor(ButtonMenuPausa), borderRadius, ImDrawFlags_RoundCornersAll, borderWidth);
		}
	}
	else if (show_config_credits)
	{
		ImVec2 windowSize = ImGui::GetWindowSize();

		const char* noms[] = {
			"Martí Armengod Villar",
			"Lara Castillejo Roig",
			"Ismael Fernandez Zarza",
			"Julia Lipin Gener Rey",
			"Joan Marc Samó Rojas",
			"Luis Vera Albarca"
		};

		ImGui::PushFont(silkscreenh3);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa);
		ImGui::Dummy(ImVec2(0.0f, 150.0f));
		for (const char* nom : noms) {
			// Calcular la mida del text
			ImVec2 textSize = ImGui::CalcTextSize(nom);

			// Calcular la posició horitzontal per centrar el text
			float textPosX = (windowSize.x - textSize.x) * 0.5f;

			ImGui::SetCursorPosX(textPosX);

			ImGui::Text("%s", nom);
			ImGui::Dummy(ImVec2(0.0f, 30.0f));
		}
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		ImGui::PopFont();

	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(4);
	ImGui::End();
	// Retorn del color de fons original
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}

void GUI::crearColoPickerFill(ImVec4* color, ImVec2 tamany, const char* text) {
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_HDR
		| ImGuiColorEditFlags_NoDragDrop
		| ImGuiColorEditFlags_AlphaPreview
		| ImGuiColorEditFlags_AlphaBar
		| ImGuiColorEditFlags_NoSidePreview
		| ImGuiColorEditFlags_PickerHueBar
		| ImGuiColorEditFlags_DisplayRGB
		| ImGuiColorEditFlags_InputRGB; // Suport per entrades numèriques en RGB

	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);  // Elimina el marge del "child"
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Fons gris fosc per al "child"

	ImGui::BeginChild(text, tamany, true, ImGuiWindowFlags_NoScrollbar);  // Defineix la regió
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));  // Text blanc
	ImGui::Text(text);
	ImGui::PopStyleColor(); // Restableix el color del text

	ImGui::PushItemWidth(-1); // Perquè el color picker ocupi tot l'espai disponible
	ImGui::ColorPicker4(text, (float*)color, flags);

	ImGui::EndChild();
	ImGui::PopStyleColor(); // Restableix el color de fons
	ImGui::PopStyleVar();   // Restableix els marges
}


void GUI::crearColorPickerU32(ImU32* color, ImVec2 tamany, const char* text) {
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_HDR
		| ImGuiColorEditFlags_NoDragDrop
		| ImGuiColorEditFlags_AlphaPreview
		| ImGuiColorEditFlags_AlphaBar
		| ImGuiColorEditFlags_NoSidePreview
		| ImGuiColorEditFlags_PickerHueBar
		| ImGuiColorEditFlags_DisplayRGB
		| ImGuiColorEditFlags_InputRGB; // Suport per entrades numèriques en RGB

	// Converteix ImU32 a ImVec4
	ImVec4 colorVec4 = ImGui::ColorConvertU32ToFloat4(*color);

	// Estil i configuració
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f); // Elimina el marge del "child"
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Fons blanc per al "child"

	ImGui::BeginChild(text, tamany, true, ImGuiWindowFlags_NoScrollbar); // Defineix la regió

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	ImGui::Text(text);
	ImGui::PopStyleColor();

	ImGui::PushItemWidth(-1); // Perquè el color picker ocupi tot l'espai disponible
	if (ImGui::ColorPicker4(text, (float*)&colorVec4, flags)) {
		// Si l'usuari modifica el color, actualitza l'ImU32
		*color = ImGui::ColorConvertFloat4ToU32(colorVec4);
	}

	ImGui::EndChild();
	ImGui::PopStyleColor(); // Restableix el color de fons
	ImGui::PopStyleVar();   // Restableix els marges
}



void GUI::MostrarPantallaSelector(ImVec2* screenSize, const char* descripcio) {

	if (musica_menu) {
		float volumActual = musica_menu->getVolume();
		if (musica_menu->getIsPaused())
			musica_menu->setIsPaused(false);
		if (volumActual < *volum_menu)
			musica_menu->setVolume(volumActual + 0.05);
		else if (volumActual > *volum_menu)
			musica_menu->setVolume(*volum_menu);
	}
	if (musica_partida) {
		if (!musica_partida->getIsPaused())
			musica_partida->setIsPaused(true);
	}



	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5 - 550, screenSize->y * 0.2));
	ImGui::SetNextWindowSize(ImVec2(1200, 150));
	ImGui::Begin("Titol", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);
	ImGui::PushFont(silkscreensubtitle);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text(descripcio);
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	//terra rotatoria menu
	DrawRotatedImage(screenSize, (ImTextureID)(intptr_t)earth, ImVec2(0.0, 0.6), ImVec2(970, 550), 0.15);

	int padding = 15;
	ImVec2 buttonSize(150, 150);
	ImVec2 windowSize((buttonSize.x + padding) * PLANETES.size(), buttonSize.y + 50);
	ImVec2 windowPos = ImVec2(
		(screenSize->x - windowSize.x) * 0.5f,
		(screenSize->y - windowSize.y) * 0.5f
	);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin(descripcio, &show_selector_planeta_origen, window_flags | ImGuiWindowFlags_NoBackground);

	for (int i = 0; i < PLANETES.size(); i++) {

		// Calcula la posició del botó basant-te en l'índex
		ImVec2 buttonPos = ImVec2(
			i * (buttonSize.x + padding),
			0  // Tots els botons estan en la mateixa fila
		);
		ImGui::SetCursorPos(buttonPos);  // Ajusta la posició del botó

		// Aplica els estils
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));  // Fons transparent
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));  // Fons semi-transparent en hover
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));  // Fons transparent actiu
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  // Text blanc
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);  // Arrodoniment

		// Crea el botó d'imatge
		if (ImGui::ImageButton((void*)(intptr_t)PLANETES[i].getTextureIDMenu(), buttonSize)) {
			show_selector_planeta_origen = false;
			show_selector_planeta_desti = true;
			PlanetOrigen = i;
			/*std::cout << "show_selector_planeta_origen ->" << show_selector_planeta_origen << std::endl;
			std::cout << "show_selector_planeta_desti ->" << show_selector_planeta_desti << std::endl;*/
		}

		// Calcula la posició del text
		ImVec2 textSize = ImGui::CalcTextSize(PLANETES[i].getName().c_str());
		ImVec2 textPos = ImVec2(
			buttonPos.x + (buttonSize.x - textSize.x) * 0.5f,  // Centrat horitzontalment respecte al botó
			buttonSize.y + 10  // Per sota del botó
		);
		ImGui::SetCursorPos(textPos);
		ImGui::Text(PLANETES[i].getName().c_str());

		// Finalitza l'estil
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(4);
	}

	ImGui::End();

}

void GUI::MostrarPantallaSelectorD(ImVec2* screenSize, const char* descripcio) {

	if (musica_menu) {
		musica_menu->setIsPaused(false); // Pausa el sonido
		musica_menu->setVolume(*volum_menu);  // Cambia el volumen (0.0 a 1.0)
		//musica->setPlaybackSpeed(1.5f); // Cambia la velocidad de reproducción
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5 - 400, screenSize->y * 0.2));
	ImGui::SetNextWindowSize(ImVec2(1200, 150));
	ImGui::Begin("Titol", &show_user_windows, window_flags | ImGuiWindowFlags_NoBackground);
	ImGui::PushFont(silkscreensubtitle);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text(descripcio);
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	//origen rotatori menu
	DrawRotatedImage(screenSize, (ImTextureID)(intptr_t)PLANETES[PlanetOrigen].getTextureIDMenuSelect(), ImVec2(0.0, 0.6), ImVec2(970, 550), 0.15);

	int padding = 15;
	ImVec2 buttonSize(150, 150);
	ImVec2 windowSize((buttonSize.x + padding) * PLANETES.size(), buttonSize.y + 50);
	ImVec2 windowPos = ImVec2(
		(screenSize->x - windowSize.x) * 0.5f + 100,
		(screenSize->y - windowSize.y) * 0.5f
	);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin(descripcio, &show_selector_planeta_origen, window_flags | ImGuiWindowFlags_NoBackground);
	int continuiti = 0;
	for (int i = 0; i < PLANETES.size(); i++) {

		if (i == PlanetOrigen)
			continue; // Salta aquest planeta

		// Calcula la posició del botó basant-te en l'índex
		ImVec2 buttonPos = ImVec2(
			continuiti * (buttonSize.x + padding),
			0  // Tots els botons estan en la mateixa fila
		);
		ImGui::SetCursorPos(buttonPos);  // Ajusta la posició del botó

		// Aplica els estils
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));  // Fons transparent
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));  // Fons semi-transparent en hover
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));  // Fons transparent actiu
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  // Text blanc
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);  // Arrodoniment

		// Crea el botó d'imatge
		if (ImGui::ImageButton((void*)(intptr_t)PLANETES[i].getTextureIDMenu(), buttonSize)) {
			show_selector_planeta_desti = false;
			show_pantalla_carrega = true;
			PlanetDesti = i;
			/*std::cout << "---------------------------------------------------------------" << std::endl;
			std::cout << "show_selector_planeta_origen ->" << show_selector_planeta_origen << std::endl;
			std::cout << "show_selector_planeta_desti ->" << show_selector_planeta_desti << std::endl;
			std::cout << "..............................................................................................." << std::endl;*/
		}

		// Calcula la posició del text
		ImVec2 textSize = ImGui::CalcTextSize(PLANETES[i].getName().c_str());
		ImVec2 textPos = ImVec2(
			buttonPos.x + (buttonSize.x - textSize.x) * 0.5f,  // Centrat horitzontalment respecte al botó
			buttonSize.y + 10  // Per sota del botó
		);
		ImGui::SetCursorPos(textPos);
		ImGui::Text(PLANETES[i].getName().c_str());

		// Finalitza l'estil
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(4);
		continuiti++;
	}

	ImGui::End();
}

void GUI::MostrarPantallaCarrega(ImVec2* screenSize) {


	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5 - 550, screenSize->y * 0.5));
	ImGui::SetNextWindowSize(ImVec2(1200, 150));
	ImGui::Begin("Pantalla Carrega", &show_pantalla_carrega, window_flags + ImGuiWindowFlags_NoBackground);
	ImGui::PushFont(silkscreentitle);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc
	ImGui::Text("Carregant .......");
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();
	show_pantalla_carrega = false;
	show_game_window = true;
	show_fons = false;
	IniciarSimulador();
}

// Funció per calcular la distància euclidiana entre dos punts
float GUI::distanciaEuclidiana(const vec3& point1, const vec3& point2) {
	return std::sqrt(std::pow(point2.x - point1.x, 2) +
		std::pow(point2.y - point1.y, 2) +
		std::pow(point2.z - point1.z, 2));
}

void GUI::CircularProgressBar(const char* label, float progress, const ImVec2& size, const ImVec4& color) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGui::BeginGroup();
	ImGui::PushID(label);
	ImGui::Text(label);
	ImGui::Spacing();
	ImVec2 pos = ImGui::GetCursorScreenPos();
	float circleRadius = ImMin(size.x, size.y) * 0.5f;
	ImVec2 center = ImVec2(pos.x + circleRadius, pos.y + circleRadius);

	float arcAngle = 2.0f * IM_PI * progress;

	const ImU32 bgColor = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	window->DrawList->AddCircleFilled(center, circleRadius + 5, bgColor, 32);

	if (progress > 0.0f) {
		ImVec2 innerPos(center.x - circleRadius, center.y - circleRadius);
		ImVec2 outerPos(center.x + circleRadius, center.y + circleRadius);
		//window->DrawList->PathArcTo(center, circleRadius, -IM_PI * 0.5f, -IM_PI * 0.5f - arcAngle, 32);
		window->DrawList->PathArcTo(center, circleRadius, -IM_PI * 0.5f, -IM_PI * 0.5f + arcAngle, 32);
		window->DrawList->PathStroke(ImGui::GetColorU32(color), false, 10.0f);
	}

	char textBuffer[32];
	snprintf(textBuffer, sizeof(textBuffer), "%.0f%%", progress * 100.0f);
	ImVec2 textSize = ImGui::CalcTextSize(textBuffer);
	ImVec2 textPos = ImVec2(center.x - textSize.x * 0.5f, center.y - textSize.y * 0.5f);
	window->DrawList->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), textBuffer);

	ImGui::PopID();
	ImGui::EndGroup();
}

void GUI::MostrarPantallaMenuJugador(ImVec2* screenSize) {

	if (musica_menu) {
		float volumActual = musica_menu->getVolume();
		if (musica_menu->getIsPaused())
			musica_menu->setIsPaused(false);
		if (volumActual < *volum_menu)
			musica_menu->setVolume(volumActual + 0.05);
		else if (volumActual > *volum_menu)
			musica_menu->setVolume(*volum_menu);
	}
	if (musica_partida) {
		if (!musica_partida->getIsPaused())
			musica_partida->setIsPaused(true);
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/
	// Calcula les dimensions de la finestra principal
	ImVec2 tamany_buttons(400, 55);
	ImVec2 windowSize(tamany_buttons.x + 40, tamany_buttons.y * 8);
	ImVec2 espai(0.0f, 30.0f);

	// Calcula la posició per centrar la finestra a la pantalla
	ImVec2 windowPos = ImVec2(
		(screenSize->x - windowSize.x) * 0.5f,
		(screenSize->y - windowSize.y) * 0.4f
	);

	// Configura el padding de la finestra
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20)); // Marge de 20 píxels
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 20.0f); // Cantonades rodones de 15 píxels

	// Configura el color de fons blanc
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // negre opac
	ImGui::PushStyleColor(ImGuiCol_WindowBg, FonsMenuPausa);

	ImGui::Begin("Menus", &show_menu_game, window_flags);

	// Configura els colors i l'estil dels botons
	ImGui::PushStyleColor(ImGuiCol_Button, ButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoverButtonMenuPausa);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveButtonMenuPausa);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f); // Arrodoniment de 12 píxels per als botons

	// Centra el text "Menu"

	ImGui::PushStyleColor(ImGuiCol_Text, Title_config_Color);
	ImGui::PushFont(silkscreensubtitle);

	ImVec2 textSize = ImGui::CalcTextSize("Menu"); // Mida del text
	float textPosX = (windowSize.x - textSize.x) * 0.5f; // Calcula la posició X centrada
	ImGui::SetCursorPosX(textPosX); // Situa el cursor al punt centrat
	ImGui::Text("Menu");

	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::PushStyleColor(ImGuiCol_Text, TextMenuPausa);

	// Dibuixa espais i botons
	ImGui::Dummy(espai);

	if (ImGui::Button("Continuar", tamany_buttons)) {
		show_menu_jugador_config = !show_menu_jugador_config;
		pause = !pause;
	}

	ImGui::Dummy(espai);
	if (ImGui::Button("Configuració", tamany_buttons)) {
		show_game_settings = true;
	}

	ImGui::Dummy(espai);
	if (ImGui::Button("Sortir del Joc", tamany_buttons)) {
		glfwSetWindowShouldClose(window, GL_TRUE);  // Marca la finestra per tancar
	}

	ImGui::PopStyleVar(); // Padding
	ImGui::PopStyleColor(3);
	ImGui::End();

	// Recupera els estils generals
	ImGui::PopStyleVar(2); // Padding
	ImGui::PopStyleColor(); // Background


}

void GUI::DibuixarBarraDistanciaPlaneta(float distancePercentage, ImVec2 bar, ImVec2 position){

	// Crear una finestra invisible per col·locar la barra en la posició correcta
	ImGui::SetNextWindowPos(position, ImGuiCond_Always);
	ImGui::SetNextWindowSize(bar, ImGuiCond_Always);
	ImGui::Begin("PlanetaDistanciaBarra", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

	// Dibuixar la barra horitzontal amb vores rodones
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);  // Vores rodones
	ImGui::PushStyleColor(ImGuiCol_FrameBg, color_interficie);  // Color de fons de la barra
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ButtonMenuPausa);  // Canviar el color de la barra

	ImGui::SameLine(0.0f, 50.0f);  // Espai entre la imatge i la barra
	ImGui::Image((void*)(intptr_t)PLANETES[PlanetOrigen].getTextureIDMenu(), ImVec2(30, 30));  // Imatge del planeta origen
	ImGui::SameLine(0.0f, 10.0f);  // Espai entre la imatge i la barra
	// Crear la barra horitzontal
	ImGui::ProgressBar(distancePercentage, ImVec2(0.0f, 0.0f));
	ImGui::SameLine(0.0f, 10.0f);  // Espai entre la imatge i la barra
	ImGui::Image((void*)(intptr_t)PLANETES[PlanetDesti].getTextureIDMenu(), ImVec2(30, 30));  // Imatge del planeta destí

	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar();

	// Dibuixar les imatges dels planetes

	ImGui::End();
}

void GUI::dibuixarOrbita2D(Planeta& planeta, ImVec2 minimapSize, ImVec2 minimapPosition, ImDrawList* drawList, bool circular, float radius, ImVec2 center, bool centratsol) {
	const int numPoints = 100;
	double a = planeta.getSemieixMajor() * AU_IN_METERS * ESCALA_DISTANCIA; // Semieje mayor escalado
	double e = planeta.getExcentricitat(); // Excentricitat
	double inclinacio = planeta.getInclinacio() * DEG_A_RAD; // Inclinació en radians
	double longNodeAsc = planeta.getLongitudNodeAscendent() * DEG_A_RAD; // Longitud del node ascendent
	double periapsis = planeta.getPeriapsis() * DEG_A_RAD; // Argument del periapsis

	// Matrius de rotació per transformar l'òrbita del pla orbital al espai 3D
	glm::mat3 R_periapsis = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)periapsis, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat3 R_inclinacio = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)inclinacio, glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat3 R_longNodeAsc = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)longNodeAsc, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat3 R = R_longNodeAsc * R_inclinacio * R_periapsis;

	// Contenidor per a punts de l'òrbita
	std::vector<ImVec2> orbitPoints;
	std::vector<std::vector<ImVec2>> orbitSegments;
	std::vector<ImVec2> currentSegment;

	for (int i = 0; i < numPoints; ++i) {
		// Càlcul de coordenades
		double nu = 2.0 * PI * i / numPoints;
		double r = a * (1 - e * e) / (1 + e * cos(nu));  // Radi en cada punt
		double x_orb = r * cos(nu);
		double y_orb = r * sin(nu);
		double z_orb = 0.0;
		glm::dvec3 posicion_orb(x_orb, y_orb, 0.0);
		ImVec2 minimapPoint;

		if (centratsol) {
			minimapPoint = convertirAPosicioMiniMapa(glm::vec3(x_orb, y_orb, z_orb), glm::vec3(tamanySS, tamanySS, 0), minimapSize, minimapPosition);
		}
		else {
			minimapPoint = convertirAPosicioMiniMapaDesdeJugador(glm::vec3(x_orb, y_orb, z_orb), glm::vec3(tamanySS, tamanySS, 0), minimapSize, minimapPosition, nau->getO());
		}

		// Comprovar si el punt està dins del radi
		bool insideCircle = (circular) ? distanciaEntrePunts(minimapPoint, center) <= radius : true;

		// Afegir el punt només si compleix les condicions
		if (insideCircle) {
			currentSegment.push_back(minimapPoint);
		}
		else if (!currentSegment.empty()) {
			// Si el segment actual té punts, emmagatzema'l i comença un de nou
			orbitSegments.push_back(currentSegment);
			currentSegment.clear();
		}
	}

	// Emmagatzemar l'últim segment
	if (!currentSegment.empty()) {
		orbitSegments.push_back(currentSegment);
	}

	// Tancar el cercle connectant l'últim punt amb el primer
	if (orbitSegments.size() >= 1) {
		orbitSegments[orbitSegments.size() - 1].push_back(orbitSegments[0][0]);
	}

	// Dibuixar els segments de l'òrbita
	for (const auto& segment : orbitSegments) {
		if (segment.size() > 1) {
			drawList->AddPolyline(segment.data(), segment.size(), IM_COL32(200, 200, 200, 255), false, 1.0f);
		}
	}
}


void GUI::DrawSpeedometer(float value, float maxValue, float centerX, float centerY, float radius, bool isRPM) {
	float startAngle = 0; // Starting angle (90 degrees)

	// Draw background circle (speedometer face)
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddCircleFilled(ImVec2(centerX, centerY), radius, IM_COL32(0, 0, 0, 255)); // black background

	// Draw border
	float borderRadius = radius + 10.0f;
	drawList->AddCircle(ImVec2(centerX, centerY), borderRadius, IM_COL32(255, 255, 255, 255), 50, 6.0f); // White border with thicker line

	// Draw the scale marks (lines) around the circle
	int numMarks = 20;
	for (int i = 0; i <= numMarks; ++i) {
		float angle = startAngle - i * (PI / (numMarks / 2));
		ImVec2 markerStart = ImVec2(centerX + radius * cos(angle), centerY - radius * sin(angle));
		ImVec2 markerEnd = ImVec2(centerX + (radius - 20) * cos(angle), centerY - (radius - 20) * sin(angle));

		if (i < numMarks / 3) {
			drawList->AddLine(markerStart, markerEnd, IM_COL32(0, 255, 0, 255), 4.0f); // Green for safe
		}
		else if (i < 2 * numMarks / 3) {
			drawList->AddLine(markerStart, markerEnd, IM_COL32(255, 165, 0, 255), 4.0f); // Orange for caution
		}
		else {
			drawList->AddLine(markerStart, markerEnd, IM_COL32(255, 0, 0, 255), 4.0f); // Red for danger
		}
	}

	// Draw the text (unit values)
	for (int i = 0; i <= numMarks; ++i) {
		float angle = startAngle - i * (PI / (numMarks / 2));
		float unitValue = (i / float(numMarks)) * maxValue;
		ImVec2 textPos = ImVec2(centerX + (radius - 30) * cos(angle), centerY - (radius - 30) * sin(angle));

		char text[10];
		snprintf(text, sizeof(text), "%.0f", unitValue);
		drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), text);
	}

	// Draw the needle
	float angle = startAngle - (value / maxValue) * PI;  // Calculate needle position
	ImVec2 needleEnd = ImVec2(centerX + (radius - 10) * cos(angle), centerY - (radius - 10) * sin(angle));
	drawList->AddLine(ImVec2(centerX, centerY), needleEnd, IM_COL32(255, 0, 0, 255), 6.0f); // Red needle

	// Draw the RPM or km/h text in the center
	const char* label = isRPM ? "RPM x1000" : "km/h";
	ImGui::SetCursorPos(ImVec2(centerX - 50, centerY + radius + 10));
	ImGui::Text("%s", label);

	// Draw the current value text in the center
	ImGui::SetCursorPos(ImVec2(centerX - 20, centerY - 10));
	ImGui::Text("%.0f", value);
}

void GUI::MostrarMapaSistemaSolar(ImVec2* screenSize) {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/

	ImVec2 windowMapaSize(1600, 880);

	// Definir proporció de la llegenda i del mapa (ex: 20% llegenda, 80% mapa)
	float llegendaRatio = 0.2f;
	float mapaRatio = 1.0f - llegendaRatio;
	float marge = 20.0f;

	// Calcular les mides de la llegenda i del mapa
	ImVec2 TitleSize(windowMapaSize.x, 80);
	ImVec2 LlegendaSize(windowMapaSize.x * llegendaRatio, windowMapaSize.y - TitleSize.y - marge);
	ImVec2 MapaSize(windowMapaSize.x * mapaRatio - marge, windowMapaSize.y - TitleSize.y - marge);

	// Posició de la finestra principal
	ImVec2 windowMapaPosition = ImVec2((screenSize->x - windowMapaSize.x) / 2, (screenSize->y - windowMapaSize.y) / 2);

	// Posicions relatives dins de la finestra
	ImVec2 LlegendaPosition = ImVec2(marge, TitleSize.y);
	ImVec2 MapaPosition = ImVec2(LlegendaSize.x + marge, TitleSize.y); // El mapa comença després de la llegenda

	// Configurar la finestra principal
	ImGui::SetNextWindowSize(windowMapaSize);
	ImGui::SetNextWindowPos(windowMapaPosition);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(marge, marge));
	// Establir el color de fons de la finestra a blanc
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 0.9f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);   // Arrodoniment del borde

	if (ImGui::Begin("Mapa Gran", nullptr, window_flags)) {
		//Titol
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("Titol mapa", TitleSize, true, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
		ImGui::PushFont(silkscreensubtitle);
		ImGui::PushStyleColor(ImGuiCol_Text, ButtonMenuPausa); // Color blanc
		ImGui::Text("Mapa Sistema Solar");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::EndChild();

		// Configura els colors i l'estil
		ImGui::PushStyleColor(ImGuiCol_Button, ButtonMenuPausa);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoverButtonMenuPausa);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveButtonMenuPausa);
		ImGui::PushStyleColor(ImGuiCol_Text, TextMenuPausa);

		// Arrodoniment
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f); // Canvia el valor per ajustar el grau d'arrodoniment

		ImVec2 tamany_botons(LlegendaSize.x - marge * 2, 40);
		// Dibuixar la llegenda
		ImGui::SetCursorPos(LlegendaPosition);
		ImGui::BeginChild("Llegenda", LlegendaSize, false, ImGuiWindowFlags_NoBackground);
		if (ImGui::Button("On/Off Asteroides", tamany_botons)) {
			asteroides_minimapa = !asteroides_minimapa;
		}
		ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Espai vertical entre botons
		if (ImGui::Button("On/Off Estacions", tamany_botons)) {
			estacions_minimapa = !estacions_minimapa;
		}
		ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Espai vertical entre botons
		if (ImGui::Button("On/Off Diposits", tamany_botons)) {
			diposits_minimapa = !diposits_minimapa;
		}
		ImGui::Dummy(ImVec2(0.0f, 10.0f)); // Espai vertical entre botons
		if (ImGui::Button("On/Off Orbites", tamany_botons)) {
			orbites_minimapa = !orbites_minimapa;
		}
		ImGui::EndChild();
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar();

		// Dibuixar el mapa del sistema solar
		ImGui::SetCursorPos(MapaPosition);
		ImGui::BeginChild("Mapa Sistema Solar", MapaSize, false, ImGuiWindowFlags_NoBackground);
		float temp = tamanySS;
		tamanySS = tamanySS * 10;
		crearMiniMapaCentratSol(MapaSize, MapaPosition);
		tamanySS = temp;
		ImGui::EndChild();

	}
	ImGui::End();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();
}

void GUI::MostrarPantallaJoc(ImVec2* screenSize) {

	if (musica_menu) {
		if (!musica_menu->getIsPaused())
		{
			if (musica_menu->getVolume() > 0)
				musica_menu->setVolume(musica_menu->getVolume() - 0.015);
			else
				musica_menu->setIsPaused(true);
		}
	}

	if (musica_partida) {
		if (musica_partida->getIsPaused())
			musica_partida->setIsPaused(false);
		if (musica_partida->getVolume() != *volum_partida)
			musica_partida->setVolume(*volum_partida);
	}


	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse;
	/*if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	*/



	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(60, 60));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

	ImGui::Begin("Opcions", &show_user_windows, window_flags + ImGuiWindowFlags_NoBackground);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	// Configura els colors i l'estil
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color del botó (blanc)
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Color quan es passa el ratolí (grisa clara)
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f)); // Color quan es fa clic (grisa)

	// Arrodoniment
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);
	//if (ImGui::Button("Planetes", ImVec2(200, 35))) {
	if (ImGui::ImageButton((void*)(intptr_t)menu, ImVec2(30, 30))) {
		show_menu_jugador_config = !show_menu_jugador_config;
		pause = !pause;
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::End();
	ImGui::PopStyleVar();

	//std::cout << std::endl;
	vec3 posnau = nau->getO();

	//std::cout << " x :" << posnau.x << "  y :" << posnau.y << "  z :" << posnau.z << std::endl;
	//bool isNearAnyPlanet = false;
	float llindar = DISTANCIA_DEFAULT_TERRA * 0.4;  // Llindar de distància per determinar si estàs a prop (per exemple, 10 unitats)
	float llindarAlertaPerill = DISTANCIA_DEFAULT_TERRA * 0.1;  // Llindar de distància per determinar si estàs a prop (per exemple, 10 unitats)
	float minim = std::numeric_limits<float>::infinity();  // Llindar de distància per determinar si estàs a prop (per exemple, 10 unitats)
	int planetaAprop = -1;
	int planetaMoltAprop = -1;

	// Iterar per cada planeta
	for (int i = 0; i < PLANETES.size(); ++i) {
		//std::cout << std::endl;
		vec3 temp = PLANETES[i].getPosition();
		float distPrevia = distanciaEuclidiana(posnau, PLANETES[i].getPosition());
		//std::cout << "Vector Planeta " << PLANETES[i].getName() << ": " << " x :" << temp.x << "  y :" << temp.y << "  z :" << temp.z << std::endl;
		//std::cout << "Distancia al planeta " << PLANETES[i].getName() << ": " << distPrevia << std::endl;
		//std::cout << "Radi planeta " << PLANETES[i].getName() << ": " << PLANETES[i].getRadi() << std::endl;

		float dist = distPrevia - PLANETES[i].getRadi();
		//std::cout << "Distancia Definitiva " << PLANETES[i].getName() << ": " << dist << std::endl;

		// Comprovar si el punt està a prop del planeta
		if (dist < llindar && minim > dist) {
			minim = dist;
			planetaAprop = i;
			// Comprovar si el punt està MOLT a prop del planeta
			if (dist < llindarAlertaPerill) {
				planetaMoltAprop = i;
				//isNearAnyPlanet = true;
				//std::cout << "Estàs MOLT APROP " << PLANETES[i].getName() << "!" << std::endl;
				if (so_alerta) {
					if (so_alerta->getVolume() < *volum_alerta)
						so_alerta->setVolume(so_alerta->getVolume() + 0.15);
					else if (so_alerta->getVolume() > *volum_alerta)
						so_alerta->setVolume(*volum_alerta);

					if (so_alerta->getVolume() > 0)
						so_alerta->setIsPaused(false);
				}
			}
			else
			{
				if (so_alerta) { //luis desactivar alerta
					if (so_alerta->getVolume() > 0)
						so_alerta->setVolume(so_alerta->getVolume() - 0.02);

					if (so_alerta->getVolume() <= 0)
						so_alerta->setIsPaused(true);
				}
			}
			//std::cout << "Estàs a prop del planeta " << PLANETES[i].getName() << "!" << std::endl;
			//std::cout << std::endl;
			//isNearAnyPlanet = true;
		}

	}

	/*if (!isNearAnyPlanet) {
		std::cout << "Estàs massa lluny de tots els planetes." << std::endl;
	}*/
	//std::cout << PLANETES[PlanetOrigen].getPosition().x << std::endl;
	ImVec2 winsize(200, 35);
	ImGui::SetNextWindowPos(ImVec2(screenSize->x - winsize.x - 10, 10.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(winsize);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, colorVerd); // Fons verd brillant (#00bf63)
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::Begin("Opcions", &show_user_windows, window_flags);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc

	if (planetaAprop >= 0) {
		ImVec2 textSize = ImGui::CalcTextSize(PLANETES[planetaAprop].getName().c_str());
		ImVec2 textPos = ImVec2(
			(winsize.x - textSize.x) * 0.5f, // Centrat horitzontalment dins de la finestra
			(winsize.y - textSize.y) * 0.5f  // Centrat verticalment dins de la finestra
		);
		ImGui::SetCursorPos(textPos);
		ImGui::Text(PLANETES[planetaAprop].getName().c_str());
	}
	else {
		ImVec2 textSize = ImGui::CalcTextSize("Espai Exterior");
		ImVec2 textPos = ImVec2(
			(winsize.x - textSize.x) * 0.5f, // Centrat horitzontalment dins de la finestra
			(winsize.y - textSize.y) * 0.5f  // Centrat verticalment dins de la finestra
		);
		ImGui::SetCursorPos(textPos);
		ImGui::Text("Espai Exterior");
	}

	ImGui::PopStyleColor();
	ImGui::End();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	if (planetaMoltAprop >= 0) {
		AfegirAlerta(3, "Alerta !!! Orbita Baixa Perill",2.0f);
	}


	//DrawSpeedometer(nau->getPotencia() * 1000, 10000.0f, 300.0f, 300.0f, 150.0f, true); // RPM speedometer (3000 RPM)
	//DrawSpeedometer(120.0f, 280.0f, 600.0f, 150.0f, 150.0f, false); // km/h speedometer (120 km/h)

	ImVec2 windowSizeVelocimetres(400, 180);
	ImVec2 windowPosVelocimetres = ImVec2(20, screenSize->y - windowSizeVelocimetres.y-180);
	ImGui::SetNextWindowPos(windowPosVelocimetres, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSizeVelocimetres);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 0));
	double velocitat = nau->getSpeed();

	double dist = distanciaEuclidiana(nau->getO(), PLANETES[PlanetDesti].getPosition()) - PLANETES[PlanetDesti].getRadi();
	double distOrigen = distanciaEuclidiana(PLANETES[PlanetOrigen].getPosition(), PLANETES[PlanetDesti].getPosition()) - PLANETES[PlanetOrigen].getRadi() - PLANETES[PlanetDesti].getRadi();

	if (ImGui::Begin("Velocimetres", nullptr, window_flags | ImGuiWindowFlags_NoBackground)) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::Text("Velocitat: %.2f LightSpeed", velocitat); 
		if (PlanetOrigen != -1 && PlanetDesti != -1) {
			ImGui::Text("Distancia: %.2f ", dist);
			ImGui::Text("Distancia Origen: %.2f ", distOrigen);
		}
		ImGui::Text("Temps: %.2f ", m_time);
		//ImGui::Text("Puntuació: %.2f ", m_time);

		//DrawSpeedometer(nau->getPotencia() * 1000, 10000.0f, 0.0f, 150.0f, 150.0f, true); // RPM speedometer (3000 RPM)
		//DrawSpeedometer(120.0f, 280.0f, 600.0f, 150.0f, 150.0f, false); // km/h speedometer (120 km/h)
		ImGui::PopStyleColor();
	}

	ImGui::End();
	ImGui::PopStyleVar();

	if (PlanetOrigen != -1 && PlanetDesti != -1) {
		float totalDistance = distOrigen;  // Distància total
		float remainingDistance = dist;  // Distància que falta, pot ser negativa

		// Calcular el percentatge recorregut, permetent distàncies negatives
		float distanceTravelled = totalDistance - remainingDistance;  // Distància recorreguda
		float percentage = distanceTravelled / totalDistance;

		// Assegurar que el percentatge estigui entre 0 i 1 (per la barra de progrés)
		percentage = ImClamp(percentage, 0.0f, 1.0f);  // Restringir el valor entre 0 i 1

		ImVec2 barra = ImVec2(600.0f,50.0f);  // 50 px d'espai des de la part inferior
		// Establir la posició per centrar la barra a la part inferior de la pantalla
		ImVec2 position = ImVec2((screenSize->x - barra.x) / 2, screenSize->y - barra.y - 30.0f);  // 50 px d'espai des de la part inferior

		// Dibuixar la barra amb el percentatge calculat
		DibuixarBarraDistanciaPlaneta(percentage, barra,position);

		if (percentage >= 0.9f) {
			//Alerta(screenSize, 1, "Ja queda poc per arribar al Destí");
			AfegirAlerta(1, "Ja queda poc per arribar al Destí", 2.0f);
		}
	}

	ImVec2 espai(0.0f, 30.0f);
	// Dades de progrés
	ImVec2 windowSize(800, 180);
	ImVec2 windowPos = ImVec2(20, screenSize->y - windowSize.y);
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(windowSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 0));

	if (ImGui::Begin("Dades en quesitos", nullptr, window_flags | ImGuiWindowFlags_NoBackground)) {
		//ImDrawList* drawList = ImGui::GetWindowDrawList();
		//ImVec2 p = ImGui::GetCursorScreenPos();
		//drawList->AddRectFilled(ImVec2(0,0), ImVec2(p.x + windowSize.x, p.y + windowSize.y), color_interficie);


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(40, 10)); // Change padding (spacing between items)
		//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10)); // Change padding inside frames (buttons, input fields, etc.)
		ImVec4 colorFuel = colorVerd;
		ImVec4 colorLife = colorVerd;
		float fuel = nau->getFuel();
		if (fuel < 0.50f && fuel > 0.25f) {
			colorFuel = colorTaronja;
		}
		else if (fuel < 0.25f) {
			colorFuel = colorVermell;
		}
		float life = nau->getLife();
		if (life < 0.50f && life > 0.25f) {
			colorLife = colorTaronja;
		}
		else if (life < 0.25f) {
			colorLife = colorVermell;
		}
		CircularProgressBar("Combustible", fuel, ImVec2(100, 100), colorFuel);
		ImGui::SameLine();
		CircularProgressBar("Danys      ", life, ImVec2(100, 100), colorLife);
		ImGui::SameLine();
		CircularProgressBar("Acceleració", nau->getPotencia(), ImVec2(100, 100), colorVerd);

		//mGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	ImGui::End();
	ImGui::PopStyleVar();

	vector<Asteroide*> asteroidesaprop = findCollidingAsteroids(*nau, 10.0);

	if (asteroidesaprop.size() >= 1) {
		AfegirAlerta(2, "Alerta Aproximació d'Asteroides !!!", 2.0f);
	}

	//Crear mini mapa
	if (minimapas_circulars) {
		//Adalt
		ImVec2 minimapcircularSize(tamanyradar, tamanyradar);
		ImVec2 minimapPositionCircular = ImVec2(screenSize->x - minimapcircularSize.x - 20, 20);
		ImGui::SetNextWindowSize(ImVec2(minimapcircularSize.x + 20, minimapcircularSize.y + 20));
		ImGui::SetNextWindowPos(minimapPositionCircular);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("MiniMapaCircular", nullptr, window_flags | ImGuiWindowFlags_NoBackground)) {
			if (minimapas_centrat_sol) {
				crearMiniMapaCentratSolCircular(minimapcircularSize, minimapPositionCircular, false, 5.0f);
			}
			else {
				crearMiniMapaCentratJugadorCircular(minimapcircularSize, minimapPositionCircular, false, 5.0f);
			}
		}
		ImGui::End();
		ImGui::PopStyleVar();

		//Radar
		ImVec2 radarcircularSize(tamanyradar, tamanyradar);
		ImVec2 radarPositionCircular = ImVec2(screenSize->x - radarcircularSize.x, screenSize->y - radarcircularSize.y);
		ImGui::SetNextWindowSize(ImVec2(radarcircularSize.x, radarcircularSize.y));
		ImGui::SetNextWindowPos(radarPositionCircular);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("RadarCircular", nullptr, window_flags | ImGuiWindowFlags_NoBackground)) {
			crearRadarVertical(radarcircularSize, radarPositionCircular, true, 30.0f);
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
	else {
		ImVec2 minimapSize(tamanyminimapa_x, tamanyminimapa_y);
		ImVec2 minimapPosition = ImVec2(screenSize->x - minimapSize.x, 0);
		ImGui::SetNextWindowSize(ImVec2(minimapSize.x, minimapSize.y));
		ImGui::SetNextWindowPos(minimapPosition);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("MiniMapa", nullptr, window_flags)) {
			if (minimapas_centrat_sol) {
				crearMiniMapaCentratSol(minimapSize, minimapPosition);
			}
			else {
				crearMiniMapaCentratJugador(minimapSize, minimapPosition);
			}
		}
		ImGui::End();
		ImGui::PopStyleVar();

		ImVec2 radarSize(tamanyminimapa_x, tamanyminimapa_y);
		ImVec2 radarPosition = ImVec2(screenSize->x - radarSize.x, screenSize->y - radarSize.y);
		ImGui::SetNextWindowSize(ImVec2(radarSize.x, radarSize.y));
		ImGui::SetNextWindowPos(radarPosition);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("Radar", nullptr, window_flags)) {
			crearRadarVerticalQuadrat(radarSize, radarPosition, false, 0.0f);
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
//Mirar de fer per fer if mes maco 
/*void crearMiniMapa(ImVec2* screenSize, float x, float y) {
	ImVec2 minimapSize(x, y);
	ImVec2 minimapPosition = ImVec2(screenSize->x - minimapSize.x, 0);
	ImGui::SetNextWindowSize(ImVec2(minimapSize.x, minimapSize.y));
	ImGui::SetNextWindowPos(minimapPosition);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	if (ImGui::Begin("MiniMapa", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
		if (minimapas_centrat_sol) {
			crearMiniMapaCentratSol(minimapSize, minimapPosition);
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();

	ImVec2 radarSize(tamanyminimapa_x, tamanyminimapa_y);
	ImVec2 radarPosition = ImVec2(screenSize->x - radarSize.x, screenSize->y - radarSize.y);
	ImGui::SetNextWindowSize(ImVec2(radarSize.x, radarSize.y));
	ImGui::SetNextWindowPos(radarPosition);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	if (ImGui::Begin("Radar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
		if (minimapas_centrat_sol) {
			crearMiniMapaCentratSol(radarSize, radarPosition);
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}
*/

void GUI::crearMiniMapaCentratSolCircular(ImVec2 minimapSize, ImVec2 minimapPosition, bool abaix, float borderThickness) {
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	vec3 worldSize(tamanySS, tamanySS, 0);

	// INICI jugadorPos Comprovacio

	// Convertir la posició del jugador al mini mapa
	ImVec2 jugadorPosComprovacio = convertirAPosicioMiniMapa(nau->getCam().getO(), worldSize, minimapSize, minimapPosition);

	// Centre i radi del mini mapa
	ImVec2 center = ImVec2(minimapPosition.x + minimapSize.x / 2, minimapPosition.y + minimapSize.y / 2);
	float radius = (((minimapSize.x) < (minimapSize.y)) ? (minimapSize.x) : (minimapSize.y)) / 2.0f - borderThickness - 1;

	// Comprovar si el jugador està fora del radi del mini mapa
	float distance = sqrtf(pow(jugadorPosComprovacio.x - center.x, 2) + pow(jugadorPosComprovacio.y - center.y, 2));
	if (distance > radius) {
		// Augmentar la mida del mini mapa
		tamanySS += tamanySS * 0.5f;  // Augmenta la mida horitzontal
	}

	// FI jugadorPos Comprovacio

	// Fons del mini mapa
	if (abaix) {
		drawList->AddRectFilled(ImVec2(p.x, p.y + minimapSize.y / 2), ImVec2(p.x + minimapSize.x, p.y + minimapSize.y), color_interficie);
	}
	drawList->AddCircleFilled(center, radius, IM_COL32(20, 20, 20, 255)); // Fons del mini mapa

	// Dibuixa els planetes
	for (auto& planeta : PLANETES) {
		ImVec2 planetaPos = convertirAPosicioMiniMapa(planeta.getPosition(), worldSize, minimapSize, p);
		//std::cout << PLANETES[PlanetOrigen].getName()  << std::endl;
		if (orbites_minimapa) {
			dibuixarOrbita2D(planeta, minimapSize, minimapPosition, drawList, true, radius, center, true);
		}
		if (distanciaEntrePunts(planetaPos, center) <= radius) {
			if (planeta.getName() == "Sol") {
				drawList->AddCircleFilled(planetaPos, 12.0f, colorSol);

			}
			else if (PlanetOrigen != -1 && PlanetDesti != -1) {
				if (PLANETES[PlanetOrigen].getName() == planeta.getName()) {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaOrigen);

				}
				else if (PLANETES[PlanetDesti].getName() == planeta.getName()) {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaDesti);
				}
				else {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
				}
			}
			else {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
			}
		}
	}

	// Dibuixar els asteroides
	if (asteroides_minimapa) {
		for (const auto& asteroide : ASTEROIDES) {
			ImVec2 asteroidePos = convertirAPosicioMiniMapa(asteroide.getPosition(), worldSize, minimapSize, p);
			if (distanciaEntrePunts(asteroidePos, center) <= radius) {
				drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroides);
			}
		}
	}

	for (const auto& asteroide : ASTEROIDESCINTURO) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapa(asteroide.getPosition(), worldSize, minimapSize, p);
		if (distanciaEntrePunts(asteroidePos, center) <= radius) {
			drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroidescinturons);  // Vermell
		}
	}

	if (diposits_minimapa) {
		for (const auto& Objjoc : DIPOSITS) {
			// Converteix la posició del dipòsit al mini mapa
			ImVec2 objEspaiPos = convertirAPosicioMiniMapa(Objjoc.getPosition(), worldSize, minimapSize, p);
			if (distanciaEntrePunts(objEspaiPos, center) <= radius) {
				// Dimensions de la pastilla
				float pillWidth = 4.0f;   // Amplada de la pastilla
				float pillHeight = 4.0f;  // Alçada de la pastilla
				float cornerRadius = 0.0f; // Radi de les vores arrodonides

				// Dibuixa la pastilla com un rectangle arrodonit
				drawList->AddRectFilled(ImVec2(objEspaiPos.x - pillWidth / 2, objEspaiPos.y - pillHeight / 2),
					ImVec2(objEspaiPos.x + pillWidth / 2, objEspaiPos.y + pillHeight / 2),
					colorDiposits, cornerRadius);
			}
		}
	}

	if (estacions_minimapa) {
		for(auto& planeta : PLANETES)
		{
			for (auto& estacions : planeta.satelits)
			{
			ImVec2 estacionsPos = convertirAPosicioMiniMapa(estacions.getPosition(), worldSize, minimapSize, p);
			if (distanciaEntrePunts(estacionsPos, center) <= radius) {

				// Dimensions de la creu
				float crossSize = 4.0f; // Mida de la creu (ajustable)

				// Dibuixa les dues línies de la creu
				drawList->AddLine(ImVec2(estacionsPos.x - crossSize, estacionsPos.y),  // Línia horitzontal
					ImVec2(estacionsPos.x + crossSize, estacionsPos.y),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)

				drawList->AddLine(ImVec2(estacionsPos.x, estacionsPos.y - crossSize),  // Línia vertical
					ImVec2(estacionsPos.x, estacionsPos.y + crossSize),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)
			}
			}
		}
	}

	ImVec2 jugadorPos = convertirAPosicioMiniMapa(nau->getCam().getO(), worldSize, minimapSize, p);
	if (distanciaEntrePunts(jugadorPos, center) <= radius) {

		// Radi del triangle i orientació
		float puntaLlargada = 8.0f; // Longitud de la punta
		float baseAmple = 5.0f;    // Ample de la base del triangle
		float orientacio = nau->getAngle(); // Orientació en radians
		//std::cout << orientacio << std::endl;

		// Calcular els vèrtexs del triangle
		ImVec2 p1 = ImVec2(
			jugadorPos.x + cos(orientacio) * puntaLlargada,
			jugadorPos.y + sin(orientacio) * puntaLlargada
		);

		ImVec2 p2 = ImVec2(
			jugadorPos.x + cos(orientacio + IM_PI * 0.75f) * baseAmple,
			jugadorPos.y + sin(orientacio + IM_PI * 0.75f) * baseAmple
		);

		ImVec2 p3 = ImVec2(
			jugadorPos.x + cos(orientacio - IM_PI * 0.75f) * baseAmple,
			jugadorPos.y + sin(orientacio - IM_PI * 0.75f) * baseAmple
		);

		// Dibuixar el triangle
		drawList->AddTriangleFilled(p1, p2, p3, colorJugador); // Color groc

	}

	// Dibuixar el border circular
	drawList->AddCircle(center, radius + (borderThickness / 2), color_interficie, 64, borderThickness);

}

void GUI::crearMiniMapaCentratJugadorCircular(ImVec2 minimapSize, ImVec2 minimapPosition, bool abaix, float borderThickness) {
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	vec3 worldSize(tamanySS, tamanySS, 0);

	// INICI jugadorPos Comprovacio

	// Convertir la posició del jugador al mini mapa
	ImVec2 jugadorPosComprovacio = convertirAPosicioMiniMapaDesdeJugador(nau->getO(), worldSize, minimapSize, minimapPosition, nau->getO());

	// Centre i radi del mini mapa
	ImVec2 center = ImVec2(minimapPosition.x + minimapSize.x / 2, minimapPosition.y + minimapSize.y / 2);
	float radius = (((minimapSize.x) < (minimapSize.y)) ? (minimapSize.x) : (minimapSize.y)) / 2.0f - borderThickness - 1;

	// Comprovar si el jugador està fora del radi del mini mapa
	float distance = sqrtf(pow(jugadorPosComprovacio.x - center.x, 2) + pow(jugadorPosComprovacio.y - center.y, 2));
	if (distance > radius) {
		// Augmentar la mida del mini mapa
		tamanySS += tamanySS * 0.5f;  // Augmenta la mida horitzontal
	}

	// FI jugadorPos Comprovacio

	// Fons del mini mapa
	if (abaix) {
		drawList->AddRectFilled(ImVec2(p.x, p.y + minimapSize.y / 2), ImVec2(p.x + minimapSize.x, p.y + minimapSize.y), color_interficie);
	}
	drawList->AddCircleFilled(center, radius, IM_COL32(20, 20, 20, 255)); // Fons del mini mapa

	// Dibuixa els planetes
	for (auto& planeta : PLANETES) {
		ImVec2 planetaPos = convertirAPosicioMiniMapaDesdeJugador(planeta.getPosition(), worldSize, minimapSize, p, nau->getO());
		//std::cout << PLANETES[PlanetOrigen].getName()  << std::endl;
		if (orbites_minimapa) {
			dibuixarOrbita2D(planeta, minimapSize, minimapPosition, drawList, true, radius, center, false);
		}
		if (distanciaEntrePunts(planetaPos, center) <= radius) {
			if (planeta.getName() == "Sol") {
				drawList->AddCircleFilled(planetaPos, 12.0f, colorSol);

			}
			else if (PlanetOrigen != -1 && PlanetDesti != -1) {
				if (PLANETES[PlanetOrigen].getName() == planeta.getName()) {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaOrigen);

				}
				else if (PLANETES[PlanetDesti].getName() == planeta.getName()) {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaDesti);
				}
				else {
					drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
				}
			}
			else {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
			}
		}
	}

	// Dibuixar els asteroides
	if (asteroides_minimapa) {
		for (const auto& asteroide : ASTEROIDES) {
			ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugador(asteroide.getPosition(), worldSize, minimapSize, p, nau->getO());
			if (distanciaEntrePunts(asteroidePos, center) <= radius) {
				drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroides);
			}
		}
	}

	for (const auto& asteroide : ASTEROIDESCINTURO) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugador(asteroide.getPosition(), worldSize, minimapSize, p, nau->getO());
		if (distanciaEntrePunts(asteroidePos, center) <= radius) {
			drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroidescinturons);  // Vermell
		}
	}

	if (diposits_minimapa) {
		for (const auto& Objjoc : DIPOSITS) {
			// Converteix la posició del dipòsit al mini mapa
			ImVec2 objEspaiPos = convertirAPosicioMiniMapaDesdeJugador(Objjoc.getPosition(), worldSize, minimapSize, p, nau->getO());
			if (distanciaEntrePunts(objEspaiPos, center) <= radius) {
				// Dimensions de la pastilla
				float pillWidth = 4.0f;   // Amplada de la pastilla
				float pillHeight = 4.0f;  // Alçada de la pastilla
				float cornerRadius = 0.0f; // Radi de les vores arrodonides

				// Dibuixa la pastilla com un rectangle arrodonit
				drawList->AddRectFilled(ImVec2(objEspaiPos.x - pillWidth / 2, objEspaiPos.y - pillHeight / 2),
					ImVec2(objEspaiPos.x + pillWidth / 2, objEspaiPos.y + pillHeight / 2),
					colorDiposits, cornerRadius);
			}
		}
	}

	if (estacions_minimapa) {
		for (auto& planeta : PLANETES)
		{
			for (auto& estacions : planeta.satelits)
			{
				ImVec2 estacionsPos = convertirAPosicioMiniMapaDesdeJugador(estacions.getPosition(), worldSize, minimapSize, p, nau->getO());
				if (distanciaEntrePunts(estacionsPos, center) <= radius) {

					// Dimensions de la creu
					float crossSize = 4.0f; // Mida de la creu (ajustable)

					// Dibuixa les dues línies de la creu
					drawList->AddLine(ImVec2(estacionsPos.x - crossSize, estacionsPos.y),  // Línia horitzontal
						ImVec2(estacionsPos.x + crossSize, estacionsPos.y),
						colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)

					drawList->AddLine(ImVec2(estacionsPos.x, estacionsPos.y - crossSize),  // Línia vertical
						ImVec2(estacionsPos.x, estacionsPos.y + crossSize),
						colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)
				}
			}
		}
	}

	ImVec2 jugadorPos = convertirAPosicioMiniMapaDesdeJugador(nau->getO(), worldSize, minimapSize, p, nau->getO());
	if (distanciaEntrePunts(jugadorPos, center) <= radius) {

		// Radi del triangle i orientació
		float puntaLlargada = 8.0f; // Longitud de la punta
		float baseAmple = 5.0f;    // Ample de la base del triangle
		float orientacio = nau->getAngle(); // Orientació en radians
		//std::cout << orientacio << std::endl;

		// Calcular els vèrtexs del triangle
		ImVec2 p1 = ImVec2(
			jugadorPos.x + cos(orientacio) * puntaLlargada,
			jugadorPos.y + sin(orientacio) * puntaLlargada
		);

		ImVec2 p2 = ImVec2(
			jugadorPos.x + cos(orientacio + IM_PI * 0.75f) * baseAmple,
			jugadorPos.y + sin(orientacio + IM_PI * 0.75f) * baseAmple
		);

		ImVec2 p3 = ImVec2(
			jugadorPos.x + cos(orientacio - IM_PI * 0.75f) * baseAmple,
			jugadorPos.y + sin(orientacio - IM_PI * 0.75f) * baseAmple
		);

		// Dibuixar el triangle
		drawList->AddTriangleFilled(p1, p2, p3, colorJugador); // Color groc

	}

	// Dibuixar el border circular
	drawList->AddCircle(center, radius + (borderThickness / 2), color_interficie, 64, borderThickness);

}

void GUI::crearRadarVertical(ImVec2 radarSize, ImVec2 radarPosition, bool abaix, float borderThickness) {
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();
	vec3 worldSize(tamanySS, tamanySS, 0);

	// Centre del radar i radi
	ImVec2 center = ImVec2(radarPosition.x + radarSize.x / 2, radarPosition.y + radarSize.y / 2);
	float radius = (((radarSize.x) < (radarSize.y)) ? (radarSize.x) : (radarSize.y)) / 2.0f - borderThickness - 1;

	if (abaix) {
		drawList->AddRectFilled(ImVec2(radarPosition.x, radarPosition.y + radarSize.y / 2), ImVec2(radarPosition.x + radarSize.x, radarPosition.y + radarSize.y), color_interficie);
	}
	// Dibuixar el fons del radar
	drawList->AddCircleFilled(center, radius, IM_COL32(20, 20, 20, 255)); // Color de fons
	// Dibuixar la línia horitzontal per indicar l'orientació
	float orientacio = nau->getAngleV(); // Orientació en radians

	// Coordenades de la línia abans de rotar
	ImVec2 start(center.x - radius, center.y); // Part esquerra
	ImVec2 end(center.x + radius, center.y);   // Part dreta

	// Rotar els punts de la línia al voltant del centre
	float cosAngle = cos(orientacio);
	float sinAngle = sin(orientacio);

	auto rotatePoint = [&](ImVec2 point) {
		float x = point.x - center.x;
		float y = point.y - center.y;
		return ImVec2(
			center.x + x * cosAngle - y * sinAngle,
			center.y + x * sinAngle + y * cosAngle
		);
		};

	ImVec2 rotatedStart = rotatePoint(start);
	ImVec2 rotatedEnd = rotatePoint(end);

	// Dibuixar la línia amb l'angle especificat
	drawList->AddLine(
		rotatedStart,  // Inici de la línia
		rotatedEnd,    // Final de la línia
		IM_COL32(255, 255, 255, 255), // Color blanc
		2.0f            // Gruix de la línia
	);


	// Dibuixar asteroides que estan a 20 unitats davant o darrere
	for (const auto& asteroide : ASTEROIDES) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugadorVertical(asteroide.getPosition(), worldSize, radarSize, radarPosition, nau->getO());

		// Comparar l'altura de l'asteroide amb la del jugador
		float diferenciaAltura = asteroide.getPosition().z - nau->getO().z;

		if (distanciaEntrePunts(asteroidePos, center) <= radius) {
			// Diferenciar visualment si està per sobre o per sota
			ImU32 colorAsteroide = diferenciaAltura > 0
				? IM_COL32(0, 255, 0, 255) // Verd (per sobre)
				: IM_COL32(255, 0, 0, 255); // Vermell (per sota)

			glm::vec3 astVel = glm::vec3(asteroide.getVelocitat());

			double tCollision = timeToCollision(
				nau->getO(),
				nau->getVelocitat(),
				0.5f * glm::length(nau->getShipDimensions()),
				asteroide.getPosition(),
				astVel,
				(float)asteroide.getRadi()
			);

			if (tCollision >= 0.0 && tCollision <= 20.0) {
				// Dibuixar asteroide
				drawList->AddCircleFilled(asteroidePos, tCollision/2, colorAsteroide);
			}
			else {
				// Dibuixar asteroide
				drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroide);
			}
		}
	}

	/*
	for (const auto& asteroide : ASTEROIDESCINTURO) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugadorVertical(
			asteroide.getPosition(), worldSize, radarSize, radarPosition, nau->getO());

		// Comparar la distància en l'eix Z (profunditat)
		float diferenciaProfunditat = asteroide.getPosition().z - nau->getO().z;

		// Només mostrar els asteroides dins del rang [-20, 20] en l'eix Z
		if (fabs(diferenciaProfunditat) <= 20.0f) {
			// Diferenciar visualment segons si estan davant o darrere
			ImU32 colorAsteroide = diferenciaProfunditat > 0
				? IM_COL32(0, 255, 255, 255) // Blau clar (davant)
				: IM_COL32(255, 165, 0, 255); // Taronja (darrere)

			// Dibuixar l'asteroide si està dins del radi del radar
			if (distanciaEntrePunts(asteroidePos, center) <= radius) {
				drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroide);
			}
		}
	}


	if (diposits_minimapa) {
		for (const auto& Objjoc : DIPOSITS) {
			// Converteix la posició del dipòsit al mini mapa
			ImVec2 objEspaiPos = convertirAPosicioMiniMapaDesdeJugadorVertical(Objjoc.getPosition(), worldSize, radarSize, radarPosition, nau->getO());
			// Comparar la distància en l'eix Z (profunditat)

			if (distanciaEntrePunts(objEspaiPos, center) <= radius) {
				// Dimensions de la pastilla
				float pillWidth = 4.0f;   // Amplada de la pastilla
				float pillHeight = 4.0f;  // Alçada de la pastilla
				float cornerRadius = 0.0f; // Radi de les vores arrodonides

				// Dibuixa la pastilla com un rectangle arrodonit
				drawList->AddRectFilled(ImVec2(objEspaiPos.x - pillWidth / 2, objEspaiPos.y - pillHeight / 2),
					ImVec2(objEspaiPos.x + pillWidth / 2, objEspaiPos.y + pillHeight / 2),
					colorDiposits, cornerRadius);
			}

		}
	}

	if (estacions_minimapa) {
		for (const auto& estacions : ESTACIONS) {
			ImVec2 estacionsPos = convertirAPosicioMiniMapaDesdeJugadorVertical(estacions.getPosition(), worldSize, radarSize, radarPosition, nau->getO());
			// Comparar la distància en l'eix Z (profunditat)
			float diferenciaProfunditat = estacions.getPosition().z - nau->getO().z;

			// Només mostrar els asteroides dins del rang [-20, 20] en l'eix Z
			if (fabs(diferenciaProfunditat) <= 20.0f) {
				if (distanciaEntrePunts(estacionsPos, center) <= radius) {

					// Dimensions de la creu
					float crossSize = 4.0f; // Mida de la creu (ajustable)

					// Dibuixa les dues línies de la creu
					drawList->AddLine(ImVec2(estacionsPos.x - crossSize, estacionsPos.y),  // Línia horitzontal
						ImVec2(estacionsPos.x + crossSize, estacionsPos.y),
						colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)

					drawList->AddLine(ImVec2(estacionsPos.x, estacionsPos.y - crossSize),  // Línia vertical
						ImVec2(estacionsPos.x, estacionsPos.y + crossSize),
						colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)
				}
			}
		}
	}*/

	// Calcula la posició del jugador al radar
	/*ImVec2 jugadorPos = convertirAPosicioMiniMapaDesdeJugador(nau->getO(), worldSize, radarSize, p, nau->getO());

	// Configuració del triangle rectangular
	float baseAmple = 8.0f;    // Ample de la base del triangle
	float orientacio_2 = nau->getAngle(); // Orientació en radians

	// Càlcul del vèrtex de la punta (a la direcció del jugador)
	ImVec2 p1 = ImVec2(
		jugadorPos.x + cos(orientacio_2) * baseAmple,
		jugadorPos.y + sin(orientacio_2) * baseAmple
	);

	// Càlcul del primer vèrtex de la base (esquerra)
	ImVec2 p2 = ImVec2(
		jugadorPos.x + cos(orientacio_2 + IM_PI / 2.0f) * baseAmple,
		jugadorPos.y + sin(orientacio_2 + IM_PI / 2.0f) * baseAmple
	);

	// Càlcul del segon vèrtex de la base (dreta)
	ImVec2 p3 = ImVec2(
		jugadorPos.x + cos(orientacio_2 - IM_PI / 2.0f) * baseAmple,
		jugadorPos.y + sin(orientacio_2 - IM_PI / 2.0f) * baseAmple
	);

	// Dibuixar el triangle al radar
	drawList->AddTriangleFilled(p1, p2, p3, colorJugador); // Color groc
	*/


	// Border del radar
	drawList->AddCircle(center, radius + (borderThickness / 2), color_interficie, 64, borderThickness);
}


void GUI::crearRadarVerticalQuadrat(ImVec2 radarSize, ImVec2 radarPosition, bool abaix, float borderThickness)
{

}



void GUI::ferRectangleAcceleracio(ImVec2* screenSize, ImGuiWindowFlags window_flags) {
	ImVec2 ColumnaSize(70, 240); // Augmentem l'altura per donar espai al text
	ImVec2 ColumnaPos = ImVec2(screenSize->x - ColumnaSize.x, screenSize->y - ColumnaSize.y - 300);
	ImGui::SetNextWindowPos(ColumnaPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ColumnaSize);
	ImGui::Begin("Potencia", nullptr, window_flags | ImGuiWindowFlags_NoBackground);

	// Configuració de les dimensions de la barra de progrés
	ImVec2 size(40, 200); // amplada 40, alçada 200
	ImVec2 pos = ImGui::GetCursorScreenPos(); // Posició de la barra dins de la finestra

	// Dibuixem el fons de la barra (gris clar)
	ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(50, 50, 50, 255));

	// Dibuixem la part de la barra de progrés
	float filledHeight = size.y * nau->getPotencia(); // La quantitat de la barra de progrés que està "omplerta"
	ImGui::GetWindowDrawList()->AddRectFilled(
		ImVec2(pos.x, pos.y + size.y - filledHeight),
		ImVec2(pos.x + size.x, pos.y + size.y),
		IM_COL32(
			(int)(colorVerd.x * 255),  // R component
			(int)(colorVerd.y * 255),  // G component
			(int)(colorVerd.z * 255),  // B component
			(int)(colorVerd.w * 255)   // A component
		)
	);

	// Dibuixem la línia de contorn (opcional)
	ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(0, 0, 0, 255));

	// Ajustem la posició per al text sota la barra
	ImVec2 textSize = ImGui::CalcTextSize("Gas");
	ImVec2 textPos = ImVec2(
		pos.x + (size.x - textSize.x * 0.5f) - 20,  // Centrat horitzontalment respecte a la barra
		pos.y + size.y + 5                     // Una mica més avall del final de la barra
	);
	ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Gas");

	ImGui::End();
}

void GUI::crearMiniMapaCentratSol(ImVec2 minimapSize, ImVec2 minimapPosition) {
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	//INICI jugadorPos Comprovacio

	// Convertir la posició del jugador al mini mapa
	ImVec2 jugadorPosComprovacio = convertirAPosicioMiniMapa(nau->getO(), vec3(tamanySS, tamanySS, 0), minimapSize, minimapPosition);

	// Comprovar si el jugador està fora dels límits del mini mapa
	if (jugadorPosComprovacio.x < minimapPosition.x || jugadorPosComprovacio.x > minimapPosition.x + minimapSize.x ||
		jugadorPosComprovacio.y < minimapPosition.y || jugadorPosComprovacio.y > minimapPosition.y + minimapSize.y) {
		// Augmentar la mida del mini mapa
		tamanySS += tamanySS * 0.5f;  // Augmenta la mida horitzontal
	}
	//FI jugadorPos Comprovacio

	vec3 worldSize(tamanySS, tamanySS, 0);

	// Fons del mini mapa
	drawList->AddRectFilled(p, ImVec2(p.x + minimapSize.x, p.y + minimapSize.y), IM_COL32(20, 20, 20, 255));

	// Dibuixa els planetes
	for (auto& planeta : PLANETES) {
		ImVec2 planetaPos = convertirAPosicioMiniMapa(planeta.getPosition(), worldSize, minimapSize, p);
		//std::cout << PLANETES[PlanetOrigen].getName()  << std::endl;
		if (orbites_minimapa) {
			dibuixarOrbita2D(planeta, minimapSize, minimapPosition, drawList, false, 0.0, ImVec2(0, 0), true);
		}

		//FI PROVA
		if (planeta.getName() == "Sol") {
			drawList->AddCircleFilled(planetaPos, 12.0f, colorSol);

		}
		else if (PlanetOrigen != -1 && PlanetDesti != -1) {
			if (PLANETES[PlanetOrigen].getName() == planeta.getName()) {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaOrigen);

			}
			else if (PLANETES[PlanetDesti].getName() == planeta.getName()) {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaDesti);
			}
			else {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
			}
		}
		else {
			drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
		}

	}

	// Dibuixar els asteroides
	if (asteroides_minimapa) {
		for (const auto& asteroide : ASTEROIDES) {
			ImVec2 asteroidePos = convertirAPosicioMiniMapa(asteroide.getPosition(), worldSize, minimapSize, p);
			drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroides);
		}
	}

	for (const auto& asteroide : ASTEROIDESCINTURO) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapa(asteroide.getPosition(), worldSize, minimapSize, p);
		drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroidescinturons);  // Vermell
	}

	if (diposits_minimapa) {
		for (const auto& Objjoc : DIPOSITS) {
			// Converteix la posició del dipòsit al mini mapa
			ImVec2 objEspaiPos = convertirAPosicioMiniMapa(Objjoc.getPosition(), worldSize, minimapSize, p);

			// Dimensions de la pastilla
			float pillWidth = 8.0f;   // Amplada de la pastilla
			float pillHeight = 4.0f;  // Alçada de la pastilla
			float cornerRadius = 2.0f; // Radi de les vores arrodonides

			// Dibuixa la pastilla com un rectangle arrodonit
			drawList->AddRectFilled(ImVec2(objEspaiPos.x - pillWidth / 2, objEspaiPos.y - pillHeight / 2),
				ImVec2(objEspaiPos.x + pillWidth / 2, objEspaiPos.y + pillHeight / 2),
				colorDiposits, cornerRadius);
		}
	}

	if (estacions_minimapa) {
		for (auto& planeta : PLANETES)
		{
			for (auto& estacions : planeta.satelits)
			{
				ImVec2 estacionsPos = convertirAPosicioMiniMapa(estacions.getPosition(), worldSize, minimapSize, p);

				// Dimensions de la creu
				float crossSize = 4.0f; // Mida de la creu (ajustable)

				// Dibuixa les dues línies de la creu
				drawList->AddLine(ImVec2(estacionsPos.x - crossSize, estacionsPos.y),  // Línia horitzontal
					ImVec2(estacionsPos.x + crossSize, estacionsPos.y),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)

				drawList->AddLine(ImVec2(estacionsPos.x, estacionsPos.y - crossSize),  // Línia vertical
					ImVec2(estacionsPos.x, estacionsPos.y + crossSize),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)
			}
		}
	}

	// Dibuixa el jugador
	//ImVec2 jugadorPos = convertirAPosicioMiniMapa(nau.getCam().getO(), worldSize, minimapSize, p);
	//drawList->AddCircleFilled(jugadorPos, 5.0f, colorJugador);  // Groc

	ImVec2 jugadorPos = convertirAPosicioMiniMapa(nau->getO(), worldSize, minimapSize, p);

	// Radi del triangle i orientació
	float puntaLlargada = 8.0f; // Longitud de la punta
	float baseAmple = 5.0f;    // Ample de la base del triangle
	float orientacio = nau->getAngle(); // Orientació en radians
	//std::cout << orientacio << std::endl;

	// Calcular els vèrtexs del triangle
	ImVec2 p1 = ImVec2(
		jugadorPos.x + cos(orientacio) * puntaLlargada,
		jugadorPos.y + sin(orientacio) * puntaLlargada
	);

	ImVec2 p2 = ImVec2(
		jugadorPos.x + cos(orientacio + IM_PI * 0.75f) * baseAmple,
		jugadorPos.y + sin(orientacio + IM_PI * 0.75f) * baseAmple
	);

	ImVec2 p3 = ImVec2(
		jugadorPos.x + cos(orientacio - IM_PI * 0.75f) * baseAmple,
		jugadorPos.y + sin(orientacio - IM_PI * 0.75f) * baseAmple
	);

	// Dibuixar el triangle
	drawList->AddTriangleFilled(p1, p2, p3, colorJugador);
}

void GUI::crearMiniMapaCentratJugador(ImVec2 minimapSize, ImVec2 minimapPosition) {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p = ImGui::GetCursorScreenPos();

	//INICI jugadorPos Comprovacio

	// Convertir la posició del jugador al mini mapa
	ImVec2 jugadorPosComprovacio = convertirAPosicioMiniMapaDesdeJugador(nau->getO(), vec3(tamanySS, tamanySS, 0), minimapSize, minimapPosition, nau->getO());

	// Comprovar si el jugador està fora dels límits del mini mapa
	if (jugadorPosComprovacio.x < minimapPosition.x || jugadorPosComprovacio.x > minimapPosition.x + minimapSize.x ||
		jugadorPosComprovacio.y < minimapPosition.y || jugadorPosComprovacio.y > minimapPosition.y + minimapSize.y) {
		// Augmentar la mida del mini mapa
		tamanySS += tamanySS * 0.5f;  // Augmenta la mida horitzontal
	}
	//FI jugadorPos Comprovacio

	vec3 worldSize(tamanySS, tamanySS, 0);

	// Fons del mini mapa
	drawList->AddRectFilled(p, ImVec2(p.x + minimapSize.x, p.y + minimapSize.y), IM_COL32(20, 20, 20, 255));

	// Dibuixa els planetes
	for (auto& planeta : PLANETES) {
		ImVec2 planetaPos = convertirAPosicioMiniMapaDesdeJugador(planeta.getPosition(), worldSize, minimapSize, p, nau->getO());
		//std::cout << PLANETES[PlanetOrigen].getName()  << std::endl;
		if (orbites_minimapa) {
			dibuixarOrbita2D(planeta, minimapSize, minimapPosition, drawList, false, 0.0, ImVec2(0, 0), false);
		}
		//FI PROVA
		if (planeta.getName() == "Sol") {
			drawList->AddCircleFilled(planetaPos, 12.0f, colorSol);

		}
		else if (PlanetOrigen != -1 && PlanetDesti != -1) {
			if (PLANETES[PlanetOrigen].getName() == planeta.getName()) {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaOrigen);

			}
			else if (PLANETES[PlanetDesti].getName() == planeta.getName()) {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaDesti);
			}
			else {
				drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
			}
		}
		else {
			drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
		}

	}

	// Dibuixar els asteroides
	if (asteroides_minimapa) {
		for (const auto& asteroide : ASTEROIDES) {
			ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugador(asteroide.getPosition(), worldSize, minimapSize, p, nau->getO());
			drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroides);
		}
	}

	for (const auto& asteroide : ASTEROIDESCINTURO) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugador(asteroide.getPosition(), worldSize, minimapSize, p, nau->getO());
		drawList->AddCircleFilled(asteroidePos, 2.0f, colorAsteroidescinturons);  // Vermell
	}

	if (diposits_minimapa) {
		for (const auto& Objjoc : DIPOSITS) {
			// Converteix la posició del dipòsit al mini mapa
			ImVec2 objEspaiPos = convertirAPosicioMiniMapaDesdeJugador(Objjoc.getPosition(), worldSize, minimapSize, p, nau->getO());

			// Dimensions de la pastilla
			float pillWidth = 8.0f;   // Amplada de la pastilla
			float pillHeight = 4.0f;  // Alçada de la pastilla
			float cornerRadius = 2.0f; // Radi de les vores arrodonides

			// Dibuixa la pastilla com un rectangle arrodonit
			drawList->AddRectFilled(ImVec2(objEspaiPos.x - pillWidth / 2, objEspaiPos.y - pillHeight / 2),
				ImVec2(objEspaiPos.x + pillWidth / 2, objEspaiPos.y + pillHeight / 2),
				colorDiposits, cornerRadius);
		}
	}

	if (estacions_minimapa) {
		for (auto& planeta : PLANETES)
		{
			for (auto& estacions : planeta.satelits)
			{
				ImVec2 estacionsPos = convertirAPosicioMiniMapaDesdeJugador(estacions.getPosition(), worldSize, minimapSize, p, nau->getO());

				// Dimensions de la creu
				float crossSize = 4.0f; // Mida de la creu (ajustable)

				// Dibuixa les dues línies de la creu
				drawList->AddLine(ImVec2(estacionsPos.x - crossSize, estacionsPos.y),  // Línia horitzontal
					ImVec2(estacionsPos.x + crossSize, estacionsPos.y),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)

				drawList->AddLine(ImVec2(estacionsPos.x, estacionsPos.y - crossSize),  // Línia vertical
					ImVec2(estacionsPos.x, estacionsPos.y + crossSize),
					colorEstacions, 1.5f); // Amplada de la línia (1.5 píxels)
			}
		}
	}

	// Dibuixa el jugador
	//ImVec2 jugadorPos = convertirAPosicioMiniMapa(nau.getCam().getO(), worldSize, minimapSize, p);
	//drawList->AddCircleFilled(jugadorPos, 5.0f, colorJugador);  // Groc

	ImVec2 jugadorPos = convertirAPosicioMiniMapaDesdeJugador(nau->getO(), worldSize, minimapSize, p, nau->getO());

	// Radi del triangle i orientació
	float puntaLlargada = 8.0f; // Longitud de la punta
	float baseAmple = 5.0f;    // Ample de la base del triangle
	float orientacio = nau->getAngle(); // Orientació en radians
	//std::cout << orientacio << std::endl;

	// Calcular els vèrtexs del triangle
	ImVec2 p1 = ImVec2(
		jugadorPos.x + cos(orientacio) * puntaLlargada,
		jugadorPos.y + sin(orientacio) * puntaLlargada
	);

	ImVec2 p2 = ImVec2(
		jugadorPos.x + cos(orientacio + IM_PI * 0.75f) * baseAmple,
		jugadorPos.y + sin(orientacio + IM_PI * 0.75f) * baseAmple
	);

	ImVec2 p3 = ImVec2(
		jugadorPos.x + cos(orientacio - IM_PI * 0.75f) * baseAmple,
		jugadorPos.y + sin(orientacio - IM_PI * 0.75f) * baseAmple
	);

	// Dibuixar el triangle
	drawList->AddTriangleFilled(p1, p2, p3, colorJugador);



	// Dibuixa els planetes
	/*for (const auto& planeta : PLANETES) {
		ImVec2 planetaPos = convertirAPosicioMiniMapaDesdeJugador(planeta.getPosition(), worldSize, minimapSize, nau.getCam().getO());
		std::cout << "Posició planeta: " << planetaPos.x << ", " << planetaPos.y << std::endl;  // Depuració

		if (planeta.getName() == "Sol") {
			drawList->AddCircleFilled(planetaPos, 10.0f, colorSol);
		}
		else if (PLANETES[PlanetOrigen].getName() == planeta.getName()) {
			drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaOrigen);
		}
		else if (PLANETES[PlanetDesti].getName() == planeta.getName()) {
			drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetaDesti);
		}
		else {
			drawList->AddCircleFilled(planetaPos, 5.0f, colorPlanetes);
		}
	}

	// Dibuixar els asteroides
	for (const auto& asteroide : ASTEROIDES) {
		ImVec2 asteroidePos = convertirAPosicioMiniMapaDesdeJugador(asteroide.getPosition(), worldSize, minimapSize, nau.getCam().getO());
		std::cout << "Posició asteroide: " << asteroidePos.x << ", " << asteroidePos.y << std::endl;  // Depuració
		drawList->AddCircleFilled(asteroidePos, 5.0f, colorAsteroides);
	}

	// Dibuixar el jugador
	ImVec2 jugadorPos = convertirAPosicioMiniMapaDesdeJugador(nau.getCam().getO(), worldSize, minimapSize, nau.getCam().getO());
	std::cout << "Posició jugador: " << jugadorPos.x << ", " << jugadorPos.y << std::endl;  // Depuració
	drawList->AddCircleFilled(jugadorPos, 5.0f, colorJugador);  // Groc
	*/
}

// Funció per calcular la distància entre dos punts
float GUI::distanciaEntrePunts(const ImVec2& a, const ImVec2& b) {
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ImVec2 GUI::convertirAPosicioMiniMapa(const glm::vec3& posicioMon,
	const glm::vec3& worldSize,
	const ImVec2& minimapSize,
	const ImVec2& minimapPosition) {

	// Mapa de coordenades del món va de -2500 a 2500
	// El punt 0, 0, 0 es troba al centre del món

	// Desplaçar les coordenades del món perquè el punt (0, 0, 0) estigui al centre
	glm::vec3 posicioDesplacada = posicioMon + glm::vec3(worldSize.x / 2.0f, worldSize.y / 2.0f, 0.0f);

	// Calcular l'escala per als eixos X i Y
	float scaleX = minimapSize.x / worldSize.x;
	float scaleY = minimapSize.y / worldSize.y;

	// Convertir a coordenades 2D del mini mapa
	float posX = minimapPosition.x + (posicioDesplacada.x * scaleX);
	float posY = minimapPosition.y + (posicioDesplacada.y * scaleY);

	return ImVec2(posX, posY);
}

ImVec2 GUI::convertirAPosicioMiniMapaDesdeJugador(const glm::vec3& posicioMon,
	const glm::vec3& worldSize,
	const ImVec2& minimapSize,
	const ImVec2& minimapPosition,
	const glm::vec3& posicioJugador) {

	// Desplaçar les coordenades del món perquè el centre sigui la posició del jugador
	glm::vec3 posicioDesplacada = posicioMon - posicioJugador;

	// Calcular l'escala per als eixos X i Y
	float scaleX = minimapSize.x / worldSize.x;
	float scaleY = minimapSize.y / worldSize.y;

	// Convertir a coordenades 2D del mini mapa
	float posX = minimapPosition.x + (posicioDesplacada.x * scaleX) + (minimapSize.x / 2.0f);
	float posY = minimapPosition.y + (posicioDesplacada.y * scaleY) + (minimapSize.y / 2.0f);

	return ImVec2(posX, posY);
}

ImVec2 GUI::convertirAPosicioMiniMapaDesdeJugadorVertical(const glm::vec3& posicioMon,
	const glm::vec3& worldSize,
	const ImVec2& minimapSize,
	const ImVec2& minimapPosition,
	const glm::vec3& posicioJugador) {

	// Desplaçar les coordenades del món perquè el centre sigui la posició del jugador
	glm::vec3 posicioDesplacada = posicioMon - posicioJugador;

	// Calcular l'escala per als eixos X i Y
	float scaleX = minimapSize.x / worldSize.x; // Amplada del radar (eix X del món)
	float scaleY = minimapSize.y / worldSize.y; // Alçada del radar (eix Y del món)

	// Convertir a coordenades 2D del radar vertical
	float posX = minimapPosition.x + (posicioDesplacada.x * scaleX) + (minimapSize.x / 2.0f);
	float posY = minimapPosition.y + (posicioDesplacada.y * scaleY) + (minimapSize.y / 2.0f);

	return ImVec2(posX, posY);
}


void GUI::MostrarAlerta(ImVec2* screenSize, const Alerta& alerta, float posY) {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse;

	ImVec4 color;
	switch (alerta.tipus) {
	case 1:
		color = colorVerd;
		break;
	case 2:
		color = colorTaronja;
		break;
	case 3:
		color = colorVermell;
		break;
	case 4:
		color = colortransparentalerta;
		break;
	}

	ImVec2 winsize(600, 60);
	// Dibuixar l'ombra primer
	ImVec2 shadowOffset(5.0f, 5.0f);
	ImVec4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f); // Color d'ombra semi-transparent
	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5f - winsize.x * 0.5f + shadowOffset.x, posY + shadowOffset.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(winsize);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, shadowColor);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f); // Rouding més suau
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10)); // Afegir espai dins la finestra
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // Sense bordes
	std::string alertText = "Alerta_Shadow"+ std::to_string(posY);
	ImGui::Begin(alertText.c_str(), NULL, window_flags);
	ImGui::End();
	ImGui::PopStyleColor();

	// Mostrar la finestra principal
	ImGui::SetNextWindowPos(ImVec2(screenSize->x * 0.5f - winsize.x * 0.5f, posY), ImGuiCond_Always);
	ImGui::SetNextWindowSize(winsize);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, color);

	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Sense bordes

	std::string alertText2 = "Alerta" + std::to_string(posY);
	ImGui::Begin(alertText2.c_str(), NULL, window_flags);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Color blanc per al text

	// Centrat del text
	ImVec2 textSize = ImGui::CalcTextSize(alerta.text);
	ImVec2 textPos = ImVec2(
		(winsize.x - textSize.x) * 0.5f, // Centrat horitzonalment dins de la finestra
		(winsize.y - textSize.y) * 0.5f  // Centrat verticalment dins de la finestra
	);
	ImGui::SetCursorPos(textPos);
	ImGui::Text(alerta.text);

	ImGui::PopStyleColor();
	ImGui::End();

	// Restablir els canvis al final
	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar(3); // Hem canviat el nombre de var per evitar conflictes
}


void GUI::GestionarAlertes(ImVec2* screenSize) {
	float posY = 10.0f;  // Posició inicial per la primera alerta

	for (auto& alerta : alertes) {
		// Si l'alerta encara té temps restant per mostrar-se
		if (alerta.temps > 0.0f) {
			// Mostrar l'alerta a la pantalla
			MostrarAlerta(screenSize, alerta, posY);
			alerta.temps -= ImGui::GetIO().DeltaTime; // Disminuir el temps restant

			// Desplaçar la posició Y per la següent alerta
			posY += 70.0f;  // Incrementar la posició Y per la següent alerta
		}
	}

	// Eliminar alertes amb temps 0
	alertes.erase(std::remove_if(alertes.begin(), alertes.end(), [](const Alerta& alerta) {
		return alerta.temps <= 0.0f;
		}), alertes.end());
}

void GUI::AfegirAlerta(int tipus, const char* text, float temps) {
	// Comprovar si ja s'ha afegit una alerta amb aquest tipus i text
	if (text == nullptr || strlen(text) == 0) {
		std::cout << "Error: el text de l'alerta no pot ser nul o buit." << std::endl;
		return;  // No afegir alerta si el text no és vàlid
	}
	bool alertaJaAfegida = false;
	for (auto& alerta : alertes) {
		if (alerta.tipus == tipus && strcmp(alerta.text, text) == 0) {
			alerta.temps = temps;
			alertaJaAfegida = true;
			break;  // Si ja existeix l'alerta, no afegir una nova
		}
	}

	// Si no s'ha afegit encara, afegir l'alerta a la llista
	if (!alertaJaAfegida) {
		Alerta novaAlerta = { tipus, text, temps };
		alertes.push_back(novaAlerta);
	}
	//}
}


// Funció per mostrar la pantalla de guanyador
void GUI::MostrarPantallaGuanyador(ImVec2* screenSize) {
	ImGui::Begin("Pantalla de Guanyador", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

	// Missatge principal
	ImGui::Text("Has arribat al teu destí!");
	ImGui::Separator();
	float score = 0.0;
	// Puntuació i temps
	ImGui::Text("Punts Finals: %d", score);
	ImGui::Text("Temps Final: %.2f segons", m_time);

	// Opcional: altres estadístiques
	ImGui::Text("Nau intacta: %s", (nau->getLife() > 0.8f) ? "Si" : "No");
	ImGui::Text("Combustible: %s", nau->getFuel());

	// Espai per estètica
	ImGui::Spacing();
	ImGui::Spacing();

	// Botons d'acció
	/*if (ImGui::Button("Tornar al Menú Principal")) {
	}

	ImGui::SameLine();

	if (ImGui::Button("Tornar a Jugar")) {
	}

	ImGui::SameLine();*/
	if (ImGui::Button("Sortir del Joc")) {
		glfwSetWindowShouldClose(window, GL_TRUE);  // Marca la finestra per tancar
	}

	ImGui::End();
}





//Getters

int GUI::getPlanetaOrigen() {
	return PlanetOrigen;
}

int GUI::getPlanetaDesti() {
	return PlanetDesti;
}

bool GUI::getMenuJugadorConfig() const {
	return show_menu_jugador_config;
}

bool* GUI::getWindowAbout() {
	return &show_window_about;
}

bool GUI::getPause() {
	return pause;
}
bool* GUI::getDebugWindow() {
	return &show_debug_windows;
}
bool* GUI::getDemoWindow() {
	return &show_demo_window;
}

bool* GUI::getMapaWindow() {
	return &show_mapa_windows;
}

//Setters
void GUI::switchMenuJugadorConfig() {
	show_menu_jugador_config = !show_menu_jugador_config;
}
void GUI::switchPause() {
	pause = !pause;
}
void GUI::switchMapaWindow() {
	show_mapa_windows = !show_mapa_windows;
	show_game_window = !show_game_window;
}
