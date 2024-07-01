#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

using Task = std::function<void()>;

class ThreadPool {
   public:
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency());

    ~ThreadPool();

    // Enqueue task for execution by the thread pool
    void enqueue(Task task);

   private:
    // Vector to store worker threads
    std::vector<std::thread> threads_;

    // Queue of tasks
    std::queue<Task> tasks_;

    // Mutex to synchronize access to shared data
    std::mutex queue_mutex_;

    // Condition variable to signal changes in the state of the tasks queue
    std::condition_variable cv_;

    // Flag to indicate whether the thread pool should stop or not
    bool stop_ = false;
};