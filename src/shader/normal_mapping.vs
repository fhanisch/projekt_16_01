//vertex shader
//Erstellt: 14.02.2016

#version 440

uniform mat4 mProj;
uniform mat4 mView;
uniform mat4 mModel;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 lightDir;
out vec3 viewDir;
out vec2 textureCoords;

const vec3 lightSource = vec3(100.0, 100.0, 100.0);

void main()
{			
	vec4 tangent = vec4(-1.0, 0.0, 0.0, 1.0);

	vec4 vertexPosition = mView * mModel * vec4(vertex, 1.0);
	vec4 normalPosition = normalize(transpose(inverse(mView*mModel)) * vec4(normal, 1.0));
	vec4 lightPosition = mView * vec4(lightSource, 1.0);
	vec4 tangentPosition = normalize(transpose(inverse(mView*mModel)) * tangent);	
	vec3 biNormalPosition = normalize(cross(normalPosition.xyz, tangentPosition.xyz))*1.0;

	mat3 toObjLocal =  transpose(mat3(tangentPosition.x, biNormalPosition.x, normalPosition.x,
				tangentPosition.y, biNormalPosition.y, normalPosition.y,
				tangentPosition.z, biNormalPosition.z, normalPosition.z));
	
	lightDir = toObjLocal*(lightPosition.xyz - vertexPosition.xyz);
	viewDir = toObjLocal*vertexPosition.xyz;

	textureCoords = texCoords;	
	gl_Position = mProj * vertexPosition;
}

