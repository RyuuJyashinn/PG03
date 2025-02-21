#pragma once
#include "Bullet.h"

const int MAX_BULLETS = 10;

class Player {
private:
	int posX_;
	int posY_;
	int radius_;
	int speed_;
public:
	Bullet* bullets_[MAX_BULLETS];

public:
	Player(int posX, int posY, int speed, int radius);
	~Player();

	void Draw(int playergraph);
	void Move(char* keys);
	void Update(char* keys, char* prekeys);

	// Getter
	int GetPosX() const { return posX_; }
	int GetPosY() const { return posY_; }
	int GetRadius() const { return radius_; }
	int GetSpeed() const { return speed_; }
	

	
	// Setter
	void SetPosX(int x) { posX_ = x; }
	void SetPosY(int y) { posY_ = y; }
	void SetSpeed(int speed) { speed_ = speed; }
	void SetRadius(int radius) { radius_ = radius; }
};
