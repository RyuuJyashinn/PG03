#pragma once

class Bullet {
private:
	int posX_;
	int posY_;
	int speed_;
	int radius_;
	bool isShot_;

public:
	Bullet(int posX = 0, int posY = 0, int speed = 10, int radius = 5, bool isShot = false);

	void Update();
	void Draw();

	// Getter
	int GetPosX() const { return posX_; }
	int GetPosY() const { return posY_; }
	int GetSpeed() const { return speed_; }
	int GetRadius() const { return radius_; }
	bool GetIsShot() const { return isShot_; }

	// Setter
	void SetPosX(int x) { posX_ = x; }
	void SetPosY(int y) { posY_ = y; }
	void SetSpeed(int speed) { speed_ = speed; }
	void SetRadius(int radius) { radius_ = radius; }
	void SetIsShot(bool isShot) { isShot_ = isShot; }
};
