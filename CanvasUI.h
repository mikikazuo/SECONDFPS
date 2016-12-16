/*
 * CanvasUI.h
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#ifndef CANVASUI_H_
#define CANVASUI_H_

class CanvasUI {
private:
	int handle[50];
	int time;
	int a;
	int shakeX;
	int shakeY;
	int dam;
	int wall_info[5];
	int level;
public:
	CanvasUI();
	virtual ~CanvasUI();
	void view2D();
	void Initialize();
	void DrawInitialize();
	void DrawFinalize();

	void Update();
	void Draw();

};

#endif /* CANVASUI_H_ */
