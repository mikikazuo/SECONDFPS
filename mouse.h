/*
 * mouse.h
 *
 *  Created on: 2016/09/12
 *      Author: user
 */

#ifndef MOUSE_H_
#define MOUSE_H_

typedef struct{
	int x,y;
}MousePosition;

typedef struct{
	float mousebutton_flag;
	float mousebutton_count;
}Mouse;


typedef enum{
	LEFT_BUTTON,
	MIDDLE_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON_SCROLL
}Buttontype;


void motion(int x, int y);
void mouse(int button , int state , int x , int y);
void mouseCounter();
MousePosition get_mouseinfo();
int get_mousebutton_count(Buttontype button);

#endif /* MOUSE_H_ */
