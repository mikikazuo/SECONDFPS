#include "Game.h"
#include "SceneMgr.h"
#include "Start.h"


Request_flag stop_flag=STOP_REQUEST_OFF;
eScene mNextScene;    //次のシーン管理変数

Request_flag SceneMgr::get_stop_falag(){
	return stop_flag;
}

void SceneMgr::get_stop_falag(Request_flag next){
	stop_flag=next;
}
SceneMgr::SceneMgr() //:
		//mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Start(this);
}

//初期化
void SceneMgr::Initialize(){

	mScene->Initialize();

}

//終了処理
void SceneMgr::Finalize(){
	mScene->Finalize();

}

void SceneMgr::DrawInitialize(){
	mScene->DrawInitialize();
}

void SceneMgr::DrawFinalize(){
	mScene->DrawFinalize();
}
//更新
void SceneMgr::Update(){

	if(mNextScene != eScene_None){    //次のシーンがセットされていたら
		switch(stop_flag){
		case STOP_REQUEST_OFF:
			mScene->Finalize();//現在のシーンの終了処理を実行
			stop_flag=FINALIZE_TO_DRAWFIN;
			break;
		case DRAWFIN_TO_SCENECHANGE:
			delete mScene;
			{
				switch(mNextScene){       //シーンによって処理を分岐
				case eScene_Menu:        //次の画面がメニューなら
					mScene = (BaseScene*) new Start(this);
					break;//以下略
				case eScene_Game:
					mScene = (BaseScene*) new Game(this);
					break;
				case eScene_Config:

					break;
				default:
					break;
				}
				stop_flag=SCENECHANGE_TO_DRAWINI;
			}
			break;

		case DRAWINI_TO_INI:
			mNextScene = eScene_None;    //次のシーン情報をクリア
			mScene->Initialize();    //シーンを初期化
			stop_flag=STOP_REQUEST_OFF;
			break;
		default:
			break;
		}




	}

	mScene->Update(); //シーンの更新
}

//描画
void SceneMgr::Draw(){

	//フェーズ移行　一時停止処理
	switch(stop_flag){
	case FINALIZE_TO_DRAWFIN:
		mScene->DrawFinalize();
		stop_flag=DRAWFIN_TO_SCENECHANGE;
		break;
	case SCENECHANGE_TO_DRAWINI:
		mScene->DrawInitialize();
		stop_flag=DRAWINI_TO_INI;
		break;

	default:
		break;
	}


	if(stop_flag==STOP_REQUEST_OFF)
		mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;    //次のシーンをセットする

}
