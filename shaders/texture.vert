#version 150 core

in vec3 inPosition;      // Les coordonn�es des sommets du mod�le
in vec2 inTexCoord;      // Les coordonn�es de texture associ�es � chaque sommet

out vec2 fragTexCoord;  // Transf�rer les coordonn�es de texture au fragment shader

uniform mat4 projection; // Matrice de projection
uniform mat4 modelview;  // Matrice de vue du mod�le

void main()
{
    // Calcul de la position finale du sommet en utilisant les matrices de projection et de mod�le-vue
    gl_Position = projection * modelview * vec4(inPosition, 1.0);

    // Transf�rer les coordonn�es de texture au fragment shader
    fragTexCoord = inTexCoord;
}
