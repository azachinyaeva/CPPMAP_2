#include <iostream>
#include <windows.h>
#include <locale.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "consoleParameter.h"

using namespace std::chrono_literals;

std::mutex m;

void bar(int width, int threads, int index) {

    m.lock();
    consoleParameter::setPosition(1, index);
    std::cout << index;
    consoleParameter::setPosition(5, index);
    std::cout << std::this_thread::get_id();
    m.unlock();

    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 15; j < width + 15; ++j) {
        std::this_thread::sleep_for(200ms);
        m.lock();
        consoleParameter::setPosition(j, index);
        std::cout << "#";
        m.unlock();
    }

    m.lock();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    consoleParameter::setPosition(40, index);
    std::cout << time.count();
    m.unlock();
}

void create_threads(int threads, int width) {
    std::vector<std::thread> th;
    std::cout << "N\t" << "Id\t" << "Progress\t" << "\tTime" << std::endl;
    for (int i = 0; i < threads; ++i)
    {
        std::thread thread(bar, width, threads, i + 1);
        th.push_back(move(thread));
    }

    for (int i = 0; i < threads; ++i)
    {
        th[i].join();
    }
}

int main()
{

    const int threads = 10;
    const int width = 10;
    create_threads(threads, width);
}

