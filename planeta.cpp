#include "Planeta.h"

// Constructors
Planeta::Planeta() {
    m_radi = 1.0f;
    m_slices = 20;
    m_stacks = 20;
    m_massa = 0.0;
    m_velocitat = glm::dvec3(0.0f, 0.0f, 0.0f);
    m_acceleracio = glm::dvec3(0.0f, 0.0f, 0.0f);
    m_angle_rotacio_orbita = 0.0f;
    m_radi_orbita = 0.0;
    m_color = { 0.0, 0.0, 0.0, 1.0 };
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

Planeta::Planeta(float radi, int slices, int stacks, glm::vec3 position) {
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

Planeta::Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, glm::vec3 position) {
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

Planeta::Planeta(float radi, int slices, int stacks, double massa, glm::dvec3 velocitat, float angleRotacio, double radiOrbita, glm::vec3 position) {
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

// Orbital Trajectory
void Planeta::agregarPosicionHistorica(const glm::vec3& posicion) {
    if (posicionesHistoricas.size() > m_puntsOrbita) {
        posicionesHistoricas.erase(posicionesHistoricas.begin());
    }
    posicionesHistoricas.push_back(posicion);
}

const std::vector<glm::vec3>& Planeta::getPosicionesHistoricas() const {
    return posicionesHistoricas;
}

// Getters
size_t Planeta::getPuntsOrbita() const { return m_puntsOrbita; }
std::string Planeta::getName() const { return m_name; }
std::string Planeta::getRutaTextura() const { return m_rutaTextura; }
unsigned int Planeta::getTextureID() const { return m_textureID; }
double Planeta::getRadi() const { return m_radi; }
double Planeta::getRadiOrbita() const { return m_radi_orbita; }
double Planeta::getMassa() const { return m_massa; }
glm::dvec3 Planeta::getVelocitat() const { return m_velocitat; }
int Planeta::getSlices() const { return m_slices; }
int Planeta::getStacks() const { return m_stacks; }
float Planeta::getAngleRotacio() const { return m_angle_rotacio_orbita; }
float Planeta::getVelocitatRotacio() const { return m_velocitat_rotacio; }
int Planeta::getDireccioRotacio() const { return m_direccio_rotacio; }
glm::dvec3 Planeta::getAcceleracio() const { return m_acceleracio; }
glm::vec3 Planeta::getEixosRotacioPlaneta() const { return m_eixos_rotacio_planeta; }
glm::vec4 Planeta::getColor() const { return m_color; }
glm::vec3 Planeta::getPosition() const { return m_position; }
double Planeta::getPeriapsis() { return m_periapsis; }
double Planeta::getSemieixMajor() { return m_semieix_major; }
double Planeta::getLongitudNodeAscendent() { return m_long_node_asc; }
double Planeta::getInclinacio() { return m_inclinacio; }
double Planeta::getExcentricitat() { return m_excentricitat; }

// Setters
void Planeta::setPuntsOrbita(size_t puntsOrbita) { m_puntsOrbita = puntsOrbita; }
void Planeta::setName(std::string name) { m_name = name; }
void Planeta::setTextureID(unsigned int texID) { m_textureID = texID; }
void Planeta::setRutaTextura(std::string rutaTextura) { m_rutaTextura = rutaTextura; }
void Planeta::setRadi(float radi) { m_radi = radi; }
void Planeta::setRadiOrbita(float radiOrbita) { m_radi_orbita = radiOrbita; }
void Planeta::setMassa(float massa) { m_massa = massa; }
void Planeta::setVelocitat(glm::dvec3 velocitat) { m_velocitat = velocitat; }
void Planeta::setSlices(int slices) { m_slices = slices; }
void Planeta::setStacks(int stacks) { m_stacks = stacks; }
void Planeta::setAngleRotacio(float angleRotacio) { m_angle_rotacio_orbita = angleRotacio; }
void Planeta::setColor(glm::vec4 color) { m_color = color; }
void Planeta::setPosition(glm::vec3 position) { m_position = position; }
void Planeta::setVelocitatRotacio(float velocitat) { m_velocitat_rotacio = velocitat; }
void Planeta::setDireccioRotacio(int direccio) { m_direccio_rotacio = direccio; }
void Planeta::setEixosRotacioPlaneta(glm::vec3 eixos_rotacio_planeta) { m_eixos_rotacio_planeta = eixos_rotacio_planeta; }
void Planeta::setAcceleracio(glm::dvec3 acceleracio) { m_acceleracio = acceleracio; }
void Planeta::setSemieixMajor(double semieix) { m_semieix_major = semieix; }
void Planeta::setExcentricitat(double exc) { m_excentricitat = exc; }
void Planeta::setInclinacio(double inclinacio) { m_inclinacio = inclinacio; }
void Planeta::setLongitudNodeAscendent(double lon) { m_long_node_asc = lon; }
void Planeta::setPeriapsis(double periapsis) { m_periapsis = periapsis; }

bool paintorbit = false;