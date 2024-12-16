#include "asteroide.h"
#include <glm/gtx/norm.hpp> // For distance calculations
#include <cmath>
#include<iostream> //luis
using namespace std;//luis
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
    m_radi(0.5f), // Default radius for an asteroid
    m_so_colisio(false) //luis
{
    posicionesHistoricas.reserve(m_puntsOrbita);
    m_soundEngine = createIrrKlangDevice();//luis
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
    m_radi(radi),
    m_so_colisio(false) //luis
{
    posicionesHistoricas.reserve(m_puntsOrbita);
    m_soundEngine = createIrrKlangDevice();//luis
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
    m_radi(radi),
    m_so_colisio(false) //luis
{
    posicionesHistoricas.reserve(m_puntsOrbita);
    m_soundEngine = createIrrKlangDevice();//luis
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
    m_radi(radi),
    m_so_colisio(false) //luis
{
    posicionesHistoricas.reserve(m_puntsOrbita);
    m_soundEngine = createIrrKlangDevice();//luis
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

bool Asteroide::isCollidingWith(const Asteroide& other) { //li vaig treure el const per poder modificar el boolea, si trobem la manera de fer-ho sense boolea podem tornar el const
    double distanceSquared = glm::distance2(glm::dvec3(m_position), glm::dvec3(other.m_position));
    double radiusSum = static_cast<double>(m_radi*2.2) + static_cast<double>(other.m_radi*2.2);

    bool isColliding = distanceSquared <= (radiusSum * radiusSum); //luis

    if (!isColliding)
    {
        if (m_so_colisio)
            m_so_colisio = false; //luis
    }

    return isColliding; //luis
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

    if (!m_so_colisio) { //luis
        // Calcular la posición promedio de la colisión
        /*glm::vec3 minDistancePosition = glm::vec3(0.1f, 0.1f, 0.1f);
        irrklang::vec3df collisionPosition = irrklang::vec3df(
            std::max(collisionPosition.X, minDistancePosition.x), //tot això són intents de so direccional
            std::max(collisionPosition.Y, minDistancePosition.y),
            std::max(collisionPosition.Z, minDistancePosition.z)
        );*/

        // Reproducir el sonido de la colisión en 3D Luis
        //engine2->play3D("./media/altres/seleccio_menu.wav", collisionPosition, false, false, false);

        playCollisionSound();
        m_so_colisio = true;

    }

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

void Asteroide::playCollisionSound() { //luis
    if (m_soundEngine) {
        m_soundEngine->play2D("C:/Users/lvera/Desktop/vgi cosas/Entorn VGI-GLFW-VS2022 - GL4.3 - ImGui/EntornVGI/media/altres/colisio.wav", false, false, false);

    }

    /*if (m_soundEngine) {
        // Convertir la posición del asteroide de glm::vec3 a irrklang::vec3df
        irrklang::vec3df soundPosition(m_position.x, m_position.y, m_position.z);

        // Reproducir el sonido en la posición 3D del asteroide
        m_soundEngine->play3D("C:/Users/lvera/Desktop/vgi cosas/Entorn VGI-GLFW-VS2022 - GL4.3 - ImGui/EntornVGI/media/altres/colisio.wav", soundPosition, false, false, true);
    }*/
    else {
        std::cerr << "Error: El motor de sonido no está inicializado." << std::endl;
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
