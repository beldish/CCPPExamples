#include <iostream>
#include <thread>
#include <map>
#include <atomic>
#include <vector>

// static std::atomic<bool> stop(false);

void RefreshForecast(std::map<std::string, int> &forecast, std::atomic<bool> &stop)
{
    while(!stop.load())
    {
    for( auto& item : forecast )
        {
            item.second++;
            std::cout << item.first << ": " << item.second << std::endl;
        }
        std::cout << "---------------" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Exiting refresh thread" << std::endl;

}

int main(int argc, char *argv[]) 
{
    std::map<std::string, int> forecastMap = {
        {"Tbilisi", 30},
        {"Erevan", 18},
        {"Bacu", 31}    
    };
    static std::vector<std::atomic<bool>> stop(5);
    stop[0].store(false);

    [](){}();

    std::thread w1(RefreshForecast, std::ref(forecastMap), std::ref(stop[0]));
    std::thread w2(RefreshForecast, std::ref(forecastMap), std::ref(stop[0]));
    std::cin.get();

    stop[0].store(true);
    w1.join();
    w2.join();
    std::cout << "Exiting main" << std::endl;

    return 0;
}


