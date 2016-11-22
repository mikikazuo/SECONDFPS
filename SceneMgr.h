#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

typedef enum {
	STOP_REQUEST_OFF,
	FINALIZE_TO_DRAWFIN,
	DRAWFIN_TO_SCENECHANGE,
	SCENECHANGE_TO_DRAWINI,
	DRAWINI_TO_INI
}Request_flag;

class SceneMgr : public ISceneChanger, Task {

private:
    BaseScene* mScene;    //シーン管理変数
    eScene mNextScene;    //次のシーン管理変数

public:
    Request_flag get_stop_falag();
    void get_stop_falag(Request_flag next);
    SceneMgr();
    void Initialize() ;		//初期化
    void Finalize() ;			//終了処理
    void Update() ;			//更新
	void DrawInitialize() ;
	void DrawFinalize() ;
    void Draw() ;				//描画

    //引数 nextScene にシーンを変更する
    void ChangeScene(eScene NextScene) ;

};
