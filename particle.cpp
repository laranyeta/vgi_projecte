#include "particle.h"

void Particle::respawn(glm::vec3 origen, glm::vec3 direccio, float velocitat) {
	m_pos = origen;
	m_velocitatActual = glm::normalize(direccio) * velocitat;
	m_vida = m_maxVida;
	m_activa = true;
	setColor(glm::vec4(
		0.0f,
		static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f,
		0.0f,
		0.8f
	)); //color blavos
}

void Particle::update(float deltaTime) {
	if (m_vida > 0) {
		m_pos += m_velocitatActual * deltaTime;
		m_vida -= deltaTime * 0.2;
		float alpha = static_cast<float>(m_vida) / m_maxVida;
		m_color.a = alpha;
		if (m_vida <= 0) {
			m_vida = 0;
			m_activa = false;
		}
	}
}