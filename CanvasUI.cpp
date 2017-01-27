/*
 * CanvasUI.cpp
 *
 *  Created on: 2016/11/09
 *      Author: user
 */

#include "CanvasUI.h"
#include "GL/glut.h"
#include "image.h"

#include "player.h"

CanvasUI::CanvasUI() {
	// TODO 自動生成されたコンストラクター・スタブ

}

CanvasUI::~CanvasUI() {
	// TODO Auto-generated destructor stub
}

//計算関連の初期化
void CanvasUI::Initialize(){
	dam = 0;
	a = 100;
	time = 0;
	shakeX = 0;
	shakeY = 0;
	level = 0;

	progress_time = 0;
	progress_per  = 0;

	set = 0;
	del = 0;

	res_time = 0;
	res_per = 0;

	fin_mes = 0;
	fin_time = 0;
	fin_per = 0;

	int i;
	for(i=0;i<5;i++){
		wall_info[i]=100;
	}
}

//描画関連の初期化
void CanvasUI::DrawInitialize(){
	//handle[0]=image_Load("Data/image/capture2.png");
	handle[0]=image_Load("Data/image/assist.png");
	handle[1]=image_Load("Data/image/man.png");
	handle[2]=image_Load("Data/image/man_B.png");
	//handle[3]=image_Load("Data/image/num/level.png");
	handle[4]=image_Load("Data/image/pHP_bar2.png");
	handle[5]=image_Load("Data/image/BULLET_bar2.png");
	handle[6]=image_Load("Data/image/exp_bar.png");

	handle[7]=image_Load("Data/image/level_R.png");
	handle[8]=image_Load("Data/image/level_B.png");

	//HPbar 10-13
	handle[10]=image_Load("Data/image/HP_bar_B.png");//Blue
	handle[11]=image_Load("Data/image/HP_bar_R.png");//Red
	//handle[12]=image_Load("Data/image/HP_bar_tex.png");//質感
	//handle[13]=image_Load("Data/image/HP_bar_frame.png");//枠

	//Wallinfo
	handle[14]=image_Load("Data/image/wall_info.png");//壁情報


	//数字　30-40
	handle[30]=image_Load("Data/image/num/0.png");
	handle[31]=image_Load("Data/image/num/1.png");
	handle[32]=image_Load("Data/image/num/2.png");
	handle[33]=image_Load("Data/image/num/3.png");
	handle[34]=image_Load("Data/image/num/4.png");
	handle[35]=image_Load("Data/image/num/5.png");
	handle[36]=image_Load("Data/image/num/6.png");
	handle[37]=image_Load("Data/image/num/7.png");
	handle[38]=image_Load("Data/image/num/8.png");
	handle[39]=image_Load("Data/image/num/9.png");
	handle[40]=image_Load("Data/image/num/Lv.png");

	handle[41]=image_Load("Data/image/sousa.png");

	//壁進捗バー枠
	handle[42]=image_Load("Data/image/wall_progress_bar.png");
	//リスポーン進捗バー枠
	handle[43]=image_Load("Data/image/message.png");
	//死亡画面エフェクト画像
	handle[44]=image_Load("Data/image/dead_screen1.png");

	//YOU WIN!!
	handle[45]=image_Load("Data/image/you_win.png");
	//YOU LOSE...
	handle[46]=image_Load("Data/image/you_lose.png");

	//スナイパーエフェクト
	handle[47]=image_Load("Data/image/sniper.png");
	handle[48]=image_Load("Data/image/sniper_bar.png");

}


//描画関連の終了処理
void CanvasUI::DrawFinalize(){
	for(int i=0;i<(int)(sizeof handle/sizeof handle[0]);i++)
		image_free(handle[i]);

}


//2D描画用に変換
void CanvasUI::view2D() {
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,w,h,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

//毎フレーム計算
void CanvasUI::Update() {
	time += 1;

	if(time % 150 >= 149){//一定時間ごとに自動ダメージ
		dam = time;
		a -= 5+rand()%20;

		level = rand()%100;

		if(a<0) a=100;

		int i;
		for(i=0;i<5;i++){//壁ダメ変化
			wall_info[i]=rand()%100;
			if(rand()%10==0) wall_info[i]=-1;
		}

	}else{
		//dam = 0;
	}

	if((time-dam)<30){
		if((time-dam)%3 == 0){
			shakeX = rand()%15-7;
			shakeY = rand()%15-7;
		}
	}else{
		shakeX = 0;
		shakeY = 0;
	}

	/***壁に関する動作***/
	//if(壁に関する動作中){
		progress_time++;
		//if(壁設置中){
			progress_per = progress_time / WALL_SET;

			if(progress_time == WALL_SET){
				progress_time = 0;
				//ここで壁設置実行
			}
		//}

		//else if(壁除去中){
			//progress_per = 1 - (progress_time / WALL_DELETE);	//(右から左に減少させるために1から進捗率を引いている)
			if(progress_time == WALL_DELETE){
				//progress_time = 0;
				//ここで壁除去実行
			}
		//}
	//}

	/***リスポーン待機***/
	//if(リスポーン待機中)
		res_time++;

		if(res_time >= RESPAWN_TIME){
			res_time = 0;
			//ここでリスポーン実行処理
		}

		res_per = res_time / RESPAWN_TIME;
	//}

	/***ゲーム終了メッセージ***/
	//if(ゲーム終了 && fin_mes == 0){
		if(fin_mes == 0){//本来は必要ないが動作確認のためのif文
			//fin_mes = 1;	//第一段階開始
		}
	//}

	if(fin_mes != 0){
		fin_time++;
	}
	//次の段階への移行
	if((fin_mes == 1 && fin_time >= FIN_MES1) || (fin_mes == 2 && fin_time >= FIN_MES2)){
		fin_time = 0;
		fin_mes++;
	}

	/***スナイパーモード***/
	/*if(スナイパーモード){
		snipe_per = 現在の数値/最大数値;
	}*/
}


//毎フレーム描画
void CanvasUI::Draw() {
	//ゲーム終了メッセージを表示する際は非表示に
	if(fin_mes == 0){
		//image_DrawExRota(handle[0],500,200,0,1);
		image_DrawExRota(handle[0],600,350,0,1);//照準
	}

	//自陣HP
	glColor3d(1.0,0.2,0.2);//赤指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[11],10+shakeX,10+shakeY,280*0.01*a,60);//ゲージ描画
	glColor3d(0.2,0.2,0.2);//黒指定
	rect_Draw2D(handle[11],10+shakeX+(280*0.01*a),10+shakeY,280*(1-0.01*a),60);//裏ゲージ描画
	image_DrawExRota(handle[11],150+shakeX,50+shakeY,0,1);//HPバー

	//image_DrawExRota(handle[12],150+shakeX,50+shakeY,0,1);//ハイライト,質感
	//image_DrawExRota(handle[13],150+shakeX,50+shakeY,0,1);//枠

	//敵陣HP
	glColor3d(0.2,0.2,1.0);//青指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[9],1190-280*0.01*a+shakeX,10+shakeY,280*0.01*a,60);//ゲージ描画
	glColor3d(0.2,0.2,0.2);//黒指定
	rect_Draw2D(handle[9],910+shakeX,10+shakeY,280*(1-0.01*a),60);//裏ゲージ描画
	image_DrawExRota(handle[10],1050+shakeX,50+shakeY,0,1);//HPバー

	//image_DrawExRota(handle[12],1050+shakeX,50+shakeY,0,1);//ハイライト、質感
	//image_DrawExRota(handle[13],1050+shakeX,50+shakeY,0,1);//枠


	//レベル表示
	//image_DrawExRota(handle[3],75+shakeX,680+shakeY,0,2);//Lv
	//image_DrawExRota(handle[7],75+shakeX,680+shakeY,0,2);//Red
	image_DrawExRota(handle[8],75+shakeX,680+shakeY,0,2);//Blue
	int number1,number10;
	number1 = level%10;//ひとけため
	number10 = (level/10)%10;//ふたけため
	//printf("lv.%d,%d,%d\n",level,number1,number10);
	image_DrawExRota(handle[40],50+shakeX,660+shakeY,0,1);
	image_DrawExRota(handle[30+number1],125+shakeX,660+shakeY,0,1);//1
	image_DrawExRota(handle[30+number10],100+shakeX,660+shakeY,0,1);//10



	glColor3d(1.0*0.01*(100-a),1.0*0.01*a,0);//色指定
	if((time-dam)==0) glColor3d(1.0,1.0,1.0);
	rect_Draw2D(handle[3],210+shakeX,660+shakeY,260*0.01*a,40);//ゲージ描画
	glColor3d(0.0,0.0,0.0);//黒指定
	rect_Draw2D(handle[3],210+shakeX+(260*0.01*a),660+shakeY,(260*(1-0.01*a)),40);//裏ゲージ描画
	image_DrawExRota(handle[4],320+shakeX,680+shakeY,0,1);//playerHP

	glColor3d(0.3,0.5,1.0);
	rect_Draw2D(handle[3],510+shakeX,660+shakeY,260*0.01*a,40);//ゲージ描画
	glColor3d(0.1,0.1,0.1);//黒指定
	rect_Draw2D(handle[3],510+shakeX+(260*0.01*a),660+shakeY,(260*(1-0.01*a)),40);//裏ゲージ描画
	image_DrawExRota(handle[5],620+shakeX,680+shakeY,0,1);//bullet

	glColor3d(0.1,0.8,0.5);
	rect_Draw2D(handle[6],210+shakeX,640+shakeY,260*0.01*a,20);//ゲージ描画
	glColor3d(0.1,0.1,0.1);
	rect_Draw2D(handle[6],210+shakeX+(260*0.01*a),640+shakeY,(260*(1-0.01*a)),40);//裏ゲージ
	image_DrawExRota(handle[6],320+shakeX,650+shakeY,0,1);

	int i;
	for(i=0;i<4;i++){
		image_DrawExRota(handle[1],350+55*i+shakeX,40+shakeY,0,1);
		image_DrawExRota(handle[2],850-55*i+shakeX,40+shakeY,0,1);
	}

	for(i=0;i<5;i++){
		GLdouble R=0,G=0,B=0;
		switch(wall_info[i]){
		case -1:
			R=0.2;
			G=0.2;
			B=0.2;
			break;
		default:
			R=1.0*0.01*(100-wall_info[i]);
			G=1.0*0.01*wall_info[i];
			B=0.0;
			break;
		}


		glColor3d(R,G,B);//青指定
		rect_Draw2D(handle[14],850+(50*i)+shakeX,650+shakeY,34,34);//壁情報ランプ
	}
	image_DrawExRota(handle[14],948+shakeX,668+shakeY,0,1);//壁情報枠


	image_DrawExRota(handle[41],105,540,0,1.0);//Blue

	/***壁設置・除去進捗バー***/
	//if(壁に関する動作中){
		//壁設置中
		//if(壁設置中){
			glColor3d(0.486,1.0,0.333);	//緑指定
			rect_Draw2D(handle[42],510+shakeX,640+shakeY,260 * progress_per,20); //進捗バー(左から右へ増加)
		//}

		//壁除去中
		//else if(壁除去中){
			//glColor3d(1.0,0.2,0.263);		//赤指定
			//rect_Draw2D(handle[42],510+shakeX,640+shakeY,260 * progress_per,20);   //進捗バー(右から左へ減少)
		//}

		glColor3d(0.0,0.0,0.0);		//黒指定
		//引数補足:不要，左上の座標(x,y),横幅，高さ
		rect_Draw2D(handle[42],510+shakeX,640+shakeY,260,20); //裏ゲージ

		//進捗バーの枠表示
		//画像番号，中心の座標(x,y),回転(そのままなら0)，大きさ(等倍なら1)
		image_DrawExRota(handle[42],620+shakeX,650+shakeY,0,1);	//進捗バー枠
	//}

	/***リスポーン待機関連***/
	//if(リスポーン待機中){
		glColor3d(0.444,1.0,0.64);		//緑指定
		//rect_Draw2D(0,380,230,440 * res_per,70); 	//進捗バー
		glColor3d(1.0,0.302,0.302);	//赤指定
		//rect_Draw2D(0,380,230,440,70); 				//裏ゲージ
		//image_DrawExRota(handle[43],600,250,0,0.5);	//枠

		//image_DrawExRota(handle[44],600,350,0,1);	//死亡時(リスポーン待機時)に画面を黒くさせるために用いる画像
	//}

	/***ゲーム終了時***/
	//ゲーム終了メッセージ表示開始
	//if(ゲーム終了 && fin_mes == 0){
	//if(fin_mes == 0)//本来は必要ないが動作確認のためのif文
		//fin_mes = 1;	//第一段階開始
	//}


	//終了メッセージ表示時
		//動作確認
		//printf("fin_mes = %d\n",fin_mes);

		//勝敗に応じてメッセージ表示領域の色変更
		//if(勝利){
			glColor3d(1,1,1);		//白指定
		//}
		//else if(敗北){
			//glColor3d(0,0,0);		//黒指定
		//}

		/***ゲーム終了メッセージ表示(fin_mesは表示段階を示す)***/
		switch(fin_mes){
			case 1:
				fin_per = fin_time / FIN_MES1;
				rect_Draw2D(0,0,348.5,1200 * fin_per,3);	//メッセージ表示領域(横に伸びる)
				break;
			case 2:
				fin_per = fin_time / FIN_MES2;
				rect_Draw2D(0,0,350 - (FIN_MES_HEIGHT * fin_per/2),1200,FIN_MES_HEIGHT * fin_per);	//メッセージ表示領域(縦に伸びる)
				break;
			case 3:
				rect_Draw2D(0,0,350 - FIN_MES_HEIGHT/2,1200,FIN_MES_HEIGHT);	//メッセージ表示領域
				//if(勝利){
					image_DrawExRota(handle[45],600,350,0,1);					//YOU WIN!!表示
				//}
				//if(敗北){
					//image_DrawExRota(handle[46],600,350,0,1); 					//YOU LOSE...表示
				//}
				break;
		}

	//動作確認(本来は 現在の数値/最大数値 にて算出)
	snipe_per = progress_per;

	/***スナイパーモード***/
	//if(スナイパーモード時)
		image_DrawExRota(handle[47],600,350,0,1);	//黒いエフェクト＆倍率バー
		image_DrawExRota(handle[48],1050,600 - 500 * snipe_per,0,1);	//現在の倍率表示
	//}
}


