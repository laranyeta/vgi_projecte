#ifndef OBB_H
#define OBB_H

#include <glm/glm.hpp>

// Oriented bounding box
struct OBB {
    glm::vec3 center;
    // Eixos locals de la caixa (mateixos que els de la nau)
    glm::vec3 axes[3];      // vectors d'orientació
    // Distancia del centre a les cares de la caixa al llarg dels
    // seus eixos locals
    glm::vec3 halfExtents; 

    OBB() : center(0.0f, 0.0f, 0.0f),
        axes{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
        halfExtents(1.0f, 1.0f, 1.0f) {}

    OBB(const glm::vec3& c, const glm::vec3* a, const glm::vec3& he)
        : center(c), halfExtents(he) {
        axes[0] = a[0];
        axes[1] = a[1];
        axes[2] = a[2];
    }
};

#endif // OBB_H