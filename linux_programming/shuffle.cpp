#include <random>
#include <algorithm>
#include <string>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char ** argv)
{
 	std::vector<std::string> files(argv+1, argv+argc);

	std::random_device rd;
	std::mt19937 rnd(rd());

	std::shuffle(files.begin(), files.end(), rnd);

	for(const auto& s: files)
		std::cout << s <<std::endl;
}

/* 
 * Ref: yt=>5Da6ZyQJjE0 
 *
 * g++ shuffle.cpp  -Wall -Wextra -O --std=c++14 -o shuffle
 *
 * */
