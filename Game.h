#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"

//ゲーム画面クラス
class Game : public BaseScene {

public :
    Game(ISceneChanger* changer);
    void Initialize() ;    //初期化処理をオーバーライド。
    //void Finalize() override;        //終了処理をオーバーライド。
    void Update() ;        //更新処理をオーバーライド。
    void DrawInitialize();
    void Draw() ;            //描画処理をオーバーライド。
    void DrawFinalize();

};
