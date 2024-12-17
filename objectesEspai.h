#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>
class objectesEspai
{
public:
    // Constructors
    objectesEspai();
    objectesEspai(const int type);
    objectesEspai(float radi, double massa, const glm::dvec3& velocitat, const glm::vec3& position);
    objectesEspai(float radi, double massa, const glm::dvec3& velocitat, double radiOrbita, const glm::vec3& position);
    objectesEspai(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position);
    objectesEspai(float radi, double massa, const glm::dvec3& velocitat, float angleRotacio, double radiOrbita, const glm::vec3& position, const int type);

    // Getters
    size_t getPuntsOrbita() const;
    std::string getName() const;
    double getRadi() const;
    double getRadiOrbita() const;
    double getMassa() const;
    glm::dvec3 getVelocitat() const;
    float getAngleRotacio() const;
    glm::vec3 getPosition() const;
    float getValor() const { return m_valor; }

    // Setters
    void setName(const std::string& name);
    void setRadi(float radi);
    void setRadiOrbita(double radiOrbita);
    void setMassa(double massa);
    void setVelocitat(const glm::dvec3& velocitat);
    void setAngleRotacio(float angleRotacio);
    void setPosition(const glm::vec3& position);
    void setValor(const float value);
    void setPitch(float p) { m_pitch = p; }
    void setYaw(float p) { m_yaw = p; }
    void setRoll(float p) { m_roll = p; }
    float getPitch() { return m_pitch; }
    float getYaw() { return m_yaw; }
    float getRoll() { return m_roll; }
    int getDireccioRotacio() { return direccioRotacio; }
    void setDireccioRotacio(int d) { direccioRotacio = d; }
    float getLastTimeUsed() { return lastTimeUsed; }
    void setLastTimeUsed(float t) { lastTimeUsed = t; }
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
    int m_type;// 1: Combustible, 2: Estacio Vida
    float m_valor;
    float m_pitch;
    float m_yaw;
    float m_roll;
    int direccioRotacio;
    float lastTimeUsed;
};

