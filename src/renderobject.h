//renderobject.h
//Erstellt: 30.01.2016

typedef unsigned int uint;

typedef struct
{
	float x,y,z;
} Vector3;

typedef struct
{
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
} Matrix4;

typedef struct
{
	GLfloat x,y,z;
} Vertex;

typedef struct
{
	GLfloat x,y;
} TexCoords;

typedef struct
{
	GLfloat r,g,b,a;
} Color;

typedef struct
{
	GLuint iboID, uID, vID;
	GLfloat *u, *v;
	GLuint uSize, vSize;
	GLuint *indices, indicesLen, indicesSize;
} MeshGridObject;

typedef struct
{
	GLchar *texFileName;
	GLubyte *texture;
	GLuint texID;
	int xTexSize, yTexSize;
} Texture;

typedef struct
{
	GLuint vertexShader, fragmentShader, shaderProgram, vboID, nboID, iboID, uID, vID, tcoID, texID;
	GLint mProjHandle, mViewHandle, mModelHandle, colorHandle, samplerHandle;
	GLenum renderMode;
	GLchar *vertex_shader_filename, *fragment_shader_filename;
	GLchar *vertex_shader_text, *fragment_shader_text;
	GLfloat *vertices, *normals, *u, *v, *texCoords;
	GLuint verticesSize, normalsSize, uSize, vSize, texCoordsSize;
	GLuint *indices;
	GLuint indicesLen;
	GLuint indicesSize;
	Matrix4 mProj;
	Matrix4 mView;
	Matrix4 mModel;	
	Color color;	
} RenderObject;

Matrix4 camera;

int loadShader(GLchar **shaderStr, char *fileName);
int loadTexture (Texture *tex);
void bindTexture(Texture *tex);
GLuint createShader(GLenum shaderType, const GLchar *shaderStr);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
void createVBO(GLuint *vboID, GLuint verticesSize, GLfloat *vertices);
void createIBO(GLuint *iboID, GLuint indicesSize, GLuint *indices);
Color getColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
Vector3 vec3(float x, float y, float z);
float *vecf(float start, float step, unsigned int count);
unsigned int *veci(unsigned int start, unsigned int count);
Vector3 cross(Vector3 v1, Vector3 v2);
Matrix4 identity();
Matrix4 scale(float x, float y, float z);
Matrix4 translate(float x, float y, float z);
Matrix4 rotateX(float phi);
Matrix4 rotateY(float phi);
Matrix4 rotateZ(float phi);
Matrix4 matMult(Matrix4 L, Matrix4 R);
Vector3 getXAxis(Matrix4 M);
Vector3 getYAxis(Matrix4 M);
Vector3 getZAxis(Matrix4 M);
Matrix4 setFrustum(float r, float t, float n, float f);
void setPixel(GLubyte *tex, int xSize, int x, int y, Color c);
void createMeshGrid(float **u, float **v, unsigned int *uSize, unsigned int *vSize, int m, int n);
void createMeshGridIndices(uint **indices, uint *indicesLen, uint *indicesSize, int m, int n);
void genMeshGridObject(MeshGridObject *meshGridObj);
void initObj(RenderObject *r);
void drawObj(RenderObject *r);
