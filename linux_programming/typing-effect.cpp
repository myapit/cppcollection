/*
 * Example of slow printing (like typing)
 * https://en.cppreference.com/w/cpp/chrono/duration
 * https://en.cppreference.com/w/cpp/thread/sleep_for
 *
 */

#include <iostream>
#include <string>
#include <thread> //threading support libraray
#include <chrono> //date tiem utilities

void typing(const std::string& mesej , unsigned int milisaat)
{
    for (const char c: mesej)
    {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(milisaat));
    }
}

int main()
{
     std::string me = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\nLorem Ipsum has been the industry's standard dummy text ever since the 1500s, \nwhen an unknown printer took a galley of type and scrambled it to make a type specimen book";
     typing(me,25);

     std::cout << "." << std::endl;
    return 0;
}
