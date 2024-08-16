#ifndef CAISSE_H
#define CAISSE_H

// Includes
#include "Cube.h"
#include "Texture.h"
#include <string>



class Caisse : public Cube
{
public:
    Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    ~Caisse();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
    Texture m_texture;
    float m_coordTexture[72];
};

#endif // CAISSE_H
