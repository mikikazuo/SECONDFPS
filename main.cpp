/* C4-2.c */



//#include "ShaderLoader.h"
////#include "Matrix.h"
//#include "ObjLoader.h"
#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#include <GL/glut.h>

//#include <X11/Xlib.h>

#include <stdlib.h>


#include <math.h>
#include "key.h"


#include "fps.h"
#include "main.h"

#include "mouse.h"
#include "image.h"
#include "SceneMgr.h"



#define LOOK_DISTANT 1000            //見える距離
#define TEXWIDTH  512
#define TEXHEIGHT 512

static bool debug=false;    //sever connect


SceneMgr sceneMgr;
static SDL_Thread *update;  //ゲーム書利用スレッド
fps mainfps;

static int *argci;
static char** argvi;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	sceneMgr.Draw();

	glutSwapBuffers();

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h,0.1,LOOK_DISTANT);//view volume 注意
	glMatrixMode(GL_MODELVIEW);
}

void myInit(char *progname)
{

	int width=1200,height=700;
	float aspect =(float)width/(float)height;

	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
		//printf("error");
		exit(-1);
	}

	mainfps.fps_Initialize();

	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor(0.0,0.2,0.5,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspect,0.1,LOOK_DISTANT);//view volume 注意
	glMatrixMode(GL_MODELVIEW);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMouseFunc(mouse);

	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);

	glutKeyboardFunc(normal);
	glutKeyboardUpFunc(normalup);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialup);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	image_Init();





}

void timer(int no){
	glutTimerFunc(1000/DRAWFPS,timer,0);
	//mouse_Update_WindowSize();
	// if(frameCount_draw%setting_DrawFrame)

	glutPostRedisplay();
}

int thread_Update(void *arg){

	sceneMgr.Initialize();
	while(1){
		mainfps.UpdateUpDatefps();
		mainfps.fps_UpdateDeltaTime();

		mouseCounter();
		sceneMgr.Update();  //更新
		mainfps.wait_Update();
		key_Update();


	}
	sceneMgr.Finalize();
	return 0;
}

int main (int argc, char** argv)
{
	argci = &argc;
	argvi = argv;



	glutInit(&argc,argv);

	myInit(argv[0]);

	sceneMgr.DrawInitialize();
	glutDisplayFunc(display);
	glutTimerFunc(1000/DRAWFPS,timer,0);
	update= SDL_CreateThread(thread_Update,NULL);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}

fps get_mainfps(){
	return mainfps;
}

int *get_argc(){
	return argci;
}
char** get_argv(){
	return argvi;
};





