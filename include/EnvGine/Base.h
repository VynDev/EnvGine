#pragma once

class Engine;
class Environment;

class Base {

    public:

    Base(Engine *engine);

    Engine &GetEngine();
    Engine *GetEnginePointer();

    private:

    Engine *engine = nullptr;
};