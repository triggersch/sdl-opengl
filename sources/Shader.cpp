#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string vertexSource, std::string fragmentSource)
    :  m_vertexID(0), m_fragmentID(0), m_programID(0),
       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}

Shader::~Shader()
{

}

bool Shader::charger()
{
// Compilation des shaders
    if(!compilerShader(m_vertexID, GL_VERTEX_SHADER,
                       m_vertexSource))
        return false;
    if(!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER,
                       m_fragmentSource))
        return false;

    // Création du programme
    m_programID = glCreateProgram();


    // Association des shaders
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    glLinkProgram(m_programID);

    // Vérification du linkage
    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);
// S'il y a eu une erreur
    if(erreurLink != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de mémoire
        char *erreur = new char[tailleErreur + 1];
        // Récupération de l'erreur
        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur,
                           erreur);
        erreur[tailleErreur] = '\0';

        // Affichage de l'erreur
        std::cout << erreur << std::endl;
// Libération de la mémoire et retour du booléen false
        delete[] erreur;
        glDeleteProgram(m_programID);
        return false;

    }
    else// Sinon c'est que tout s'est bien passé
        return true;

}

GLuint Shader::getProgramID() const
{
    return m_programID;
}

bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader
    shader = glCreateShader(type);
    if(shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ")n'existe pas" << std::endl;
        return false;
    }
    // Flux de lecture
    std::ifstream fichier(fichierSource.c_str());

    // Test d'ouverture
    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);
        return false;
    }

    // Strings permettant de lire le code source
    std::string ligne;
    std::string codeSource;

    // Lecture
    while(getline(fichier, ligne))
        codeSource += ligne + '\n';

    // Fermeture du fichier
    fichier.close();

    // Récupération de la chaine C du code source
    const GLchar* chaineCodeSource = codeSource.c_str();
// Envoi du code source au shader
    glShaderSource(shader, 1, &chaineCodeSource, 0);
// Compilation du shader
    glCompileShader(shader);
// Vérification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);
    // S'il y a eu une erreur
    if(erreurCompilation != GL_TRUE)
    {
// Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);
// Allocation de mémoire
        char *erreur = new char[tailleErreur + 1];
// Récupération de l'erreur
        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur,
                           erreur);
        erreur[tailleErreur] = '\0';
// Affichage de l'erreur
        std::cout << erreur << std::endl;
// Libération de la mémoire et retour du booléen false
        delete[] erreur;
        glDeleteShader(shader);
        return false;
    }
// Sinon c'est que tout s'est bien passé
    else
        return true;
}
