#ifndef CUBE_H
#define CUBE_H

// Includes OpenGL
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Includes
#include "Shader.h"


class Cube
{
public:
    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);

    void charger();

protected:
    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];

    GLuint m_vboID;
    int m_tailleVerticesBytes;
    int m_tailleCouleursBytes;
};

#endif // CUBE_H
