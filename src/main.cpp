#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>

#define THREAD_COUNT 5
#define COUNT 100

class Wallet
{
public:
    Wallet() : _ballance(0) {};
    ~Wallet() {};
    void addToBallance(int ammount)
    {
        _mutex.lock();
        for (int i = 0; i < ammount; i++)
        {
            _ballance++;
            std::cout << "Thread: " << std::this_thread::get_id() << " Current Ballance: " << _ballance << std::endl; 
        }
        _mutex.unlock();
    }

    int getBallance()
    {
        return _ballance;
    }
private:
    int _ballance;
    std::mutex _mutex;   
};

int multithreadedWallet()
{
    Wallet wallet;
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads.push_back(std::thread(&Wallet::addToBallance, &wallet, COUNT));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    return wallet.getBallance();
}

int main()
{   
    int value = 0;
    for (int i = 0; i < COUNT; i++)
    {   
        // value = multithreadedWallet();
        if ((value = multithreadedWallet()) != COUNT * THREAD_COUNT)
        {
            std::cout << "error at: " << i << " Current Ballance: " << value << std::endl;
        }
    }

    std::cout << "Final result: " << value << std::endl;
    std::cin.get();
}