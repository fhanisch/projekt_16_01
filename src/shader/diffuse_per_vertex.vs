//vertex shader
//Erstellt: 03.02.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
out float lightIntensity;

const vec3 lightSource = vec3(10.0, 10.0, 10.0);

void main()
{
	vec4 vertexPosition;
	vec4 normalPosition;
	vec4 lightPosition;
		
	vertexPosition = mView * mModel * vec4(vertex, 1.0);
	normalPosition = transpose(inverse(mView*mModel)) * vec4(normal, 1.0);

	lightPosition = mView * vec4(lightSource, 1.0);
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	lightIntensity = max(dot(s,normalize(normalPosition.xyz)), 0.0);
		
	gl_Position = mProj * vertexPosition;
}

