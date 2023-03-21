#include "snake.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <conio.h>
using namespace std::chrono_literals;
using namespace games;
snake::snake()
{
	for (int i = a.height * a.width / 2, j = i; i < j + 4; ++i) {
		body.push(i);
		collisionDetector.insert(i);
	}
}

void snake::forward()
{
	checkCollision();
	if (!isalive) { return; }
	int i = head() + direction;
	if (a.obstacles.contains(i) && isdigit(a.obstacles.at(i)[0])) {
		body.push(std::stoi(a.obstacles.at(i)));
	}
	else {
		body.push(i);
	}
	collisionDetector.insert(head());
	if (head() != eggPos) {
		collisionDetector.erase(body.front());
		body.pop();
	}
	else {
		eggPos = -1;
	}
	newEggPos();

	moved = true;
}


void snake::checkCollision()
{
	int newPos = head() + direction;
	bool hitBarrier = a.obstacles.contains(newPos) && !isdigit(a.obstacles.at(newPos)[0]);
	
	isalive = !hitBarrier && !collisionDetector.contains(newPos);
}

void snake::setDirection(int dir)
{
	if (dir == direction || dir == -direction) {
		return;
	}
	while (!moved && isalive) {
		std::this_thread::sleep_for(100ms);
	}
	direction = dir;
	moved = false;
}

void snake::print()
{
	printf("\033[2J");
	printf("\033[%d;%dH", 0, 0);
	
	for (int i = 0; i < boardSize; ++i) {
		if (i % a.width == 0) {
			std::cout << '\n';
		}
		if (i == head()) {
			printHead();
		}
		else if (collisionDetector.contains(i) || i == eggPos) {
			std::cout << '.';
		}
		else if (a.obstacles.contains(i) && !isdigit(a.obstacles.at(i)[0])) {
			std::cout << a.obstacles.at(i);
		}
		else if (a.obstacles.contains(i) && isdigit(a.obstacles.at(i)[0])) {
			std::cout << 'O';
		}
		else {
			std::cout << ' ';
		}
	}
}

void snake::printHead()
{
	if (direction == a.width) {
		std::cout << 'v';
	}
	else if (direction == -a.width) {
		std::cout << '^';
	}
	else if (direction == 1) {
		std::cout << '>';
	}
	else {
		std::cout << '<';
	}
}

void snake::newEggPos()
{
	int div = 1 + rand() % 100;
	if (eggPos >= 0 || 5 / div == 0) return;
	do {
		eggPos = rand() % boardSize;
	} while (collisionDetector.contains(eggPos) || a.obstacles.contains(eggPos));

}

enum {
	KEY_UP = 72,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80
};
void nextPos(snake* s) {
	char c, ex;
	int count = 0;
	do {
		c = _getch();
		if (c != char(224)) {
			std::cout << "FOOL!";
		}
		else {
			++count;
			switch (ex = _getch()) {
			case KEY_UP:
				s->setDirection(-52);
				++count;

				break;
			case KEY_LEFT:
				s->setDirection(-1);
				++count;
				break;
			case KEY_DOWN:
				s->setDirection(52);
				++count;
				break;
			case KEY_RIGHT:
				s->setDirection(1);
				++count;
				break;
			}
		}
		if (count > 0) {
			std::this_thread::sleep_for(100ms);
			--count;
		}
	} while (s->healthCheck());
}

void games::run_snake() {
	snake s;
	std::thread keys(nextPos, &s);
	s.print();
	while (s.healthCheck()) {
		s.forward();
		s.print();
		std::this_thread::sleep_for(33.33ms);
	}
	keys.join();
}