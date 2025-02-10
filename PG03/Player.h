#pragma once
#include "Bullet.h"

const int MAX_BULLETS = 10;

class Player {
public:
	int posX_;
	int posY_;
	int radius_;
	int speed_;
	Bullet* bullets_[MAX_BULLETS];
public:
	Player(int posX, int posY, int speed, int radius);
	~Player();

	void Draw(int playergraph);
	void Move(char* keys);
	void Update(char* keys, char* prekeys);
};
