#include "Engine.h"

template<class T>
T* Engine::CreateEnvironment() {
    T *environment = new T(this);
    environmentsMutex.lock();
    environments.push_back(environment);
    environmentsMutex.unlock();
    return environment;
}