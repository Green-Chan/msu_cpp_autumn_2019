/*
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
*/
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"
#include "mingw.future.h"

#include <vector>
#include <queue>
#include <functional>
#include <memory>

class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
    ThreadPool(ThreadPool &&adr) = delete;
    ThreadPool(const ThreadPool &adr) = delete;

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto promise = std::make_shared< std::promise<decltype(func(args...))> >();
        std::future<decltype(func(args...))> future = promise->get_future();

        auto task = [this](std::shared_ptr< std::promise<decltype(func(args...))> > p,
                       Func func, Args... args) {
            foo(p, func, args...);
        };
        {
            std::lock_guard<std::mutex> guard(q_mutex);
            func_queue.push(std::bind(task, promise, func, args...));
        }
        isready.notify_one();
        return future;
    }
private:
    std::vector<std::thread> thread_vec;
    std::queue< std::function<void()> > func_queue;
    bool isalive = true;
    std::condition_variable isready;
    std::mutex q_mutex;

    template <class Func, class... Args>
    void foo(std::shared_ptr< std::promise<void> > p,
                       Func func, Args... args) {
        func(args...);
        p->set_value();
    }
    template <class PromPtr, class Func, class... Args>
    void foo (PromPtr p, Func func, Args... args) {
        p->set_value(func(args...));
    };
};
