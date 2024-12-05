#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
#include <vector>
#include <cstdlib>
#include <GL/glew.h>

enum class ParticleType {
    Sol,
    Nau
};

class ParticleSystem {
public:
    ParticleSystem(int maxParticles, ParticleType type, glm::vec3 origen, glm::vec3 direccion = glm::vec3(0.0f)): maxParticles(maxParticles) {
        particles.resize(maxParticles);
        if (type == ParticleType::Sol)
            initParticles_Sol(origen);
        else if (type == ParticleType::Nau)
            initParticles_Nau(origen, direccion);
    }

    void initParticles_Sol(glm::vec3 origen);
    void initParticles_Nau(glm::vec3 origen, glm::vec3 direccion);

    void update(float deltaTime);
    void render(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG);

private:
    std::vector<Particle> particles;
    int maxParticles;
};

#endif