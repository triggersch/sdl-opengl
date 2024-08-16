#version 150 core

in vec2 fragTexCoord;   // Les coordonn�es de texture re�ues du vertex shader

out vec4 fragColor;    // Couleur finale du fragment (couleur de la texture)

uniform sampler2D textureSampler; // Texture � utiliser

void main()
{
    // �chantillonner la texture � l'emplacement des coordonn�es de texture actuelles
    fragColor = texture(textureSampler, fragTexCoord);

    //pour le d�boguage
   //fragColor = vec4(fragTexCoord.x,fragTexCoord.y, 1,0);
}
