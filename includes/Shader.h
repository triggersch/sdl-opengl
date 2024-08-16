#ifndef SHADER_H
#define SHADER_H
#include <string>
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif



class Shader
{
public:
    Shader(std::string vertexSource, std::string fragmentSource);
    bool charger();
    GLuint getProgramID() const;
    ~Shader();

private:
    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;

    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);

};

#endif // SHADER_H
