#include "Environment.h"

template<class T>
T* Environment::CreateEntity() {
    T *entity = new T(this);
    entities.push_back(entity);
    return entity;
}