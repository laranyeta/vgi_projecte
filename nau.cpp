#include "nau.h"
#include <iostream>

void Nau::resolveCollisionWithAsteroid(Asteroide& asteroid, const glm::vec3& collisionPoint) {
    // Escalat de masses
    asteroid.playCollisionSound();
    const float massScale = 1e-12f;
    double scaledShipMass = m_massa * massScale;
    double scaledAsteroidMass = asteroid.getMassa() * massScale;

    // Vector de col�lisi� normal del centre de l'asteroide al punt de col�lisi�
    glm::vec3 normal = collisionPoint - asteroid.getPosition();
    float distance = glm::length(normal);
    if (distance == 0.0f) {
        normal = glm::vec3(1.0f, 0.0f, 0.0f);
        distance = 1.0f;
    }
    normal /= distance;

    // A partir d'aqui proc�s similar del tractament de col�lisions
    // asteroide amb asteroide

    // Velocitat relativa
    glm::vec3 relativeVelocity = (glm::dvec3)m_velocitat - asteroid.getVelocitat();
    std::cout << "Relative velocity: X: " << relativeVelocity.x << " Y: " << relativeVelocity.y << " Z: " << relativeVelocity.z << std::endl;
    float velocityAlongNormal = glm::dot(relativeVelocity, normal);
    std::cout << "Velocity along normal: " << velocityAlongNormal << std::endl;

    if (velocityAlongNormal > 0)
        return;

    float e = 1.0f;
    float j = -(1 + e) * velocityAlongNormal;
    j /= (1 / static_cast<float>(scaledShipMass)) + (1 / static_cast<float>(scaledAsteroidMass));

    glm::vec3 impulse = j * normal;
    m_velocitat += impulse / static_cast<float>(scaledShipMass);
    glm::dvec3 asteroidVelocity = asteroid.getVelocitat() - (glm::dvec3)impulse / scaledAsteroidMass;
    std::cout << "Impulse: X: " << impulse.x << " Y: " << impulse.y << " Z: " << impulse.z << std::endl;
    std::cout << "M_velocitat: X: " << m_velocitat.x << " Y: " << m_velocitat.y << " Z: " << m_velocitat.z << std::endl;

    // Actualitzar velocitats
    m_s = glm::length(m_velocitat);
    asteroid.setVelocitat(asteroidVelocity);

    // Tractar overlapping
    float shipRadiusApprox = glm::length(m_obb.halfExtents); // Approximate ship's "radius"
    float overlap = (asteroid.getRadi() + shipRadiusApprox) - distance;
    if (overlap > 0) {
        glm::vec3 correction = (overlap / (scaledShipMass + scaledAsteroidMass)) * (glm::dvec3)normal;
        m_o += correction * static_cast<float>(scaledAsteroidMass / (scaledShipMass + scaledAsteroidMass));
        glm::vec3 newAsteroidPos = asteroid.getPosition() - correction * static_cast<float>(scaledShipMass / (scaledShipMass + scaledAsteroidMass));
        std::cout << "newAsteroidPos: X: " << newAsteroidPos.x << " Y: " << newAsteroidPos.y << " Z: " << newAsteroidPos.z << std::endl;
        std::cout << "currentAsteroidPos: x: " << asteroid.getPosition().x << " Y: " << asteroid.getPosition().y << " Z: " << asteroid.getPosition().z << std::endl;
        asteroid.setPosition(newAsteroidPos);
    }

    // Actualitzar vida de la nau
    m_life -= 0.1f;
    std::cout << m_life << std::endl;

    updateOBB();
}

void Nau::updatePhysicsWithPlanets(const std::vector<Planeta>& planetas, double deltaTime)
{
}
