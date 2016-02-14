//renderobject.h
//Erstellt: 30.01.2016

//Vertex Shader
#define	GENERIC_VS_FILENAME			"src/shader/generic.vs"
#define CIRCLE_VS_FILENAME			"src/shader/circle.vs"
#define DIFFUSE_PER_VERTEX_VS_FILENAME		"src/shader/diffuse_per_vertex.vs"
#define ADS_PER_FRAGMENT_VS_FILENAME		"src/shader/ads_per_fragment.vs"
#define SPHERE_ADS_PER_FRAGMENT_VS_FILENAME	"src/shader/sphere_ads_per_fragment.vs"
#define APFEL_VS_FILENAME			"src/shader/apfel.vs"
#define NORMAL_MAPPING_VS_FILENAME		"src/shader/normal_mapping.vs"

//Fragment Shader
#define	GENERIC_FS_FILENAME			"src/shader/generic.fs"
#define ADS_PER_FRAGMENT_FS_FILENAME		"src/shader/ads_per_fragment.fs"
#define ADS_PER_FRAGMENT_PLANE_FS_FILENAME	"src/shader/ads_per_fragment_plane.fs"
#define NORMAL_MAPPING_FS_FILENAME		"src/shader/normal_mapping.fs"

typedef GLchar VertexShaderStr;
typedef GLchar FragmentShaderStr;
typedef GLuint VertexShader;
typedef GLuint FragmentShader;
typedef GLuint ShaderProgram;

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
	GLuint shaderProgram, vboID, nboID, iboID, uID, vID, tcoID, texID[2];
	GLint mProjHandle, mViewHandle, mModelHandle, colorHandle, samplerHandle[2];		
	GLfloat *vertices, *normals, *u, *v, *texCoords;
	GLuint verticesSize, normalsSize, uSize, vSize, texCoordsSize;
	GLuint *indices;
	GLuint indicesLen;
	GLuint indicesSize;
	Matrix4 mProj;
	Matrix4 mView;
	Matrix4 mModel;
	GLenum renderMode;
	Color color;	
} RenderObject;

VertexShaderStr		*generic_vs_str, *circle_vs_str, *ads_per_fragment_vs_str, *sphere_ads_per_fragment_vs_str, *apfel_vs_str, *normal_mapping_vs_str;
FragmentShaderStr	*generic_fs_str, *ads_per_fragment_fs_str, *ads_per_fragment_plane_fs_str, *normal_mapping_fs_str;
VertexShader		generic_vs, circle_vs, ads_per_fragment_vs, sphere_ads_per_fragment_vs, apfel_vs, normal_mapping_vs;
FragmentShader		generic_fs, ads_per_fragment_fs, ads_per_fragment_plane_fs, normal_mapping_fs;
ShaderProgram		generic_sp, ads_per_fragment_sp, circle_sp, boden_sp, sphere_sp, apfel_sp, normal_mapping_sp;
Matrix4 camera;

int loadShader(GLchar **shaderStr, char *fileName);
int loadTexture (Texture *tex);
void bindTexture(Texture *tex);
GLuint createShader(GLenum shaderType, const GLchar *shaderStr);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
void genShaderPrograms();
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
