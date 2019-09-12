#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    std::string default_console = "\033[D";
    for (int i = 30; i <= 37; i++)
    {
        std::string color = "\033[0;36m";

        std::cout<<color<<"test "<<i<<std::endl;

        color = "\033[137m";

        std::cout<<color<<"test "<<i<<" bold"<<std::endl;
        std::cout<<default_console<<std::endl;

    }

    std::cout << "Done" << std::endl;

    return 0;
}
