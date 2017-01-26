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
#define RESPAWN_TIME	600		//死亡してからリスポーンするまでの待機時間

#define FIN_MES1 50		//ゲーム終了メッセージを表示する際に使用
#define FIN_MES2 15
#define FIN_MES_HEIGHT 100 //ゲーム終了メッセージを表示する領域の高さ

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
	double res_time;		//リスポーン待機経過時間
	double res_per;
	int fin_mes; //ゲーム終了メッセージの表示状況を格納
	double fin_time; //ゲーム終了メッセージを表示する際に使用
	double fin_per; //ゲーム終了メッセージを表示する際に使用

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
