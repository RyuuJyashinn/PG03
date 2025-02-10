#include<Novice.h>
#include"Player.h"
#include"Bullet.h"

void Player::Move(char* keys) {

	if (keys[DIK_W]&&posY_>radius_) {
		Player::posY_ -= Player::speed_;
	}

	if (keys[DIK_S]&&posY_<720-radius_) {
		Player::posY_ += Player::speed_;
	}

	if (keys[DIK_A]&&posX_>radius_) {
		Player::posX_ -= Player::speed_;
	}

	if (keys[DIK_D]&&posX_ < 1280 - radius_) {
		Player::posX_ += Player::speed_;
	}

}

Player::Player(int posX, int posY, int speed, int radius) : posX_(posX), posY_(posY), speed_(speed), radius_(radius) {
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

	if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!bullets_[i]->isShot_) {
				bullets_[i]->isShot_ = true;
				bullets_[i]->posX_ = posX_;
				bullets_[i]->posY_ = posY_;
				break;
			}
		}
	}


	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets_[i]->isShot_) {
			bullets_[i]->Update();
		}
	}
}


void Player::Draw(int playergraph) {
	Novice::DrawSprite(posX_ - 32, posY_ - 32, playergraph, 1.0f, 1.0f, 0.0f, WHITE);

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets_[i]->isShot_) {
			bullets_[i]->Draw();
		}
	}
}