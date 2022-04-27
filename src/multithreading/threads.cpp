#include <chrono>
#include <iostream>
#include <thread>

void func() { std::cout << "Simple thread function\n"; }

void calcNthFibonacci(uint n, uint &result) {
    if (n == 0) {
        result = 0;
    } else if (n == 1) {
        result = 1;
    } else {
        uint sum1 = 0;
        uint sum2 = 1;
        for (uint i = 1; i < n; i++) {
            uint temp = sum2;
            sum2 += sum1;
            sum1 = temp;
        }
        result = sum2;
    }
}

class FunctionObject {
  public:
    void operator()() {
        std::cout << "FunctionObject invoked " << std::this_thread::get_id()
                  << '\n';
    }
};

class ScopedThread {
  public:
    explicit ScopedThread(std::thread t) : m_T(std::move(t)) {
        if (!m_T.joinable()) {
            throw std::logic_error("No thread");
        }
    }
    ~ScopedThread() { m_T.join(); }
    ScopedThread(ScopedThread const &) = delete;
    ScopedThread &operator=(ScopedThread const &) = delete;

  private:
    std::thread m_T;
};

int main() {
    // Very simple thread
    std::thread simpleThread(func);
    simpleThread.join();

    // Simple thread using function object
    FunctionObject f;
    std::thread functionObjectThread(f);
    functionObjectThread.join();

    // Thread taking arguments
    uint result;
    std::thread argsThread(calcNthFibonacci, 0, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';

    // Reusing thread object
    argsThread = std::thread(calcNthFibonacci, 1, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';
    argsThread = std::thread(calcNthFibonacci, 2, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';
    argsThread = std::thread(calcNthFibonacci, 3, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';
    argsThread = std::thread(calcNthFibonacci, 4, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';
    argsThread = std::thread(calcNthFibonacci, 5, std::ref(result));
    argsThread.join();
    std::cout << "Fibonacci result: " << result << '\n';

    // ScopedThread using RAII to join thread
    // Note the use of brackets otherwise this gets parsed as a
    // function declaration.
    ScopedThread st{std::thread(func)};
}
