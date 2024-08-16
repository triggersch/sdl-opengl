#version 150 core

in vec2 fragTexCoord;   // Les coordonnées de texture reçues du vertex shader

out vec4 fragColor;    // Couleur finale du fragment (couleur de la texture)

uniform sampler2D textureSampler; // Texture à utiliser

void main()
{
    // Échantillonner la texture à l'emplacement des coordonnées de texture actuelles
    fragColor = texture(textureSampler, fragTexCoord);

    //pour le déboguage
   //fragColor = vec4(fragTexCoord.x,fragTexCoord.y, 1,0);
}
