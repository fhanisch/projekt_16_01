//geo_objects.h
//Erstellt: 31.01.2016

#define WND_WIDTH 1920
#define WND_HEIGHT 1080

void initLines(RenderObject *Lines, ShaderProgram sp);
void initTriangle(RenderObject *triangle, ShaderProgram sp);
void initRectangle(RenderObject *rect, ShaderProgram sp);
void initCircle(RenderObject *rect, ShaderProgram sp);
void initStern(RenderObject *stern, ShaderProgram sp);
void initPlane(RenderObject *plane, ShaderProgram sp);
void initCube(RenderObject *cube, ShaderProgram sp);
void initSphere(RenderObject *sphere, ShaderProgram sp, MeshGridObject *mesh);
void initApfel(RenderObject *apfel, ShaderProgram sp, MeshGridObject *mesh);
