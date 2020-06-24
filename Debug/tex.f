// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;
in vec4 position;

// Uniform

uniform sampler2D tex;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel
	vec4 tex = texture2D(tex, coordTexture);
	
    out_Color = tex;
}
