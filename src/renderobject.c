//renderobject.c
//Erstellt: 30.01.2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>
//#include <GL/glu.h>
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

Matrix4 identity()
{
	Matrix4 I;
	memset(&I,0,sizeof(Matrix4));
	I.m11 = 1.0f;
	I.m22 = 1.0f;
	I.m33 = 1.0f;
	I.m44 = 1.0f;
	printf("Size of Matrix4: %ld\n", sizeof(Matrix4));

	return I;
}

Matrix4 setFrustum(float r, float t, float n, float f)
{
	Matrix4 F;
	memset(&F,0,sizeof(Matrix4));

	F.m11=n/r;	F.m12=0;	F.m13=0;		F.m14=0;
	F.m21=0;	F.m22=n/t;	F.m23=0;		F.m24=0;
	F.m31=0;	F.m32=0;	F.m33=-(f+n)/(f-n);	F.m34=-2*f*n/(f-n);
	F.m41=0;	F.m42=0;	F.m43=-1;		F.m44=0;

	return F;
}

void setPixel(GLubyte *tex, int xSize, int x, int y)
{
	GLubyte value = 255;
	uint pixelPtr;

	pixelPtr = (y*xSize+x)*4;
	tex[pixelPtr] = 0;
	tex[pixelPtr+1] = value;
	tex[pixelPtr+2] = 0;
}

void initObj(RenderObject *r)
{
	loadShader(&r->vertex_shader_text, r->vertex_shader_filename);
	loadShader(&r->fragment_shader_text, r->fragment_shader_filename);
	r->vertexShader = createShader(GL_VERTEX_SHADER, r->vertex_shader_text);
	printf("vertexShader %i\n",r->vertexShader);
	r->fragmentShader = createShader(GL_FRAGMENT_SHADER, r->fragment_shader_text);
	printf("fragmentShader %i\n",r->fragmentShader);
	r->shaderProgram = createShaderProgram(r->vertexShader, r->fragmentShader);
	printf("shaderProgram %i\n",r->shaderProgram);

	if (r->verticesSize!=0)	
	{
		createVBO(&r->vboID,r->verticesSize,r->vertices);
		printf("vboID: %i\n",r->vboID);
		printf("Size of Vertices: %d\n",r->verticesSize);
	}
	else
	{
		createVBO(&r->uID,r->uSize,r->u);
		printf("uID: %i\n",r->uID);
		printf("Size of u: %d\n",r->uSize);		
	}
	createIBO(&r->iboID, r->indicesSize, r->indices);
	printf("iboID: %i\n",r->iboID);
	printf("Size of Indices: %d\n",r->indicesSize);

	r->colorHandle = glGetUniformLocation(r->shaderProgram,"color");
	r->vTransHandle = glGetUniformLocation(r->shaderProgram,"vTrans");
	r->scaleHandle = glGetUniformLocation(r->shaderProgram,"vScale");
	r->rotZHandle = glGetUniformLocation(r->shaderProgram,"rotZ");
	
	if (r->verticesSize!=0)	
	{
		r->vertexHandle = glGetAttribLocation(r->shaderProgram,"vertex");
		printf("vertexHandle %i\n", r->vertexHandle);
	}
	else
	{
		r->uHandle = glGetAttribLocation(r->shaderProgram,"u");
		printf("uHandle %i\n", r->uHandle);
	}
}

void drawObj(RenderObject *r)
{
	glUseProgram(r->shaderProgram);

	glUniform4fv(r->colorHandle,1, (GLfloat*)&r->color);
	glUniform3fv(r->vTransHandle,1, (GLfloat*)&r->vPos);
	glUniform3fv(r->scaleHandle,1, (GLfloat*)&r->vScale);
	glUniform1f(r->rotZHandle, r->rotZ);	
	
	if (r->verticesSize!=0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->vboID);
		glEnableVertexAttribArray(r->vertexHandle);
		glVertexAttribPointer(r->vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->uID);
		glEnableVertexAttribArray(r->uHandle);
		glVertexAttribPointer(r->uHandle, 1, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->iboID);
	glDrawElements(r->renderMode, r->indicesLen, GL_UNSIGNED_INT, 0);
}

