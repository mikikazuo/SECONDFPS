/*
 * Letter.cpp
 *
 *  Last edit: 2017/2/9
 *      Author: 三木
 */

#include "Letter.h"
#include "locale.h"
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include "Game.h"
//using namespace Leap;

#define MOZI_DEBUG 0//1でデバッグ出力モード


//文字情報格納用構造体(文字単体)
typedef struct Mozi_chinfos {
	int textureNo;//テクスチャの識別番号
	int Width;//文字の幅
	int Heigh;//文字の高さ(一定値にしたい)
	char FileName[40];
} Mozi_chInfomation;

//文字情報格納用構造体
typedef struct Mozi_Moziinfos {
	struct Mozi_Moziinfos *next;//前の構造体へのポインタ
	wchar_t Mozi;//文字(ワイド)
	Mozi_chInfomation syouzan_gyousyo;//衡山毛筆フォント行書の情報
	Mozi_chInfomation syouzan_sousyo;//衡山毛筆フォント草書の情報
	Mozi_chInfomation HGmintyouE;//HG明朝Eの情報
	Mozi_chInfomation AdobeFangsong;//Adobeファングソングの情報
	Mozi_chInfomation AGENCYBold;//AGENCYBoldの情報
	Mozi_chInfomation SFSquareHeadCondensed;//
} Mozi_Infomation;



static int IndexNO = 0;//文字情報の添字
static int Mozi_ALART_nummmozi = 0;//存在しない文字が入力された時のエラーを出力したかどうか
static int Mozi_ALART_Nommozicolor = 0;//存在しない文字種類が入力された時のエラーを出力したかどうか
static TTF_Font* font_kouzan_kyousyo;	//フォント読み込み用(SDL)
static TTF_Font* font_kouzan_sousyo;	//フォント読み込み用(SDL)
static TTF_Font* font_HGmintyouE;	//フォント読み込み用(SDL)
static TTF_Font* font_AdobeFangsong;	//フォント読み込み用(SDL)
static TTF_Font* font_AGENCYBold;	//フォント読み込み用(SDL)
static TTF_Font* font_SFSquareHeadCondensed;	//フォント読み込み用(SDL)

//文字列をリスト構造で保存する(無限可変配列)
static Mozi_Infomation root;//根

static Mozi_Infomation *mozi_getMoziPointer(wchar_t ch);
static GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
/*
 * 文字列描画の初期化
 */
void initMozi() {
	TTF_Init();
#ifdef WINDOWS
#include <Windows.h>//Win
	char *txt = setlocale(LC_ALL, "JPN");
	if (MOZI_DEBUG)	printf("ロケーション設定%s\n", txt);
#else
	char *txt = setlocale(LC_ALL, "ja_JP.UTF-8");
	if (MOZI_DEBUG)	printf("ロケーション設定%s\n", txt);
#endif


	font_kouzan_kyousyo = TTF_OpenFont("Data/Mozi/TTF/kouzan_kyousyo.ttf", 120);//フォトのロード
	font_kouzan_sousyo = TTF_OpenFont("Data/Mozi/TTF/kouzan_sousyo.ttf", 120);//フォトのロード
	font_HGmintyouE = TTF_OpenFont("Data/Mozi/TTF/HGRME.TTC", 100);//フォトのロード
	font_AdobeFangsong = TTF_OpenFont("Data/Mozi/OTF/AdobeFangsongStd-Regular.otf", 100);//フォトのロード
	font_AGENCYBold = TTF_OpenFont("Data/Mozi/TTF/AGENCYB.TTF", 100);//フォトのロード
	font_SFSquareHeadCondensed = TTF_OpenFont("Data/Mozi/TTF/SF_Square_Head_Condensed.ttf", 150);//フォトのロード
	printf("%s\n",SDL_GetError());
	IndexNO = 0;
	Mozi_ALART_nummmozi = 0;
	Mozi_ALART_Nommozicolor = 0;

	root.next = NULL;//最初の配列の初期化
	//	TTF_CloseFont(font_kouzan_kyousyo);
	//	TTF_CloseFont(font_kouzan_sousyo);
	//	TTF_CloseFont(font_HGmintyouE);
}


//文字列描画用の構造体の作成
Mozi_Infomation *Mozi_Struction2(wchar_t Mozi) {
	GLfloat TextureSize[4];
	//構造体のメモリ確保
	Mozi_Infomation *mozi2 = (Mozi_Infomation *)malloc(sizeof(Mozi_Infomation));

	if (MOZI_DEBUG)	printf("Mozi:add'%C'\n", Mozi);

	mozi2->Mozi = Mozi;


	//衡山毛筆フォント行書
	// ラスタライズしたビットマップを取得
	SDL_Color font_color = { 255, 255, 255 };//フォントの色指定
	char mozi[6];
	sprintf(mozi, "%C", Mozi);
	//SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font_kouzan_kyousyo, mozi, font_color);//フォントのサーフェイス化
	SDL_Surface* text_surface = TTF_RenderUNICODE_Blended(font_kouzan_kyousyo, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->syouzan_gyousyo.Width = text_surface->w;
	mozi2->syouzan_gyousyo.Heigh = text_surface->h;
	sprintf(mozi2->syouzan_gyousyo.FileName, "FromttfFile");
	mozi2->syouzan_gyousyo.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);


	//衡山毛筆フォント草書
	// ラスタライズしたビットマップを取得
	//text_surface = TTF_RenderUTF8_Bextern "C" void play_Initialize()lended(font_kouzan_sousyo, mozi, font_color);//フォントのサーフェイス化
	text_surface = TTF_RenderUNICODE_Blended(font_kouzan_sousyo, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->syouzan_sousyo.Width = text_surface->w;
	mozi2->syouzan_sousyo.Heigh = text_surface->h;
	sprintf(mozi2->syouzan_sousyo.FileName, "FromttfFile");
	mozi2->syouzan_sousyo.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);



	//HG明朝E
	// ラスタライズしたビットマップを取得
	//text_surface = TTF_RenderUTF8_Blended(font_HGmintyouE, mozi, font_color);//フォントのサーフェイス化
	text_surface = TTF_RenderUNICODE_Blended(font_HGmintyouE, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->HGmintyouE.Width = text_surface->w;
	mozi2->HGmintyouE.Heigh = text_surface->h;
	sprintf(mozi2->HGmintyouE.FileName, "FromttfFile");
	mozi2->HGmintyouE.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);


	//HG明朝E
	// ラスタライズしたビットマップを取得
	//text_surface = TTF_RenderUTF8_Blended(font_AdobeFangsong, mozi, font_color);//フォントのサーフェイス化
	text_surface = TTF_RenderUNICODE_Blended(font_AdobeFangsong, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->AdobeFangsong.Width = text_surface->w;
	mozi2->AdobeFangsong.Heigh = text_surface->h;
	sprintf(mozi2->AdobeFangsong.FileName, "FromttfFile");
	mozi2->AdobeFangsong.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);


	//HG明朝E
	// ラスタライズしたビットマップを取得
	//text_surface = TTF_RenderUTF8_Blended(font_AGENCYBold, mozi, font_color);//フォントのサーフェイス化
	text_surface = TTF_RenderUNICODE_Blended(font_AGENCYBold, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->AGENCYBold.Width = text_surface->w;
	mozi2->AGENCYBold.Heigh = text_surface->h;
	sprintf(mozi2->AGENCYBold.FileName, "FromttfFile");
	mozi2->AGENCYBold.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);


	//HG明朝E
	// ラスタライズしたビットマップを取得
	//text_surface = TTF_RenderUTF8_Blended(font_SFSquareHeadItalic, mozi, font_color);//フォントのサーフェイス化
	text_surface = TTF_RenderUNICODE_Blended(font_SFSquareHeadCondensed, (const Uint16*)&Mozi, font_color);//フォントのサーフェイス化(UNICODE)
	mozi2->SFSquareHeadCondensed.Width = text_surface->w;
	mozi2->SFSquareHeadCondensed.Heigh = text_surface->h;
	sprintf(mozi2->SFSquareHeadCondensed.FileName, "FromttfFile");
	mozi2->SFSquareHeadCondensed.textureNo = SDL_GL_LoadTexture(text_surface, TextureSize);


	//リストの先頭に追加する
	mozi2->next = root.next;
	root.next = mozi2;
	IndexNO++;
	return mozi2;
}

void Mozi_DrawM(const char *mstr, double X, double Y, double scale, int type) {
	wchar_t ws[130];
	ws[0] = '\0';

	//setlocale( LC_ALL, "ja_JP.UTF-8" );
	mbstowcs(ws, mstr, 100);
	Mozi_Draw(ws, X, Y, scale, type);
}

void Mozi_DrawMCenter(const char *mstr, double X, double Y, double scale, int type) {
	wchar_t ws[130];
	ws[0] = '\0';

	//setlocale( LC_ALL, "ja_JP.UTF-8" );
	mbstowcs(ws, mstr, 100);
	Mozi_DrawCenter(ws, X, Y, scale, type);
}

void Mozi_DrawM_3D(const char *mstr, double X, double Y, double scale, int type) {
	wchar_t ws[130];
	ws[0] = '\0';

	//setlocale( LC_ALL, "ja_JP.UTF-8" );
	mbstowcs(ws, mstr, 100);
	Mozi_Draw_3D(ws, X, Y, scale, type);
}

/*
 * 文字列の描画
 * 上限100文字
 */
void Mozi_Draw(wchar_t *wstr, double X, double Y, double scale, int type) {
	//バイリニア補間
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int i;
	Mozi_chInfomation tmpmozi;
	Mozi_Infomation *tmp2;
	glEnable(GL_TEXTURE_2D);//テクスチャ有効
	glEnable(GL_ALPHA_TEST);//アルファテスト開始
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			//日本語不可
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {
				glBindTexture(GL_TEXTURE_2D, tmpmozi.textureNo);
				glBegin(GL_QUADS);

				glTexCoord2f(0.0f, 1.0f);	// 画像の左下と次の頂点を対応させる
				glVertex2f(X, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 1.0f);	// 画像の右下と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 0.0f);	// 画像の右上と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y);
				glTexCoord2f(0.0f, 0.0f);	// 画像の左上と次の頂点を対応させる
				glVertex2f(X, Y);
				glEnd();
				X += tmpmozi.Width*scale;
			}
			else {
			}
		}
	}
	//バイリニア補間ここまで
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//２次元文字　中心位置
void Mozi_DrawCenter(wchar_t *wstr, double X, double Y, double scale, int type) {
	//バイリニア補間
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int i;
	double sumlength=0;
	Mozi_chInfomation tmpmozi;
	Mozi_Infomation *tmp2;
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			//日本語不可
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {
				sumlength += tmpmozi.Width*scale;
			}
			else {
			}
		}
	}
	glPushMatrix();
	glTranslated(-sumlength/2,0,0);

	glEnable(GL_TEXTURE_2D);//テクスチャ有効
	glEnable(GL_ALPHA_TEST);//アルファテスト開始
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			//日本語不可
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {
				glBindTexture(GL_TEXTURE_2D, tmpmozi.textureNo);
				glBegin(GL_QUADS);

				glTexCoord2f(0.0f, 1.0f);	// 画像の左下と次の頂点を対応させる
				glVertex2f(X, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 1.0f);	// 画像の右下と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 0.0f);	// 画像の右上と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y);
				glTexCoord2f(0.0f, 0.0f);	// 画像の左上と次の頂点を対応させる
				glVertex2f(X, Y);
				glEnd();
				X += tmpmozi.Width*scale;
			}
			else {
			}
		}
	}
	glPopMatrix();
	//バイリニア補間ここまで
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Mozi_Draw_3D(wchar_t *wstr, double X, double Y, double scale, int type) {
	//バイリニア補間
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int i;
	double sumlength=0;
	Mozi_chInfomation tmpmozi;
	Mozi_Infomation *tmp2;
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			//日本語不可
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {
				sumlength += tmpmozi.Width*scale;
			}
			else {
			}
		}
	}
	glPushMatrix();
	glTranslated(-sumlength/2,0,0);

	glEnable(GL_TEXTURE_2D);//テクスチャ有効
	glEnable(GL_ALPHA_TEST);//アルファテスト開始

	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			//日本語不可
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {


				glBindTexture(GL_TEXTURE_2D, tmpmozi.textureNo);
				glBegin(GL_QUADS);

				glTexCoord2f(0.0f, 1.0f);	// 画像の左下と次の頂点を対応させる
				glVertex2f(X, Y);
				glTexCoord2f(1.0f, 1.0f);	// 画像の右下と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y);
				glTexCoord2f(1.0f, 0.0f);	// 画像の右上と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(0.0f, 0.0f);	// 画像の左上と次の頂点を対応させる
				glVertex2f(X, Y + tmpmozi.Heigh*scale);

				glEnd();


				X += tmpmozi.Width*scale;
			}
			else {
			}
		}
	}
	glPopMatrix();
	//バイリニア補間ここまで
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Mozi_DrawM_H(char *mstr, double X, double Y, double scale, int type) {
	wchar_t ws[130];
	ws[0] = '\0';

	//setlocale( LC_ALL, "ja_JP.UTF-8" );
	mbstowcs(ws, mstr, 100);
	Mozi_Draw_H(ws, X, Y, scale, type);
}

//縦文字
void Mozi_Draw_H(wchar_t *wstr, double X, double Y, double scale, int type) {

	int i;
	Mozi_chInfomation tmpmozi;
	Mozi_Infomation *tmp2;
	glEnable(GL_TEXTURE_2D);//テクスチャ有効
	glEnable(GL_ALPHA_TEST);//アルファテスト開始
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					if (MOZI_DEBUG)	printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return;
			}
			if (tmpmozi.textureNo > 0) {
				glBindTexture(GL_TEXTURE_2D, tmpmozi.textureNo);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);	// 画像の左上と次の頂点を対応させる
				glVertex2f(X, Y);
				glTexCoord2f(0.0f, 1.0f);	// 画像の左下と次の頂点を対応させる
				glVertex2f(X, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 1.0f);	// 画像の右下と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y + tmpmozi.Heigh*scale);
				glTexCoord2f(1.0f, 0.0f);	// 画像の右上と次の頂点を対応させる
				glVertex2f(X + tmpmozi.Width*scale, Y);
				glEnd();
				Y += tmpmozi.Heigh*scale;
			}
			else {
			}
		}
	}
}

double Mozi_WidthM(char *mstr, double scale, int type) {
	wchar_t ws[130];
	ws[0] = '\0';

	mbstowcs(ws, mstr, 100);
	return Mozi_Width(ws, scale, type);
}

//文字の長さの取得(ピクセル)
double Mozi_Width(wchar_t *wstr, double scale, int type) {
	double X = 0;

	int i;
	Mozi_chInfomation tmpmozi;
	Mozi_Infomation *tmp2;
	for (i = 0; wstr[i] != '\0'; i++) {
		//		tmp = mozi_getMoziNO(wstr[i]);
		tmp2 = mozi_getMoziPointer(wstr[i]);
		if (tmp2 == NULL) {//存在しない文字は無視
		}
		else {
			if (type == MOZI_SHOUZANGYOUSYO) {//衡山毛筆フォント行書
				tmpmozi = tmp2->syouzan_gyousyo;
			}
			else if (type == MOZI_SHOUZANSOUSYO) {
				tmpmozi = tmp2->syouzan_sousyo;
			}
			else if (type == MOZI_HGMINTYOE) {
				tmpmozi = tmp2->HGmintyouE;
			}
			else if (type == MOZI_ADOBEFANGSONG) {
				tmpmozi = tmp2->AdobeFangsong;
			}
			else if (type == MOZI_AGENCYBOLD) {
				tmpmozi = tmp2->AGENCYBold;
			}
			else if (type == MOZI_SFSQUAREHEADCONDENSED) {
				tmpmozi = tmp2->SFSquareHeadCondensed;
			}
			else {
				if (Mozi_ALART_Nommozicolor == 0) {
					printf("存在しない文字種類です:%d(最初の一度のみ警告)\n", type);
					Mozi_ALART_Nommozicolor = 1;
				}
				return X;
			}
			if (tmpmozi.textureNo != 0) {
				X += tmpmozi.Width*scale;
			}
		}
	}

	return X;
}

Mozi_Infomation *mozi_getMoziPointer(wchar_t ch) {

	Mozi_Infomation *tmp;
	for (tmp = root.next; tmp != NULL; tmp = tmp->next) {
		if (tmp->Mozi == ch) {
			return tmp;
		}
	}


	return Mozi_Struction2(ch);
}

//文字の全消去
void Mozi_Delete() {
	Mozi_Infomation *tmp = root.next;
	root.next = NULL;
	Mozi_Infomation *tmp2;
	while (1) {
		if (tmp == NULL) {
			break;
		}
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		IndexNO--;
	}
}
//文字列の描画(書式設定あり)
void Mozi_DrawM2(double X, double Y, double scale, int type, const char *format, ...)
{
	va_list args;
	char str[100];
	str[0] = '\0';
	//        char *strtmp = str;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	Mozi_DrawM(str, X, Y, scale, type);
}

//文字列の描画(書式設定あり)
void Mozi_DrawM2Ceneter(double X, double Y, double scale, int type, const char *format, ...)
{
	va_list args;
	char str[100];
	str[0] = '\0';
	//        char *strtmp = str;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	Mozi_DrawMCenter(str, X, Y, scale, type);
}

void Mozi_DrawM2_3D(vec3 Center,double rota,vec3 nvec, double scale, int type, const char *format, ...)
{
	glPushMatrix();
	//double length=strlen(format);
	glTranslated(Center.x,Center.y,Center.z);

	vec3 toplayer_dir = get_player()->position-Center;
	float toplayer_dir_big=sqrt(toplayer_dir.x*toplayer_dir.x+toplayer_dir.y*toplayer_dir.y+toplayer_dir.z*toplayer_dir.z);
	toplayer_dir.x/=toplayer_dir_big;
	toplayer_dir.y/=toplayer_dir_big;
	toplayer_dir.z/=toplayer_dir_big;
	vec3 angles=vec3(atan2(toplayer_dir.x,toplayer_dir.z),
			atan2(toplayer_dir.y,toplayer_dir.x*toplayer_dir.x+toplayer_dir.z*toplayer_dir.z), atan2(toplayer_dir.z,toplayer_dir.x));
	glRotated(angles.x * 180 /M_PI ,0,1,0);
	glRotated(-angles.y * 180 /M_PI ,1,0,0);
	//glTranslated(-length*0.12,0,0);
	va_list args;
	char str[100];
	str[0] = '\0';
	//        char *strtmp = str;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	Mozi_DrawM_3D(str, 0, 0, scale, type);

	glPopMatrix();
}

void Mozi_DrawM2_H(double X, double Y, double scale, int type, const char *format, ...)
{
	va_list args;
	char str[100];
	str[0] = '\0';
	//        char *strtmp = str;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	Mozi_DrawM_H(str, X, Y, scale, type);
}


//文字列の描画(書式設定あり)
double Mozi_WidthM2(double scale, int type, const char *format, ...)
{
	va_list args;
	char str[100];
	str[0] = '\0';
	//        char *strtmp = str;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	return Mozi_WidthM(str, scale, type);
}

//文字列をあらかじめ登録する(glBeginの中で文字を描画するときなど)
void Mozi_preset(wchar_t *wstr) {
	int i;
	for (i = 0; wstr[i] != '\0'; i++) {
		mozi_getMoziPointer(wstr[i]);
	}
}

//文字列をあらかじめ登録する
void Mozi_presetM(char *mstr) {
	wchar_t ws[130];
	ws[0] = '\0';
	mbstowcs(ws, mstr, 100);
	return Mozi_preset(ws);
}

//文字列をあらかじめ登録する
void Mozi_presetM2(const char *format, ...) {
	va_list args;
	char str[100];
	str[0] = '\0';
	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	return Mozi_presetM(str);
}

/* Quick utility function for texture creation */
static int power_of_two(int input)
{
	int value = 1;

	while ( value < input ) {
		value <<= 1;
	}
	return value;
}

//サーフェイスをテクスチャに変換
static GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
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

