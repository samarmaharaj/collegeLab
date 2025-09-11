#include <windows.h>
#include <iostream>
#include <atomic>

std::atomic<bool> lock_flag(false);  // Atomic flag for busy waiting

// Spinlock (Busy Waiting) implementation
void acquire_lock() {
    while (lock_flag.exchange(true, std::memory_order_acquire)) {
        // Busy-wait until the lock is released
        while (lock_flag.load(std::memory_order_relaxed)) {
            SwitchToThread();  // Yield execution to another thread (Windows API)
        }
    }
}

void release_lock() {
    lock_flag.store(false, std::memory_order_release);  // Release the lock
}

// Shared resource function
void critical_section(int threadID) {
    acquire_lock();  // Lock before entering critical section

    // Critical section: Only one thread executes this at a time
    std::cout << "Thread " << threadID << " is accessing the shared resource.\n";
    Sleep(1000);  // Simulate work inside critical section
    std::cout << "Thread " << threadID << " is leaving the shared resource.\n";

    release_lock();  // Unlock after finishing
}

// Thread function
DWORD WINAPI ThreadFunction(LPVOID param) {
    int threadID = *(int*)param;
    critical_section(threadID);
    return 0;
}

int main() {
    const int NUM_THREADS = 5;
    HANDLE threads[NUM_THREADS];
    int threadIDs[NUM_THREADS];

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIDs[i] = i + 1;
        threads[i] = CreateThread(NULL, 0, ThreadFunction, &threadIDs[i], 0, NULL);
        if (threads[i] == NULL) {
            std::cerr << "Failed to create thread " << i + 1 << std::endl;
            return 1;
        }
    }

    // Wait for all threads to finish execution
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    return 0;
}
