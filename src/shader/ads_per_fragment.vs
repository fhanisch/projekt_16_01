//vertex shader
//Erstellt: 03.02.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 vertexPosition;
out vec4 normalPosition;

void main()
{				
	vertexPosition = mView * mModel * vec4(vertex, 1.0);
	normalPosition = transpose(inverse(mView*mModel)) * vec4(normal, 1.0);
			
	gl_Position = mProj * vertexPosition;
}

