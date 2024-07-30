#include <iostream>
#include <pthread.h>

// Abstract base class that will act as a Singleton
template <class T>
class Singleton {
public:
    // Delete copy constructor and assignment operator to prevent copies of the singleton instance
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Method to get the singleton instance
    static T* getInstance() {
        pthread_mutex_lock(&mutex_);
        if (instance_ == nullptr) {
            instance_ = new T();
            std::cout << "Instance created by thread: " << pthread_self() << std::endl;
        }
        pthread_mutex_unlock(&mutex_);
        return instance_;
    }

    virtual ~Singleton() {}

    virtual void doSomething() = 0;

protected:
    Singleton() {}

private:
    static T* instance_;
    static pthread_mutex_t mutex_;
};

// Initialize the static members
template <class T> T* Singleton<T>::instance_ = nullptr;
template <class T> pthread_mutex_t Singleton<T>::mutex_ = PTHREAD_MUTEX_INITIALIZER;

// Example of derived class
class SingletonDerived : public Singleton<SingletonDerived> {
    friend class Singleton<SingletonDerived>;
    
private:
    // Private constructor to prevent direct instantiation
    SingletonDerived() {
        std::cout << "SingletonDerived instance created!" << std::endl;
    }

public:
    void doSomething() override {
        std::cout << "Doing something with SingletonDerived instance by thread: " << pthread_self() << std::endl;
    }
};

// Thread function to demonstrate concurrent access to Singleton
void* threadFunction(void*) {
    SingletonDerived* instance = SingletonDerived::getInstance();
    instance->doSomething();
    return nullptr;
}

int main() {
    const int NUM_THREADS = 2;
    pthread_t threads[NUM_THREADS];

    std::cout <<"Create two threads that will access the singleton instance"<< std::endl;
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, threadFunction, nullptr);
    }

    // Wait for both threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}
