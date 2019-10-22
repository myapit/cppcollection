/*
 * Structure od Mutex 
 */
#include <mutex>

int main() 
{
    mutex m;
    m.lock();
    /* Doing thread-safe stuff */
    m.unlock();

    return 0;
}

