#ifndef PLANETA_H
#define PLANETA_H
#include <vector>
#include <glm/glm.hpp>	
#include <string>
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
		m_eixos_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
		m_periapsis = 0.0;
		m_semieix_major = 0.0;
		m_inclinacio = 0.0;
		m_long_node_asc = 0.0;
		m_excentricitat = 0.0;
		m_textureID = 0;
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
		m_eixos_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
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
		m_eixos_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
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
		m_eixos_rotacio_planeta = glm::vec3(1.0f, 0.0f, 0.0f);
		m_direccio_rotacio = 1;
	}
	// 
	std::string getName() const { return m_name; }
	std::string getRutaTextura() const { return m_rutaTextura; }
	unsigned int  getTextureID() const {return m_textureID;}
	double getRadi() const { return m_radi; }
	double getRadiOrbita() const  { return m_radi_orbita; }
	double getMassa() const  { return m_massa; }
	glm::dvec3 getVelocitat() const { return m_velocitat; }
	int getSlices() const { return m_slices; }
	int getStacks()  const { return m_stacks; }
	float getAngleRotacio() const { return m_angle_rotacio_orbita; }
	float getVelocitatRotacio() const { return m_velocitat_rotacio; }
	int getDireccioRotacio() const {return m_direccio_rotacio;}
	glm::dvec3 getAcceleracio() const { return m_acceleracio; }
	glm::vec3 getEixosRotacioPlaneta() const { return m_eixos_rotacio_planeta; }
	glm::vec4 getColor() const { return m_color; }
	glm::vec3 getPosition() const { return m_position; }
	double getPeriapsis() { return m_periapsis; }
	double getSemieixMajor() { return m_semieix_major; }
	double getLongitudNodeAscendent(double lon) { return m_long_node_asc; }
	double getInclinacio() { return m_inclinacio; }
	double getExcentricitat() { return m_excentricitat; }
	// SETTERS
	void setName(std::string name) { m_name = name; }
	void setTextureID(unsigned int texID) {m_textureID = texID;}
	void setRutaTextura(std::string rutaTextura) { m_rutaTextura = rutaTextura; }
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
	void setEixosRotacioPlaneta(glm::vec3 eixos_rotacio_planeta) { m_eixos_rotacio_planeta = eixos_rotacio_planeta; }
	void setAcceleracio(glm::dvec3 acceleracio) { m_acceleracio = acceleracio;  }
	// Orbites 3D
	void setSemieixMajor(double semieix) { m_semieix_major = semieix; }
	void setExcentricitat(double exc) { m_excentricitat = exc; }
	void setInclinacio(double inclinacio) { m_inclinacio = inclinacio;  }
	void setLongitudNodeAscendent(double lon) { m_long_node_asc = lon; }
	void setPeriapsis(double periapsis) { m_periapsis = periapsis; }
private:
	std::string m_name;
	unsigned int m_textureID;
	std::string m_rutaTextura;
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
	glm::vec3 m_eixos_rotacio_planeta;
	int m_direccio_rotacio;
	// Elements orbitals 3D
	double m_semieix_major;   // a
	double m_excentricitat;    // e
	double m_inclinacio;      // i (radians)
	double m_long_node_asc;    // Ω (radians)
	double m_periapsis;    // ω (radians)
};	

#endif