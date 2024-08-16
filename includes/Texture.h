#ifndef TEXTURE_H
#define TEXTURE_H

// Include
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>



class Texture
{
public:
    Texture(std::string fichierImage);
    Texture(Texture const &textureACopier);
    Texture();
    ~Texture();
    Texture& operator=(Texture const &textureACopier);

    bool charger();
    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);


private:

    GLuint m_id;
    std::string m_fichierImage;

    SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;
};

#endif // TEXTURE_H
