#pragma once

class Enemy {
private:
	bool isAlive_;
	int posX_;
	int posY_;
	int radius_;
	int speed_;

public:
	Enemy(bool isAlive, int posX, int posY, int speed, int radius);

	void Update();
	void Draw(int enemygraph);
	void Reset(char* keys);

	// Getter
	bool GetIsAlive() const { return isAlive_; }
	int GetPosX() const { return posX_; }
	int GetPosY() const { return posY_; }
	int GetRadius() const { return radius_; }
	int GetSpeed() const { return speed_; }

	// Setter
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }
	void SetPosX(int x) { posX_ = x; }
	void SetPosY(int y) { posY_ = y; }
	void SetSpeed(int speed) { speed_ = speed; }
};
