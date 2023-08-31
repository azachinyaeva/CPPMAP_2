#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class MySpin
{

private:

    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:

    void lock()
    {
        while (flag.test_and_set())
        {

        }
    }

    void unlock()
    {
        flag.clear();
    }

};

MySpin s;
std::mutex m;

void progressBar(int num, int& progress, std::chrono::steady_clock::time_point start[]) {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
       std::lock_guard<std::mutex> lg(m);
        std::cout << num + 1 << " \t" << std::this_thread::get_id() << " [";
    for (int i = 0; i < 10; i++) {
        if (i <= progress) {
            std::cout << "#";
        }
        else
            std::cout << " ";
        //std::lock_guard<MySpin> lg(s);
        ++progress;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }
    std::cout << "] " << (progress) * 10 << "%" << " |\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start[num]).count() << "ms" << std::endl;
    
}

void thread(const int threads, int& progress, std::chrono::steady_clock::time_point start[]) {
   // while (progress[threads-1] < 10)
    //{
    
       for (int i = 0; i < threads; ++i) {
            
            //system("cls");
            if (progress < 10) {
                progressBar(i, std::ref(progress), start);
                ++progress;
            }
        }
    //}
}


int main() {

    const int threads = 10;

    std::vector<std::thread> th;
    std::vector<int> progress(threads, 0);

    std::chrono::steady_clock::time_point start[threads];

    for (int i = 0; i < threads; ++i) {
        start[i] = (std::chrono::steady_clock::now());
        //th.emplace_back(std::thread(progressBar, i, std::ref(progress[i]), start));
        th.emplace_back(std::thread(progressBar, i, std::ref(progress[i]), start));
    }
    std::cout << "N\t" << "Id\t" << "Progress\t" << "\tTime" << std::endl;

    for (int i = 0; i < threads; ++i) {
        th[i].join();
    }
    return 0;
}