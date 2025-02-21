#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy(bool isAlive, int posX, int posY, int speed, int radius)
	: isAlive_(isAlive), posX_(posX), posY_(posY), speed_(speed), radius_(radius) {}

void Enemy::Reset(char* keys) {
	if (keys[DIK_R]) {
		SetIsAlive(true);
	}
}

void Enemy::Update() {
	if (GetIsAlive()) {
		SetPosX(GetPosX() + GetSpeed());

		if (GetPosX() > 1260 || GetPosX() < 20) {
			SetSpeed(-GetSpeed());
		}
	}
}

void Enemy::Draw(int enemygraph) {
	if (GetIsAlive()) {
		Novice::DrawSprite(GetPosX() - 32, GetPosY() - 32, enemygraph, 1.0f, 1.0f, 0.0f, WHITE);
	}
}
