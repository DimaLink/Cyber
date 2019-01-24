#pragma once
#ifndef SNOWBALL_H
#define SNOWBALL_H


class SnowBall
{
public:
	SnowBall();
	SnowBall(int _stepX, int _stepY, int _diagonalStepTotal, int _size, int _borderX, int _borderY);
	~SnowBall();
	void move();

	void setX(int);
	int getX();
	void setY(int);
	int getY();

	void setStepX(int);
	int getStepX();

	void setStepY(int);
	int getStepY();

	void setDiagonalStepTotal(int);
	int getDiagonalStepTotal();

	void setBorderX(int);
	int getBorderX();

	void setBorderY(int);
	int getBorderY();

	void setSize(int);
	int getSize();


private:
	void generateDirection();

	int x;
	int y;
	int stepX;
	int stepY;
	int diagonalStepCounter;
	int diagonalStepTotal;
	int direction;
	int size;

	int borderX;
	int borderY;


};

#endif
