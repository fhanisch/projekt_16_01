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
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );

	SDL_SetVideoMode(600,600,32,SDL_OPENGL);
	SDL_WM_SetCaption(wndName, NULL);

	return 0;
}

int main(int argc, char **argv)
{
	int quit = 0;
	unsigned int key[256];
	const GLubyte *vendor, *renderer, *oglVersion, *glslVersion;
	RenderObject lines, triangle, rectangle, circle, stern;	

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

	initLines(&lines);
	initTriangle(&triangle);
	initRectangle(&rectangle);
	initCircle(&circle);
	initStern(&stern);
	
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
		drawObj(&lines);
		drawObj(&triangle);
		drawObj(&rectangle);
		drawObj(&circle);
		drawObj(&stern);		
		
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
			}
		}	
		
		if (key[SDLK_LEFT]) stern.rotZ += 0.01;				
		if (key[SDLK_RIGHT]) stern.rotZ -= 0.01;
		SDL_Delay(5);
	}
	
	SDL_Quit();

	return 0;
}
