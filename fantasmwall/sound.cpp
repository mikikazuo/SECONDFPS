/*
 * sound.c
 *
 *  Created on: 2016/01/19
 *      Author: c501406006
 */
#include "sound.h"
#include <cstddef>
#include <AL/al.h>
#include <AL/alure.h>
#include "net_common.h"

#define MAXSE 20

static ALuint bgm_src;
static ALuint se_src[MAXSE];
static ALuint bgm_buf1, bgm_buf2, bgm_buf3, bgm_buf4, bgm_buf5, bgm_buf6,bgm_buf7;
static ALuint se_buf[MAXSE];
//static int NowPlaying = 0;//現在再生しているBGM
static int se_now;


ALuint mobsources[MOBNUM];

void setMobSound(int no,vec3 pos){
    alSource3f(mobsources[no], AL_POSITION,pos.x,pos.y,pos.z );
   // alSource3f(mobsources[no], AL_ORIENTATION,pos.x,pos.y,pos.z );

}
void setPlayerListen(vec3 pos,vec3 dir){
	  ALfloat listenerPos[] = {pos.x, pos.y, pos.z};
	  ALfloat listenerOri[] = {dir.x, dir.y, dir.z, 0.0, 1.0, 0.0}; // look.x.y.z / up.x.y.z
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_ORIENTATION, listenerOri);

}
void SoundInit() {
	// まず最初にALUREを初期化
	if (!alureInitDevice(NULL, NULL)) {
	}

	// 音源を作成
	alGenSources(1, &bgm_src);
	int i;
	for (i = 0; i < MAXSE; i++) {
		alGenSources(1, &se_src[i]);
	}

	 alGenSources(MOBNUM, mobsources); //空間に配置する数の分生成する.

	//音量の設定
	alSourcef(bgm_src, AL_GAIN, 1);

	alSourcei(bgm_src, AL_LOOPING, AL_TRUE); // ループの設定

	//	音の登録
	bgm_buf1 = alureCreateBufferFromFile("Data/BGM/aa.wav");
	bgm_buf2 = alureCreateBufferFromFile("Data/BGM/bbb.wav");
	bgm_buf3 = alureCreateBufferFromFile("Data/BGM/noranekonokuchibue.wav");
	bgm_buf4 = alureCreateBufferFromFile("Data/BGM/retrogamecenter.wav");
	bgm_buf5 = alureCreateBufferFromFile("Data/BGM/ryunomai.wav");
	bgm_buf6 = alureCreateBufferFromFile("Data/BGM/famipop3.wav");
	bgm_buf7 = alureCreateBufferFromFile("Data/BGM/sousou3.wav");
	alSourcei(bgm_src, AL_BUFFER, bgm_buf1); // 音データのバッファを指定

	se_buf[0] = alureCreateBufferFromFile("Data/SE/ccc.wav");
	se_buf[1] = alureCreateBufferFromFile("Data/SE/good.wav");
	se_buf[2] = alureCreateBufferFromFile("Data/SE/ok.wav");
	se_buf[3] = alureCreateBufferFromFile("Data/SE/bad.wav");
	se_buf[4] = alureCreateBufferFromFile("Data/SE/decide.wav");
	se_buf[5] = alureCreateBufferFromFile("Data/SE/select.wav");
	se_buf[6] = alureCreateBufferFromFile("Data/SE/sp.wav");
	se_buf[7] = alureCreateBufferFromFile("Data/SE/nomp.wav");
	se_buf[8] = alureCreateBufferFromFile("Data/SE/start.wav");
	se_buf[9] = alureCreateBufferFromFile("Data/SE/taiko.wav");
	se_buf[10] = alureCreateBufferFromFile("Data/SE/result.wav");
	se_buf[11] = alureCreateBufferFromFile("Data/SE/moveup.wav");
	se_buf[12] = alureCreateBufferFromFile("Data/SE/movedown.wav");
	se_buf[13] = alureCreateBufferFromFile("Data/SE/attack.wav");
	se_buf[14] = alureCreateBufferFromFile("Data/SE/miss.wav");
	se_buf[15] = alureCreateBufferFromFile("Data/SE/charging.wav");
	se_buf[16] = alureCreateBufferFromFile("Data/SE/charged.wav");
	se_buf[17] = alureCreateBufferFromFile("Data/SE/efe.wav");
	se_buf[17] = alureCreateBufferFromFile("Data/SE/heavy-machine-gun1.wav");
//	se_buf[18] = alureCreateBufferFromFile("Data/sound/se/se_extend.wav");
//	se_buf[19] = alureCreateBufferFromFile("Data/sound/se/se_cardget.wav");
	for (i = 0; i < MAXSE; i++) {
		alSourcei(se_src[i], AL_BUFFER, se_buf[i]);
	}

	for (int j = 0; j < (int)(sizeof(mobsources)/sizeof(mobsources[0])); j++) {
			alSourcei(mobsources[j], AL_BUFFER, se_buf[0]);
		}
}

void PlayMobMusic(int no){
	alSourcePlay(mobsources[no]);
}
void PlayMusic(int src_no) {
	switch (src_no) {
	case BGM:
		alSourcePlay(bgm_src);
		break;
	case SE:
		alSourcePlay(se_src[se_now]);
		break;
	default: //効果音系は普通に分かるので
		if (0 <= src_no - 21 && src_no - 21 < MAXSE)
			alSourcePlay(se_src[src_no - 21]);
		break;
	}
}

void StopMusic(int src_no) {
	switch (src_no) {
	case BGM:
		alSourceStop(bgm_src);
		break;
	default: //効果音系は普通に分かるので
		//if (0 <= src_no - 21 && src_no - 21 < MAXSE)
			alSourceStop(se_src[src_no /*- 21*/]);
		break;
	}
}

void PauseMusic(int src) {
	switch (src) {
	case BGM:
		alSourcePause(bgm_src);
		break;
	default: //効果音系は普通に分かるので
	//	if (0 <= src - 21 && src - 21 < MAXSE)
			alSourcePause(se_src[src /*- 21*/]);
		break;
	}
}

void ChangeBGM(int change_buff) {

	StopMusic(BGM);
	switch (change_buff) {
	case BGM_1:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf1);
		break;
	case BGM_2:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf2);
		break;
	case BGM_TITLE:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf3);
		break;
	case BGM_DRAW:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf4);
		break;
	case BGM_PLAY:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf5);
		break;
	case BGM_RESULT:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf6);
		break;
	case BGM_GAMEOVER:
		alSourcei(bgm_src, AL_BUFFER, bgm_buf7);
		break;
	default:
		break;
	}
	PlayMusic(BGM);
}

void ChangeSE(int next_se){
	se_now=next_se;
	PlayMusic(SE);
}
void PlayMusicPosition(int src_no, double x, double y) {
	switch (src_no) {
	case BGM:

		break;
	case SE:

		//alSource3f(se_src[0], AL_POSITION, (x / WINDOW_WIDE* 2 - 1) * 2, 0, 2);


		break;
	}
	PlayMusic(src_no);
}
