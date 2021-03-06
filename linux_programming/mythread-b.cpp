#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
vector<thread> spawn()
{
 vector<thread> threads;
     for(int index=0; index<16;index++)
     {
        threads.emplace_back([index]
            {
              this_thread::sleep_for(chrono::milliseconds(10*index));
              cout << "Hai .. this is thread. " << index << endl;
           });
    }
    return threads;
}

int main()
{

    vector<thread> threads = spawn();
    cout << "This is main.\n";

   //C++11 
   for (auto & t: threads)
       t.join();
   
    return 0;
}
