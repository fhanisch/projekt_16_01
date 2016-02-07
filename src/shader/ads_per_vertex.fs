//fragment shader
//Erstellt: 04.02.2016

#version 440

in vec3 ADS;
out vec4 FragColor;

void main()
{	
	FragColor = vec4(ADS, 1.0);	
}
