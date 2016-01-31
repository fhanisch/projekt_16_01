//geo_objects.c
//Erstellt: 31.01.2016

#include <stdio.h>
//#include <string.h>
#include "ogl.h"
#include "renderobject.h"
#include "geo_objects.h"

void init(RenderObject *r)
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

void initLines(RenderObject *lines)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vert";
	GLchar fragment_shader_filename[] = "src/shader/generic.frag";
	GLfloat vertices[] = {	 0.0f,-1.0f, 0.0f,
			 	-1.0f, 0.0f, 0.0f,
			 	 0.0f, 1.0f, 0.0f,
				 1.0f, 0.0f, 0.0f};
	GLuint indices[] = {0,2,1,3};
	
	lines->vertex_shader_filename = vertex_shader_filename;	
	lines->fragment_shader_filename = fragment_shader_filename;
	lines->vertices = vertices;
	lines->verticesSize = sizeof(vertices);
	lines->indices = indices;
	lines->indicesLen = 4;
	lines->indicesSize = sizeof(indices);
	lines->color = getColor(1.0f, 0.0f, 0.0f, 1.0f);
	lines->vPos = vec3(-0.0f, 0.0f, 0.0f);
	lines->vScale = vec3(1.0f, 1.0f, 1.0f);
	lines->rotZ = 0.0f;
	lines->renderMode = GL_LINES;
	init(lines);
}

void initTriangle(RenderObject *triangle)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vert";
	GLchar fragment_shader_filename[] = "src/shader/generic.frag";
	GLfloat vertices[] = {	-1.0f,-1.0f, 0.0f,
			 	 1.0f,-1.0f, 0.0f,
			 	 0.0f, 1.0f, 0.0f};
	GLuint indices[] = {0,1,2};
	
	triangle->vertex_shader_filename = vertex_shader_filename;	
	triangle->fragment_shader_filename = fragment_shader_filename;
	triangle->vertices = vertices;
	triangle->verticesSize = sizeof(vertices);
	triangle->indices = indices;
	triangle->indicesLen = 3;
	triangle->indicesSize = sizeof(indices);
	triangle->color = getColor(1.0f, 0.0f, 1.0f, 1.0f);
	triangle->vPos = vec3(-0.5f, 0.5f, 0.0f);
	triangle->vScale = vec3(0.25f, 0.25f, 0.25f);
	triangle->rotZ = 0.0f;
	triangle->renderMode = GL_TRIANGLES;
	init(triangle);
}

void initRectangle(RenderObject *rect)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vert";
	GLchar fragment_shader_filename[] = "src/shader/generic.frag";
	GLfloat vertices[] = {	-1.0f,-1.0f, 0.0f,
			 	 1.0f,-1.0f, 0.0f,
			 	-1.0f, 1.0f, 0.0f,
				 1.0f, 1.0f, 0.0f};
	GLuint indices[] = {0,1,2,3};
	
	rect->vertex_shader_filename = vertex_shader_filename;	
	rect->fragment_shader_filename = fragment_shader_filename;
	rect->vertices = vertices;
	rect->verticesSize = sizeof(vertices);
	rect->indices = indices;
	rect->indicesLen = 4;
	rect->indicesSize = sizeof(indices);
	rect->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);
	rect->vPos = vec3(0.5f, -0.5f, 0.0f);
	rect->vScale = vec3(0.25f, 0.25f, 0.25f);
	rect->rotZ = 0.0f;
	rect->renderMode = GL_TRIANGLE_STRIP;
	init(rect);
}

void initCircle(RenderObject *circle)
{			
	GLchar vertex_shader_filename[] = "src/shader/circle.vert";
	GLchar fragment_shader_filename[] = "src/shader/generic.frag";
	
	circle->vertex_shader_filename = vertex_shader_filename;	
	circle->fragment_shader_filename = fragment_shader_filename;
	circle->verticesSize=0;
	circle->u = vecf(0.0f, 1.0f, 100);
	circle->uSize = 100*sizeof(GLfloat);
	circle->indices = veci(0,100);
	circle->indicesLen = 100;
	circle->indicesSize = 100*sizeof(GLuint);
	circle->color = getColor(1.0f, 1.0f, 0.0f, 1.0f);
	circle->vPos = vec3(-0.5f, -0.5f, 0.0f);
	circle->vScale = vec3(0.25f, 0.25f, 0.25f);
	circle->rotZ = 0.0f;
	circle->renderMode = GL_POLYGON;
	init(circle);
}

void initStern(RenderObject *stern)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vert";
	GLchar fragment_shader_filename[] = "src/shader/generic.frag";

	GLfloat vertices[] = {	   0.0f,  -1.0f, 0.0f,
			 	  0.25f, -0.25f, 0.0f,
			 	   1.0f,   0.0f, 0.0f,
				  0.25f,  0.25f, 0.0f,
				   0.0f,   1.0f, 0.0f,
				 -0.25f,  0.25f, 0.0f,
				  -1.0f,   0.0f, 0.0f,
				 -0.25f, -0.25f, 0.0f};

	GLuint indices[] = {0,1,7, 1,2,3, 3,4,5, 5,6,7, 1,3,5, 5,7,1};
	
	stern->vertex_shader_filename = vertex_shader_filename;	
	stern->fragment_shader_filename = fragment_shader_filename;
	stern->vertices = vertices;
	stern->verticesSize = sizeof(vertices);
	stern->indices = indices;
	stern->indicesLen = 18;
	stern->indicesSize = sizeof(indices);
	stern->color = getColor(0.0f, 0.0f, 1.0f, 1.0f);
	stern->vPos = vec3(0.5f, 0.5f, 0.0f);
	stern->vScale = vec3(0.35f, 0.35f, 0.35f);
	stern->rotZ = 0.0f;
	stern->renderMode = GL_TRIANGLES;
	init(stern);
}

