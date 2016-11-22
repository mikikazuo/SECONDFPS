/*
 * image.h
 *
 *  Created on: 2016/09/25
 *      Author: user
 */

#ifndef IMAGE_H_
#define IMAGE_H_
//#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glut.h>
struct img{
	GLuint no;
	GLfloat color[4];

	int oriX,oriY;

};
int enableNo(int no);
void img_Draw(int no,GLfloat x,GLfloat y);
void img_zoom(int no,GLfloat x,GLfloat y,double exp);
void image_DrawExRota(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp);
void img_zoomDraw_C(int no,GLfloat Centerx,GLfloat Centery,double exp);
void image_Draw_C(int no,GLfloat x,GLfloat y);
void img_Ori_Rota(int no,GLfloat CenterX,GLfloat CenterY,double rota);
void image_Init();
int image_Load(const char *name);
void imgOri_Draw(int no,GLfloat x,GLfloat y);
void img_DrawXY(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h);
void image_free(int no);
void image_DrawExRotaa(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp,GLdouble a);
void img_zoomDraw_Ca(int no,GLfloat Centerx,GLfloat Centery,double exp,GLdouble a);

void rect_Draw2D(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h);
void Circle2DFill(float radius,int x,int y);//****

//3D用
void image_DrawExRota3D(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp);
void img_zoomDraw_C3D(int no,GLfloat Centerx,GLfloat Centery,double exp);
void img_DrawXY3D(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h);

img get_sa(int no);
#endif /* IMAGE_H_ */
