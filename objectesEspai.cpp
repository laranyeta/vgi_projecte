
#include "objectesEspai.h"
#include <glm/gtx/norm.hpp> // For distance calculations
#include <cmath>

// Constructors

// Default constructor
objectesEspai::objectesEspai()
    : m_puntsOrbita(100), // Default number of orbit points
    m_name("Diposit"),
    m_position(0.0f, 0.0f, 0.0f),
    m_massa(1.0), // Default mass
    m_velocitat(0.0, 0.0, 0.0),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(0.0),
    m_radi(0.5f), // Default radius for an asteroid
    m_type(1)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor without orbit radius
objectesEspai::objectesEspai(float radi, double massa, const glm::dvec3& velocitat, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Diposit"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(0.0),
    m_radi(radi), 
    m_type(1)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor with orbit radius
objectesEspai::objectesEspai(float radi, double massa, const glm::dvec3& velocitat, double radiOrbita, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Diposit"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(radiOrbita),
    m_radi(radi),
    m_type(1)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor with angle rotation and orbit radius
objectesEspai::objectesEspai(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Diposit"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(angleRotacio),
    m_radi_orbita(radiOrbita),
    m_radi(radi),
    m_type(1)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}


// Parameterized constructor with angle rotation and orbit radius
objectesEspai::objectesEspai(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position, const int type)
    : m_puntsOrbita(100),
    m_name("Diposit"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(angleRotacio),
    m_radi_orbita(radiOrbita),
    m_radi(radi),
    m_type(type)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Getters

size_t objectesEspai::getPuntsOrbita() const {
    return m_puntsOrbita;
}

std::string objectesEspai::getName() const {
    return m_name;
}

double objectesEspai::getRadi() const {
    return static_cast<double>(m_radi);
}

double objectesEspai::getRadiOrbita() const {
    return m_radi_orbita;
}

double objectesEspai::getMassa() const {
    return m_massa;
}

glm::dvec3 objectesEspai::getVelocitat() const {
    return m_velocitat;
}

float objectesEspai::getAngleRotacio() const {
    return m_angle_rotacio_orbita;
}

glm::vec3 objectesEspai::getPosition() const {
    return m_position;
}

// Setters

void objectesEspai::setName(const std::string& name) {
    m_name = name;
}

void objectesEspai::setRadi(float radi) {
    m_radi = radi;
}

void objectesEspai::setRadiOrbita(double radiOrbita) {
    m_radi_orbita = radiOrbita;
}

void objectesEspai::setMassa(double massa) {
    m_massa = massa;
}

void objectesEspai::setVelocitat(const glm::dvec3& velocitat) {
    m_velocitat = velocitat;
}

void objectesEspai::setAngleRotacio(float angleRotacio) {
    m_angle_rotacio_orbita = angleRotacio;
}

void objectesEspai::setPosition(const glm::vec3& position) {
    m_position = position;
}

void objectesEspai::setValor(const float value)
{
    m_valor = value;
}
