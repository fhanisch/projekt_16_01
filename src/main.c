//main.c
//Erstellt: 30.01.2016

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include "renderobject.h"
#include "geo_objects.h"


SDL_Event event;

int initOpenGLWindow(char *wndName)
{	
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8 );
    	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	SDL_SetVideoMode(WND_WIDTH,WND_HEIGHT,32,SDL_OPENGL|SDL_FULLSCREEN);
	SDL_WM_SetCaption(wndName, NULL);

	return 0;
}

int main(int argc, char **argv)
{
	int quit = 0;
	unsigned int key[512];
	unsigned int F1=1;
	int mouseX = 0;
	int mouseY = 0;
	Vector3 rotAxis;
	const GLubyte *vendor, *renderer, *oglVersion, *glslVersion;
	RenderObject lines, triangle, rectangle, circle, stern, plane, cube, apfel, steine;
	RenderObject *sphere = malloc(4*sizeof(RenderObject));	
	MeshGridObject mesh;
	Texture texBoden, texFliessen, texSteine, texSteineNorm;

	printf("Programm: %s\n",argv[0]+2);
	memset(key,0,sizeof(key));
	
	if (initOpenGLWindow(argv[0]+2)!=0) return 1;
	if (glewInit()!=0) return 1;

	vendor		= glGetString(GL_VENDOR);
	renderer	= glGetString(GL_RENDERER);
	oglVersion	= glGetString(GL_VERSION);
	glslVersion	= glGetString(GL_SHADING_LANGUAGE_VERSION);
			
	printf("Vendor: %s\n", vendor);
	printf("Renderer: %s\n",renderer);
	printf("OpenGL Version: %s\n",oglVersion);
	printf("GLSL Version: %s\n", glslVersion);

	genShaderPrograms();

	genMeshGridObject(&mesh);
	texBoden.texFileName="res/laminat.bmp";	
	texFliessen.texFileName = "res/fliessen.bmp";
	texSteine.texFileName = "res/pflaster.bmp";
	texSteineNorm.texFileName = "res/pflaster.bmp";
	loadTexture(&texBoden);
	loadTexture(&texFliessen);
	loadTexture(&texSteine);
	loadTexture(&texSteineNorm);
	glActiveTexture(GL_TEXTURE0);
	bindTexture(&texBoden);
	bindTexture(&texSteine);
	glActiveTexture(GL_TEXTURE1);
	bindTexture(&texFliessen);
	bindTexture(&texSteineNorm);
	
	initLines(&lines, generic_sp);
	initTriangle(&triangle, generic_sp);
	initRectangle(&rectangle, generic_sp);
	initCircle(&circle, circle_sp);
	initStern(&stern, generic_sp);
	
	initPlane(&plane, boden_sp);
	plane.texID[0] = texBoden.texID;
	plane.texID[1] = texFliessen.texID;
	initCube(&cube, ads_per_fragment_sp);
	initSphere(&sphere[0], sphere_sp, &mesh);
	initSphere(&sphere[1], sphere_sp, &mesh);
	initSphere(&sphere[2], sphere_sp, &mesh);
	initSphere(&sphere[3], sphere_sp, &mesh);
	initApfel(&apfel, apfel_sp, &mesh);
	initPlane(&steine, normal_mapping_sp);	
	steine.texID[0] = texSteine.texID;
	steine.texID[1] = texSteineNorm.texID;
	camera = identity();

	plane.mModel = matMult(scale(20.0, 1.0, 20.0), plane.mModel);
	cube.mModel = matMult(translate(0.0, 5.0, 0.0), cube.mModel);
	sphere[0].mModel = matMult(translate(0.0, 1.0, -5.0), sphere[0].mModel);	
	sphere[1].mModel = matMult(translate(0.0, 1.0, 5.0), sphere[1].mModel);
	sphere[1].color = getColor(1.0, 0.0, 1.0, 1.0);
	sphere[2].mModel = matMult(translate(5.0, 1.0, 0.0), sphere[2].mModel);
	sphere[2].color = getColor(1.0, 1.0, 0.0, 1.0);
	sphere[3].mModel = matMult(translate(-5.0, 1.0, 0.0), sphere[3].mModel);
	sphere[3].color = getColor(0.0, 0.0, 1.0, 1.0);
	apfel.mModel = matMult(rotateX(-0.5), apfel.mModel);
	apfel.mModel = matMult(rotateY(0.1), apfel.mModel);
	apfel.mModel = matMult(translate(0.0, 0.85, 0.0), apfel.mModel);
	steine.mModel = matMult(scale(2.0, 1.0, 2.0), steine.mModel);
	steine.mModel = matMult(translate(0.0, 0.01, 0.0), steine.mModel);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearDepthf(1.0f);

	while(!quit)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Ansichten mit F1 F2 usw. umschalten
		if (!F1)
		{
			drawObj(&lines);
			drawObj(&triangle);
			drawObj(&rectangle);
			drawObj(&circle);
			drawObj(&stern);
		}
		else
		{
			drawObj(&plane);
			//drawObj(&cube);
			drawObj(&sphere[0]);
			drawObj(&sphere[1]);
			drawObj(&sphere[2]);
			drawObj(&sphere[3]);
			//drawObj(&apfel);
			drawObj(&steine);
			//drawObj(&circle);
		}

		SDL_GL_SwapBuffers();		

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: 
					quit=1;
					break;
				case SDL_KEYDOWN:
					key[event.key.keysym.sym] = 1;
					break;
				case SDL_KEYUP:
					key[event.key.keysym.sym] = 0;
					break;
				case SDL_MOUSEMOTION:
					mouseX = event.motion.xrel;
					mouseY = event.motion.yrel;
					break;
			}
		}	
		
		//if (key[SDLK_F1]) F1=0;
		//if (key[SDLK_F2]) F1=1;
		if (key[SDLK_ESCAPE]) quit=1;
		if (!F1)
		{
			if (key[SDLK_LEFT]) stern.mModel = matMult(rotateZ(0.01), stern.mModel);
			if (key[SDLK_RIGHT]) stern.mModel = matMult(rotateZ(-0.01), stern.mModel);
		}
		else
		{			
			if (key[SDLK_w]) camera = matMult(translate(0.0, 0.0, 0.02), camera);
			if (key[SDLK_s]) camera = matMult(translate(0.0, 0.0, -0.02), camera);
			if (key[SDLK_a]) camera = matMult(translate(0.02, 0.0, 0.0), camera);
			if (key[SDLK_d]) camera = matMult(translate(-0.02, 0.0, 0.0), camera);
			if (key[SDLK_y])
			{
				rotAxis = cross(getXAxis(camera),getZAxis(camera));
				camera = matMult(translate(rotAxis.x*0.02,rotAxis.y*0.02,rotAxis.z*0.02), camera);
			}
			if (key[SDLK_x])
			{
				rotAxis = cross(getXAxis(camera),getZAxis(camera));
				camera = matMult(translate(rotAxis.x*-0.02,rotAxis.y*-0.02,rotAxis.z*-0.02), camera);
			}
			if (key[SDLK_LEFT])
			{
				rotAxis = cross(getXAxis(camera),getZAxis(camera));
				camera = matMult(rotateX(rotAxis.x*0.005), camera);
				camera = matMult(rotateY(rotAxis.y*0.005), camera);
				camera = matMult(rotateZ(rotAxis.z*-0.005), camera);
			}
			if (key[SDLK_RIGHT])
			{
				rotAxis = cross(getXAxis(camera),getZAxis(camera));
				camera = matMult(rotateX(rotAxis.x*-0.005), camera);
				camera = matMult(rotateY(rotAxis.y*-0.005), camera);
				camera = matMult(rotateZ(rotAxis.z*0.005), camera);
			}
			if (key[SDLK_UP]) camera = matMult(rotateX(-0.005), camera);
			if (key[SDLK_DOWN]) camera = matMult(rotateX(0.005), camera);
			
			//camera = matMult(rotateY(mouseX/600.0f),camera);		
			//camera = matMult(rotateX(mouseY/600.0f),camera);
			//mouseX=0;
			//mouseY=0;
		}

		SDL_Delay(5);
	}
	
	SDL_Quit();

	return 0;
}
