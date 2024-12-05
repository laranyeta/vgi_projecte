#include "particle.h"

void Particle::respawn(glm::vec3 origen, glm::vec3 direccio, float velocitat) {
	pos = origen;
	velocitatActual = glm::normalize(direccio) * velocitat;
	vida = maxVida;
	activa = true;
	setColor(glm::vec4(
		1.0f,
		static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f,
		0.0f,
		0.8f
	));
}

void Particle::update(float deltaTime) {
	if (vida > 0) {
		pos += velocitatActual * deltaTime;
		vida--;
		float alpha = static_cast<float>(vida) / maxVida;
		color.a = alpha;
		if (vida <= 0)
			rebot = true;
	}
}

/*void Particle::renderFlameradaSol() {
	//encara s'ha d'afegir les coordenades del sol!!
	glBegin(GL_POINTS);
	for (int i = 0; i < MAX_PARTICULES; i++) {
		if (particules[i].activa) {
			glColor4f(1.0f, 0.9f, 0.1f, 0.5); //rgba

			//apliquem posicio radial
			float theta = rand() / (float)RAND_MAX * 2.0f * M_PI;
			float phi = acos(2.0f * (rand() / (float)RAND_MAX) - 1.0f);
			float radi = posSol + (rand() / (float)RAND_MAX);

			particules[i].pos.x = posSol.x + sin(phi) * cos(theta) * radi;
			particules[i].pos.y = posSol.y + sin(phi) * cos(theta) * radi;
			particules[i].pos.z = posSol.z + sin(phi) * cos(theta) * radi;

			glm::vec3 direccio = glm::normalize(particules[i].pos - glm::vec3(posSol.x, posSol.y, posSol.z));
			particules[i].velocitatActual = direccio * particules[i].velocitatActual;
			particules[i].pos += particules[i].velocitatActual * deltaTime;

			glVertex3f(particules[i].pos.x, particules[i].pos.y, particules[i].pos.z);
			//podem aplicar dispersio: NOISE
		}
	}
	glEnd();
	//return 0;
}

void Particle::renderPropulsioNau() {
	glBegin(GL_POINTS);
	for (int i = 0; i < MAX_PARTICULES; i++) {
		if (particules[i].activa) {
			glColor4f(0.3f, 0.1f, 1.0f, 0.5); //rgba
			//anirà cap enrera
			glVertex3f(particules[i].pos.x, -(particules[i].pos.y), particules[i].pos.z);
		}
	}
	glEnd();
	//return 0;
}

void Particle::initParticle() {
	srand((int)time(NULL));

	for (int i = 0; i < MAX_PARTICULES; i++) {
		particules[i].activa = false;
		particules[i].velocitatTarget = { 0.0f, 0.0f, 0.0f };
	}
}

void Particle::activarParticle() {
	for (int i = 0; i < MAX_PARTICULES; i++) {
		if (!particules[i].activa) {
			//activem particula
			particules[i].activa = true;
			//set punt origen {0,0,0}
			particules[i].pos = { 0.0f, 0.0f, 0.0f };
			//set vida i vida maxima
			particules[i].vida = 0;
		}
	}
}

void Particle::ajustarParticle() {
	coeficient = 0.05; //velocitat s'ajusta al 5%
	for (int i = 0; i < MAX_PARTICULES; i++) {
		particules[i].velocitatActual += ((particules[i].velocitatTarget - p.particules[i].velocitatActual))*coeficient;
		particules[i].pos += particules[i].velocitatActual; //actualitzem posició

		if (particules[i].pos.y < 0.0f) {
			particules[i].pos.y = 0.0f;
			particules[i].velocitatActual.y = -(p.particules[i].velocitatActual.y); //farà l'efecte de rebot
			rebotCount++;
		}
		particules[i].vida++;
		if (particules[i].vida >= MAX_VIDA_PARTICULA)
			particules[i].activa = false;
	}
}

void Particle::initParticle_Sol(glm::vec3 origen) {
	srand((int)time(NULL));
	for (int i = 0; i < MAX_PARTICULES; i++) {
		particules[i].activa = true;
		particules[i].pos = origen;
		particules[i].vida = (rand() % 50) + 50;
		particules[i].maxVida = particules[i].vida;
		float angle = (rand() % 360) * (M_PI / 180.0f);
		float radius = (rand() % 100 + 50) / 10.0f;
		particules[i].velocitatActual = glm::vec3(
			radius * cos(angle),
			radius * sin(angle),
			(rand() % 200 - 100) / 100.0f
		);
		particules[i].color = glm::vec4(1.0f, 0.5f + (rand() % 50) / 100.0f, 0.0f, 1.0f);
	}
}

void Particle::ajustarParticle_Sol(float deltaTime, glm::vec3 origen) {
	for (int i = 0; i < MAX_PARTICULES; i++) {
		if (!particules[i].activa)
			continue;
		//en cas que la particula sigui activa
		particules[i].vida--;
		if (particules[i].vida <= 0) {
			particules[i].vida = particules[i].maxVida;
			particules[i].pos = origen;
			float angle = (rand() % 360) * (M_PI / 180.0f);
			float radius = (rand() % 100 + 50) / 10.0f;
			particules[i].velocitatActual = glm::vec3(
				radius * cos(angle),
				radius * sin(angle),
				(rand() % 200 - 100) / 100.0f
			);
		}
		particules[i].pos += particules[i].velocitatActual * deltaTime;
		float coeficientVida = (float)((particules[i].vida) / (particules[i].maxVida)) ;
		particules[i].color = glm::vec4(1.0f, coeficientVida * 0.5f, 0.0f, coeficientVida); //alpha = vida restant
	}
}

/*void Particle::renderParticle_Sol() {
	glBegin(GL_POINTS);
	for (int i = 0; i < MAX_PARTICULES; i++) {
		if (!particules[i].activa)
			continue;
		glColor4f(particules[i].color.r, particules[i].color.g, particules[i].color.b, particules[i].color.a);
		glVertex3f(particules[i].pos.x, particules[i].pos.y, particules[i].pos.z);
	}
	glEnd();
}*/
