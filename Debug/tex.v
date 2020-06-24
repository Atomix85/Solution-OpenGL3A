// Version du GLSL

#version 330 core


// Entr�es

in vec3 in_Vertex;
in vec2 in_TexCoord0;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;

layout(location = 2) in vec2 vertexUV;

// Sortie

out vec2 coordTexture;
out vec4 position;

// Fonction main

void main()
{
    // Position finale du vertex en 3D

	position = vec4(in_Vertex,1.0) ;

	coordTexture = vertexUV;
	
    gl_Position = projection * modelview * vec4(in_Vertex,1.0);


    // Envoi des coordonn�es de texture au Fragment Shader

    
}
