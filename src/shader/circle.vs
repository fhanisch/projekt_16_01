//vertex shader
//Erstellt: 31.01.2016

#version 440

uniform mat4 mProj;
uniform vec3 vTrans;
uniform vec3 vScale;
uniform float rotZ;

layout (location = 0) in float u;

void main()
{
	float x,y;
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

	x = cos(u*2*3.14159/100.0);
	y = -sin(u*2*3.14159/100.0);

	gl_Position = mProj * mTrans * mRot * mScale * vec4(x, y, 0.0, 1.0);
}

