#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

class Stopwatch {
public:
    Stopwatch() : running(false) {}

    void start() {
        if (!running) {
            running = true;
            stopwatch_thread = std::thread(&Stopwatch::run, this);
        }
    }

    void stop() {
        if (running) {
            running = false;
            if (stopwatch_thread.joinable()) {
                stopwatch_thread.join();
            }
        }
    }

    void reset() {
        std::lock_guard<std::mutex> lock(mutex);
        elapsed_time = std::chrono::seconds(0);
    }

    double elapsed_seconds() {
        std::lock_guard<std::mutex> lock(mutex);
        return std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count();
    }

    ~Stopwatch() {
        stop();
    }

private:
    std::atomic<bool> running;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::duration<double> elapsed_time;
    std::mutex mutex;
    std::thread stopwatch_thread;

    void run() {
        start_time = std::chrono::high_resolution_clock::now();
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for a short period to reduce CPU usage
            std::lock_guard<std::mutex> lock(mutex);
            elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
        }
    }
};