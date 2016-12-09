
#include "key.h"
#include "GL/glut.h"
#include "glm.h"


static int move = 0;
static int keycount[none];
void key_Update(){
	for(int i=0;i<none;i++)
		if(keycount[i])
			keycount[i]++;

}
void normal(unsigned char key , int x, int y){
	if(key =='a')
		keycount[Left]++;
	if(key =='d')
		keycount[Right]++;
	if(key =='w')
		keycount[Forward]++;
	if(key == 's')
		keycount[Backward]++;
	if(key == ' ')
		keycount[Jump]++;
	if(key == 'e')
		keycount[Setwall]++;
	if(key == 'q')
		keycount[Removewall]++;
	if(key == 't')
		keycount[Test]++;

	//  if(key == KEY_PAGEUP)
	//    move |= up;
	//  if(key == KEY_PAGEDOWN)
	//    move |= down;
}


void normalup(unsigned char key , int x, int y){
	if(key =='a')
		keycount[Left]=0;
	if(key =='d')
		keycount[Right]=0;
	if(key =='w')
		keycount[Forward]=0;
	if(key == 's')
		keycount[Backward]=0;
	if(key == ' ')
		keycount[Jump]=0;
	if(key == 'e')
		keycount[Setwall]=0;
	if(key == 'q')
		keycount[Removewall]=0;
	if(key == 't')
			keycount[Test]=0;

}

void special(int key, int x, int y) {
	if(key == GLUT_KEY_LEFT)
		move |= left;
	if(key == GLUT_KEY_RIGHT)
		move |= right;
	if(key ==GLUT_KEY_UP)
		move |= forward;
	if(key == GLUT_KEY_DOWN)
		move |= backward;
}

void specialup(int key, int x, int y) {
	if(key == GLUT_KEY_LEFT)
		move &= ~left;
	if(key == GLUT_KEY_RIGHT)
		move &= ~right;
	if(key == GLUT_KEY_UP)
		move &= ~forward;
	if(key == GLUT_KEY_DOWN)
		move &= ~backward;
}

int key_getmove(Key key){
	return keycount[key];
}
