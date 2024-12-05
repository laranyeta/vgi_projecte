#include "particleSystem.h"

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

        float velocitat = static_cast<float>(rand()) / RAND_MAX * 2.0f;

        p.respawn(position, direccio, velocitat * 5);

        p.setColor(glm::vec4(
            1.0f,
            static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f,  // Verde aleatorio
            0.0f,
            0.5f));
    }
}

void ParticleSystem::initParticles_Nau(glm::vec3 origen, glm::vec3 direccion) {
    for (auto& p : particles) {
        glm::vec3 dispersio = glm::vec3(
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            0.0f);
        float velocitat = static_cast<float>(rand()) / RAND_MAX * 5.0f;
        p.respawn(origen, direccion + dispersio, velocitat);

        p.setColor(glm::vec4(
            static_cast<float>(rand()) / RAND_MAX * 0.2f + 0.8f,
            static_cast<float>(rand()) / RAND_MAX * 0.2f + 0.8f, 
            1.0f,                                               
            1.0f));
    }
}

void ParticleSystem::update(float deltaTime) {
    for (auto& p : particles) {
        if (p.isActiva()) {
            p.update(deltaTime);
            glm::vec3 pos = p.getPos();
            glm::vec3 direccio = p.getVelAct();

            float maxRadiDispersio = 12.0f;

            if (glm::length(pos) > maxRadiDispersio) {
                glm::vec3 rebot = glm::normalize(pos);
                glm::vec3 novaDireccio = direccio - 2.0f * glm::dot(direccio, rebot) * rebot;
                p.setVelAct(novaDireccio);

                p.setVida(p.getMaxVida());
            }
        }
        std::cout << "Posición partícula: "
            << p.getPos().x << ", "
            << p.getPos().y << ", "
            << p.getPos().z << std::endl;
    }
}

void ParticleSystem::render(GLuint sh_programID, glm::mat4 MatriuVista, glm::mat4 MatriuTG) {
    GLuint VAO, VBO, colorBuffer;

    // Generamos los buffers (solo una vez)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &colorBuffer); // Buffer adicional para los colores

    glBindVertexArray(VAO);

    std::vector<GLfloat> positions;
    std::vector<GLfloat> colors;

    // Llenamos los buffers con las posiciones y colores de las partículas activas
    for (auto& p : particles) {
        if (p.isActiva()) {
            glm::vec3 pos = p.getPos();
            glm::vec4 color = p.getColor();  // Obtén el color de cada partícula

            // Posiciones de las partículas
            positions.push_back(pos.x);
            positions.push_back(pos.y);
            positions.push_back(pos.z);

            // Colores de las partículas (rgba)
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
        }
    }

    // Cargar las posiciones en el VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);

    // Configuración de las posiciones en el shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Cargar los colores en el buffer de colores
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

    // Configuración de los colores en el shader
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // Usamos el programa de shaders
    glUseProgram(sh_programID);

    // Enviar la matriz de vista y transformación al shader
    GLuint matLoc = glGetUniformLocation(sh_programID, "modelViewProjectionMatrix");
    glm::mat4 modelViewProjection = MatriuVista * MatriuTG;  // Calculamos la matriz de proyección y vista
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

    // Dibuja las partículas
    glPointSize(5.0f);  // Tamaño de los puntos de las partículas
    glDrawArrays(GL_POINTS, 0, positions.size() / 3);  // Renderiza todas las partículas

    // Desvincula los buffers y VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Limpiar los buffers y VAO después de dibujar
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteVertexArrays(1, &VAO);

    //glUniform1i(glGetUniformLocation(sh_programID, "sw_material"), false);
}