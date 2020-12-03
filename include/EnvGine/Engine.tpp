#include "Engine.h"

template<class T>
T* Engine::CreateEnvironment() {
    T *environment = new T(this);
    environmentsMutex.lock();
    environments.push_back(environment);
    environmentsMutex.unlock();
    return environment;
}

template<class T>
Monitor *Engine::SelectMonitor() {
    monitor = std::make_unique<T>(this);
    return monitor.get();
}