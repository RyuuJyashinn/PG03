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
	double dis = sqrt((enemy->posX_ - bullet->posX_) * (enemy->posX_ - bullet->posX_) +
		(enemy->posY_ - bullet->posY_) * (enemy->posY_ - bullet->posY_));
	return (int)dis <= (enemy->radius_ + bullet->radius_);
}

bool isPlayerHitEnemy(Player* player, Enemy* enemy) {
	double dis = sqrt((player->posX_ - enemy->posX_) * (player->posX_ - enemy->posX_) +
		(player->posY_ - enemy->posY_) * (player->posY_ - enemy->posY_));
	return (int)dis <= (player->radius_ + enemy->radius_);
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Enemy* enemy[4];

	enemy[0] = new Enemy(1,300, 100, 5, 15);
	enemy[1] = new Enemy(1,640, 200, 5, 20);
	enemy[2] = new Enemy(1,100, 300, 5, 15);
	enemy[3] = new Enemy(1,1040, 400, 5, 20);


	Player* player = new Player(600, 640, 5, 20);
	for (int i = 0; i < MAX_BULLETS; i++) {
		player->bullets_[i]->isShot_ = false;
		player->bullets_[i]->posX_ = 0;
		player->bullets_[i]->posY_ = 0;
		player->bullets_[i]->speed_ = 20;
		player->bullets_[i]->radius_ = 10;
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
				if (enemy[i]->isAlive_) {
					enemy[i]->Update();
					if (isPlayerHitEnemy(player, enemy[i])) {
						gameState = GAMEOVER;
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < MAX_BULLETS; j++) {
					if (player->bullets_[j]->isShot_ && enemy[i]->isAlive_ &&
						isBulletHitEnemy(enemy[i], player->bullets_[j])) {
						enemy[i]->isAlive_ = false;
					}
				}
			}
			
			if (!enemy[0]->isAlive_ && !enemy[1]->isAlive_ && !enemy[2]->isAlive_ && !enemy[3]->isAlive_) {
				gameState = GAMECLEAR;
			}
			break;

		case GAMEOVER:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				gameState = TITLE;

				enemy[0]->isAlive_ = true; enemy[0]->posX_ = 300; enemy[0]->posY_ = 100;
				enemy[1]->isAlive_ = true; enemy[1]->posX_ = 640; enemy[1]->posY_ = 200;
				enemy[2]->isAlive_ = true; enemy[2]->posX_ = 100; enemy[2]->posY_ = 300;
				enemy[3]->isAlive_ = true; enemy[3]->posX_ = 1040; enemy[3]->posY_ = 400;

				player->posX_ = 600;
				player->posY_ = 640;

				for (int i = 0; i < MAX_BULLETS; i++) {
					player->bullets_[i]->isShot_ = false;
					player->bullets_[i]->posX_ = 0;
					player->bullets_[i]->posY_ = 0;
				}
			}
			break;

		case GAMECLEAR:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

				gameState = TITLE;

				enemy[0]->isAlive_ = true; enemy[0]->posX_ = 300; enemy[0]->posY_ = 100;
				enemy[1]->isAlive_ = true; enemy[1]->posX_ = 640; enemy[1]->posY_ = 200;
				enemy[2]->isAlive_ = true; enemy[2]->posX_ = 100; enemy[2]->posY_ = 300;
				enemy[3]->isAlive_ = true; enemy[3]->posX_ = 1040; enemy[3]->posY_ = 400;

				player->posX_ = 600;
				player->posY_ = 640;

				for (int i = 0; i < MAX_BULLETS; i++) {
					player->bullets_[i]->isShot_ = false;
					player->bullets_[i]->posX_ = 0;
					player->bullets_[i]->posY_ = 0;
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