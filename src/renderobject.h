//renderobject.h
//Erstellt: 30.01.2016

typedef struct
{
	float x,y,z;
} Vector3;

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
	GLuint vertexShader, fragmentShader, shaderProgram, vboID, iboID, uID, vertexHandle, uHandle;
	GLint colorHandle, vTransHandle, scaleHandle, rotZHandle;
	GLenum renderMode;
	GLchar *vertex_shader_filename, *fragment_shader_filename;
	GLchar *vertex_shader_text, *fragment_shader_text;
	GLfloat *vertices, *u;
	GLuint verticesSize, uSize;
	GLuint *indices;
	GLuint indicesLen;
	GLuint indicesSize;
	Color color;
	Vector3 vPos;
	Vector3 vScale;
	GLfloat rotZ;
} RenderObject;

int loadShader(GLchar **shaderStr, char *fileName);
GLuint createShader(GLenum shaderType, const GLchar *shaderStr);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
void createVBO(GLuint *vboID, GLuint verticesSize, GLfloat *vertices);
void createIBO(GLuint *iboID, GLuint indicesSize, GLuint *indices);
Color getColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
Vector3 vec3(float x, float y, float z);
float *vecf(float start, float step, unsigned int count);
unsigned int *veci(unsigned int start, unsigned int count);
void initObj(RenderObject *r);
void drawObj(RenderObject *r);
