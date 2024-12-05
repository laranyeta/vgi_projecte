#ifndef PARTICLE_H
#define PARTICLE_H

#define PARTICLE_CLASS_DECL     __declspec(dllexport)

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

constexpr int MAX_PARTICLES = 1000;
#define M_PI 3.14159265358979323846

class Particle {
public:
	Particle()
		: pos(0.0f), velocitatActual(0.0f), velocitatTarget(0.0f), color(1.0f),
		vida(0), maxVida(100), activa(false), rebot(false) {}

	glm::vec3 getPos() { return pos; }
	int getVida() { return vida; }
	int getMaxVida() { return maxVida; }
	glm::vec3 getVelAct() { return velocitatActual; }
	glm::vec3 getVelTarget() { return velocitatTarget; }
	glm::vec4 getColor() { return color; }

	void setVelAct(const glm::vec3& novaVelocitatActual) { velocitatActual = novaVelocitatActual; }
	void setVida(const int& novaVida) { vida = novaVida; }
	void setColor(const glm::vec4& nouColor) { color = nouColor; }
	void respawn(glm::vec3 origen, glm::vec3 direccio, float velocitat);
	void update(float deltaTime);

	bool isActiva() { return activa; }
	bool applyingRebot() { return rebot; }

private:
	glm::vec3 pos; //xyz
	glm::vec3 velocitatActual; //xyz
	glm::vec3 velocitatTarget; //xyz
	glm::vec4 color; //rgba
	int vida;
	int maxVida;
	bool activa;
	bool rebot;
};

#endif