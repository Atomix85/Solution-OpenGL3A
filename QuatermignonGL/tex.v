// Version du GLSL

#version 330 core


// Entrées

in vec3 in_Vertex;
in vec2 in_coord;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;


// Sortie

out vec2 coordTexture;
out vec4 position;

// Fonction main

void main()
{
    // Position finale du vertex en 3D

	position = vec4(in_Vertex,1.0) ;

	coordTexture = in_coord;
	
    gl_Position = projection * modelview * vec4(in_Vertex,1.0);


    // Envoi des coordonnées de texture au Fragment Shader

    
}
