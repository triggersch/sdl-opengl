#include "SceneOpenGL.h"
#include "Shader.h"
#include "Texture.h"
#include "Caisse.h"

using namespace glm;

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre): m_titreFenetre(titreFenetre),
    m_largeurFenetre(largeurFenetre),m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0),
    m_input()
{
    //ctor
}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : "
                  << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
// Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    m_fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();
        return false;
    }

    return true;
}

bool SceneOpenGL::initGL()
{
#ifdef WIN32
// On initialise GLEW
    GLenum initialisationGLEW( glewInit() );
// Si l'initialisation a échouée :
    if(initialisationGLEW != GLEW_OK)
    {
// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
        std::cout << "Erreur d'initialisation de GLEW : " <<
                  glewGetErrorString(initialisationGLEW) << std::endl;
// On quitte la SDL
        SDL_GL_DeleteContext(m_contexteOpenGL);
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();
        return false;
    }
#endif
// Activation du Depth Buffer
    glEnable(GL_DEPTH_TEST);
    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    // Variables
    unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    // Objet Caisse
    Caisse caisse(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/crate13.jpg");
// Matrices
    mat4 projection;
    mat4 modelview;
    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);

    // Caméra mobile
    Camera camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0), 0.5, 0.5);
    // Capture du pointeur
    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);


// Vertices
    float vertices[] = {-10, 0, -10,   10, 0, -10,  10, 0, 10,  //Triangle 1
                        -10, 0, -10,   -10, 0, 10,  10, 0, 10
                       }; //Triangle 2
// Coordonnées de texture
    float coordTexture[] = {0, 0,   7, 0,   7, 7, // Triangle 1
                            0, 0,   0, 7,   7, 7
                           }; // Triangle 2

    // Texture
    Texture texture("Textures/veg005.jpg");
    texture.charger();
// Shader
    Shader shaderTexture("Shaders/texture.vert",
                         "Shaders/texture.frag");
    shaderTexture.charger();
// Boucle principale

    while(!m_input.terminer())
    {
// On définit le temps de début de boucle
        debutBoucle = SDL_GetTicks();
// Gestion des événements
        m_input.updateEvenements();
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;

        camera.deplacer(m_input);
// Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Placement de la caméra
        // Gestion de la caméra
        camera.lookAt(modelview);

        // Sauvegarde de la matrice modelview
        mat4 sauvegardeModelview = modelview;
        // Translation pour positionner le cube
        modelview = translate(modelview, vec3(0, 1, 0));
        // Affichage du cube
        caisse.afficher(projection, modelview);
        // Restauration de la matrice
        modelview = sauvegardeModelview;
// Activation du shader
        glUseProgram(shaderTexture.getProgramID());
// Envoi des vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);
// Envoi des coordonnées de texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, coordTexture);
        glEnableVertexAttribArray(1);
// Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramID(),
                                                "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramID(),
                                                "modelview"), 1, GL_FALSE, value_ptr(modelview));
// Verrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, texture.getID());
// Rendu
        glDrawArrays(GL_TRIANGLES, 0, 6);
// Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);
// Désactivation des tableaux
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
// Désactivation du shader
        glUseProgram(0);
// Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);
// Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;
// Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }

}

/*void SceneOpenGL::bouclePrincipale()
{
    // Variables relatives à la boucle
    unsigned int frameRate (1000 / 60);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

// Création du shader
    Cube cube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

// Matrices
    mat4 projection;
    mat4 modelview;
    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);

    // Variable angle
    float angle(0.0);
    float angleX(0.0);
    modelview = mat4(1.0);

// Texture
    Texture texture("Textures/crate13.jpg");
    texture.charger();
// Boucle principale
    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle
        debutBoucle = SDL_GetTicks();
        // Gestion des événements
        m_input.updateEvenements();
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;
        if(m_input.getTouche(SDL_SCANCODE_LEFT))
            angle += 4.0;
        if(m_input.getTouche(SDL_SCANCODE_RIGHT))
            angle -= 4.0;

        if(m_input.getTouche(SDL_SCANCODE_UP))
            angleX += 4.0;
        if(m_input.getTouche(SDL_SCANCODE_DOWN))
            angleX -= 4.0;
        if(m_input.mouvementSouris() && m_input.getBoutonSouris(1))
        {
            angle += m_input.getXRel();
            angleX += m_input.getYRel();
        }

        // Nettoyage de l'écran et du Depth Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Placement de la caméra
        modelview = lookAt(vec3(6, 6, 6), vec3(3, 0, 0), vec3(0, 1, 0));

        // Incrémentation de l'angle
        //angle += 4.0;
        if(angle >= 360.0)
            angle -= 360.0;

        // Translation
        //modelview = translate(modelview, vec3(0.4, 0.0, 0.0));

        // Sauvegarde de la matrice modelview
        mat4 sauvegardeModelview = modelview;

        // Rotation
        //modelview = rotate(modelview, angle, vec3(0.0, 1.0, 0.0));
        modelview = rotate(modelview, angle, vec3(0, 1, 0));
        modelview = rotate(modelview, angleX, vec3(1, 0, 0));


        // Homothétie ou symétrie
        //modelview = scale(modelview, vec3(1, -1, 1));

        // Affichage du cube
        cube.afficher(projection, modelview);

        // Restauration de la matrice
        modelview = sauvegardeModelview;

        // Affichage du second cube un peu plus loin
        modelview = translate(modelview, vec3(10, 0, 0));
        cube.afficher(projection, modelview);

        // Restauration de la matrice
        modelview = sauvegardeModelview;



// Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);

        // Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;

        // Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}*/
