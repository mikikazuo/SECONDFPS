/*
 * Letter.h
 *
 *  Created on: 2017/01/22
 *      Author: c501506022
 */

#ifndef LETTER_H_
#define LETTER_H_
#include "glm.h"

enum LETTER_TYPE{
	MOZI_SHOUZANGYOUSYO,
	MOZI_SHOUZANSOUSYO,
	MOZI_HGMINTYOE,
	MOZI_ADOBEFANGSONG,
	MOZI_AGENCYBOLD,
	MOZI_SFSQUAREHEADCONDENSED

};
extern void initMozi() ;
//extern Mozi_Infomation *Mozi_Struction2(Uint16 Mozi);
//extern void Mozi_GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)DrawM(char *mstr, double X, double Y, double scale, int type);
extern void Mozi_Draw(wchar_t *wstr, double X, double Y, double scale, int type);
void Mozi_DrawCenter(wchar_t *wstr, double X, double Y, double scale, int type);
void Mozi_Draw_3D(wchar_t *wstr, double X, double Y, double scale, int type);
extern void Mozi_DrawM(const char *mstr, double X, double Y, double scale, int type);

extern void Mozi_DrawM_H(char *mstr, double X, double Y, double scale, int type) ;
extern void Mozi_Draw_H(wchar_t *wstr, double X, double Y, double scale, int type);
extern double Mozi_WidthM(char *mstr, double scale, int type);
extern double Mozi_Width(wchar_t *wstr, double scale, int type);
//extern Mozi_Infomation *mozi_getMoziPointer(wchar_t ch);
extern void Mozi_Delete() ;
extern void Mozi_DrawM2(double X, double Y, double scale, int type, const char *format, ...);
void Mozi_DrawM2Ceneter(double X, double Y, double scale, int type, const char *format, ...);
void Mozi_DrawM2_3D(vec3 Center,double rota,vec3 nvec, double scale, int type, const char *format, ...);
extern void Mozi_DrawM2_H(double X, double Y, double scale, int type, const char *format, ...);
extern double Mozi_WidthM2(double scale, int type, const char *format, ...);
extern void Mozi_preset(wchar_t *wstr) ;
extern void Mozi_presetM(char *mstr);
extern void Mozi_presetM2(const char *format, ...) ;




#endif /* LETTER_H_ */
