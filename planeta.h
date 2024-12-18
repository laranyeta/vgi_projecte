#ifndef PLANETA_H
#define PLANETA_H

#define PLANETA_CLASS_DECL     __declspec(dllexport)
#include <vector>
#include <glm/glm.hpp>	
#include <string>
#include "objectesEspai.h"
class Planeta
{
public:

	Planeta();
	Planeta(float radi, int slices, int stacks, glm::vec3 position);
	Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, glm::vec3 position);
	Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, float angleRotacio, double radiOrbita, glm::vec3 position);


	void agregarPosicionHistorica(const glm::vec3& posicion);
	const std::vector<glm::vec3>& getPosicionesHistoricas() const;
	int getNLlunes() const { return m_llunes; }
	const char* getRutaTexturaMenu() const { return m_rutaTexturaMenu; }
	unsigned int  getTextureIDMenu() const { return m_textureIDMenu; }
	std::vector<Planeta> moons;
	std::vector<objectesEspai> satelits;
	size_t getPuntsOrbita() const;
	unsigned int  getTextureIDMenuSelect() const { return m_textureIDMenuSelect; }
	std::string getName() const;
	std::string getRutaTextura() const;
	unsigned int getTextureID() const;
	double getRadi() const;
	double getRadiOrbita() const;
	double getMassa() const;
	glm::dvec3 getVelocitat() const;
	int getSlices() const;
	int getStacks() const;
	float getAngleRotacio() const;
	float getVelocitatRotacio() const;
	int getDireccioRotacio() const;
	glm::dvec3 getAcceleracio() const;
	glm::vec3 getEixosRotacioPlaneta() const;
	glm::vec4 getColor() const;
	glm::vec3 getPosition() const;
	int getNSatelits() { return m_satelits; }
	double getPeriapsis();
	double getSemieixMajor();
	double getLongitudNodeAscendent();
	double getInclinacio();
	double getExcentricitat();
	float getOffsetInicial() { return m_offsetInicial; }
	// SETTERS
	void setTextureIDMenu(unsigned int texID) { m_textureIDMenu = texID; }
	void setRutaTexturaMenu(const char* rutaTexturaMenu) { m_rutaTexturaMenu = rutaTexturaMenu; }
	void setTextureIDMenuSelect(unsigned int texID) { m_textureIDMenuSelect = texID; }
	void setPuntsOrbita(size_t puntsOrbita);
	void setName(std::string name);
	void setTextureID(unsigned int texID);
	void setRutaTextura(std::string rutaTextura);
	void setRadi(float radi);
	void setRadiOrbita(float radiOrbita);
	void setMassa(float massa);
	void setVelocitat(glm::dvec3 velocitat);
	void setSlices(int slices);
	void setStacks(int stacks);
	void setAngleRotacio(float angleRotacio);
	void setColor(glm::vec4 color);
	void setPosition(glm::vec3 position);
	void setVelocitatRotacio(float velocitat);
	void setDireccioRotacio(int direccio);
	void setEixosRotacioPlaneta(glm::vec3 eixos_rotacio_planeta);
	void setAcceleracio(glm::dvec3 acceleracio);
	void setSemieixMajor(double semieix);
	void setExcentricitat(double exc);
	void setInclinacio(double inclinacio);
	void setLongitudNodeAscendent(double lon);
	void setPeriapsis(double periapsis);
	void setNLlunes(int llunes) { m_llunes = llunes; }
	void setNSatelits(int s) { m_satelits = s; }
	void setOffsetInicial(float offset) { m_offsetInicial = offset; }
private:
	int m_llunes;
	int m_satelits;
	size_t m_puntsOrbita;
	std::vector<glm::vec3> posicionesHistoricas;
	std::string m_name;
	unsigned int m_textureID;
	unsigned int m_textureIDMenu;
	std::string m_rutaTextura;
	const char* m_rutaTexturaMenu;
	glm::vec3 m_position;
	glm::vec4 m_color;
	float m_radi;
	double m_radi_orbita;
	double m_massa;
	glm::dvec3 m_velocitat;
	unsigned int m_textureIDMenuSelect;
	glm::dvec3 m_acceleracio;
	int m_slices;
	int m_stacks;
	float m_angle_rotacio_orbita;
	float m_velocitat_rotacio;
	glm::vec3 m_eixos_rotacio_planeta;
	int m_direccio_rotacio;
	float m_offsetInicial;
	// Elements orbitals 3D
	double m_semieix_major;   // a
	double m_excentricitat;    // e
	double m_inclinacio;      // i (radians)
	double m_long_node_asc;    // Ω (radians)
	double m_periapsis;    // ω (radians)
};

extern bool paintorbit;

#endif