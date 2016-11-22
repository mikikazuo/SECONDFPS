/*
 * fps.cpp
 *
 *  Created on: 2016/09/12
 *      Author: user
 */
#include  "fps.h"
#include <SDL/SDL.h>



void fps::fps_Initialize(){
	Fps_Update.fpsStart 		= 0;			//測定開始時刻
	Fps_Update.fpsCounter 		= 0; 			//カウンター
	Fps_Update.N 				= 60;			//平均を取るサンプル数
	Fps_Update.waitTime 		= 0; 			//待機時間のサンプリングフレーム間での合計
	Fps_Update.waitTime_Ave 	= 0;  			//待機時間の平均
	Fps_Update.fps_Ave 			= 0;  			//平均fps
	Fps_Update.FrameCount 		= 0;
	Fps_Update.FPS 				= UPDATEFPS;
}

int fps::UpdateUpDatefps(){
	Fps_Update.FrameCount++;

	if(Fps_Update.fpsCounter == 0)
		Fps_Update.fpsStart = SDL_GetTicks();
	if(Fps_Update.fpsCounter == (unsigned int)Fps_Update.N){
		unsigned int N = SDL_GetTicks();
		Fps_Update.fps_Ave 		= 1000./((N-Fps_Update.fpsStart)/(double)Fps_Update.N);
		Fps_Update.waitTime_Ave = Fps_Update.waitTime/(double)Fps_Update.N;
		Fps_Update.fpsCounter 	= 0;
		Fps_Update.waitTime 	= 0;
		Fps_Update.fpsStart 	= N;
	}
	Fps_Update.fpsCounter++;
	return 0;
}

int fps::wait_Update(){
	if(Fps_Update.FPS>0){
		int tookTime=SDL_GetTicks()-Fps_Update.fpsStart;
		int waitTime=Fps_Update.fpsCounter*1000.0f/Fps_Update.FPS-tookTime;
		if(waitTime>0)
			Fps_Update.waitTime+=waitTime;
		else
			Fps_Update.waitTime=waitTime;
		if(waitTime>0)
			SDL_Delay(waitTime);
	}
	return 0;
}

void fps::fps_UpdateDeltaTime(){
	static float pt = 0;

	// Calculate time since last call to idle()
	int t = SDL_GetTicks();
	dt = (float)(t - pt) /1000;
	pt = t;

}

float fps::fps_getDeltaTime(){
	return dt;
}

int fps::get_fps_Ave(){
	return Fps_Update.fps_Ave;
}

