#include <Novice.h>
#include "Player.h"
#include "Bullet.h"

void Player::Move(char* keys) {
	if (keys[DIK_W] && GetPosY() > GetRadius()) {
		SetPosY(GetPosY() - GetSpeed());
	}

	if (keys[DIK_S] && GetPosY() < 720 - GetRadius()) {
		SetPosY(GetPosY() + GetSpeed());
	}

	if (keys[DIK_A] && GetPosX() > GetRadius()) {
		SetPosX(GetPosX() - GetSpeed());
	}

	if (keys[DIK_D] && GetPosX() < 1280 - GetRadius()) {
		SetPosX(GetPosX() + GetSpeed());
	}
}

Player::Player(int posX, int posY, int speed, int radius)
	: posX_(posX), posY_(posY), speed_(speed), radius_(radius) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullets_[i] = new Bullet();
	}
}

Player::~Player() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		delete bullets_[i];
	}
}

void Player::Update(char* keys, char* prekeys) {
	Move(keys);

	// 按下空格键时发射子弹
	if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!bullets_[i]->GetIsShot()) {  
				bullets_[i]->SetIsShot(true); 
				bullets_[i]->SetPosX(GetPosX()); 
				bullets_[i]->SetPosY(GetPosY()); 
				break;
			}
		}
	}


	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets_[i]->GetIsShot()) {
			bullets_[i]->Update();
		}
	}
}

void Player::Draw(int playergraph) {
	Novice::DrawSprite(GetPosX() - 32, GetPosY() - 32, playergraph, 1.0f, 1.0f, 0.0f, WHITE);

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets_[i]->GetIsShot()) {  
			bullets_[i]->Draw();
		}
	}
}
