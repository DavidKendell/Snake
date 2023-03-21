#include "snake.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <windows.h>

int main() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
	srand(time(0));
	games::run_snake();
}