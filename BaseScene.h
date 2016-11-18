#pragma once

#include "Task.h"
#include "ISceneChanger.h"

//シーンの基底クラス。
class BaseScene : public Task {

protected:
    int mImageHandle;                //画像ハンドル格納用変数
    ISceneChanger* mSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス

public :
    BaseScene(ISceneChanger* changer);
    virtual ~BaseScene(){}
    virtual void Initialize() {}    //初期化処理をオーバーライド。
    virtual void Finalize()  ;        //終了処理をオーバーライド。
    virtual void Update() {}        //更新処理をオーバーライド。

    virtual void DrawInitialize() {} ; //描画初期化処理をオーバーライド。
    virtual void DrawFinalize()  {};   //描画終了処理をオーバーライド。
    virtual void Draw() ;            //描画処理をオーバーライド。
};
