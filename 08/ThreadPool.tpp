ThreadPool::ThreadPool(size_t poolSize) {
    for (size_t i = 0; i < poolSize; i++) {
        my_threads.emplace_back([this]() {
            while (!work_cond) {
                std::unique_lock < std::mutex > lock(get_from_queue);
                cond_for_notification.wait(lock, [this]() {
                    bool res = !tasks.empty() || work_cond;
                    return res;
                });
                if (!tasks.empty()) {
                    auto next_task = std::move(tasks.front());
                    tasks.pop();
                    next_task();
                } else {
                    return;
                }
            }
        });
    }
}

template < class Func, class...Args >
    auto ThreadPool::exec(Func func, Args...args) -> std::future < decltype(func(args...)) > {
        auto one_more_task = std::make_shared < std::packaged_task < decltype(func(args...))() >>
        ([func, args...]() {
            return func(args...);
        });

        std::future < decltype(func(args...)) > result = one_more_task -> get_future(); {
            std::lock_guard < std::mutex > lock(get_from_queue);
            tasks.emplace([one_more_task]() {
                ( * one_more_task)();
            });
        }
        cond_for_notification.notify_one();
        return result;
    }

ThreadPool::~ThreadPool() {
    work_cond = true;
    cond_for_notification.notify_all();
    for (auto & i: my_threads) {
        i.join();
    }
}