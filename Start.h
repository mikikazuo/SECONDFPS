/*
 * Start.h
 *
 *  Created on: 2017/01/19
 *      Author: c501506022
 */

#ifndef START_H_
#define START_H_
#include "BaseScene.h"
#include "ISceneChanger.h"

class Start : public BaseScene{
private:
	int handle[10];
public:
	Start(ISceneChanger* changer);
	virtual ~Start();
    void Initialize();			//初期化処理をオーバーライド。
    void DrawInitialize();
    void Update() ;				//更新処理をオーバーライド。
    void Draw() ;					//描画処理をオーバーライド。
    void DrawFinalize();
    void Finalize();
};

#endif /* START_H_ */
