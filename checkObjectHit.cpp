/*
 * checkObjectHit.cpp
 *
 *  Created on: 2016/09/21
 *      Author: user
 */

#include "checkObjectHit.h"
#include <math.h>

//動作確認のため追加??
#include <stdio.h>


checkObjectHit::checkObjectHit() {
	// TODO 自動生成されたコンストラクター・スタブ

}

checkObjectHit::~checkObjectHit() {
	// TODO Auto-generated destructor stub
}

//1：壁やマップオブジェクトの数　2：壁やオブジェクトそのもの　3：点座標  4：点座標から広がる半径
bool checkObjectHit::sethitcheck(int num,object *obb,vec3 pointpos,float radi){
	bool hit=false;

	for(int i=0;i<num;i++)
		if(	LenOBBToPoint( obb[i],  pointpos)<=radi ){
			hit=true;
			break;
		}
	return hit;
}

bool checkObjectHit::sethitcheck(int num,Wall *obb,vec3 pointpos,float radi){
	bool hit=false;

	for(int i=0;i<num;i++)
		if(	LenOBBToPoint( obb[i].wall,  pointpos)<=radi ){
			hit=true;
			break;
		}
	return hit;
}


bool checkObjectHit::pointVsPoint(vec3 pointpos1,vec3 pointpos2,float radi){

	float xd=pow(pointpos1.x-pointpos2.x,2);
	float yd=pow(pointpos1.y-pointpos2.y,2);
	float zd=pow(pointpos1.z-pointpos2.z,2);
	float rd=pow(radi,2);

	return rd>=xd+yd+zd?true:false;
}



bool checkObjectHit::alphaOBBs( OBB &obb1,object &obb2 )
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	vec3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
	vec3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
	vec3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
	vec3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
	vec3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
	vec3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
	vec3 Interval = obb1.GetPos_W() - obb2.GetPos_W();

	// 分離軸 : Ae1
	float rA = Vec3Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	float L = fabs(Dot( &Interval, &NAe1 ));
	if( L > rA + rB )
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = Vec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Ae3
	rA = Vec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &NAe3 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be1 );
	L = fabs(Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be2 );
	L = fabs(Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be3 );
	L = fabs(Dot( &Interval, &NBe3 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C11
	vec3 cross;
	crossFunc( &cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C12
	crossFunc( &cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C13
	crossFunc( &cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C21
	crossFunc( &cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C22
	crossFunc( &cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C23
	crossFunc( &cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C31
	crossFunc( &cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C32
	crossFunc( &cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C33
	crossFunc( &cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

bool checkObjectHit::ColOBBs( object &obb1,object &obb2 )
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	vec3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
	vec3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
	vec3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
	vec3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
	vec3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
	vec3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
	vec3 Interval = obb1.GetPos_W() - obb2.GetPos_W();

	// 分離軸 : Ae1
	float rA = Vec3Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	float L = fabs(Dot( &Interval, &NAe1 ));
	if( L > rA + rB )
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = Vec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &NAe2 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Ae3
	rA = Vec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &NAe3 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be1 );
	L = fabs(Dot( &Interval, &NBe1 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be2 );
	L = fabs(Dot( &Interval, &NBe2 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = Vec3Length( &Be3 );
	L = fabs(Dot( &Interval, &NBe3 ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C11
	vec3 cross;
	crossFunc( &cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C12
	crossFunc( &cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C13
	crossFunc( &cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C21
	crossFunc( &cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C22
	crossFunc( &cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C23
	crossFunc( &cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C31
	crossFunc( &cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be2, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C32
	crossFunc( &cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be3 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離軸 : C33
	crossFunc( &cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &cross, &Be1, &Be2 );
	L = fabs(Dot( &Interval, &cross ));
	if( L > rA + rB )
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

//オブジェクトとの当たり判定をする際に用いる関数
//&obb:判定対象のオブジェクト
//pointpos:プレイヤーの当たり判定対象座標
//返却値:オブジェクトとプレイヤーの当たり判定座標の間の距離
float checkObjectHit::LenOBBToPoint(object &obb, vec3 pointpos)
{
	vec3 samp;   //最終的に長さを求めるベクトル

	//各軸についてはみ出た部分のベクトルを算出
	for(int i=0; i<3; i++)
	{
		//x,y,z軸それぞれの中心までの長さを取得(各軸方向の長さの半分を取得)
		float L = obb.GetLen_W(i);
		//Lが0以下のとき
		if( L <= 0 ){
			continue;
		}

		//プレイヤーの当たり判定座標 - オブジェクトの座標
		//この値がプレイヤーの当たり判定の半径より小さいと衝突
		//sa:差
		vec3 sa	 = pointpos - obb.GetPos_W();
		//動作確認
		/*if(i == 1){
			printf("i = %d sa.x = %lf\n",i,sa.x);
		}*/

		//x,y,z軸の単位方向ベクトルを格納
		vec3 dir = obb.GetDirect(i);

		//sに saとdirの内積 を 各軸方向の長さの半分 で割った値を格納
		float s = Dot(&sa, &dir) / L;

		//sの値から、はみ出した部分があればそのベクトルを加算
		s = fabs(s);	//絶対値を取得
		if(s > 1)
			//1−sの値は必ず負の値をとる
			samp += obb.GetDirect(i)*(1-s)*L;   //はみ出した部分のベクトル算出
	}

	//ベクトルの大きさを返す
	return Vec3Length(&samp);
}


float checkObjectHit::LenOBBToPoint_move(object &obb, vec3 pointpos)
{
	vec3 samp;   //最終的に長さを求めるベクトル

	//各軸についてはみ出た部分のベクトルを算出
	for(int i=0; i<3; i++)
	{
		//x,y,z軸それぞれの中心までの長さを取得(各軸方向の長さの半分を取得)
		float L = obb.GetLen_W(i);
		//Lが0以下のとき
		if( L <= 0 ){
			continue;
		}

		//プレイヤーの当たり判定座標 - オブジェクトの座標
		//この値がプレイヤーの当たり判定の半径より小さいと衝突
		//sa:差
		vec3 sa	 = pointpos - obb.Pos_move;
		sa.y--;
		//動作確認
		/*if(i == 1){
			printf("i = %d sa.x = %lf\n",i,sa.x);
		}*/

		//x,y,z軸の単位方向ベクトルを格納
		vec3 dir = obb.GetDirect(i);

		//sに saとdirの内積 を 各軸方向の長さの半分 で割った値を格納
		float s = Dot(&sa, &dir) / L;

		//sの値から、はみ出した部分があればそのベクトルを加算
		s = fabs(s);	//絶対値を取得
		if(s > 1)
			//1−sの値は必ず負の値をとる
			samp += obb.GetDirect(i)*(1-s)*L;   //はみ出した部分のベクトル算出
	}

	//ベクトルの大きさを返す
	return Vec3Length(&samp);
}


