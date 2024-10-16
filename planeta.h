#ifndef PLANETA_H
#define PLANETA_H
#include <vector>
#include <glm/glm.hpp>	
class Planeta
{
public:
	Planeta() {
		m_radi = 1.0f;
		m_slices = 20;
		m_stacks = 20;
		m_massa = 0.0;
		m_velocitat = glm::dvec3(0.0f, 0.0f, 0.0f);
		m_acceleracio = glm::dvec3(0.0f, 0.0f, 0.0f);;
		m_angle_rotacio_orbita = 0.0f;
		m_radi_orbita = 0.0;
		m_color = { 0.0,0.0,0.0,1.0 };
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_velocitat_rotacio = 5.0f;
		m_angle_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
	}

	Planeta(float radi, int slices, int stacks, glm::vec3 position) {
		m_position = position;
		m_radi = radi;
		m_slices = slices;
		m_stacks = stacks;
		m_massa = 0.0;
		m_velocitat = glm::dvec3(0.0f, 0.0f, 0.0f);
		m_angle_rotacio_orbita = 0.0f;
		m_radi_orbita = 0.0;
		m_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_velocitat_rotacio = 5.0f;
		m_angle_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
	}

	Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, glm::vec3 position) {
		m_radi = radi;
		m_slices = slices;
		m_stacks = stacks;
		m_massa = massa;
		m_velocitat = velocitat;
		m_angle_rotacio_orbita = 0.0f;
		m_radi_orbita = 0.0;
		m_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_position = position;
		m_velocitat_rotacio = 5.0f;
		m_angle_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
	}

	Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, float angleRotacio, double radiOrbita, glm::vec3 position) {
		m_radi = radi;
		m_slices = slices;
		m_stacks = stacks;
		m_massa = massa;
		m_velocitat = velocitat;
		m_angle_rotacio_orbita = angleRotacio;
		m_radi_orbita = radiOrbita;
		m_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		m_position = position;
		m_velocitat_rotacio = 5.0f;
		m_angle_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
	}

	double getRadi() { return m_radi; }
	double getRadiOrbita() { return m_radi_orbita; }
	double getMassa() { return m_massa; }
	glm::dvec3 getVelocitat() { return m_velocitat; }
	int getSlices() { return m_slices; }
	int getStacks() { return m_stacks; }
	float getAngleRotacio() { return m_angle_rotacio_orbita; }
	float getVelocitatRotacio() { return m_velocitat_rotacio; }
	int getDireccioRotacio() {
		return m_direccio_rotacio;
	}
	glm::dvec3 getAcceleracio() { return m_acceleracio; }
	glm::vec3 getAngleRotacioPlaneta() { return m_angle_rotacio_planeta; }
	glm::vec4 getColor() { return m_color; }
	glm::vec3 getPosition() { return m_position; }
	void setRadi(float radi) { m_radi = radi; }
	void setRadiOrbita(float radiOrbita) { m_radi_orbita = radiOrbita; }
	void setMassa(float massa) { m_massa = massa; }
	void setVelocitat(glm::dvec3 velocitat) { m_velocitat = velocitat; }
	void setSlices(int slices) { m_slices = slices; }
	void setStacks(int stacks) { m_stacks = stacks; }
	void setAngleRotacio(float angleRotacio) { m_angle_rotacio_orbita = angleRotacio; }
	void setColor(glm::vec4 color) { m_color = color; }
	void setPosition(glm::vec3 position) {m_position = position;}
	void setVelocitatRotacio(float velocitat) { m_velocitat_rotacio = velocitat; }
	void setDireccioRotacio(int direccio) { m_direccio_rotacio = direccio; }
	void setAngleRotacioPlaneta(glm::vec3 angle_rotacio_planeta) { m_angle_rotacio_planeta = angle_rotacio_planeta; }
	void setAcceleracio(glm::dvec3 acceleracio) { m_acceleracio = acceleracio;  }
private:
	glm::vec3 m_position;
	glm::vec4 m_color;
	float m_radi;
	double m_radi_orbita;
	double m_massa;
	glm::dvec3 m_velocitat;
	glm::dvec3 m_acceleracio;
	int m_slices;
	int m_stacks;
	float m_angle_rotacio_orbita;
	float m_velocitat_rotacio;
	glm::vec3 m_angle_rotacio_planeta;
	int m_direccio_rotacio;
};	

#endif