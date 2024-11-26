#include "asteroide.h"
#include <glm/gtx/norm.hpp> // For distance calculations
#include <cmath>

// Constructors

// Default constructor
Asteroide::Asteroide()
    : m_puntsOrbita(100), // Default number of orbit points
    m_name("Asteroide"),
    m_position(0.0f, 0.0f, 0.0f),
    m_massa(1.0), // Default mass
    m_velocitat(0.0, 0.0, 0.0),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(0.0),
    m_radi(0.5f) // Default radius for an asteroid
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor without orbit radius
Asteroide::Asteroide(float radi, double massa, const glm::dvec3& velocitat, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Asteroide"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(0.0),
    m_radi(radi)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor with orbit radius
Asteroide::Asteroide(float radi, double massa, const glm::dvec3& velocitat, double radiOrbita, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Asteroide"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(0.0f),
    m_radi_orbita(radiOrbita),
    m_radi(radi)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Parameterized constructor with angle rotation and orbit radius
Asteroide::Asteroide(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position)
    : m_puntsOrbita(100),
    m_name("Asteroide"),
    m_position(position),
    m_massa(massa),
    m_velocitat(velocitat),
    m_angle_rotacio_orbita(angleRotacio),
    m_radi_orbita(radiOrbita),
    m_radi(radi)
{
    posicionesHistoricas.reserve(m_puntsOrbita);
}

// Orbital Trajectory Methods

void Asteroide::agregarPosicionHistorica(const glm::vec3& posicion) {
    if (posicionesHistoricas.size() >= m_puntsOrbita) {
        posicionesHistoricas.erase(posicionesHistoricas.begin());
    }
    posicionesHistoricas.push_back(posicion);
}

const std::vector<glm::vec3>& Asteroide::getPosicionesHistoricas() const {
    return posicionesHistoricas;
}

// Collision Handling

bool Asteroide::isCollidingWith(const Asteroide& other) const {
    double distanceSquared = glm::distance2(glm::dvec3(m_position), glm::dvec3(other.m_position));
    double radiusSum = static_cast<double>(m_radi*2.2) + static_cast<double>(other.m_radi*2.2);
    return distanceSquared <= (radiusSum * radiusSum);
}

void Asteroide::resolveCollision(Asteroide& other) {
    // Calculate the normal vector
    glm::dvec3 normal = other.m_velocitat - this->m_velocitat;
    double distance = glm::length(normal);
    if (distance == 0.0) {
        // Prevent division by zero
        normal = glm::dvec3(1.0, 0.0, 0.0);
        distance = 1.0;
    }
    normal /= distance;

    // Relative velocity
    glm::dvec3 relativeVelocity = this->m_velocitat - other.m_velocitat;
    double velocityAlongNormal = glm::dot(relativeVelocity, normal);

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0)
        return;

    // Coefficient of restitution (1.0 for elastic collision)
    double e = 1.0;

    // Calculate impulse scalar
    double j = -(1 + e) * velocityAlongNormal;
    j /= (1 / this->m_massa) + (1 / other.m_massa);

    // Apply impulse
    glm::dvec3 impulse = j * normal;
    this->m_velocitat += impulse / this->m_massa;
    other.m_velocitat -= impulse / other.m_massa;

    // Optional: Adjust positions to prevent overlapping
    double overlap = (static_cast<double>(m_radi*2.2) + static_cast<double>(other.m_radi*2.2)) - distance;
    if (overlap > 0) {
        glm::dvec3 correction = (overlap / (this->m_massa + other.m_massa)) * normal;
        this->m_position -= static_cast<float>(correction.x * other.m_massa / (this->m_massa + other.m_massa));
        this->m_position -= static_cast<float>(correction.y * other.m_massa / (this->m_massa + other.m_massa));
        this->m_position -= static_cast<float>(correction.z * other.m_massa / (this->m_massa + other.m_massa));

        other.m_position += static_cast<float>(correction.x * this->m_massa / (this->m_massa + other.m_massa));
        other.m_position += static_cast<float>(correction.y * this->m_massa / (this->m_massa + other.m_massa));
        other.m_position += static_cast<float>(correction.z * this->m_massa / (this->m_massa + other.m_massa));
    }
}

// Getters

size_t Asteroide::getPuntsOrbita() const {
    return m_puntsOrbita;
}

std::string Asteroide::getName() const {
    return m_name;
}

double Asteroide::getRadi() const {
    return static_cast<double>(m_radi);
}

double Asteroide::getRadiOrbita() const {
    return m_radi_orbita;
}

double Asteroide::getMassa() const {
    return m_massa;
}

glm::dvec3 Asteroide::getVelocitat() const {
    return m_velocitat;
}

float Asteroide::getAngleRotacio() const {
    return m_angle_rotacio_orbita;
}

glm::vec3 Asteroide::getPosition() const {
    return m_position;
}

// Setters

void Asteroide::setPuntsOrbita(size_t puntsOrbita) {
    m_puntsOrbita = puntsOrbita;
    posicionesHistoricas.reserve(m_puntsOrbita);
}

void Asteroide::setName(const std::string& name) {
    m_name = name;
}

void Asteroide::setRadi(float radi) {
    m_radi = radi;
}

void Asteroide::setRadiOrbita(double radiOrbita) {
    m_radi_orbita = radiOrbita;
}

void Asteroide::setMassa(double massa) {
    m_massa = massa;
}

void Asteroide::setVelocitat(const glm::dvec3& velocitat) {
    m_velocitat = velocitat;
}

void Asteroide::setAngleRotacio(float angleRotacio) {
    m_angle_rotacio_orbita = angleRotacio;
}

void Asteroide::setPosition(const glm::vec3& position) {
    m_position = position;
}
