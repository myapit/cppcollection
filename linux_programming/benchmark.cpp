#include <iostream>
#include <memory>
#include <chrono>

class Timer
{
    private:
        std::chrono::time_point <std::chrono::high_resolution_clock> m_StartTimePoint;

    public:
        Timer()
        {
            m_StartTimePoint = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            Stop();
        }

        void Stop()
        {
            auto endTimePoint = std::chrono::high_resolution_clock::now();
            
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count(); 

            auto duration = end - start;
            double ms = duration * 0.001;

            std::cout << duration <<  "us (" << ms << " ms)\n";
        }

};

int main()
{
    int val = 0;
    {
        Timer timer;
        for(int i=0;i<1000000;++i)
            val +=2;
    }

    struct Vector2
    {
        float x,y;  
    };
    {
        std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
        Timer T1;
        for(int z=0; z< sharedPtrs.size(); ++z)
            sharedPtrs[z] = std::make_shared<Vector2>();
    }

    {
        std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
        Timer T1;
        for(int z=0; z< sharedPtrs.size(); ++z)
            sharedPtrs[z] = std::shared_ptr<Vector2>(new Vector2());
    }

    {
        std::array<std::unique_ptr<Vector2>, 1000> sharedPtrs;
        Timer T1;
        for(int z=0; z< sharedPtrs.size(); ++z)
            sharedPtrs[z] = std::make_unique<Vector2>();
    }
    
}

