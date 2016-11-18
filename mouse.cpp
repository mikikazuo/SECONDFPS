/*
 * mouse.cpp

 *
 *  Created on: 2016/09/12
 *      Author: user
 */
#include "mouse.h"
#include  "GL/glut.h"
#include  "Game.h"
#include  "fps.h"
MousePosition mouseinfo;


static Mouse counter[4];

static int counta;
//ドラッグ
void motion(int x, int y) {
	mouseinfo.x = x;
	mouseinfo.y = y;
}

void reset_Scroll(){
	counter[MIDDLE_BUTTON_SCROLL].mousebutton_count=0;
}
void mouse(int button , int state , int x , int y) {
	switch(button){
	case LEFT_BUTTON:
	case MIDDLE_BUTTON:
	case RIGHT_BUTTON:
		if(state==GLUT_DOWN)
			counter[button].mousebutton_flag++;
		else
			counter[button].mousebutton_flag=0;
		break;
	case 3:
		counter[MIDDLE_BUTTON_SCROLL].mousebutton_count++;
		break;
	case 4:
		counter[MIDDLE_BUTTON_SCROLL].mousebutton_count--;
		break;
	}



	counta=button;
}
void mouseCounter(){
	for(int i=0;i<=RIGHT_BUTTON;i++){
		if(counter[i].mousebutton_flag)
			counter[i].mousebutton_count++;
		else
			counter[i].mousebutton_count=0;
	}
}


MousePosition get_mouseinfo() {
	return mouseinfo;
}

int get_mousebutton_count(Buttontype button){
	return counter[button].mousebutton_count;
}


