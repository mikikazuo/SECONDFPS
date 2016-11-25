#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "map.h"
#include "mob.h"
#include "player.h"


//ゲーム画面クラス
class Game : public BaseScene {

public :
    Game(ISceneChanger* changer);
    void Initialize();			//初期化処理をオーバーライド。
    //void Finalize() override;		//終了処理をオーバーライド。
    map get_map();
    void Update() ;				//更新処理をオーバーライド。
    void setInfoPlayerWall();
    void DrawInitialize();
    void Draw() ;					//描画処理をオーバーライド。
    void DrawFinalize();

};

map *get_mapobj();
Wall **get_allplayerwall();
player *get_player();
mob *get_mober();
int get_mobernum();
