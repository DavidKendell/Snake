#include <queue>
#include <unordered_set>
#include <iostream>
#include "arena.h"
#pragma once

namespace games {
	class snake
	{

	public:
		snake();
		void forward();
		void checkCollision();
		int& head() { return body.back(); }
		void setDirection(int dir);
		bool healthCheck() { return isalive; }
		void print();
		void getBoardSize() { std::cout << eggPos; }

	private:
		arena a;
		void printHead();
		void newEggPos();
		bool moved = false;
		std::queue<int> body;
		std::unordered_set<int> collisionDetector;
		bool isalive = true;
		//const int width = 52;
		//const int height = 20;
		const int boardSize = a.width * a.height;
		int eggPos = a.width + 5;

		int direction = 1;
	};

	void run_snake();
}