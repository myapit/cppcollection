#include <string>
#include <iostream>
#include <iomanip>
 
unsigned to_unsigned(char ch)
{
	return static_cast<unsigned>(static_cast<unsigned char>(ch));
}
 
int main()
{
	std::cout << "Enter a string: ";
 
	std::string line;
	std::getline(std::cin, line);
 
	for (std::size_t pos = 0; pos < line.size(); ++pos)
	{
		std::cout << std::setfill(' ');
		std::cout << std::setw(2) << line[pos];
 
		unsigned ascii = to_unsigned(line[pos]);
 
		std::cout << " = " << std::setw(3) << std::dec << ascii;
		std::cout << " = 0x" << std::setw(2) << std::hex << std::setfill('0') << ascii;
		std::cout << '\n';
	}
}