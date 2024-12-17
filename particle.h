#ifndef PARTICLE_H
#define PARTICLE_H

#define PARTICLE_CLASS_DECL     __declspec(dllexport)

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "nau.h"

constexpr int MAX_PARTICLES = 1000;
#define M_PI 3.14159265358979323846

class Particle {
public:
	Particle()
		: m_pos(0.0f), m_velocitatActual(0.0f), m_velocitatTarget(0.0f), m_color(1.0f),
		m_vida(0), m_maxVida(10), m_activa(false), m_rebot(false) {}

	glm::vec3 getPos() { return m_pos; }
	int getVida() { return m_vida; }
	int getMaxVida() { return m_maxVida; }
	glm::vec3 getVelAct() { return m_velocitatActual; }
	glm::vec3 getVelTarget() { return m_velocitatTarget; }
	glm::vec4 getColor() { return m_color; }

	void setPos(const glm::vec3& novaPos) { m_pos = novaPos; }
	void setVelAct(const glm::vec3& novaVelocitatActual) { m_velocitatActual = novaVelocitatActual; }
	void setVida(const int& novaVida) { m_vida = novaVida; }
	void setColor(const glm::vec4& nouColor) { m_color = nouColor; }
	void respawn(glm::vec3 origen, glm::vec3 direccio, float velocitat);
	void update(float deltaTime);

	bool isActiva() { return m_activa; }
	bool applyingRebot() { return m_rebot; }

private:
	glm::vec3 m_pos; //xyz
	glm::vec3 m_velocitatActual; //xyz
	glm::vec3 m_velocitatTarget; //xyz
	glm::vec4 m_color; //rgba
	int m_vida;
	int m_maxVida;
	bool m_activa;
	bool m_rebot;
};

#endif