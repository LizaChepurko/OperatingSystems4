#include <iostream>
#include <pthread.h>
#include <unistd.h>

// Guard class to automatically manage mutex locking and unlocking
class MutexGuard {
public:
    // Constructor that locks the mutex
    MutexGuard(pthread_mutex_t &mutex) : mutex_(mutex) {
        pthread_mutex_lock(&mutex_);
    }

    // Destructor that unlocks the mutex
    ~MutexGuard() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t &mutex_; 
};

void *threadFunction(void *arg) {
    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;

    {
        MutexGuard lock(*mutex); // Automatically locks the mutex

        std::cout << "Thread " << pthread_self() << " is in the locked section." << std::endl;
        sleep(1);
    } // Automatically unlocks the mutex at the end of this scope

    return nullptr;
}

int main() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    pthread_mutex_t mutex;

    // Initialize the mutex
    pthread_mutex_init(&mutex, nullptr);

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, threadFunction, (void *)&mutex);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}

