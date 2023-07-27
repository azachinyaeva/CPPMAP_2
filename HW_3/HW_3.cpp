#include <iostream>
#include <thread>
#include <mutex>

class Data {
public:
    Data (int value) : data (value) {}

    int get_data()
    {
        return data;
    }

    void set_data(int value)
    {
        data = value;
    }

    std::mutex& get_mutex()
    {
        return mt;
    }

private:
    int data;
    std::mutex mt;

};

void print(Data& d1, Data& d2)
{
    std::cout << "d1 = " << d1.get_data() << '\n';
    std::cout << "d2 = " << d2.get_data() << '\n';
}

void swap_lock (Data& d1, Data& d2)
{
    d1.get_mutex().lock();
    d2.get_mutex().lock();
    std::lock_guard lock1(d1.get_mutex(), std::adopt_lock);
    std::lock_guard lock2(d2.get_mutex(), std::adopt_lock);

    std::cout << "Lock: \n";
    print(d1, d2);
    int temp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(temp);
    print(d1, d2);
}

void swap_scoped_lock (Data& d1, Data& d2)
{
    std::mutex& mt1 = d1.get_mutex();
    std::mutex& mt2 = d2.get_mutex();
    std::scoped_lock l (mt1, mt2);

    std::cout << "Scoped_lock: \n";
    print(d1, d2);
    int temp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(temp);
    print(d1, d2);
}

void swap_unique_lock (Data& d1, Data& d2)
{
    std::unique_lock<std::mutex> lock_1(d1.get_mutex(), std::defer_lock);
    std::unique_lock<std::mutex> lock_2(d2.get_mutex(), std::defer_lock);
    std::lock(lock_1, lock_2);

    std::cout << "Unique_lock: \n";
    print(d1, d2);
    int temp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(temp);
    print(d1, d2);

}


int main()
{

    Data d1(1);
    Data d2(9);

    std::thread t1(swap_lock, std::ref(d1), std::ref(d2));
    std::thread t2(swap_scoped_lock, std::ref(d1), std::ref(d2));
    std::thread t3(swap_unique_lock, std::ref(d1), std::ref(d2));

    t1.join();
    t2.join();
    t3.join();
    
}
