//geo_objects.c
//Erstellt: 31.01.2016

#include <stdio.h>
#include <stdlib.h>
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
	lines->v = NULL;
	lines->vertices = vertices;
	lines->verticesSize = sizeof(vertices);
	lines->indices = indices;
	lines->indicesLen = 4;
	lines->indicesSize = sizeof(indices);
	lines->mProj = identity();
	lines->mModel = scale(1.0f, 1.0f, 1.0f);
	lines->color = getColor(1.0f, 0.0f, 0.0f, 1.0f);			
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
	triangle->v = NULL;
	triangle->vertices = vertices;
	triangle->verticesSize = sizeof(vertices);
	triangle->indices = indices;
	triangle->indicesLen = 3;
	triangle->indicesSize = sizeof(indices);
	triangle->mProj = identity();
	triangle->mProj.m11 = (GLfloat)WND_HEIGHT/(GLfloat)WND_WIDTH;
	triangle->mModel = scale(0.25f, 0.25f, 0.25f);
	triangle->mModel = matMult(translate(-0.5f, 0.5f, 0.0f), triangle->mModel);
	triangle->color = getColor(1.0f, 0.0f, 1.0f, 1.0f);			
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
	rect->v = NULL;
	rect->vertices = vertices;
	rect->verticesSize = sizeof(vertices);
	rect->indices = indices;
	rect->indicesLen = 4;
	rect->indicesSize = sizeof(indices);
	rect->mProj = identity();
	rect->mProj.m11 = (GLfloat)WND_HEIGHT/(GLfloat)WND_WIDTH;
	rect->mModel = scale(0.25f, 0.25f, 0.25f);
	rect->mModel = matMult(translate(0.5f, -0.5f, 0.0f), rect->mModel);
	rect->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);	
	rect->renderMode = GL_TRIANGLE_STRIP;
	initObj(rect);
}

void initCircle(RenderObject *circle)
{			
	GLchar vertex_shader_filename[] = "src/shader/circle.vs";
	GLchar fragment_shader_filename[] = "src/shader/generic.fs";
	
	circle->vertex_shader_filename = vertex_shader_filename;	
	circle->fragment_shader_filename = fragment_shader_filename;	
	circle->vertices = NULL;
	circle->normals = NULL;
	circle->v = NULL;
	circle->u = vecf(0.0f, 1.0f, 100);
	circle->uSize = 100*sizeof(GLfloat);
	circle->indices = veci(0,100);
	circle->indicesLen = 100;
	circle->indicesSize = 100*sizeof(GLuint);
	circle->mProj = identity();
	circle->mProj.m11 = (GLfloat)WND_HEIGHT/(GLfloat)WND_WIDTH;
	circle->mModel = scale(0.25f, 0.25f, 0.25f);
	circle->mModel = matMult(translate(-0.5f, -0.5f, 0.0f), circle->mModel);
	circle->color = getColor(1.0f, 1.0f, 0.0f, 1.0f);	
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
	stern->v = NULL;
	stern->vertices = vertices;
	stern->verticesSize = sizeof(vertices);
	stern->indices = indices;
	stern->indicesLen = 18;
	stern->indicesSize = sizeof(indices);
	stern->mProj = identity();
	stern->mProj.m11 = (GLfloat)WND_HEIGHT/(GLfloat)WND_WIDTH;
	stern->mProj.m33 = -1.0;
	stern->mModel = scale(0.35f, 0.35f, 0.35f);
	stern->mModel = matMult(translate(0.5f, 0.5f, 0.1f), stern->mModel);
	stern->color = getColor(0.0f, 0.0f, 1.0f, 1.0f);	
	stern->renderMode = GL_TRIANGLES;
	initObj(stern);
}

void initPlane(RenderObject *plane)
{
	GLchar vertex_shader_filename[] = "src/shader/ads_per_fragment.vs";
	GLchar fragment_shader_filename[] = "src/shader/ads_per_fragment.fs";
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
	plane->v = NULL;
	plane->vertices = vertices;
	plane->verticesSize = sizeof(vertices);
	plane->normals = normals;
	plane->normalsSize = sizeof(normals);
	plane->indices = indices;
	plane->indicesLen = 4;
	plane->indicesSize = sizeof(indices);
	plane->mProj = setFrustum(0.25*(GLfloat)WND_WIDTH/(GLfloat)WND_HEIGHT,0.25,0.5,100.0);
	plane->mModel = scale(20.0f, 20.0f, 20.0f);
	plane->mModel = matMult(translate(0.0f, 0.0f, 0.0f), plane->mModel);
	plane->color = getColor(1.0f, 1.0f, 1.0f, 1.0f);	
	plane->renderMode = GL_TRIANGLE_STRIP;
	initObj(plane);
}

void initCube(RenderObject *cube)
{
	GLchar vertex_shader_filename[] = "src/shader/ads_per_fragment.vs";
	GLchar fragment_shader_filename[] = "src/shader/ads_per_fragment.fs";
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
	cube->v = NULL;
	cube->vertices = vertices;
	cube->verticesSize = sizeof(vertices);
	cube->normals = normals;
	cube->normalsSize = sizeof(normals);
	cube->indices = indices;
	cube->indicesLen = 24;
	cube->indicesSize = sizeof(indices);
	cube->mProj = setFrustum(0.25*(GLfloat)WND_WIDTH/(GLfloat)WND_HEIGHT,0.25,0.5,100.0);
	cube->mModel = scale(1.0f, 1.0f, 1.0f);
	cube->mModel = matMult(translate(0.0f, 0.0f, 0.0f), cube->mModel);
	cube->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);	
	cube->renderMode = GL_QUADS;
	initObj(cube);
}

void initSphere(RenderObject *sphere)
{
	GLchar vertex_shader_filename[] = "src/shader/sphere_ads_per_fragment.vs";
	GLchar fragment_shader_filename[] = "src/shader/ads_per_fragment.fs";
	
	sphere->vertex_shader_filename = vertex_shader_filename;	
	sphere->fragment_shader_filename = fragment_shader_filename;	
	sphere->vertices = NULL;
	sphere->normals = NULL;
	createMeshGrid(&sphere->u, &sphere->v, &sphere->uSize, &sphere->vSize, 100, 100);
	createMeshGridIndices(&sphere->indices, &sphere->indicesLen, &sphere->indicesSize, 100, 100);
	sphere->mProj = setFrustum(0.25*(GLfloat)WND_WIDTH/(GLfloat)WND_HEIGHT,0.25,0.5,100.0);
	sphere->mModel = scale(1.0f, 1.0f, 1.0f);
	sphere->mModel = matMult(translate(0.0f, 0.0f, 0.0f), sphere->mModel);
	sphere->color = getColor(1.0f, 0.0f, 0.0f, 1.0f);	
	sphere->renderMode = GL_TRIANGLES;
	initObj(sphere);
	free(sphere->u);
	free(sphere->v);
	free(sphere->indices);
}

void initApfel(RenderObject *apfel)
{
	GLchar vertex_shader_filename[] = "src/shader/apfel.vs";
	GLchar fragment_shader_filename[] = "src/shader/ads_per_fragment.fs";
	
	apfel->vertex_shader_filename = vertex_shader_filename;	
	apfel->fragment_shader_filename = fragment_shader_filename;	
	apfel->vertices = NULL;
	apfel->normals = NULL;
	createMeshGrid(&apfel->u, &apfel->v, &apfel->uSize, &apfel->vSize, 100, 100);
	createMeshGridIndices(&apfel->indices, &apfel->indicesLen, &apfel->indicesSize, 100, 100);
	apfel->mProj = setFrustum(0.25*(GLfloat)WND_WIDTH/(GLfloat)WND_HEIGHT,0.25,0.5,100.0);
	apfel->mModel = scale(1.0f, 1.0f, 1.0f);
	apfel->mModel = matMult(translate(0.0f, 0.0f, 0.0f), apfel->mModel);
	apfel->color = getColor(0.0f, 1.0f, 0.0f, 1.0f);	
	apfel->renderMode = GL_TRIANGLES;
	initObj(apfel);
	free(apfel->u);
	free(apfel->v);
	free(apfel->indices);
}

