//vertex shader
//Erstellt: 31.01.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in float u;

void main()
{
	float x,y;
	
	x = cos(u*2*3.14159/100.0);
	y = -sin(u*2*3.14159/100.0);

	gl_Position = mProj * mView * mModel * vec4(x, y, 0.0, 1.0);
}

