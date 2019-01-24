#include <iostream>
#include <ctime>
#include "SnowBall.h"

SnowBall::SnowBall()
{
	setX(0);
	setY(0);
	setStepX(10);
	setStepY(10);
	setDiagonalStepTotal(5);
	diagonalStepCounter = 0;
	generateDirection();
	setSize(10);

	setBorderX(640);
	setBorderY(480);
}

SnowBall::SnowBall(int _stepX, int _stepY, int _diagonalStepTotal, int _size, int _borderX, int _borderY)
{
	setX(0);
	setY(0);
	setStepX(_stepX);
	setStepY(_stepY);
	setDiagonalStepTotal(_diagonalStepTotal);
	diagonalStepCounter = 0;
	generateDirection();
	setSize(_size);

	setBorderX(_borderX);
	setBorderY(_borderY);
}

SnowBall::~SnowBall()
{
	/*nothing to do*/
}

void SnowBall::setX(int _x)
{
	x = _x;
}

int SnowBall::getX()
{
	return x;
}

void SnowBall::setY(int _y)
{
	y = _y;
}

int SnowBall::getY()
{
	return y;
}

void SnowBall::generateDirection()
{
	int dir = rand() % 2 + 1;
	if (dir == 1)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}

}

void SnowBall::setStepX(int _stepX)
{
	stepX = _stepX;
}

int SnowBall::getStepX()
{
	return stepX;
}

void SnowBall::setStepY(int _stepY)
{
	stepY = _stepY;
}

int SnowBall::getStepY()
{
	return stepY;
}

void SnowBall::setBorderX(int _borderX)
{
	borderX = _borderX;
}

int SnowBall::getBorderX()
{
	return borderX;
}

void SnowBall::setBorderY(int _borderY)
{
	borderY = _borderY;
}

int SnowBall::getBorderY()
{
	return borderY;
}

void SnowBall::setDiagonalStepTotal(int _diagonalStepTotal)
{
	diagonalStepTotal = _diagonalStepTotal;
}

int SnowBall::getDiagonalStepTotal()
{
	return diagonalStepTotal;
}


void SnowBall::setSize(int _size)
{
	size = _size;
}

int SnowBall::getSize()
{
	return size;
}

void SnowBall::move()
{
	if ((getBorderY() <= getY()) || (0 >= getY()))
	{
		setY(0);
		setX(rand() % getBorderX());
	}

	setY(getY() + getStepY());
	setX(getX() + direction*getStepX());
	diagonalStepCounter++;

	if (diagonalStepCounter >= diagonalStepTotal)
	{
		direction  =-1 * direction;
	}


}

