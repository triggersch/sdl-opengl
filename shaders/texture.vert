#version 150 core

in vec3 inPosition;      // Les coordonnées des sommets du modèle
in vec2 inTexCoord;      // Les coordonnées de texture associées à chaque sommet

out vec2 fragTexCoord;  // Transférer les coordonnées de texture au fragment shader

uniform mat4 projection; // Matrice de projection
uniform mat4 modelview;  // Matrice de vue du modèle

void main()
{
    // Calcul de la position finale du sommet en utilisant les matrices de projection et de modèle-vue
    gl_Position = projection * modelview * vec4(inPosition, 1.0);

    // Transférer les coordonnées de texture au fragment shader
    fragTexCoord = inTexCoord;
}
