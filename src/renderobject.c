//renderobject.c
//Erstellt: 30.01.2016

#include <stdlib.h>
#include <stdio.h>
#include "ogl.h"
#include "renderobject.h"

int loadShader(GLchar **shaderStr, char *fileName)
{
	uint filesize;
	uint readElements;
	FILE *file = fopen(fileName,"r");

	fseek(file,0,SEEK_END);
	filesize=ftell(file);
	rewind(file);
	printf("File Size: %i\n",filesize);
	*shaderStr = malloc(filesize+1);
	readElements = fread(*shaderStr,filesize,1,file);
	printf("Elements read: %i\n",readElements);
	(*shaderStr)[filesize]='\0';
	fclose(file);

	return 0;
}

GLuint createShader(GLenum shaderType, const GLchar *shaderStr)
{
	GLuint shader;

	shader = glCreateShader(shaderType);
	glShaderSource(shader,1,&shaderStr,NULL);
	glCompileShader(shader);		

	return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

void createVBO(GLuint *vboID, GLuint verticesSize, GLfloat *vertices)
{	
	glGenBuffers(1,vboID);
	glBindBuffer(GL_ARRAY_BUFFER, *vboID);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}

void createIBO(GLuint *iboID, GLuint indicesSize, GLuint *indices)
{	
	glGenBuffers(1,iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);	
}

Color getColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	Color c;
	c.r=r; c.g=g; c.b=b; c.a=a;
	return c;
}

Vector3 vec3(float x, float y, float z)
{
	Vector3 vOut={x,y,z};
	return vOut;
}

float *vecf(float start, float step, unsigned int count)
{
	unsigned int i;
	float *out = malloc(count*sizeof(float));
	
	for (i=0;i<count;i++) out[i] = start + i*step;

	return out;
}

unsigned int *veci(unsigned int start, unsigned int count)
{
	unsigned int i;
	unsigned int *out = malloc(count*sizeof(unsigned int));
	
	for (i=0;i<count;i++) out[i] = start + i;

	return out;
}
