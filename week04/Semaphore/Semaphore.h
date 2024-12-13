#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// Task 3
#include <condition_variable>
#include <mutex>
class Semaphore {
    // TODO: Task3
   public:
    void P() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return value > 0; });
        --value;
    }
    void V() {
        std::unique_lock<std::mutex> lock(mtx);
        ++value;
        cv.notify_one();
    }
    Semaphore(int value) {
        this->value = value;
    }

   private:
    int value;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif  // SEMAPHORE_H