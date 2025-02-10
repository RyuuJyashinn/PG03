#pragma once
class Bullet {
public:
	int posX_;
	int posY_;
	int speed_;
	int radius_;
	bool isShot_;

public:
	void Update();
	void Draw();


};