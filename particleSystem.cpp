#include "particleSystem.h"
#include "nau.h"
#include "visualitzacio.h"

void ParticleSystem::initParticles_Sol(glm::vec3 origen) {
    float minPos = -7.0f;
    float maxPos = 7.0f;

    for (auto& p : particles) {
        float x = static_cast<float>(rand()) / RAND_MAX * (maxPos - minPos) + minPos;
        float y = static_cast<float>(rand()) / RAND_MAX * (maxPos - minPos) + minPos;
        float z = static_cast<float>(rand()) / RAND_MAX * (maxPos - minPos) + minPos;

        glm::vec3 position = glm::vec3(x, y, z) + origen;

        glm::vec3 direccio = glm::normalize(glm::vec3(
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            static_cast<float>(rand()) / RAND_MAX - 0.5f));

        float velocitat = static_cast<float>(rand()) / RAND_MAX;

        p.respawn(position, direccio, velocitat);

        p.setColor(glm::vec4(
            0.1f,
            static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f,
            0.0f,
            0.8f));
    }
}

void ParticleSystem::initParticles_Nau(glm::vec3 origen, glm::vec3 direccio) {
    Nau nau;
    direccio = nau.getCam().getO();
    glm::vec3 direccionBase = glm::normalize(glm::vec3(nau.getR() * glm::vec4(-direccio, 0.0f))); //direccio cap a la camera

   
    for (auto& p : particles) {
        glm::vec3 offset = glm::vec3(0.3f, 0.0f, 0.0f); //sumem 0.1 a eix X
        glm::vec3 origenParticle = glm::vec3(nau.getR() * glm::vec4(offset, 1.0f)) + origen; //particules es generen al tub d'escap, no al centre de la nau

        //dispersio de les particules
        glm::vec3 dispersio = glm::vec3(
            (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.05f, //x (cap enrera)
            (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.5f, //y
            (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.05f //z
        );

        glm::vec3 direccionFinal = glm::normalize(direccionBase + dispersio);

        float velocitat = static_cast<float>(rand()) / RAND_MAX * 1.5f + 0.5f;

        //reutilitzar particules
        p.respawn(origenParticle, direccionFinal, velocitat);


        p.setColor(glm::vec4(
            static_cast<float>(rand()) / RAND_MAX * 0.2f + 0.8f,
            static_cast<float>(rand()) / RAND_MAX * 0.2f + 0.8f,
            1.0f,
            1.0f
        ));
    }
}

void ParticleSystem::update(float deltaTime, glm::vec3 nouOrigen, glm::mat4 MatriuTG) {
    emissionTimer += deltaTime;

    while (emissionTimer >= (1 / emissionRate)) {
        emissionTimer -= (1 / emissionRate);
        generaParticle(nouOrigen, MatriuTG);
    }

    for (auto& p : particles) {
        if (p.isActiva()) {
            p.update(deltaTime);
            glm::vec4 pos = MatriuTG * glm::vec4(p.getPos(), 1.0f);
            p.setPos(glm::vec3(pos));
        }
    }
}

void ParticleSystem::generaParticle(glm::vec3 origen, glm::mat4 MatriuTG) {
    for (auto& p : particles) {
        if (!p.isActiva()) {
            glm::vec3 offset = glm::vec3(0.3f, 0.0f, 0.0f); //sumem 0.3 a eix X
            glm::vec3 origenParticle = origen + offset; //particules es generen al tub d'escap, no al centre de la nau
            glm::vec4 transOrigen = MatriuTG * glm::vec4(origenParticle, 1.0f);
            glm::vec3 novaDireccio = glm::normalize(glm::vec3(
                (static_cast<float>(rand()) / RAND_MAX - 0.05f),
                (static_cast<float>(rand()) / RAND_MAX - 0.5f),
                (static_cast<float>(rand()) / RAND_MAX - 0.05f)
            ));
            float novaVel = static_cast<float>(rand()) / RAND_MAX * 1.5f + 0.5f;
            p.respawn(glm::vec3(transOrigen), novaDireccio, novaVel);
            return;
        }
    }
}

void ParticleSystem::render(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG) {
    if (mostraParticles) {
        std::vector<GLfloat> posicions;
        std::vector<GLfloat> colores;
        std::vector<GLfloat> texCoords;

        for (auto& p : particles) {
            if (p.isActiva()) {
                glm::vec3 pos = p.getPos();
                posicions.push_back(pos.x);
                posicions.push_back(pos.y);
                posicions.push_back(pos.z);

                texCoords.push_back(0.62f);
                texCoords.push_back(0.62f);
            }
        }
        glBindVertexArray(VAO);

        if (!posicions.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, posicions.size() * sizeof(GLfloat), posicions.data());
        }

        if (!colores.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, colores.size() * sizeof(GLfloat), colores.data());
        }

        if (!texCoords.empty()) {
            GLuint texCoordBuffer;
            glGenBuffers(1, &texCoordBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
            glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0); // 3 = location del shader
            glEnableVertexAttribArray(3);
        }
        glUseProgram(sh_programID);

        GLuint matLoc = glGetUniformLocation(sh_programID, "modelViewProjectionMatrix");
        glm::mat4 modelViewProjection = MatriuVista * MatriuTG;
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

        std::string buf("textures/particle.png");  //carrega textura particle.png
        GLuint texture = loadIMA_SOIL(buf.c_str());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(sh_programID, "texture0"), 0);

        SetTextureParameters(texture, true, true, false, true);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glUniform1i(glGetUniformLocation(sh_programID, "textur"), GL_TRUE);
        glUniform1i(glGetUniformLocation(sh_programID, "modulate"), GL_TRUE);

        glPointSize(10.0f);  //mida particula
        glDrawArrays(GL_POINTS, 0, posicions.size() / 3);

        glBindVertexArray(0);
    }
}
bool mostraParticles = false;