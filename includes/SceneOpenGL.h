#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H
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

#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "Cube.h"
#include "Input.h"
#include "Camera.h"



class SceneOpenGL
{
public:
    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();
    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();

private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

    Input m_input;

};

#endif // SCENEOPENGL_H
