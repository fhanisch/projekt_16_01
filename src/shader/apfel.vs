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
const float R1 = 5.0;
const float R2 = 4.8;
const float scale = 0.1;

void main()
{
	float u = pi*(2.0*mesh_u-1.0);
	float v = pi*(2.0*mesh_v-1.0);
	vec3 vertex;
	vec3 normal;
	vec3 fu, fv;

	vertex.x = scale*(cos(u)*(R1+R2*cos(v))+pow(abs(v)/pi,20.0));  // pow(x,y) --> x kann keine negativen Werte annehmen!!!
	vertex.y = scale*(-2.3*log(1.0-v*0.3157)+6.0*sin(v)+2.0*cos(v));
	vertex.z = scale*(sin(u)*(R1+R2*cos(v))+0.25*cos(5.0*u));

	fu.x = -scale*sin(u)*(R1 + R2*cos(v));
	fu.y = 0.0;
	fu.z = -scale*((5.0*sin(5.0*u))/4.0 - cos(u)*(R1 + R2*cos(v)));

	fv.x = scale*((20.0*pow(abs(v),19.0)*sign(v))/pow(pi,20.0) - R2*cos(u)*sin(v)); // pow(x,y) --> x kann keine negativen Werte annehmen!!!
	fv.y = -scale*(2.0*sin(v) - 6.0*cos(v) + 72611.0/(100000.0*((3157.0*v)/10000.0 - 1.0)));
	fv.z = -R2*scale*sin(u)*sin(v);

	normal = -cross(fu,fv);

			
	vertexPosition = mView * mModel * vec4(vertex, 1.0);
	normalPosition = transpose(inverse(mView*mModel)) * vec4(normal, 1.0);
		
	gl_Position = mProj * vertexPosition;
}

