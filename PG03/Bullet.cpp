#include<Novice.h>
#include"Bullet.h"
#include"Player.h"



void Bullet::Update() {
	if (Bullet::isShot_) {
		Bullet::posY_ -= Bullet::speed_;
	}

	if (Bullet::posY_ < 0) {
		Bullet::isShot_ = false;
	}
}

void Bullet::Draw() {
	if (Bullet::isShot_) {
		Novice::DrawEllipse(Bullet::posX_, Bullet::posY_, Bullet::radius_, Bullet::radius_, 0.0f, GREEN, kFillModeSolid);
	}
}