//fragment shader
//Erstellt: 04.02.2016

#version 440

uniform vec4 color;

in float lightIntensity;
out vec4 FragColor;

void main()
{	
	FragColor = lightIntensity * color;
}
