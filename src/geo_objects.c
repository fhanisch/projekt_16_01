//geo_objects.c
//Erstellt: 31.01.2016

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include "renderobject.h"
#include "geo_objects.h"

void initLines(RenderObject *lines)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";
	GLfloat vertices[] = {	 0.0f,-1.0f, 0.0f,
			 	-1.0f, 0.0f, 0.0f,
			 	 0.0f, 1.0f, 0.0f,
				 1.0f, 0.0f, 0.0f};
	GLuint indices[] = {0,2,1,3};
	
	lines->vertex_shader_filename = vertex_shader_filename;	
	lines->fragment_shader_filename = fragment_shader_filename;
	lines->normals = NULL;
	lines->u = NULL;
	lines->vertices = vertices;
	lines->verticesSize = sizeof(vertices);
	lines->indices = indices;
	lines->indicesLen = 4;
	lines->indicesSize = sizeof(indices);
	lines->mProj = identity();
	lines->color = getColor(1.0f, 0.0f, 0.0f, 1.0f);
	lines->vPos = vec3(0.0f, 0.0f, 0.0f);
	lines->vScale = vec3(1.0f, 1.0f, 1.0f);
	lines->rotZ = 0.0f;
	lines->renderMode = GL_LINES;
	initObj(lines);
}

void initTriangle(RenderObject *triangle)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";
	GLfloat vertices[] = {	-1.0f,-1.0f, 0.0f,
			 	 1.0f,-1.0f, 0.0f,
			 	 0.0f, 1.0f, 0.0f};
	GLuint indices[] = {0,1,2};
	
	triangle->vertex_shader_filename = vertex_shader_filename;	
	triangle->fragment_shader_filename = fragment_shader_filename;
	triangle->normals = NULL;
	triangle->u = NULL;
	triangle->vertices = vertices;
	triangle->verticesSize = sizeof(vertices);
	triangle->indices = indices;
	triangle->indicesLen = 3;
	triangle->indicesSize = sizeof(indices);
	triangle->mProj = identity();
	triangle->color = getColor(1.0f, 0.0f, 1.0f, 1.0f);
	triangle->vPos = vec3(-0.5f, 0.5f, 0.0f);
	triangle->vScale = vec3(0.25f, 0.25f, 0.25f);
	triangle->rotZ = 0.0f;
	triangle->renderMode = GL_TRIANGLES;
	initObj(triangle);
}

void initRectangle(RenderObject *rect)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";
	GLfloat vertices[] = {	-1.0f,-1.0f, 0.0f,
			 	 1.0f,-1.0f, 0.0f,
			 	-1.0f, 1.0f, 0.0f,
				 1.0f, 1.0f, 0.0f};
	GLuint indices[] = {0,1,2,3};
	
	rect->vertex_shader_filename = vertex_shader_filename;	
	rect->fragment_shader_filename = fragment_shader_filename;
	rect->normals = NULL;
	rect->u = NULL;
	rect->vertices = vertices;
	rect->verticesSize = sizeof(vertices);
	rect->indices = indices;
	rect->indicesLen = 4;
	rect->indicesSize = sizeof(indices);
	rect->mProj = identity();
	rect->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);
	rect->vPos = vec3(0.5f, -0.5f, 0.0f);
	rect->vScale = vec3(0.25f, 0.25f, 0.25f);
	rect->rotZ = 0.0f;
	rect->renderMode = GL_TRIANGLE_STRIP;
	initObj(rect);
}

void initCircle(RenderObject *circle)
{			
	GLchar vertex_shader_filename[] = "src/shader/circle.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";
	
	circle->vertex_shader_filename = vertex_shader_filename;	
	circle->fragment_shader_filename = fragment_shader_filename;
	circle->verticesSize=0;
	circle->vertices = NULL;
	circle->normals = NULL;
	circle->u = vecf(0.0f, 1.0f, 100);
	circle->uSize = 100*sizeof(GLfloat);
	circle->indices = veci(0,100);
	circle->indicesLen = 100;
	circle->indicesSize = 100*sizeof(GLuint);
	circle->mProj = identity();
	circle->color = getColor(1.0f, 1.0f, 0.0f, 1.0f);
	circle->vPos = vec3(-0.5f, -0.5f, 0.0f);
	circle->vScale = vec3(0.25f, 0.25f, 0.25f);
	circle->rotZ = 0.0f;
	circle->renderMode = GL_POLYGON;
	initObj(circle);
}

void initStern(RenderObject *stern)
{			
	GLchar vertex_shader_filename[] = "src/shader/generic.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";

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
	stern->normals = NULL;
	stern->u = NULL;
	stern->vertices = vertices;
	stern->verticesSize = sizeof(vertices);
	stern->indices = indices;
	stern->indicesLen = 18;
	stern->indicesSize = sizeof(indices);
	stern->mProj = identity();
	stern->color = getColor(0.0f, 0.0f, 1.0f, 1.0f);
	stern->vPos = vec3(0.5f, 0.5f, 0.0f);
	stern->vScale = vec3(0.35f, 0.35f, 0.35f);
	stern->rotZ = 0.0f;
	stern->renderMode = GL_TRIANGLES;
	initObj(stern);
}

void initPlane(RenderObject *plane)
{
	GLchar vertex_shader_filename[] = "src/shader/diffuse_per_vertex.vs";
	GLchar fragment_shader_filename[] = "src/shader/diffuse_per_vertex.fs";
	GLfloat vertices[] = {	-1.0f, 0.0f, -1.0f,
			 	 1.0f, 0.0f, -1.0f,
			 	-1.0f, 0.0f,  1.0f,
				 1.0f, 0.0f,  1.0f};

	GLfloat normals[] = {	 0.0f, 1.0f,  0.0f,
			 	 0.0f, 1.0f,  0.0f,
			 	 0.0f, 1.0f,  0.0f,
				 0.0f, 1.0f,  0.0f};
	GLuint indices[] = {0,1,2,3};
	
	plane->vertex_shader_filename = vertex_shader_filename;	
	plane->fragment_shader_filename = fragment_shader_filename;
	plane->u = NULL;
	plane->vertices = vertices;
	plane->verticesSize = sizeof(vertices);
	plane->normals = normals;
	plane->normalsSize = sizeof(normals);
	plane->indices = indices;
	plane->indicesLen = 4;
	plane->indicesSize = sizeof(indices);
	plane->mProj = setFrustum(0.25,0.25,0.5,100.0);
	plane->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);
	plane->vPos = vec3(0.0f, -1.0f, -5.0f);
	plane->vScale = vec3(1.0f, 1.0f, 1.0f);
	plane->rotZ = 0.0f;
	plane->renderMode = GL_TRIANGLE_STRIP;
	initObj(plane);
}

void initCube(RenderObject *cube)
{
	GLchar vertex_shader_filename[] = "src/shader/diffuse_per_vertex.vs";
	GLchar fragment_shader_filename[] = "src/shader/diffuse_per_vertex.fs";
	GLfloat vertices[] = {	-1.0f, -1.0f, -1.0f,
			 	 1.0f, -1.0f, -1.0f,
			 	-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
			 	 1.0f,  1.0f, -1.0f,
			 	-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,

				-1.0f, -1.0f,  1.0f,
			 	 1.0f, -1.0f,  1.0f,
			 	-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,

				-1.0f, -1.0f, -1.0f,
			 	 1.0f, -1.0f, -1.0f,
			 	-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,

				 1.0f, -1.0f, -1.0f,
			 	 1.0f, -1.0f,  1.0f,
			 	 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,

				-1.0f, -1.0f, -1.0f,
			 	-1.0f, -1.0f,  1.0f,
			 	-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f};

	GLfloat normals[] = {	 0.0f, -1.0f,  0.0f,
			 	 0.0f, -1.0f,  0.0f,
			 	 0.0f, -1.0f,  0.0f,
				 0.0f, -1.0f,  0.0f,

				 0.0f,  1.0f,  0.0f,
			 	 0.0f,  1.0f,  0.0f,
			 	 0.0f,  1.0f,  0.0f,
				 0.0f,  1.0f,  0.0f,

				 0.0f,  0.0f,  1.0f,
			 	 0.0f,  0.0f,  1.0f,
			 	 0.0f,  0.0f,  1.0f,
				 0.0f,  0.0f,  1.0f,

				 0.0f,  0.0f, -1.0f,
			 	 0.0f,  0.0f, -1.0f,
			 	 0.0f,  0.0f, -1.0f,
				 0.0f,  0.0f, -1.0f,

				 1.0f,  0.0f,  0.0f,
			 	 1.0f,  0.0f,  0.0f,
			 	 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,

				-1.0f,  0.0f,  0.0f,
			 	-1.0f,  0.0f,  0.0f,
			 	-1.0f,  0.0f,  0.0f,
				-1.0f,  0.0f,  0.0f};

	GLuint indices[] = {0,1,3,2, 4,5,7,6, 8,9,11,10, 12,13,15,14, 16,17,19,18, 20,21,23,22};
	
	cube->vertex_shader_filename = vertex_shader_filename;	
	cube->fragment_shader_filename = fragment_shader_filename;
	cube->u = NULL;
	cube->vertices = vertices;
	cube->verticesSize = sizeof(vertices);
	cube->normals = normals;
	cube->normalsSize = sizeof(normals);
	cube->indices = indices;
	cube->indicesLen = 24;
	cube->indicesSize = sizeof(indices);
	cube->mProj = setFrustum(0.25,0.25,0.5,100.0);
	cube->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);
	cube->vPos = vec3(-2.0f, -2.0f, -8.0f);
	cube->vScale = vec3(1.0f, 1.0f, 1.0f);
	cube->rotZ = 0.0f;
	cube->renderMode = GL_QUADS;
	initObj(cube);
}

