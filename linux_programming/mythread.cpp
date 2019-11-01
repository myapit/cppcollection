#include <iostream>
#include <thread>
#include <time.h>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
 
map<string, string> g_pages;
mutex g_pages_mutex;
 
void save_page(const std::string &url)
{
    // simulate a long page fetch
     std::this_thread::sleep_for(std::chrono::seconds(2));
         std::string result = "fake content";
          
              std::lock_guard<std::mutex> guard(g_pages_mutex);
                  g_pages[url] = result;
 }

void sleepcp(int milliseconds);

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

void threadFunc(int i)
{
	for(int i=0; i<10; i++)
	{
		cout << " hai.. iam thread : "<< i << endl;
        	sleepcp(5000);
        	cout << " hai... "<< endl;
	}
}

void threadTwo()
{
  for (int i=0;i<10;i++)
  {
    sleepcp(1000); cout << "#";
  }
}

int main(void)
{
	thread t1(threadFunc, 1);
	thread t2(threadTwo);

	t1.join();
	t2.join();
    
   std::thread t1x(save_page, "http://foo");
    std::thread t2x(save_page, "http://bar");
    t1x.join();
    t2x.join();
     for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}
