//main.c
//Erstellt: 30.01.2016

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "ogl.h"
#include "renderobject.h"
#include "geo_objects.h"

Display			*dpy;
Window			root;
GLint			att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo		*vi;
Colormap		cmap;
XSetWindowAttributes	swa;
Window                  win;
GLXContext              glc;
XEvent                  xev;


int initOpenGLWindow(char *wndName)
{
	dpy = XOpenDisplay(NULL);
	if(dpy == NULL)
	{
        	printf("\n\tcannot connect to X server\n\n");
        	return 1;
	 }
	root = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);
	if(vi == NULL)
	{
        	printf("\n\tno appropriate visual found\n\n");
	        return 1;
	} 
	else
	{
        	printf("\n\tvisual %p selected\n", (void *)vi->visualid);
	}

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	XMapWindow(dpy, win);
	XStoreName(dpy, win, wndName);

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	return 0;
}

int main(int argc, char **argv)
{
	int quit = 0;
	unsigned int key[256];
	const GLubyte *vendor, *renderer, *oglVersion, *glslVersion;
	RenderObject lines, triangle, rectangle, circle, stern;	

	printf("Programm: %s\n",argv[0]+2);
	
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
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	while(!quit)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//Ansichten mit F1 F2 usw. umschalten
		drawObj(&lines);
		drawObj(&triangle);
		drawObj(&rectangle);
		drawObj(&circle);
		drawObj(&stern);		
		glXSwapBuffers(dpy, win);

		XNextEvent(dpy, &xev);
		if (xev.type == KeyPress) key[xev.xkey.keycode] = 1;
		else if (xev.type == KeyRelease) key[xev.xkey.keycode] = 0;

		if (key[9])
		{
			glXMakeCurrent(dpy, None, NULL);
			glXDestroyContext(dpy, glc);
			XDestroyWindow(dpy, win);
			XCloseDisplay(dpy);
			quit = 1;
		}

		if (key[111]) stern.rotZ += 0.1;				
		if (key[116]) stern.rotZ -= 0.1;			
	}

	return 0;
}
