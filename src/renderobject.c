//renderobject.c
//Erstellt: 30.01.2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
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
	*shaderStr = malloc(filesize+1);
	readElements = fread(*shaderStr,filesize,1,file);	
	(*shaderStr)[filesize]='\0';
	fclose(file);

	return 0;
}

int loadTexture (Texture *tex)
{
	char signature[2];
	unsigned short  farbtiefe;	
	uint offset;
	uint bytePtr=0;
	uint x,y;
		
	FILE *file = fopen (tex->texFileName,"r");
	fseek(file,0,SEEK_SET);
	fread(signature,2,1,file);
	printf("Bitmap Signature: %c%c\n", signature[0],signature[1]);
	fseek(file,28,SEEK_SET);
	fread(&farbtiefe,2,1,file);
	printf("Farbtiefe: %i\n", farbtiefe);
	fseek(file,18,SEEK_SET);
	fread(&tex->xTexSize,4,1,file);
	fread(&tex->yTexSize,4,1,file);
	printf("Texture size: %i x %i\n", tex->xTexSize, tex->yTexSize);
	tex->texture = malloc(tex->xTexSize*tex->yTexSize*4);
	fseek(file,10,SEEK_SET);
	fread(&offset,4,1,file);
	printf("Offset: %i\n",offset);
	fseek(file,offset,SEEK_SET);
	for (y=0;y<tex->yTexSize;y++)
	{
		for (x=0;x<tex->xTexSize;x++)
		{
			fread(tex->texture+bytePtr+2,1,1,file);
			fread(tex->texture+bytePtr+1,1,1,file);
			fread(tex->texture+bytePtr,1,1,file);
			tex->texture[bytePtr+3] = 0xff;
			bytePtr+=4;
		}
		fseek(file,tex->xTexSize%4,SEEK_CUR);
	}

	fclose(file);
	return 0;
}

void bindTexture(Texture *tex)
{	
	glGenTextures(1, &tex->texID);
	glBindTexture(GL_TEXTURE_2D,tex->texID);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex->xTexSize, tex->yTexSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->texture);
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

void genShaderPrograms()
{
	//Load Vertex Shader
	loadShader(&generic_vs_str, GENERIC_VS_FILENAME);
	loadShader(&circle_vs_str, CIRCLE_VS_FILENAME);
	loadShader(&ads_per_fragment_vs_str, ADS_PER_FRAGMENT_VS_FILENAME);
	loadShader(&sphere_ads_per_fragment_vs_str, SPHERE_ADS_PER_FRAGMENT_VS_FILENAME);
	loadShader(&apfel_vs_str, APFEL_VS_FILENAME);
	loadShader(&normal_mapping_vs_str, NORMAL_MAPPING_VS_FILENAME);

	//Load Fragment Shader
	loadShader(&generic_fs_str, GENERIC_FS_FILENAME);
	loadShader(&ads_per_fragment_fs_str, ADS_PER_FRAGMENT_FS_FILENAME);
	loadShader(&ads_per_fragment_plane_fs_str, ADS_PER_FRAGMENT_PLANE_FS_FILENAME);
	loadShader(&normal_mapping_fs_str, NORMAL_MAPPING_FS_FILENAME);

	//Create Vertex Shader
	generic_vs = createShader(GL_VERTEX_SHADER, generic_vs_str);
	circle_vs = createShader(GL_VERTEX_SHADER, circle_vs_str);
	ads_per_fragment_vs = createShader(GL_VERTEX_SHADER, ads_per_fragment_vs_str);
	sphere_ads_per_fragment_vs = createShader(GL_VERTEX_SHADER, sphere_ads_per_fragment_vs_str);
	apfel_vs = createShader(GL_VERTEX_SHADER, apfel_vs_str);
	normal_mapping_vs = createShader(GL_VERTEX_SHADER, normal_mapping_vs_str);

	//Create Fragment Shader
	generic_fs = createShader(GL_FRAGMENT_SHADER, generic_fs_str);
	ads_per_fragment_fs = createShader(GL_FRAGMENT_SHADER, ads_per_fragment_fs_str);
	ads_per_fragment_plane_fs = createShader(GL_FRAGMENT_SHADER, ads_per_fragment_plane_fs_str);
	normal_mapping_fs = createShader(GL_FRAGMENT_SHADER, normal_mapping_fs_str);

	//Create Shader Programs
	generic_sp = createShaderProgram(generic_vs, generic_fs);
	circle_sp = createShaderProgram(circle_vs, generic_fs);
	ads_per_fragment_sp = createShaderProgram(ads_per_fragment_vs, ads_per_fragment_fs);
	boden_sp = createShaderProgram(ads_per_fragment_vs, ads_per_fragment_plane_fs);
	sphere_sp = createShaderProgram(sphere_ads_per_fragment_vs, ads_per_fragment_fs);
	apfel_sp = createShaderProgram(apfel_vs, ads_per_fragment_fs);
	normal_mapping_sp = createShaderProgram(normal_mapping_vs, normal_mapping_fs);
}

void createVBO(GLenum bufferType, GLuint *bufferID, GLuint bufferSize, GLfloat *buffer)
{	
	glGenBuffers(1,bufferID);
	glBindBuffer(bufferType, *bufferID);
	glBufferData(bufferType, bufferSize, buffer, GL_STATIC_DRAW);
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

Vector3 cross(Vector3 v1, Vector3 v2)
{
	float *a=(float*)&v1;
	float *b=(float*)&v2;

	return vec3(a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
}

Matrix4 identity()
{
	Matrix4 I;
	memset(&I,0,sizeof(Matrix4));
	I.m11 = 1.0f;
	I.m22 = 1.0f;
	I.m33 = 1.0f;
	I.m44 = 1.0f;	

	return I;
}

Matrix4 scale(float x, float y, float z)
{
	Matrix4 S;
	S = identity();
	S.m11 = x;
	S.m22 = y;
	S.m33 = z;

	return S;
}

Matrix4 translate(float x, float y, float z)
{
	Matrix4 T;
	T = identity();
	T.m14 = x;
	T.m24 = y;
	T.m34 = z;

	return T;
}

Matrix4 rotateX(float phi)
{
	Matrix4 X;
	memset(&X,0,sizeof(Matrix4));
	X.m11 = 1.0f;
	X.m22 = cos(phi); X.m23 = sin(phi);	
	X.m32 = -sin(phi); X.m33 = cos(phi);
	X.m44 = 1.0f;

	return X;
}

Matrix4 rotateY(float phi)
{
	Matrix4 Y;
	memset(&Y,0,sizeof(Matrix4));
	Y.m11 = cos(phi); Y.m13 = sin(phi);
	Y.m22 = 1.0f;
	Y.m31 = -sin(phi); Y.m33 = cos(phi);
	Y.m44 = 1.0f;

	return Y;
}

Matrix4 rotateZ(float phi)
{
	Matrix4 Z;
	memset(&Z,0,sizeof(Matrix4));
	Z.m11 = cos(phi); Z.m12 = sin(phi);	
	Z.m21 = -sin(phi); Z.m22 = cos(phi);
	Z.m33 = 1.0f;
	Z.m44 = 1.0f;

	return Z;
}

Matrix4 matMult(Matrix4 L, Matrix4 R)
{
	Matrix4 M;
	float *m = (float*)&M;
	float *l = (float*)&L;
	float *r = (float*)&R;
	unsigned int i,j;
	
	for (j=0;j<4;j++)
		for (i=0;i<4;i++)
			m[4*j+i] = l[4*j]*r[i] + l[4*j+1]*r[i+4] + l[4*j+2]*r[i+8] + l[4*j+3]*r[i+12];

	return M;
}

Vector3 getXAxis(Matrix4 M)
{
	return vec3(M.m11, M.m21, M.m31);
}

Vector3 getYAxis(Matrix4 M)
{
	return vec3(M.m12, M.m22, M.m32);
}

Vector3 getZAxis(Matrix4 M)
{
	return vec3(M.m13, M.m23, M.m33);
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

void setPixel(GLubyte *tex, int xSize, int x, int y, Color c)
{
	GLubyte value = 255;
	unsigned int pixelPtr;

	pixelPtr = (y*xSize+x)*4;
	tex[pixelPtr] = 0;
	tex[pixelPtr+1] = value;
	tex[pixelPtr+2] = 0;
}

void createMeshGrid(float **u, float **v, unsigned int *uSize, unsigned int *vSize, int m, int n)
{	
	unsigned int i,j;

	*uSize = m*n*sizeof(float);
	*vSize = m*n*sizeof(float);
	printf("uSize: %d\n",*uSize);
	printf("vSize: %d\n",*vSize);
	*u = malloc(*uSize);
	*v = malloc(*vSize);

	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			(*u)[i*n+j]=(float)j/((float)n-1);
			(*v)[j*m+i]=(float)j/((float)m-1);
		}	
}

void createMeshGridIndices(uint **indices, uint *indicesLen, uint *indicesSize, int m, int n)
{
	uint i,j;

	*indicesLen=3*2*(m-1)*(n-1);
	*indicesSize = *indicesLen * sizeof(uint);
	*indices = malloc(*indicesSize);

	for(i=0;i<m-1;i++)
		for(j=0;j<n-1;j++)
		{
			(*indices)[6*(i*(n-1)+j)+0]=i*n+j;
			(*indices)[6*(i*(n-1)+j)+1]=i*n+j+1;
			(*indices)[6*(i*(n-1)+j)+2]=(i+1)*n+j;

			(*indices)[6*(i*(n-1)+j)+3]=i*n+j+1;
			(*indices)[6*(i*(n-1)+j)+4]=(i+1)*n+j;
			(*indices)[6*(i*(n-1)+j)+5]=(i+1)*n+j+1;
		}
}

void genMeshGridObject(MeshGridObject *meshGridObj)
{
	createMeshGrid(&meshGridObj->u, &meshGridObj->v, &meshGridObj->uSize, &meshGridObj->vSize, 100, 100);
	createMeshGridIndices(&meshGridObj->indices, &meshGridObj->indicesLen, &meshGridObj->indicesSize, 100, 100);
	createVBO(GL_ARRAY_BUFFER, &meshGridObj->uID,meshGridObj->uSize,meshGridObj->u);
	printf("uID: %i\n",meshGridObj->uID);	
	createVBO(GL_ARRAY_BUFFER, &meshGridObj->vID,meshGridObj->vSize,meshGridObj->v);
	printf("vID: %i\n",meshGridObj->vID);	
	createVBO(GL_ELEMENT_ARRAY_BUFFER, &meshGridObj->iboID, meshGridObj->indicesSize, (GLfloat*)meshGridObj->indices);
	printf("iboID: %i\n",meshGridObj->iboID);	
}

void initObj(RenderObject *r)
{	
	if (r->vertices!=NULL)	
	{
		createVBO(GL_ARRAY_BUFFER, &r->vboID,r->verticesSize,r->vertices);
		printf("vboID: %i\n",r->vboID);
		printf("Size of Vertices: %d\n",r->verticesSize);
	}

	if (r->u!=NULL)
	{
		createVBO(GL_ARRAY_BUFFER, &r->uID,r->uSize,r->u);
		printf("uID: %i\n",r->uID);
		printf("Size of u: %d\n",r->uSize);		
	}

	if (r->v!=NULL)
	{
		createVBO(GL_ARRAY_BUFFER, &r->vID,r->vSize,r->v);
		printf("vID: %i\n",r->vID);
		printf("Size of v: %d\n",r->vSize);		
	}

	if (r->normals!=NULL)
	{
		createVBO(GL_ARRAY_BUFFER, &r->nboID, r->normalsSize, r->normals);
		printf("nboID: %i\n",r->nboID);
		printf("Size of normals: %d\n",r->normalsSize);
	}

	if (r->texCoords!=NULL)
	{
		createVBO(GL_ARRAY_BUFFER, &r->tcoID, r->texCoordsSize, r->texCoords);
		printf("tcoID: %i\n",r->tcoID);
		printf("Size of texCoords: %d\n",r->texCoordsSize);
	}

	if (r->indices!=NULL)
	{
		createVBO(GL_ELEMENT_ARRAY_BUFFER, &r->iboID, r->indicesSize, (GLfloat*)r->indices);
		printf("iboID: %i\n",r->iboID);
		printf("Size of Indices: %d\n",r->indicesSize);
	}

	r->mProjHandle = glGetUniformLocation(r->shaderProgram,"mProj");
	r->mViewHandle = glGetUniformLocation(r->shaderProgram,"mView");
	r->mModelHandle = glGetUniformLocation(r->shaderProgram,"mModel");
	r->colorHandle = glGetUniformLocation(r->shaderProgram,"color");
	r->samplerHandle[0] = glGetUniformLocation(r->shaderProgram,"samp");
	r->samplerHandle[1] = glGetUniformLocation(r->shaderProgram,"samp2");
}

void drawObj(RenderObject *r)
{
	glUseProgram(r->shaderProgram);

	glUniformMatrix4fv(r->mProjHandle,1, GL_TRUE, (GLfloat*)&r->mProj);
	glUniformMatrix4fv(r->mViewHandle,1, GL_TRUE, (GLfloat*)&camera);
	glUniformMatrix4fv(r->mModelHandle,1, GL_TRUE, (GLfloat*)&r->mModel);
	glUniform4fv(r->colorHandle,1, (GLfloat*)&r->color);

	if (r->samplerHandle[0]>=0) glUniform1i(r->samplerHandle[0],0);
	if (r->samplerHandle[1]>=0) glUniform1i(r->samplerHandle[1],1);
			
	if (r->vboID)
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	if (r->uID)
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->uID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (r->vID)
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->vID);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (r->tcoID)
	{
		glBindBuffer(GL_ARRAY_BUFFER, r->tcoID);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (r->nboID)
	{		
		glBindBuffer(GL_ARRAY_BUFFER, r->nboID);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (r->texID[0]) glBindTexture(GL_TEXTURE_2D,r->texID[0]);
	if (r->texID[1]) glBindTexture(GL_TEXTURE_2D,r->texID[1]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->iboID);	
	glDrawElements(r->renderMode, r->indicesLen, GL_UNSIGNED_INT, 0);
}

