#include "Enemy.h"
#include<Novice.h>

void Enemy::Reset(char* keys) {
	if (keys[DIK_R]) {

		isAlive_ = true;
	}


}

void Enemy::Update() {
	if (isAlive_) {
		posX_ += speed_;
		if (posX_ > 1260 || posX_ < 20) {
			speed_ = -speed_;
		}
	}

}

void Enemy::Draw(int enemygraph) {
	if (isAlive_) {
		Novice::DrawSprite(static_cast<int>(Enemy::posX_-32), static_cast<int>(Enemy::posY_-32), enemygraph, 1.0f, 1.0f, 0.0f, WHITE);
	}

}