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
//al final nomes es fan particules nau!

class ParticleSystem {
public:
    ParticleSystem(int maxParticles, ParticleType type, glm::vec3 origen, glm::vec3 direccio=glm::vec3()) : 
        maxParticles(maxParticles), VAO(0.0f), VBO(0.0f), colorBuffer(0.0f), emissionTimer(0.0f), emissionRate(5000.0f) {
        particles.resize(maxParticles);
        if (type == ParticleType::Nau)
            initParticles_Nau(origen, direccio);
        //else if (type == ParticleType::Sol)
            //initParticles_Sol(origen);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &colorBuffer);

        glBindVertexArray(VAO);
        
        //inicialitza vbo
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, maxParticles * 3 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        //inicialitza buffer colors
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }
    
    ~ParticleSystem() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &colorBuffer);
        glDeleteVertexArrays(1, &VAO);
    }

    void initParticles_Sol(glm::vec3 origen);
    void initParticles_Nau(glm::vec3 origen, glm::vec3 direccion);

    void update(float deltaTime, glm::vec3 nouOrigen, glm::mat4 MatriuTG);
    void render(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG);

private:
    std::vector<Particle> particles;
    int maxParticles;
    GLuint VAO, VBO, colorBuffer;

    float emissionTimer; //temporitzador per a la proxiuma particula a generar-se
    float emissionRate; //quantes particules es generen per segon

    void generaParticle(glm::vec3 origen, glm::mat4 MatriuTG);
};

extern bool mostraParticles;
#endif