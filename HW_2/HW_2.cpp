#include <iostream>
#include <windows.h>
#include <mutex>
#include <thread>
#include <vector>
#include <iomanip>

std::mutex mt;

void progressBar(int progress, int duration) {
    auto start = std::chrono::high_resolution_clock::now();
    const int barWidth = 20;

    std::lock_guard<std::mutex> guard(mt);
    std::cout << progress + 1 << "\t";
    std::cout << std::this_thread::get_id() << "\t\t";
    std::cout << "[";

    for (int i = 0; i < barWidth; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        float progressRatio = static_cast<float>(i + 1) / duration;
        int barProgress = static_cast<int>(progressRatio * barWidth);

        std::cout << "=";
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "] \t";
    std::cout.flush();

    auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "\t" << time.count() << "s" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int threads = 10;
    const int duration = 100;

    std::cout << "N\t" << "Id\t\t" << "Progress\t\t" << "\tTime" << std::endl;

    std::vector<std::thread> th;

    for (int i = 0; i < threads; ++i) {
        th.push_back(std::thread(progressBar, i, duration));
    }

    for (auto& t : th) {
        t.join();
    }

    return 0;
}