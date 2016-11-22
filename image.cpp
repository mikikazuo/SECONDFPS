#include "image.h"
#include "math.h"

#define IMG_MAX 100
static GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);

#define PI 3.141592

struct img sa[IMG_MAX];

img get_sa(int no){
	return sa[no];

}
static int power_of_two(int input)
{
	int value = 1;

	while ( value < input ) {
		value <<= 1;
	}
	return value;
}


GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{

	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(surface->w);
	h = power_of_two(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */

	image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000
#else
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
#endif
	);
	if ( image == NULL ) {
		return 0;
	}

	/* Save the alpha blending attributes */
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
#if SDL_VERSION_ATLEAST(1, 3, 0)
	SDL_GetSurfaceAlphaMod(surface, &saved_alpha);
	SDL_SetSurfaceAlphaMod(surface, 0xFF);
#else
	saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, 0, 0);
	}
#endif

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
#if SDL_VERSION_ATLEAST(1, 3, 0)
	SDL_SetSurfaceAlphaMod(surface, saved_alpha);
#else
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}
#endif

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			w, h,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image->pixels);
	SDL_FreeSurface(image); /* No longer needed */

	return texture;
}


int none_Data(){
	int i;
	for(i=0;i<IMG_MAX;i++)
		if(sa[i].no==0)return i;
	printf("配列不足\n");
	return -1;
}

void image_Init(){
	int i;
	for(i=0;i<IMG_MAX;i++)
		sa[i].no=0;

}
int image_Load(const char *name){
	if(name==NULL) return -1;
	SDL_Surface *sss=IMG_Load(name);
	if(sss==NULL){
	printf("%sがありません",name);
	exit(-1);
	return -1;
	}
	GLfloat a[4];
	GLuint imageNo=SDL_GL_LoadTexture(sss,a);
	int tmp=none_Data();
	if(tmp<0) {
		SDL_FreeSurface(sss);
		exit(-1);
		return -1;
	}
	sa[tmp].no=imageNo;
	sa[tmp].color[0]=a[0];
	sa[tmp].color[1]=a[1];
	sa[tmp].color[2]=a[2];
	sa[tmp].color[3]=a[3];
	sa[tmp].oriX=sss->w;
	sa[tmp].oriY=sss->h;
	SDL_FreeSurface(sss);
	puts("OK");
	return tmp;
}

int enableNo(int no){
	if(no<0||IMG_MAX<=no)return 0;
	return (sa[no].no<=0)?0:1;
}
int getimgw(int no){
	if(!enableNo(no)) return 0;
	return sa[no].oriX;
}
int getimgh(int no){
	if(!enableNo(no)) return 0;
	return sa[no].oriY;
}

//原寸大
void imgOri_Draw(int no,GLfloat x,GLfloat y){
	if(!enableNo(no))return;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,sa[no].no);
	glColor3d(1.0,1.0,1.0);

	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(x, y);
	glTexCoord2d(0,sa[no].color[3]);
	glVertex2d(x,y+getimgh(no));
	glTexCoord2d(sa[no].color[2],sa[no].color[3]);
	glVertex2d(x+getimgw(no), y+getimgh(no));
	glTexCoord2d(sa[no].color[2],0);
	glVertex2d(x+getimgw(no), y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
//原寸大回転
void img_Ori_Rota(int no,GLfloat CenterX,GLfloat CenterY,double rota){
	glPushMatrix();
	glTranslated(CenterX,CenterY,0);
	glRotated(rota,0,0,1);
	image_Draw_C(no,0,0);
	glPopMatrix();
	printf("%d %d \n",(int)CenterX,(int)CenterY);


}
//原寸大拡大縮小
void image_DrawExRota(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp){
	glPushMatrix();
	glTranslated(CenterX,CenterY,0);
	glTranslated(CenterX,CenterY,0.000001*no);//1115 変更：レイヤー的表現用に仮変更
	glRotated(rota,0,0,1);
	img_zoomDraw_C(no, 0,0, exp);
	glPopMatrix();

}

//原寸大拡大縮小
void image_DrawExRota3D(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp){
	glPushMatrix();
	glTranslated(CenterX,CenterY,0);
	glRotated(rota,0,0,1);
	img_zoomDraw_C3D(no, 0,0, exp);
	glPopMatrix();

}

//アルファ値指定
void image_DrawExRotaa(int no,GLfloat CenterX,GLfloat CenterY,double rota,double exp,GLdouble a){
	glPushMatrix();
	glTranslated(CenterX,CenterY,0);
	glRotated(rota,0,0,1);
	img_zoomDraw_Ca(no, 0,0, exp,a);
	glPopMatrix();

}
//自由に縦横幅
void img_DrawXY(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h){
	if(!enableNo(no))return;
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,sa[no].no);
	glColor3d(1.0,1.0,1.0);

	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(x, y);
	glTexCoord2d(0,sa[no].color[3]);
	glVertex2d(x,y+h);
	glTexCoord2d(sa[no].color[2],sa[no].color[3]);
	glVertex2d(x+w, y+h);
	glTexCoord2d(sa[no].color[2],0);
	glVertex2d(x+w, y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

//自由に縦横幅
void img_DrawXY3D(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h){
	if(!enableNo(no))return;
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,sa[no].no);
	glColor3d(1.0,1.0,1.0);

	glBegin(GL_POLYGON);
	glTexCoord2d(0,sa[no].color[3]);
	glVertex2d(x, y);
	glTexCoord2d(sa[no].color[2],sa[no].color[3]);
	glVertex2d(x+w, y);
	glTexCoord2d(sa[no].color[2],0);
	glVertex2d(x+w, y+h);
	glTexCoord2d(0,0);
	glVertex2d(x,y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

//自由に縦横幅
void img_DrawXYa(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h,GLdouble a){
	if(!enableNo(no))return;
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,sa[no].no);
	glColor4d(1.0,1.0,1.0,a);

	glBegin(GL_POLYGON);
	glTexCoord2d(0,0);
	glVertex2d(x, y);
	glTexCoord2d(0,sa[no].color[3]);
	glVertex2d(x,y+h);
	glTexCoord2d(sa[no].color[2],sa[no].color[3]);
	glVertex2d(x+w, y+h);
	glTexCoord2d(sa[no].color[2],0);
	glVertex2d(x+w, y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void image_free(int no){
	if(!enableNo(no))return;
	glDeleteTextures(1,&sa[no].no);
	sa[no].no=0;

}

void img_zoomDraw_C(int no,GLfloat Centerx,GLfloat Centery,double exp){
	img_DrawXY(no,Centerx-(getimgw(no)*exp)/2,Centery-(getimgh(no)*exp)/2,getimgw(no)*exp,getimgh(no)*exp);
}

void img_zoomDraw_C3D(int no,GLfloat Centerx,GLfloat Centery,double exp){
	img_DrawXY3D(no,Centerx-(getimgw(no)*exp)/2,Centery-(getimgh(no)*exp)/2,getimgw(no)*exp,getimgh(no)*exp);
}

void img_zoomDraw_Ca(int no,GLfloat Centerx,GLfloat Centery,double exp,GLdouble a){
	img_DrawXYa(no,Centerx-(getimgw(no)*exp)/2,Centery-(getimgh(no)*exp)/2,getimgw(no)*exp,getimgh(no)*exp,a);
}

void img_zoom(int no,GLfloat x,GLfloat y,double exp){
	img_DrawXY(no,x,y,getimgw(no)*exp,getimgh(no)*exp);
}

void img_Draw(int no,GLfloat x,GLfloat y){
	img_DrawXY(no,x,y,getimgw(no),getimgh(no));
}
void image_Draw_C(int no,GLfloat x,GLfloat y){
	img_Draw(no,x-getimgw(no)/2,y-getimgh(no)/2);
}
void image_Drawrota_C(int no,GLfloat CenterX,GLfloat CenterY,int rota){
	img_Ori_Rota(no,CenterX,CenterY,rota);
}




void rect_Draw2D(int no,GLfloat x,GLfloat y,GLfloat w,GLfloat h){
	if(!enableNo(no))return;
	//glColor3d(1.0,0.2,0.2);

    //glPushMatrix();
	//glTranslated((x+w)/2,(y+w)/2,0.000001*no);//1115 変更：レイヤー的表現用に仮変更
	//glPopMatrix();

	glBegin(GL_POLYGON);
	//glTexCoord2d(0,0);
	glVertex2d(x, y);
	//glTexCoord2d(0,sa[no].color[3]);
	glVertex2d(x,y+h);
	//glTexCoord2d(sa[no].color[2],sa[no].color[3]);
	glVertex2d(x+w, y+h);
	//glTexCoord2d(sa[no].color[2],0);
	glVertex2d(x+w, y);
	glEnd();
}

void Circle2DFill(float radius,int x,int y)
{
 for (float th1 = 0.0;  th1 <= 360.0;  th1 = th1 + 1.0)
 {
  float th2 = th1 + 10.0;
  float th1_rad = th1 / 180.0 * PI;
  float th2_rad = th2 / 180.0 * PI;

  float x1 = radius * cos(th1_rad);
  float y1 = radius * sin(th1_rad);
  float x2 = radius * cos(th2_rad);
  float y2 = radius * sin(th2_rad);

  glBegin(GL_TRIANGLES);
   glVertex2f( x, y );
   glVertex2f( x1+x, y1+y );
   glVertex2f( x2+x, y2+y );
  glEnd();
 }
}

