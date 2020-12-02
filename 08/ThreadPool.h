#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>

class ThreadPool
{
    std::vector<std::thread> my_threads;
    std::queue<std::function<void()>> tasks;
    std::mutex get_from_queue;
    std::condition_variable cond_for_notification;
    std::atomic<bool> work_cond = false;

public:
    explicit ThreadPool(size_t poolSize);
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
    ~ThreadPool();
};

#include "ThreadPool.tpp"