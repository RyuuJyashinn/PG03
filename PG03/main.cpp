#include <Novice.h>
#include"Enemy.h"
#include"Player.h"
#include"Bullet.h"
#include<cmath>
const char kWindowTitle[] = "学籍番号";

enum GameState {
	TITLE,
	PLAY,
	GAMEOVER,
	GAMECLEAR
};

bool isBulletHitEnemy(Enemy* enemy, Bullet* bullet) {
	double dis = sqrt(pow(enemy->GetPosX() - bullet->GetPosX(), 2) +
		pow(enemy->GetPosY() - bullet->GetPosY(), 2));
	return dis <= (enemy->GetRadius() + bullet->GetRadius());
}

bool isPlayerHitEnemy(Player* player, Enemy* enemy) {
	double dis = sqrt(pow(player->GetPosX() - enemy->GetPosX(), 2) +
		pow(player->GetPosY() - enemy->GetPosY(), 2));
	return dis <= (player->GetRadius() + enemy->GetRadius());
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Enemy* enemy[4];
	enemy[0] = new Enemy(true, 300, 100, 5, 15);  
	enemy[1] = new Enemy(true, 640, 200, 5, 20);
	enemy[2] = new Enemy(true, 100, 300, 5, 15);
	enemy[3] = new Enemy(true, 1040, 400, 5, 20);

	Player* player = new Player(600, 640, 5, 20);
	for (int i = 0; i < MAX_BULLETS; i++) {
		player->bullets_[i]->SetIsShot(false);  
		player->bullets_[i]->SetPosX(0);        
		player->bullets_[i]->SetPosY(0);        
		player->bullets_[i]->SetSpeed(20);      
		player->bullets_[i]->SetRadius(10);     
	}

	int backGraph = Novice::LoadTexture("./images/room.png");
	int titleGraph = Novice::LoadTexture("./images/title.png");
	int gameclearGraph = Novice::LoadTexture("./images/gameclear.png");
	int gameoverGraph = Novice::LoadTexture("./images/gameover.png");

	int enemyGraph = Novice::LoadTexture("./images/enemy.png");
	int playerGraph = Novice::LoadTexture("./images/player.png");


	GameState gameState = TITLE;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		switch (gameState) {
		case TITLE:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				gameState = PLAY;
			}
			Novice::DrawSprite(0, 0, titleGraph, 1.0f, 1.0f, 0.0f, WHITE);
			break;

		case PLAY:
			player->Update(keys, preKeys);
			for (int i = 0; i < 4; i++) {
				if (enemy[i]->GetIsAlive()) { 
					enemy[i]->Update();
					if (isPlayerHitEnemy(player, enemy[i])) {
						gameState = GAMEOVER;
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < MAX_BULLETS; j++) {
					if (player->bullets_[j]->GetIsShot() &&  
						enemy[i]->GetIsAlive() &&            
						isBulletHitEnemy(enemy[i], player->bullets_[j]))
					{
						enemy[i]->SetIsAlive(false);  
					}
				}
			}

			if (!enemy[0]->GetIsAlive() &&  
				!enemy[1]->GetIsAlive() &&
				!enemy[2]->GetIsAlive() &&
				!enemy[3]->GetIsAlive())
			{
				gameState = GAMECLEAR;
			}
			break;

		case GAMEOVER:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				gameState = TITLE;

				enemy[0]->SetIsAlive(true);  
				enemy[0]->SetPosX(300);      
				enemy[0]->SetPosY(100);      

				enemy[1]->SetIsAlive(true);  
				enemy[1]->SetPosX(640);      
				enemy[1]->SetPosY(200);      

				enemy[2]->SetIsAlive(true);  
				enemy[2]->SetPosX(100);      
				enemy[2]->SetPosY(300);      

				enemy[3]->SetIsAlive(true);  
				enemy[3]->SetPosX(1040);     
				enemy[3]->SetPosY(400);      

				player->SetPosX(600); 
				player->SetPosY(640); 


				for (int i = 0; i < MAX_BULLETS; i++) {
					player->bullets_[i]->SetIsShot(false);
					player->bullets_[i]->SetPosX(0);      
					player->bullets_[i]->SetPosY(0);      
				}
			}
			break;

		case GAMECLEAR:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				gameState = TITLE;

				enemy[0]->SetIsAlive(true);  
				enemy[0]->SetPosX(300);      
				enemy[0]->SetPosY(100);      

				enemy[1]->SetIsAlive(true);  
				enemy[1]->SetPosX(640);      
				enemy[1]->SetPosY(200);      

				enemy[2]->SetIsAlive(true);  
				enemy[2]->SetPosX(100);      
				enemy[2]->SetPosY(300);      

				enemy[3]->SetIsAlive(true);  
				enemy[3]->SetPosX(1040);     
				enemy[3]->SetPosY(400);      

				player->SetPosX(600); 
				player->SetPosY(640); 


				for (int i = 0; i < MAX_BULLETS; i++) {
					player->bullets_[i]->SetIsShot(false);
					player->bullets_[i]->SetPosX(0);      
					player->bullets_[i]->SetPosY(0);      
				}
			}
			break;

		}
		///
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
			switch (gameState) {
			case TITLE:
				Novice::DrawSprite(0, 0, titleGraph, 1.0f, 1.0f, 0.0f, WHITE);
				break;

			case PLAY:
				Novice::DrawSprite(0, 0, backGraph, 1.0f, 1.0f, 0.0f, WHITE);

				for (int k = 0; k < 4; k++) {
					enemy[k]->Draw(enemyGraph);

				}
				player->Draw(playerGraph);

				
				break;

			case GAMEOVER:
				Novice::DrawSprite(0, 0, gameoverGraph, 1.0f, 1.0f, 0.0f, WHITE);
				break;

			case GAMECLEAR:
				Novice::DrawSprite(0, 0, gameclearGraph, 1.0f, 1.0f, 0.0f, WHITE);

				break;
			}
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete enemy[0];
	delete enemy[1];

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}