#ifndef CAMERA_H
#define CAMERA_H

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"


class Camera
{
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical, float sensibilite, float vitesse);
    ~Camera();

    void orienter(int xRel, int yRel);

    void deplacer(Input const &input);

    void lookAt(glm::mat4 &modelview);

    void setPointcible(glm::vec3 pointCible);

    void setPosition(glm::vec3 position);

    // Getters et Setters
    float getSensibilite() const;
    float getVitesse() const;
    void setSensibilite(float sensibilite);
    void setVitesse(float vitesse);


private:
    // Attributs d'orientation
    float m_phi;
    float m_theta;
    glm::vec3 m_orientation;

    // Attributs de d�placement
    glm::vec3 m_axeVertical;
    glm::vec3 m_deplacementLateral;
    glm::vec3 m_position;
    glm::vec3 m_pointCible;

    float m_sensibilite;
    float m_vitesse;

};

#endif // CAMERA_H
