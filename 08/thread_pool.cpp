#include "thread_pool.h"

using namespace std;

ThreadPool::ThreadPool(size_t poolSize = 0) {
    for (size_t i = 0; i < poolSize; i++) {
        thread_vec.emplace_back([this](){
            while (isalive) {
                unique_lock<mutex> q_lock(q_mutex);
                if (!func_queue.empty()) {
                    auto func = func_queue.front();
                    func_queue.pop();
                    q_lock.unlock();
                    func();
                } else {
                    isready.wait(q_lock, [this](){ return !isalive || !func_queue.empty(); };
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    isalive = false;
    isready.notify_all();
    for (size_t i = 0; i < thread_vec.size(); i++) {
        thread_vec[i].join();
    }
}

