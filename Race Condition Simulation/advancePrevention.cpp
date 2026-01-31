#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include<vector>

using namespace std;

mutex mt;
condition_variable cv;
bool inUse = false;
int counter = 0;

int task(int id){
    unique_lock<mutex> lock(mt);
    cv.wait(lock, []{return !inUse;});
    inUse = true;
    counter++;
    cout<<"Thread: "<<id<<" counter "<<counter<<endl;
    inUse = false;
    lock.unlock();
    cv.notify_one();
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 10; i++) {
        threads.emplace_back(task, i);
    }

    for (auto &t : threads) {
        t.join();
    }
return 0;
}