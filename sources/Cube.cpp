#include "Cube.h"

using namespace glm;

Cube::Cube(float taille, std::string const vertexShader, std::string const fragmentShader)
    : m_shader(vertexShader, fragmentShader), m_vboID(0), m_tailleVerticesBytes(108 * sizeof(float)),
      m_tailleCouleursBytes(108 * sizeof(float))
{
    // Chargement du shader
    m_shader.charger();

    // Division de la taille
    taille /= 2;

    // Vertices temporaires
    float verticesTmp[] = {-taille, -taille, -taille, taille,
                           -taille, -taille, taille, taille, -taille, // Face 1
                           -taille, -taille, -taille, -taille,
                           taille, -taille, taille, taille, -taille, // Face 1
                           taille, -taille, taille, taille,
                           -taille, -taille, taille, taille, -taille, // Face 2
                           taille, -taille, taille, taille,
                           taille, taille, taille, taille, -taille, // Face 2
                           -taille, -taille, taille, taille,
                           -taille, taille, taille, -taille, -taille, // Face 3
                           -taille, -taille, taille, -taille,
                           -taille, -taille, taille, -taille, -taille, // Face 3
                           -taille, -taille, taille, taille,
                           -taille, taille, taille, taille, taille, // Face 4
                           -taille, -taille, taille, -taille,
                           taille, taille, taille, taille, taille, // Face 4
                           -taille, -taille, -taille, -taille,
                           -taille, taille, -taille, taille, taille, // Face 5
                           -taille, -taille, -taille, -taille,
                           taille, -taille, -taille, taille, taille, // Face 5
                           -taille, taille, taille, taille,
                           taille, taille, taille, taille, -taille, // Face 6
                           -taille, taille, taille, -taille,
                           taille, -taille, taille, taille, -taille
                          }; // Face 6
// Couleurs temporaires
    float couleursTmp[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                           0.0, 0.0, // Face 1
                           1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                           0.0, 0.0, // Face 1
                           0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                           1.0, 0.0, // Face 2
                           0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                           1.0, 0.0, // Face 2
                           0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                           0.0, 1.0, // Face 3
                           0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                           0.0, 1.0, // Face 3
                           1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                           0.0, 0.0, // Face 4
                           1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                           0.0, 0.0, // Face 4
                           0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                           1.0, 0.0, // Face 5
                           0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                           1.0, 0.0, // Face 5
                           0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                           0.0, 1.0, // Face 6
                           0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
                           0.0, 1.0
                          }; // Face 6

    // Copie des valeurs dans les tableaux finaux
    for(int i(0); i < 108; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_couleurs[i] = couleursTmp[i];
    }

}
Cube::~Cube()
{
    // Destruction du VBO
    glDeleteBuffers(1, &m_vboID);
}

void Cube::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader
    glUseProgram(m_shader.getProgramID());

    // Envoi des vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
    glEnableVertexAttribArray(0);

    // Envoi de la couleur
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_couleurs);
    glEnableVertexAttribArray(1);

    // Envoi des matrices
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

    // Rendu
    glDrawArrays(GL_TRIANGLES, 0, 36);
// Dêsactivation des tableaux
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
// Dêsactivation du shader
    glUseProgram(0);
}

void Cube::charger()
{

    // Destruction d'un êventuel ancien VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
        glDeleteBuffers(1, &m_vboID);

// Gênêration de l'ID
    glGenBuffers(1, &m_vboID);

    // Verrouillage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Allocation de la mêmoire
    glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);

    // Transfert des donnêes
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_couleurs);


    // Dêverrouillage de l'objet
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
