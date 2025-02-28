#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <condition_variable>

constexpr int no_of_philosophers = 5;

enum class State {
    THINKING = 0,
    HUNGRY = 1,
    EATING = 2,
};

inline size_t left(size_t i) {
    return (i + no_of_philosophers - 1) % no_of_philosophers;
}

inline size_t right(size_t i) { return (i + 1) % no_of_philosophers; }

State state[no_of_philosophers];
std::mutex output_mtx;  
std::mutex forks_mtx[no_of_philosophers];
std::condition_variable cv[no_of_philosophers];

const std::array<std::string, no_of_philosophers> philosopher_names = {
    "Aristotle", "Plato", "Descartes", "Kant", "Nietzsche"
};

void test(size_t i) {
    if (state[i] == State::HUNGRY && state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING) {
        state[i] = State::EATING;
        cv[i].notify_one();  
    }
}

void think(size_t i) {
    {
        std::lock_guard<std::mutex> lk(output_mtx);
        std::cout << philosopher_names[i] << " is thinking" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  
}

void take_forks(size_t i) {
    {
        state[i] = State::HUNGRY;
        {
            std::lock_guard<std::mutex> lk(output_mtx);
            std::cout << philosopher_names[i] << " is hungry" << std::endl;
        }
        test(i); 
    }
    std::unique_lock<std::mutex> lock(forks_mtx[i]);
    cv[i].wait(lock, [i]() { return state[i] == State::EATING; });  
}

void eat(size_t i) {
    {
        std::lock_guard<std::mutex> lk(output_mtx);
        std::cout << philosopher_names[i] << " is eating." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2)); 
}

void put_forks(size_t i) {
    state[i] = State::THINKING;
    test(left(i));  
    test(right(i)); 
}

void philosopher(size_t i, bool& stopFlag) {
    while (!stopFlag) {
        think(i);      
        take_forks(i);   
        eat(i);          
        put_forks(i);   
    }
}

int main() {
    std::cout << "Dinner Started!" << std::endl;

    bool stopFlag = false;

    std::thread t0([&]() { philosopher(0, stopFlag); });
    std::thread t1([&]() { philosopher(1, stopFlag); });
    std::thread t2([&]() { philosopher(2, stopFlag); });
    std::thread t3([&]() { philosopher(3, stopFlag); });
    std::thread t4([&]() { philosopher(4, stopFlag); });

    std::this_thread::sleep_for(std::chrono::seconds(5)); 

    stopFlag = true;  

    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Dinner Done!" << std::endl;
    return 0;
}
