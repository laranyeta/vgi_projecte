#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <vector>
#include <glm/glm.hpp>
#include <string>

class Asteroide {
public:
    // Constructors
    Asteroide();
    Asteroide(float radi, double massa, const glm::dvec3& velocitat, const glm::vec3& position);
    Asteroide(float radi, double massa, const glm::dvec3& velocitat, double radiOrbita, const glm::vec3& position);
    Asteroide(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position);

    // Orbital Trajectory
    void agregarPosicionHistorica(const glm::vec3& posicion);
    const std::vector<glm::vec3>& getPosicionesHistoricas() const;

    // Collision Handling
    bool isCollidingWith(const Asteroide& other) const;
    void resolveCollision(Asteroide& other);

    // Getters
    size_t getPuntsOrbita() const;
    std::string getName() const;
    double getRadi() const;
    double getRadiOrbita() const;
    double getMassa() const;
    glm::dvec3 getVelocitat() const;
    float getAngleRotacio() const;
    glm::vec3 getPosition() const;

    // Setters
    void setPuntsOrbita(size_t puntsOrbita);
    void setName(const std::string& name);
    void setRadi(float radi);
    void setRadiOrbita(double radiOrbita);
    void setMassa(double massa);
    void setVelocitat(const glm::dvec3& velocitat);
    void setAngleRotacio(float angleRotacio);
    void setPosition(const glm::vec3& position);

    std::vector<glm::vec3> posicionesHistoricas;
private:
    size_t m_puntsOrbita;
    std::string m_name;
    glm::vec3 m_position;
    double m_massa;
    glm::dvec3 m_velocitat;
    float m_angle_rotacio_orbita;
    double m_radi_orbita;
    float m_radi;
};

#endif 
