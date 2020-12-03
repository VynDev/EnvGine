#pragma once

class Engine;

class Monitor {
    public:
    
    Monitor(Engine *engine) : engine(engine) {}

    Engine *GetEngine() {return engine;}

    virtual void Tick(float delta) {};

    private:

    Engine *engine = nullptr;
};