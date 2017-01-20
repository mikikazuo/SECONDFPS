/*
 * CanvasUI.h
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#ifndef CANVASUI_H_
#define CANVASUI_H_

#define WALL_SET 300
#define WALL_DELETE 600

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
	double 	progress_time;	//経過時間
	double progress_per;	//進捗率
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
