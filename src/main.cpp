#include <iostream>
#include <thread>
#include <string>

#define ITERATION_CYCLE 10

void displayThreadData(int num, std::string message)
{
    std::cout << "Thread number: " << num << std::endl;
    std::cout << message << std::endl;
}

// Napraviti funkciju koja prima referencu na broj, te taj isti broj uvećavati 1000x for petlja <1000 num++
// Ispisati broj u svakoj iteraciji for petlje skupa sa ID-em od threada 
// Napraviti 2 threada koja primaju istu referencu!

void threadMultipiler(int& number) 
{
    for (int i = 0; i < 100000; i++)
    {
        std::cout << "Number value is: " << number << " and ID: " << std::this_thread::get_id() << std::endl;
        number++;
    }
}

// std::thread threadObject(function, params);
int main()
{   
    // std::thread threadWithParams(displayThreadData, 10, "Hello thread!");

    // threadWithParams.join();

    int number = 0; 
    // auto threadFirst = std::thread(threadMultipiler, std::ref(number));
    // auto threadSecond = std::thread(threadMultipiler, std::ref(number));

    std::thread threadFirst(threadMultipiler, std::ref(number));
    std::thread threadSecond(threadMultipiler, std::ref(number));

    threadFirst.join();
    threadSecond.join();

    std::cout  << "Final result: " << number << std::endl;

    std::cin.get();
}