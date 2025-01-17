/*
 * fps.h
 *
 *  Created on: 2016/09/12
 *      Author: user
 */

#ifndef FPS_H_
#define FPS_H_

#define DRAWFPS 60
#define UPDATEFPS 60


typedef struct{
	int FrameCount; 		//経過フレーム数
	int FPS; 				//設定fps
	unsigned int fpsStart;	//測定開始時刻
	unsigned int fpsCounter; //カウンター
	int N;					//平均を取るサンプル数
	int waitTime; 			//待機時間のサンプリングフレーム間での合計
	double waitTime_Ave;  //待機時間の平均
	double fps_Ave;  		//平均fps
}samp;


class fps{
private:
samp Fps_Update;
	float dt;
public:
	void fps_Initialize();
	int UpdateUpDatefps();
	int wait_Update();
	void fps_UpdateDeltaTime();

	int get_fps_Ave();
	float fps_getDeltaTime();
};




#endif /* FPS_H_ */
