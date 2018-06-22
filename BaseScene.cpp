#include "BaseScene.h"
//#include <iostream>

BaseScene::BaseScene(ISceneChanger* changer) :
    mImageHandle(0) {
    mSceneChanger = changer;
}

void BaseScene::Finalize(){

}

void BaseScene::Draw(){

}
