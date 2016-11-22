/*
 * sound.h
 *
 *  Created on: 2016/11/18
 *      Author: c501506022
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "glm.h"

enum SOUND{
	BGM,
	SE
};
//BGMの種類
enum SOUND_BGM{
	BGM_1,
	BGM_2,
	BGM_TITLE,
	BGM_DRAW,
	BGM_PLAY,
	BGM_RESULT,
	BGM_GAMEOVER

};

void setMobSound(int no,vec3 pos);
void setPlayerListen(vec3 pos,vec3 dir);

void PlayMobMusic(int no);
extern void ChangeBGM(int change_buff);
extern void SoundInit();
extern void PlayMusic(int src_no);
extern void StopMusic(int src_no) ;
extern void PauseMusic(int src) ;
extern void PlayMusicPosition(int src_no, double x, double y);
extern void ChangeSE(int next_se);



#endif /* SOUND_H_ */
