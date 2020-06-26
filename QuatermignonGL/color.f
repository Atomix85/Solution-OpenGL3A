// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;
//int vec3 normal;
in vec4 position;

// Uniform

uniform sampler2D _texture;


// Sortie 

out vec4 out_Color;


// Fonction main


void main()
{
    // Couleur du pixel
	vec4 tex = position;
	
    out_Color = tex;
}
