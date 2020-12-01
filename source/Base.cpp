#include "Base.h"
#include "Engine.h"

Base::Base(Engine *engine) {
    this->engine = engine;
}

Engine &Base::GetEngine() {
    return *engine;
}

Engine *Base::GetEnginePointer() {
    return engine;
}