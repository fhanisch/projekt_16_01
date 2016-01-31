//vertex shader
//Erstellt: 30.01.2016

uniform vec3 vTrans;
uniform vec3 vScale;
uniform float rotZ;
in vec3 vertex;

void main()
{
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

	gl_Position = mTrans * mRot * mScale * vec4(vertex,1.0);
}

