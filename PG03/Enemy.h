#pragma once
class Enemy {
public:
	int isAlive_;
	int posX_;
	int posY_;
	int radius_;
	int speed_;
public:
	Enemy(int isAlive,int posX, int posY, int speed, int radius) : isAlive_(isAlive),posX_(posX), posY_(posY), speed_(speed), radius_(radius) {};
	void Update();
	void Draw(int enemygraph);
	void Reset(char* keys);
};
