#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>
#include "Concurrency.h"

int sum = 0;
// TODO: Task1-1 define a lock of type `std::mutex` here
std::mutex shared_mutex;

void increment() {
    // TODO: Task1-1 increment the variable `sum` by 1
    // You need to think about how to guarantee the atomicity of `sum` self-incrementing 1
    std::lock_guard<std::mutex> lock(shared_mutex);
    ++sum;
}

std::atomic<int> atomic_sum(0);

void init_sum(int value) {
    // TODO: Task1-2 set the value of `atomic_sum` atomically
    // The purpose of defining functions in this way is for teaching purposes
    atomic_sum.store(value, std::memory_order_relaxed);
}

void atomic_increment(int v) {
    // TODO: Task1-2 increment the variable `sum` by v
    atomic_sum.fetch_add(v, std::memory_order_relaxed);
}

int open_brackets = 0;   // Count of opening brackets
int close_brackets = 0;  // Count of closing brackets

std::mutex bracket_mtx;      // 保护共享资源的互斥锁
std::condition_variable cv;  // 条件变量
std::string brackets;        // 存储括号序列

// TODO: Task2 Define some global variable and locks for task2.
// All tests are independent, so you don't need to think about the initialization of these global variables

void produce(int k) {
    // TODO: Task2 Atomically put an opening bracket '(' at the end of 'brackets' at a time.
    std::unique_lock<std::mutex> lock(bracket_mtx);
    // 等待直到当前嵌套深度小于允许的最大值
    cv.wait(lock, [k] { return open_brackets - close_brackets < k; });
    // 添加 '(' 并更新状态
    brackets.push_back('(');
    ++open_brackets;
    cv.notify_all();  // 通知消费者线程
}

void consume([[maybe_unused]] int k) {
    // TODO: Task2 Atomically put an opening bracket ')' at the end of 'brackets' at a time.
    std::unique_lock<std::mutex> lock(bracket_mtx);
    // 等待直到存在未匹配的 '('
    cv.wait(lock, [] { return open_brackets > close_brackets; });
    // 添加 ')' 并更新状态
    brackets.push_back(')');
    ++close_brackets;
    cv.notify_all();  // 通知生产者线程
}

// === The following functions will only be used in test cases ===

void slow_increment(int times) {
    for (int i = 0; i < times; ++i) {
        increment();
    }
}

void quick_increment(int times, int v) {
    for (int i = 0; i < times; ++i) {
        atomic_increment(v);
    }
}

void producer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        produce(k);
    }
}

void consumer_thread(int times, int k) {
    for (int i = 0; i < times; ++i) {
        consume(k);
    }
}