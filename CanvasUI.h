/*
 * CanvasUI.h
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#ifndef CANVASUI_H_
#define CANVASUI_H_

//単位は1/60秒
#define WALL_SET 		300		//壁の設置にかかる時間
#define WALL_DELETE 	600		//壁の除去にかかる時間
#define RESPAWN_TIME	900		//死亡してからリスポーンするまでの待機時間

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
	int set;	//設置状況
	int del;	//除去状況
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
