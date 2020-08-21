#include <iostream>
#include <thread>

#define ITERATION_CYCLE 50

// 1. function pointer
// 2. function object
// 3. Lambda functions

void displayFirstThread()
{
    for (size_t i = 0; i < ITERATION_CYCLE; i++)
    {
        std::cout << "I am a first worker Thread!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void displaySecontThread()
{
    for (size_t i = 0; i < ITERATION_CYCLE; i++)
    {
        std::cout << "I am a second worker Thread!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 2. Function Object 
class DisplayThread
{
public:
    void operator()()
    {
        for (size_t i = 0; i < ITERATION_CYCLE; i++)
        {
            std::cout << "I am a object Thread!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};


int main()
{
    // 1. function pointer
    std::thread firstWorker(displayFirstThread);
    std::thread secondWorker(displaySecontThread);

    // 2. Function Object 
    std::thread objectThread((DisplayThread()));

    // 3. Lambda functions
    std::thread lambdaThread([] {
        for (size_t i = 0; i < ITERATION_CYCLE; i++)
        {
            std::cout << "I am a lambda Thread!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
    });

    if (firstWorker.joinable())
    {
        std::cout << "First thread is ready to join" << std::endl;
        firstWorker.join();
    }
    
    if (secondWorker.joinable())
    {
        std::cout << "Second thread is ready to join" << std::endl;
        secondWorker.join();
    }

    if (objectThread.joinable())
    {
        std::cout << "Object thread is ready to join" << std::endl;
        objectThread.join();
    }
    
    if (lambdaThread.joinable())
    {
        std::cout << "Lambda thread is ready to join" << std::endl;
        lambdaThread.join();
    }

    for (size_t i = 0; i < ITERATION_CYCLE; i++)
    {
        std::cout << "I am a main thread" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    // firstWorker.join();
    // secondWorker.join();
    return 0;
}