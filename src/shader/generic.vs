//vertex shader
//Erstellt: 30.01.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in vec3 vertex;

void main()
{	
	gl_Position = mProj * mView * mModel * vec4(vertex,1.0);
}

