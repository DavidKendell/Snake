#include "arena.h"

arena::arena() : width(52), height(20)
{
	for (int i = 0; i < width; ++i) {
		obstacles.emplace(std::make_pair(i, "_"));
	}
	for (int i = width * (height - 1); i < width * height; ++i) {
		obstacles.emplace(std::make_pair(i, "-"));
	}
	for (int i = width; i <= width * (height -1); i += width) {
		int exit = i + width - 2;
		obstacles.emplace(std::make_pair(i, std::to_string(exit)));
	}
	for (int i = width-1; i <= (width-1) * (height); i += width) {
		int exit = i - (width - 2);
		obstacles.emplace(std::make_pair(i, std::to_string(exit)));
	}
	for (int i = width / 2, j = i; i < 2 * j * height - j; i += width) {
		obstacles.emplace(std::make_pair(i, "|"));
	}
	obstacles.emplace(std::make_pair(189, "794"));

}


//for (int i = width; i <= width * (height - 2); i += width) {
//	obstacles.emplace(std::make_pair(i, '|'));
//}
//for (int i = 2 * width - 1; i <= width * (height - 1); i += width) {
//	obstacles.emplace(std::make_pair(i, '|'));
//}
//for (int i = 0; i < width; ++i) {
//	obstacles.emplace(std::make_pair(i, '_'));
//}
//for (int i = width * (height - 1); i < width * height; ++i) {
//	obstacles.emplace(std::make_pair(i, '-'));
//}