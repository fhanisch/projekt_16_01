//vertex shader
//Erstellt: 07.02.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in float mesh_u;
layout (location = 1) in float mesh_v;

out vec4 vertexPosition;
out vec4 normalPosition;

const float pi = 3.14159;

void main()
{
	float R=1.0;	

	float u = 2.0*pi*mesh_u;
	float v = pi*mesh_v;	
	vec3 vertex;
	vec3 normal;
	//vec3 fu,fv;	

	vertex.x = R*sin(v)*cos(u);
	vertex.y = R*sin(v)*sin(u);
	vertex.z = R*cos(v);

	normal.x = sin(v)*cos(u);
	normal.y = sin(v)*sin(u);
	normal.z = cos(v);	

	/*
	fu.x=-sin(v)*sin(u);
	fu.y=sin(v)*cos(u);
	fu.z=0.0;

	fv.x=cos(v)*cos(u);
	fv.y=cos(v)*sin(u);
	fv.z=-sin(v);

	normal = -cross(fu,fv);
	*/
			
	vertexPosition = mView * mModel * vec4(vertex, 1.0);
	normalPosition = transpose(inverse(mView*mModel)) * vec4(normal, 1.0);
		
	gl_Position = mProj * vertexPosition;
}

