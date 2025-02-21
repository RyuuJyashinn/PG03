#include <Novice.h>
#include "Bullet.h"

Bullet::Bullet(int posX, int posY, int speed, int radius, bool isShot)
	: posX_(posX), posY_(posY), speed_(speed), radius_(radius), isShot_(isShot) {}

void Bullet::Update() {
	if (GetIsShot()) {
		SetPosY(GetPosY() - GetSpeed());
	}

	if (GetPosY() < 0) {
		SetIsShot(false);
	}
}

void Bullet::Draw() {
	if (GetIsShot()) {
		Novice::DrawEllipse(GetPosX(), GetPosY(), GetRadius(), GetRadius(), 0.0f, GREEN, kFillModeSolid);
	}
}
