#pragma once


static const int left = 1;
static const int right = 2;
static const int forward = 4;
static const int backward = 8;
static const int jump = 16;
static const int setwall = 32;
static const int removewall = 64;

typedef enum{
	Move,
	Left,
	Right,
	Forward,
	Backward,
	Jump,
	Setwall,
	Removewall,
	Reload,
	none
}Key;



void normal(unsigned char key , int x, int y);
void normalup(unsigned char key , int x, int y);
void special(int key, int x, int y) ;
void specialup(int key, int x, int y) ;
void key_Update();

int  key_getmove(Key key);
