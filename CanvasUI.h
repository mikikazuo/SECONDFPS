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