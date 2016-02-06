//vertex shader
//Erstellt: 03.02.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform vec3 vTrans;
uniform vec3 vScale;
uniform float rotZ;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
out float lightIntensity;

const vec3 lightSource = vec3(10.0, 10.0, 10.0);

void main()
{
	vec4 vertexPosition;
	vec4 normalPosition;
	vec4 lightPosition;
	mat4 mModel;

	mat4 mTrans = mat4(1.0);
	mat4 mScale = mat4(1.0);
	mat4 mRot = mat4(1.0);

	mTrans[3].xyz = vTrans;

	mScale[0].x = vScale.x;
	mScale[1].y = vScale.y;
	mScale[2].z = vScale.z;

	mRot[0].x=cos(rotZ);
	mRot[1].x=-sin(rotZ);
	mRot[0].y=sin(rotZ);
	mRot[1].y=cos(rotZ);

	mModel = mTrans * mRot * mScale;
	vertexPosition = mView * mModel * vec4(vertex, 1.0);
	normalPosition = transpose(inverse(mView*mModel)) * vec4(normal, 1.0);

	lightPosition = mView * vec4(lightSource, 1.0);
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	lightIntensity = max(dot(s,normalize(normalPosition.xyz)), 0.0);
		
	gl_Position = mProj * vertexPosition;
}

