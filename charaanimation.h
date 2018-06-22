/*
 * charaanimation.h
 *
 *  Created on: 2016/12/16
 *      Author: c501506022
 */

#ifndef CHARAANIMATION_H_
#define CHARAANIMATION_H_

class chara_animation {
public:
	chara_animation();
    void Initialize();			//初期化処理をオーバーライド。
    void Update() ;				//更新処理をオーバーライド。
    void DrawInitialize();
    void Draw() ;					//描画処理をオーバーライド。
    void walk(int model_no,double x,double y,double z,int player_no);
    void DrawFinalize();
	virtual ~chara_animation();
};

#endif /* CHARAANIMATION_H_ */
